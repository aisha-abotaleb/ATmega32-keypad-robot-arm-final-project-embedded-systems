#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "TIMER0_interface.h"
#include "TIMER0_private.h"
#include "TIMER0_config.h"

static void(*GlobalPtrFuncNormal)(void)=NULL;
static void(*GlobalPtrFuncCompare)(void)=NULL;

void TIMER0_voidInit(void)
{
	// Timer Mode -> WGM BITS -> Interrupt source
#if TIMER_MODE == NORMAL_MODE
	CLR_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	SET_BIT(TIMSK, 0);
#elif TIMER_MODE == PHASE_CORRECT_PWM
	CLR_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
#elif TIMER_MODE == CTC_MODE
	SET_BIT(TCCR0, 3);
	CLR_BIT(TCCR0, 6);
	SET_BIT(TIMSK, 1);
#elif TIMER_MODE == FAST_PWM
	SET_BIT(TCCR0, 3);
	SET_BIT(TCCR0, 6);
#else
#error("Wrong Timer Mode Configuration");
#endif

	// Configure PreScaler
	TCCR0 &= 0b11111000;
#if PRE_SCALER == NO_CLOCK
	TCCR0 |= 0;
#elif PRE_SCALER == NO_PRESCALER
	TCCR0 |= 1;
#elif PRE_SCALER == DIV_8
	TCCR0 |= 2;
#elif PRE_SCALER == DIV_64
	TCCR0 |= 3;
#elif PRE_SCALER == DIV_256
	TCCR0 |= 4;
#elif PRE_SCALER == DIV_1024
	TCCR0 |= 5;
#elif PRE_SCALER == EXT_FALLING
	TCCR0 |= 6;
#elif PRE_SCALER == EXT_RISING
	TCCR0 |= 7;
#else
#error("Wrong PreScaler Option");
#endif
}

void TIMER0_voidSetPreLoadTicks(u8 Copy_u8Ticks)
{
	TCNT0 = Copy_u8Ticks;
}

void TIMER0_voidSetOcrTicks(u8 Copy_u8Ticks)
{
	OCR0 = Copy_u8Ticks;
}

STD_err_e TIMER0_eSetCallBackNormal(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL)
	{
		GlobalPtrFuncNormal = Pfunc;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

STD_err_e TIMER0_eSetCallBackCompare(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL)
	{
		GlobalPtrFuncCompare = Pfunc;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

void TIMER0_voidSetCompareOutputMode(OC0_Mode_e Copy_Mode)
{
	TCCR0 &= 0b11001111; // Clear COM01 and COM00 bits
	switch(Copy_Mode)
	{
	case OC0_DISCONNECTED:
		break;
	case OC0_TOGGLE:
		SET_BIT(TCCR0, 4);
		break;
	case OC0_CLEAR:
	case OC0_NON_INV:
		SET_BIT(TCCR0, 5);
		break;
	case OC0_SET:
	case OC0_INV:
		SET_BIT(TCCR0, 4);
		SET_BIT(TCCR0, 5);
		break;
	}
}

// vector of over flow
void __vector_11(void) __attribute__((signal));
void __vector_11(void)
{
	if(GlobalPtrFuncNormal != NULL)
		GlobalPtrFuncNormal();
}

// vector of compare match
void __vector_10(void) __attribute__((signal));
void __vector_10(void)
{
	if(GlobalPtrFuncCompare != NULL)
		GlobalPtrFuncCompare();
}

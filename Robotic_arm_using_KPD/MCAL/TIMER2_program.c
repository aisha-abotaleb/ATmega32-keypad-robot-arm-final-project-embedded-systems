#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "TIMER2_interface.h"
#include "TIMER2_private.h"
#include "TIMER2_config.h"

static void(*GlobalPtrFuncNormal2)(void)=NULL;
static void(*GlobalPtrFuncCompare2)(void)=NULL;

void TIMER2_voidInit(void)
{
#if TIMER2_MODE == NORMAL_MODE
	CLR_BIT(TCCR2, 3);
	CLR_BIT(TCCR2, 6);
	SET_BIT(TIMSK, 6);
#elif TIMER2_MODE == PHASE_CORRECT_PWM
	CLR_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);
#elif TIMER2_MODE == CTC_MODE
	SET_BIT(TCCR2, 3);
	CLR_BIT(TCCR2, 6);
	SET_BIT(TIMSK, 7);
#elif TIMER2_MODE == FAST_PWM
	SET_BIT(TCCR2, 3);
	SET_BIT(TCCR2, 6);
#else
#error("Wrong Timer Mode Configuration");
#endif

	TCCR2 &= 0b11111000;
#if TIMER2_PRESCALER == NO_CLOCK
	TCCR2 |= 0;
#elif TIMER2_PRESCALER == NO_PRESCALER
	TCCR2 |= 1;
#elif TIMER2_PRESCALER == DIV_8
	TCCR2 |= 2;
#elif TIMER2_PRESCALER == DIV_32
	TCCR2 |= 3;
#elif TIMER2_PRESCALER == DIV_64
	TCCR2 |= 4;
#elif TIMER2_PRESCALER == DIV_128
	TCCR2 |= 5;
#elif TIMER2_PRESCALER == DIV_256
	TCCR2 |= 6;
#elif TIMER2_PRESCALER == DIV_1024
	TCCR2 |= 7;
#else
#error("Wrong PreScaler Option");
#endif
}

void TIMER2_voidSetPreLoadTicks(u8 Copy_u8Ticks)
{
	TCNT2 = Copy_u8Ticks;
}

void TIMER2_voidSetOcrTicks(u8 Copy_u8Ticks)
{
	OCR2 = Copy_u8Ticks;
}

STD_err_e TIMER2_eSetCallBackNormal(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL)
	{
		GlobalPtrFuncNormal2 = Pfunc;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

STD_err_e TIMER2_eSetCallBackCompare(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL)
	{
		GlobalPtrFuncCompare2 = Pfunc;
	}
	else
	{
		Local_ErrorStatus = NOK;
	}
	return Local_ErrorStatus;
}

void TIMER2_voidSetCompareOutputMode(OC2_Mode_e Copy_Mode)
{
	TCCR2 &= 0b11001111;
	switch(Copy_Mode)
	{
	case OC2_DISCONNECTED:
		break;
	case OC2_TOGGLE:
		SET_BIT(TCCR2, 4);
		break;
	case OC2_CLEAR:
	case OC2_NON_INV:
		SET_BIT(TCCR2, 5);
		break;
	case OC2_SET:
	case OC2_INV:
		SET_BIT(TCCR2, 4);
		SET_BIT(TCCR2, 5);
		break;
	}
}

void __vector_5(void) __attribute__((signal));
void __vector_5(void)
{
	if(GlobalPtrFuncNormal2 != NULL)
		GlobalPtrFuncNormal2();
}

void __vector_4(void) __attribute__((signal));
void __vector_4(void)
{
	if(GlobalPtrFuncCompare2 != NULL)
		GlobalPtrFuncCompare2();
}

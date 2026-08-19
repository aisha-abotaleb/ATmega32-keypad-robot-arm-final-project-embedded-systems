#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "TIMER1_interface.h"
#include "TIMER1_private.h"
#include "TIMER1_config.h"

static void(*GlobalPtrFuncNormal1)(void)=NULL;
static void(*GlobalPtrFuncCompareA)(void)=NULL;
static void(*GlobalPtrFuncCompareB)(void)=NULL;
static void(*GlobalPtrFuncCapture)(void)=NULL;

void TIMER1_voidInit(void)
{
#if TIMER1_MODE == MODE_NORMAL
	CLR_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PC_8BIT
	SET_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PC_9BIT
	CLR_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PC_10BIT
	SET_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_CTC_OCR1A
	CLR_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_FAST_PWM_8BIT
	SET_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_FAST_PWM_9BIT
	CLR_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_FAST_PWM_10BIT
	SET_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); CLR_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PFC_ICR1
	CLR_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PFC_OCR1A
	SET_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PC_ICR1
	CLR_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_PWM_PC_OCR1A
	SET_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); CLR_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_CTC_ICR1
	CLR_BIT(TCCR1A, 0); CLR_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_FAST_PWM_ICR1
	CLR_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#elif TIMER1_MODE == MODE_FAST_PWM_OCR1A
	SET_BIT(TCCR1A, 0); SET_BIT(TCCR1A, 1); SET_BIT(TCCR1B, 3); SET_BIT(TCCR1B, 4);
#endif

	TCCR1B &= 0b11111000;
#if TIMER1_PRESCALER == NO_CLOCK
	TCCR1B |= 0;
#elif TIMER1_PRESCALER == NO_PRESCALER
	TCCR1B |= 1;
#elif TIMER1_PRESCALER == DIV_8
	TCCR1B |= 2;
#elif TIMER1_PRESCALER == DIV_64
	TCCR1B |= 3;
#elif TIMER1_PRESCALER == DIV_256
	TCCR1B |= 4;
#elif TIMER1_PRESCALER == DIV_1024
	TCCR1B |= 5;
#elif TIMER1_PRESCALER == EXT_FALLING
	TCCR1B |= 6;
#elif TIMER1_PRESCALER == EXT_RISING
	TCCR1B |= 7;
#endif
}

void TIMER1_voidSetTimerValue(u16 Copy_u16Value)
{
	TCNT1 = Copy_u16Value;
}

u16 TIMER1_u16GetTimerValue(void)
{
	return TCNT1;
}

void TIMER1_voidSetCompareValueA(u16 Copy_u16Value)
{
	OCR1A = Copy_u16Value;
}

void TIMER1_voidSetCompareValueB(u16 Copy_u16Value)
{
	OCR1B = Copy_u16Value;
}

void TIMER1_voidSetInputCaptureValue(u16 Copy_u16Value)
{
	ICR1 = Copy_u16Value;
}

u16 TIMER1_u16GetInputCaptureValue(void)
{
	return ICR1;
}

void TIMER1_voidSetCompareOutputModeA(OC1_Mode_e Copy_Mode)
{
	TCCR1A &= 0b00111111;
	switch(Copy_Mode)
	{
	case OC1_DISCONNECTED: break;
	case OC1_TOGGLE:       SET_BIT(TCCR1A, 6); break;
	case OC1_CLEAR:
	case OC1_NON_INV:      SET_BIT(TCCR1A, 7); break;
	case OC1_SET:
	case OC1_INV:          SET_BIT(TCCR1A, 6); SET_BIT(TCCR1A, 7); break;
	}
}

void TIMER1_voidSetCompareOutputModeB(OC1_Mode_e Copy_Mode)
{
	TCCR1A &= 0b11001111;
	switch(Copy_Mode)
	{
	case OC1_DISCONNECTED: break;
	case OC1_TOGGLE:       SET_BIT(TCCR1A, 4); break;
	case OC1_CLEAR:
	case OC1_NON_INV:      SET_BIT(TCCR1A, 5); break;
	case OC1_SET:
	case OC1_INV:          SET_BIT(TCCR1A, 4); SET_BIT(TCCR1A, 5); break;
	}
}

void TIMER1_voidSetInputCaptureEdge(ICU_Edge_e Copy_Edge)
{
	if(Copy_Edge == ICU_RISING_EDGE)
	{
		SET_BIT(TCCR1B, 6);
	}
	else if(Copy_Edge == ICU_FALLING_EDGE)
	{
		CLR_BIT(TCCR1B, 6);
	}
}

STD_err_e TIMER1_eSetCallBackNormal(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL) GlobalPtrFuncNormal1 = Pfunc;
	else Local_ErrorStatus = NOK;
	return Local_ErrorStatus;
}

STD_err_e TIMER1_eSetCallBackCompareA(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL) GlobalPtrFuncCompareA = Pfunc;
	else Local_ErrorStatus = NOK;
	return Local_ErrorStatus;
}

STD_err_e TIMER1_eSetCallBackCompareB(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL) GlobalPtrFuncCompareB = Pfunc;
	else Local_ErrorStatus = NOK;
	return Local_ErrorStatus;
}

STD_err_e TIMER1_eSetCallBackCapture(void (*Pfunc)(void))
{
	STD_err_e Local_ErrorStatus = OK;
	if(Pfunc != NULL) GlobalPtrFuncCapture = Pfunc;
	else Local_ErrorStatus = NOK;
	return Local_ErrorStatus;
}

void __vector_9(void) __attribute__((signal));
void __vector_9(void)
{
	if(GlobalPtrFuncNormal1 != NULL) GlobalPtrFuncNormal1();
}

void __vector_8(void) __attribute__((signal));
void __vector_8(void)
{
	if(GlobalPtrFuncCompareB != NULL) GlobalPtrFuncCompareB();
}

void __vector_7(void) __attribute__((signal));
void __vector_7(void)
{
	if(GlobalPtrFuncCompareA != NULL) GlobalPtrFuncCompareA();
}

void __vector_6(void) __attribute__((signal));
void __vector_6(void)
{
	if(GlobalPtrFuncCapture != NULL) GlobalPtrFuncCapture();
}

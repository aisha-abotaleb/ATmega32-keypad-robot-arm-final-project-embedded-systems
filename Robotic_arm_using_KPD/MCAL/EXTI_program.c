#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "EXTI_interface.h"
#include "EXTI_private.h"

static void (*GlobalPtrFunc[3])(void)={NULL};

void EXTI_voidEnableDisable(INTNUM_e Copy_eIntNum, MODE_e Copy_eMode)
{
	switch(Copy_eIntNum)
	{
	case INT0:
		if(Copy_eMode == ENABLED) SET_BIT(GICR, GICR_INT0);
		else CLR_BIT(GICR, GICR_INT0);
		break;
	case INT1:
		if(Copy_eMode == ENABLED) SET_BIT(GICR, GICR_INT1);
		else CLR_BIT(GICR, GICR_INT1);
		break;
	case INT2:
		if(Copy_eMode == ENABLED) SET_BIT(GICR, GICR_INT2);
		else CLR_BIT(GICR, GICR_INT2);
		break;
	}
}

void EXTI_voidSetSenseCtrl(INTNUM_e Copy_eIntNum, SENSTIVITY_e Copy_eSenseCtrl)
{
	switch(Copy_eIntNum)
	{
	case INT0:
		switch(Copy_eSenseCtrl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			CLR_BIT(MCUCR, MCUCR_ISC01);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, MCUCR_ISC00);
			SET_BIT(MCUCR, MCUCR_ISC01);
			break;
		}
		break;
	case INT1:
		switch(Copy_eSenseCtrl)
		{
		case LOW_LEVEL:
			CLR_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
			break;
		case ON_CHANGE:
			SET_BIT(MCUCR, MCUCR_ISC10);
			CLR_BIT(MCUCR, MCUCR_ISC11);
			break;
		case FALLING_EDGE:
			CLR_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR, MCUCR_ISC10);
			SET_BIT(MCUCR, MCUCR_ISC11);
			break;
		}
		break;
	case INT2:
		switch(Copy_eSenseCtrl)
		{
		case FALLING_EDGE:
			CLR_BIT(MCUCSR, MCUCSR_ISC2);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCSR, MCUCSR_ISC2);
			break;
		default:
			break;
		}
		break;
	}
}

void EXTI_voidClearFlag(INTNUM_e Copy_eIntNum)
{
	switch(Copy_eIntNum)
	{
	case INT0: SET_BIT(GIFR, GIFR_INTF0); break;
	case INT1: SET_BIT(GIFR, GIFR_INTF1); break;
	case INT2: SET_BIT(GIFR, GIFR_INTF2); break;
	}
}

u8 EXTI_u8GetFlag(INTNUM_e Copy_eIntNum)
{
	u8 Local_u8Flag = 0;
	switch(Copy_eIntNum)
	{
	case INT0: Local_u8Flag = GET_BIT(GIFR, GIFR_INTF0); break;
	case INT1: Local_u8Flag = GET_BIT(GIFR, GIFR_INTF1); break;
	case INT2: Local_u8Flag = GET_BIT(GIFR, GIFR_INTF2); break;
	}
	return Local_u8Flag;
}

STD_err_e EXTI_voidSetCallBack(INTNUM_e Copy_eIntNum, void (*LocalPtrFunc)(void))
{
	STD_err_e  Local_errState = OK;
	if(LocalPtrFunc != NULL)
	{
		switch(Copy_eIntNum)
		{
		case INT0: GlobalPtrFunc[0] = LocalPtrFunc; break;
		case INT1: GlobalPtrFunc[1] = LocalPtrFunc; break;
		case INT2: GlobalPtrFunc[2] = LocalPtrFunc; break;
		}
	}
	else
	{
		Local_errState = NOK;
	}
	return Local_errState;
}

void __vector_1(void)  __attribute__((signal));
void __vector_1(void)
{
	if(GlobalPtrFunc[0] != NULL)
	{
		GlobalPtrFunc[0]();
	}
}

void __vector_2(void)  __attribute__((signal));
void __vector_2(void)
{
	if(GlobalPtrFunc[1] != NULL)
	{
		GlobalPtrFunc[1]();
	}
}

void __vector_3(void)  __attribute__((signal));
void __vector_3(void)
{
	if(GlobalPtrFunc[2] != NULL)
	{
		GlobalPtrFunc[2]();
	}
}

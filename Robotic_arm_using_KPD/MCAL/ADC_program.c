#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "ADC_interface.h"
#include "ADC_private.h"
#include "ADC_config.h"

static u16 *Global_ptr = NULL;
static void (*GlobalPtrFunc)(void) = NULL;
static u8 ADC_STATE = IDLE;

void ADC_voidInit(void)
{
	u8 Local_u8AdmuxValue = 0;
	u8 Local_u8AdcsraValue = 0;

#if ADC_VREF == ADC_VREF_AREF
	CLR_BIT(Local_u8AdmuxValue, 6);
	CLR_BIT(Local_u8AdmuxValue, 7);
#elif ADC_VREF == ADC_VREF_AVCC
	SET_BIT(Local_u8AdmuxValue, 6);
	CLR_BIT(Local_u8AdmuxValue, 7);
#elif ADC_VREF == ADC_VREF_INTERNAL
	SET_BIT(Local_u8AdmuxValue, 6);
	SET_BIT(Local_u8AdmuxValue, 7);
#endif

#if ADC_ADJUST == ADC_LEFT_ADJUST
	SET_BIT(Local_u8AdmuxValue, 5);
#elif ADC_ADJUST == ADC_RIGHT_ADJUST
	CLR_BIT(Local_u8AdmuxValue, 5);
#endif

	ADMUX = Local_u8AdmuxValue;

#if ADC_PRESCALER == ADC_PRESCALER_2
	SET_BIT(Local_u8AdcsraValue, 0);
	CLR_BIT(Local_u8AdcsraValue, 1);
	CLR_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_4
	CLR_BIT(Local_u8AdcsraValue, 0);
	SET_BIT(Local_u8AdcsraValue, 1);
	CLR_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_8
	SET_BIT(Local_u8AdcsraValue, 0);
	SET_BIT(Local_u8AdcsraValue, 1);
	CLR_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_16
	CLR_BIT(Local_u8AdcsraValue, 0);
	CLR_BIT(Local_u8AdcsraValue, 1);
	SET_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_32
	SET_BIT(Local_u8AdcsraValue, 0);
	CLR_BIT(Local_u8AdcsraValue, 1);
	SET_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_64
	CLR_BIT(Local_u8AdcsraValue, 0);
	SET_BIT(Local_u8AdcsraValue, 1);
	SET_BIT(Local_u8AdcsraValue, 2);
#elif ADC_PRESCALER == ADC_PRESCALER_128
	SET_BIT(Local_u8AdcsraValue, 0);
	SET_BIT(Local_u8AdcsraValue, 1);
	SET_BIT(Local_u8AdcsraValue, 2);
#endif

#if ADC_AUTO_TRIGGER_STATE == ADC_AUTO_TRIGGER_ENABLE
	SET_BIT(Local_u8AdcsraValue, 5);
	SFIOR &= 0x1F;
	SFIOR |= ADC_TRIGGER_SOURCE;
#elif ADC_AUTO_TRIGGER_STATE == ADC_AUTO_TRIGGER_DISABLE
	CLR_BIT(Local_u8AdcsraValue, 5);
#endif

	SET_BIT(Local_u8AdcsraValue, 7);
	ADCSRA = Local_u8AdcsraValue;
}

STD_err_e ADC_u16ConvertSynch(u8 Copy_u8Channel, u16 *Pu16Reading)
{
	STD_err_e Local_eErrState = OK;
	u16 Local_u16Counter = 0;
	
	if(Pu16Reading != NULL)
	{
		if(ADC_STATE == IDLE)
		{
			ADC_STATE = BUSY;
			ADMUX &= 0xE0;
			ADMUX |= (Copy_u8Channel & 0x1F);
			SET_BIT(ADCSRA, 6);
			
			while((!GET_BIT(ADCSRA, 4)) && (Local_u16Counter < TIME_OUT))
			{
				Local_u16Counter++;
			}
			
			if(Local_u16Counter == TIME_OUT)
			{
				Local_eErrState = TIME_OUT_ERR;
			}
			else
			{
				SET_BIT(ADCSRA, 4);
#if ADC_ADJUST == ADC_LEFT_ADJUST
				*Pu16Reading = (ADC >> 6);
#else
				*Pu16Reading = ADC;
#endif
			}
			ADC_STATE = IDLE;
		}
		else
		{
			Local_eErrState = BUSY_STATE;
		}
	}
	else
	{
		Local_eErrState = NOK;
	}
	
	return Local_eErrState;
}

STD_err_e ADC_u16ConvertASynch(u8 Copy_u8Channel, u16 *Pu16Reading, void(*PtrFunc)(void))
{
	STD_err_e Local_eErrState = OK;
	
	if(ADC_STATE == IDLE)
	{
		if((Pu16Reading != NULL) && (PtrFunc != NULL))
		{
			ADC_STATE = BUSY;
			Global_ptr = Pu16Reading;
			GlobalPtrFunc = PtrFunc;
			ADMUX &= 0xE0;
			ADMUX |= (Copy_u8Channel & 0x1F);
			SET_BIT(ADCSRA, 6);
			SET_BIT(ADCSRA, 3);
		}
		else
		{
			Local_eErrState = NOK;
		}
	}
	else
	{
		Local_eErrState = BUSY_STATE;
	}
	
	return Local_eErrState;
}

void __vector_16(void) __attribute__((signal));
void __vector_16(void)
{
#if ADC_ADJUST == ADC_LEFT_ADJUST
	*Global_ptr = (ADC >> 6);
#else
	*Global_ptr = ADC;
#endif

	if(GlobalPtrFunc != NULL)
	{
		GlobalPtrFunc();
	}
	
	CLR_BIT(ADCSRA, 3);
	ADC_STATE = IDLE;
}
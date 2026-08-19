#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "USART_interface.h"
#include "USART_private.h"
#include "USART_config.h"

void USART_voidInit(void)
{
	u8 Local_u8UCSRCValue = 0;
	u16 Local_u16UBRRValue = 0;

	SET_BIT(UCSRB, UCSRB_RXEN);
	SET_BIT(UCSRB, UCSRB_TXEN);

	SET_BIT(Local_u8UCSRCValue, UCSRC_URSEL);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ1);
	SET_BIT(Local_u8UCSRCValue, UCSRC_UCSZ0);
	UCSRC = Local_u8UCSRCValue;

	Local_u16UBRRValue = (USART_SYSTEM_CLOCK / (16 * USART_BAUD_RATE)) - 1;

	UBRRL = (u8)Local_u16UBRRValue;
	UBRRH = (u8)(Local_u16UBRRValue >> 8);
}

void USART_voidSendByte(u8 Copy_u8Data)
{
	while(GET_BIT(UCSRA, UCSRA_UDRE) == 0);
	UDR = Copy_u8Data;
}

u8 USART_u8ReceiveByte(void)
{
	while(GET_BIT(UCSRA, UCSRA_RXC) == 0);
	return UDR;
}

void USART_voidSendString(u8* Copy_pu8String)
{
	u8 Local_u8Iterator = 0;
	if(Copy_pu8String != NULL)
	{
		while(Copy_pu8String[Local_u8Iterator] != '\0')
		{
			USART_voidSendByte(Copy_pu8String[Local_u8Iterator]);
			Local_u8Iterator++;
		}
	}
}

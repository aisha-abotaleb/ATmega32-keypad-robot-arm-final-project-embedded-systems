#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_

void USART_voidInit(void);
void USART_voidSendByte(u8 Copy_u8Data);
u8 USART_u8ReceiveByte(void);
void USART_voidSendString(u8* Copy_pu8String);

#endif

#ifndef DIO_INTERFACE_H_
#define DIO_INTERFACE_H_

enum {
    DIO_PIN0 = 0,
    DIO_PIN1,
    DIO_PIN2,
    DIO_PIN3,
    DIO_PIN4,
    DIO_PIN5,
    DIO_PIN6,
    DIO_PIN7
};

enum {
    DIO_PORTA = 1,
    DIO_PORTB,
    DIO_PORTC,
    DIO_PORTD
};

enum {
    DIO_IN = 0,
    DIO_OUT = 1
};

enum {
    DIO_LOW = 0,
    DIO_HIGH = 1
};

void DIO_voidSetPortDirection(u8 Copy_u8PortNum, u8 Copy_u8PortDirection);
void DIO_voidSetPinDirection(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinDirection);

void DIO_voidSetPortValue(u8 Copy_u8PortNum, u8 Copy_u8PortValue);
void DIO_voidSetPinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum, u8 Copy_u8PinValue);

u8 DIO_u8GetPinValue(u8 Copy_u8PortNum, u8 Copy_u8PinNum);

#endif

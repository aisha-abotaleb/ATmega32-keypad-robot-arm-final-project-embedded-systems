#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"

#include "LCD_config.h"
#include "LCD_private.h"
#include "LCD_interface.h"

#include <util/delay.h>

void LCD_voidSendData(u8 Copy_u8Data)
{
	DIO_voidSetPinValue(CTRL_PORT, RS, DIO_HIGH);
	DIO_voidSetPinValue(CTRL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(DATA_PORT, Copy_u8Data);
	DIO_voidSetPinValue(CTRL_PORT, EN, DIO_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT, EN, DIO_LOW);
}

void LCD_voidSendCommand(u8 Copy_u8Command)
{
	DIO_voidSetPinValue(CTRL_PORT, RS, DIO_LOW);
	DIO_voidSetPinValue(CTRL_PORT, RW, DIO_LOW);
	DIO_voidSetPortValue(DATA_PORT, Copy_u8Command);
	DIO_voidSetPinValue(CTRL_PORT, EN, DIO_HIGH);
	_delay_ms(1);
	DIO_voidSetPinValue(CTRL_PORT, EN, DIO_LOW);
}

void LCD_voidInit(void)
{	
	DIO_voidSetPortDirection(DATA_PORT, 0xFF);
	DIO_voidSetPinDirection(CTRL_PORT, RS, DIO_OUT);
	DIO_voidSetPinDirection(CTRL_PORT, RW, DIO_OUT);
	DIO_voidSetPinDirection(CTRL_PORT, EN, DIO_OUT);

	_delay_ms(20);
	LCD_voidSendCommand(LCD_FUNCTION_SET_CMD);
	_delay_ms(5);
	LCD_voidSendCommand(LCD_FUNCTION_SET_CMD);
	_delay_us(150);
	LCD_voidSendCommand(LCD_FUNCTION_SET_CMD);
	_delay_us(40);

	LCD_voidSendCommand(LCD_DISPLAY_CTRL_CMD);
	_delay_us(40);

	LCD_voidClearDisplay();

	LCD_voidSendCommand(LCD_ENTRY_MODE_CMD);
	_delay_us(40);
}

void LCD_voidSendString(u8 *PcCopy_String)
{
	u8 Local_u8Iterator = 0;
	while(PcCopy_String[Local_u8Iterator] != '\0')
	{
		LCD_voidSendData(PcCopy_String[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}

void LCD_voidSendNumber(s32 Copy_s32Number)
{
	u8 Local_u8NumberArray[10]; 
	u8 Local_u8Iterator = 0;
	s8 Local_s8PrintIterator = 0;

	if(Copy_s32Number == 0)
	{
		LCD_voidSendData('0');
		return;
	}

	if(Copy_s32Number < 0)
	{
		LCD_voidSendData('-');
		Copy_s32Number = Copy_s32Number * -1;
	}

	while(Copy_s32Number != 0)
	{
		Local_u8NumberArray[Local_u8Iterator] = (Copy_s32Number % 10) + '0';
		Local_u8Iterator++;
		Copy_s32Number /= 10;
	}

	for(Local_s8PrintIterator = Local_u8Iterator - 1; Local_s8PrintIterator >= 0; Local_s8PrintIterator--)
	{
		LCD_voidSendData(Local_u8NumberArray[Local_s8PrintIterator]);
	}
}

void LCD_voidSetPosition(u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 Local_u8Position = 0;
	switch(Copy_u8Y)
	{
	case 0: Local_u8Position = Copy_u8X; break;
	case 1: Local_u8Position = Copy_u8X + LINE1_BASE; break;
	}
	LCD_voidSendCommand(Local_u8Position + DDRAM_MSB);
	_delay_us(40);
}

void LCD_voidClearDisplay(void)
{
	LCD_voidSendCommand(LCD_CMD_CLEAR_DISPLAY);
	_delay_ms(2);
}

void LCD_voidReturnHome(void)
{
	LCD_voidSendCommand(LCD_CMD_RETURN_HOME);
	_delay_ms(2);
}

void LCD_voidDisplayControl(u8 Copy_u8DisplayState, u8 Copy_u8CursorState, u8 Copy_u8BlinkState)
{
	u8 Local_u8Command = 0x08;

	if (Copy_u8DisplayState == LCD_ON)
	{
		Local_u8Command |= 0x04;
	}
	if (Copy_u8CursorState == LCD_ON)
	{
		Local_u8Command |= 0x02;
	}
	if (Copy_u8BlinkState == LCD_ON)
	{
		Local_u8Command |= 0x01;
	}

	LCD_voidSendCommand(Local_u8Command);
	_delay_us(40);
}

void LCD_voidShiftCursorLeft(void)
{
	LCD_voidSendCommand(LCD_CMD_SHIFT_CURSOR_LEFT);
	_delay_us(40);
}

void LCD_voidShiftCursorRight(void)
{
	LCD_voidSendCommand(LCD_CMD_SHIFT_CURSOR_RIGHT);
	_delay_us(40);
}

void LCD_voidShiftDisplayLeft(void)
{
	LCD_voidSendCommand(LCD_CMD_SHIFT_DISPLAY_LEFT);
	_delay_us(40);
}

void LCD_voidShiftDisplayRight(void)
{
	LCD_voidSendCommand(LCD_CMD_SHIFT_DISPLAY_RIGHT);
	_delay_us(40);
}

void LCD_voidSendSpecialCharecter(u8 Copy_u8BlockNum, u8 *Pu8ArrayPattern, u8 Copy_u8X, u8 Copy_u8Y)
{
	u8 Local_u8Position = Copy_u8BlockNum * 8;
	LCD_voidSendCommand(Local_u8Position + CGRAM_MSB);
	_delay_us(40);

	for(u8 i = 0; i < 8; i++)
	{
		LCD_voidSendData(Pu8ArrayPattern[i]);
		_delay_us(40);
	}

	LCD_voidSetPosition(Copy_u8X, Copy_u8Y);
	LCD_voidSendData(Copy_u8BlockNum);
}

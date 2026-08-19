#ifndef LCD_INTERFACE_H_
#define LCD_INTERFACE_H_

void LCD_voidSendData(u8 Copy_u8Data);
void LCD_voidSendCommand(u8 Copy_u8Command);

void LCD_voidInit(void);
void LCD_voidSendString(u8 *PcCopy_String);
void LCD_voidSendNumber(s32 Copy_s32Number);
void LCD_voidSetPosition(u8 Copy_u8X, u8 Copy_u8Y);
void LCD_voidClearDisplay(void);
void LCD_voidReturnHome(void);
void LCD_voidDisplayControl(u8 Copy_u8DisplayState, u8 Copy_u8CursorState, u8 Copy_u8BlinkState);
void LCD_voidShiftCursorLeft(void);
void LCD_voidShiftCursorRight(void);
void LCD_voidShiftDisplayLeft(void);
void LCD_voidShiftDisplayRight(void);
void LCD_voidSendSpecialCharecter(u8 Copy_u8BlockNum, u8 *Pu8ArrayPattern, u8 Copy_u8X, u8 Copy_u8Y);

#endif

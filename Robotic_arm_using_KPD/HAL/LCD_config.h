#ifndef LCD_CONFIG_H_
#define LCD_CONFIG_H_

#define DATA_PORT    DIO_PORTD
#define CTRL_PORT    DIO_PORTC

#define RS           DIO_PIN5
#define RW           DIO_PIN6
#define EN           DIO_PIN7

/*
 * Options:
 * LCD_ON
 * LCD_OFF
 */
#define LCD_DISPLAY_STATE    LCD_ON
#define LCD_CURSOR_STATE     LCD_OFF
#define LCD_BLINK_STATE      LCD_OFF

/*
 * Options:
 * LCD_1_LINE
 * LCD_2_LINES
 */
#define LCD_LINES            LCD_2_LINES

/*
 * Options:
 * LCD_5X8_FONT
 * LCD_5X10_FONT
 */
#define LCD_FONT             LCD_5X8_FONT

/*
 * Options:
 * LCD_INCREMENT
 * LCD_DECREMENT
 */
#define LCD_ENTRY_MODE       LCD_INCREMENT

#endif

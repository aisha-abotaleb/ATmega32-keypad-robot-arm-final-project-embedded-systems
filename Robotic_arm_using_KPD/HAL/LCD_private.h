#ifndef LCD_PRIVATE_H_
#define LCD_PRIVATE_H_

#define LCD_ON                          1
#define LCD_OFF                         0

#define LCD_1_LINE                      0
#define LCD_2_LINES                     1

#define LCD_5X8_FONT                    0
#define LCD_5X10_FONT                   1

#define LCD_INCREMENT                   1
#define LCD_DECREMENT                   0

#define LINE1_BASE                      0x40
#define DDRAM_MSB                       128
#define CGRAM_MSB                       64

#define LCD_CMD_CLEAR_DISPLAY           0x01
#define LCD_CMD_RETURN_HOME             0x02

#define LCD_CMD_SHIFT_CURSOR_LEFT       0x10
#define LCD_CMD_SHIFT_CURSOR_RIGHT      0x14
#define LCD_CMD_SHIFT_DISPLAY_LEFT      0x18
#define LCD_CMD_SHIFT_DISPLAY_RIGHT     0x1C

/* Compile-Time Commands Generation */
#define LCD_FUNCTION_SET_CMD            (0x30 | (LCD_LINES << 3) | (LCD_FONT << 2))
#define LCD_DISPLAY_CTRL_CMD            (0x08 | (LCD_DISPLAY_STATE << 2) | (LCD_CURSOR_STATE << 1) | LCD_BLINK_STATE)
#define LCD_ENTRY_MODE_CMD              (0x04 | (LCD_ENTRY_MODE << 1))

#endif

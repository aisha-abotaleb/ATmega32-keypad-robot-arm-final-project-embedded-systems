#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

#define NORMAL_MODE          1
#define PHASE_CORRECT_PWM    2
#define CTC_MODE             3
#define FAST_PWM             4

#define NO_CLOCK             0
#define NO_PRESCALER         1
#define DIV_8                2
#define DIV_64               3
#define DIV_256              4
#define DIV_1024             5
#define EXT_FALLING          6
#define EXT_RISING           7

#define TCCR0       *((volatile u8*)0X53)
#define TCNT0       *((volatile u8*)0X52)
#define OCR0        *((volatile u8*)0X5C)
#define TIMSK       *((volatile u8*)0X59)
#define TIFR        *((volatile u8*)0X58)

#endif

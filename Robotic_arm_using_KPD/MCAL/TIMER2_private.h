#ifndef TIMER2_PRIVATE_H_
#define TIMER2_PRIVATE_H_

#define NORMAL_MODE          1
#define PHASE_CORRECT_PWM    2
#define CTC_MODE             3
#define FAST_PWM             4

#define NO_CLOCK             0
#define NO_PRESCALER         1
#define DIV_8                2
#define DIV_32               3
#define DIV_64               4
#define DIV_128              5
#define DIV_256              6
#define DIV_1024             7

#define TCCR2       *((volatile u8*)0x45)
#define TCNT2       *((volatile u8*)0x44)
#define OCR2        *((volatile u8*)0x43)
#define ASSR        *((volatile u8*)0x42)
#define TIMSK       *((volatile u8*)0x59)
#define TIFR        *((volatile u8*)0x58)

#endif
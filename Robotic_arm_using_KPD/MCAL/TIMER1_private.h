#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_

#define MODE_NORMAL                       0
#define MODE_PWM_PC_8BIT                  1
#define MODE_PWM_PC_9BIT                  2
#define MODE_PWM_PC_10BIT                 3
#define MODE_CTC_OCR1A                    4
#define MODE_FAST_PWM_8BIT                5
#define MODE_FAST_PWM_9BIT                6
#define MODE_FAST_PWM_10BIT               7
#define MODE_PWM_PFC_ICR1                 8
#define MODE_PWM_PFC_OCR1A                9
#define MODE_PWM_PC_ICR1                  10
#define MODE_PWM_PC_OCR1A                 11
#define MODE_CTC_ICR1                     12
#define MODE_FAST_PWM_ICR1                14
#define MODE_FAST_PWM_OCR1A               15

#define NO_CLOCK                          0
#define NO_PRESCALER                      1
#define DIV_8                             2
#define DIV_64                            3
#define DIV_256                           4
#define DIV_1024                          5
#define EXT_FALLING                       6
#define EXT_RISING                        7

#define TCCR1A       *((volatile u8*)0x4F)
#define TCCR1B       *((volatile u8*)0x4E)
#define TCNT1        *((volatile u16*)0x4C)
#define OCR1A        *((volatile u16*)0x4A)
#define OCR1B        *((volatile u16*)0x48)
#define ICR1         *((volatile u16*)0x46)
#define TIMSK        *((volatile u8*)0x59)
#define TIFR         *((volatile u8*)0x58)

#endif

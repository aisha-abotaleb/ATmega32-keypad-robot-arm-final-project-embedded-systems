#ifndef ADC_PRIVATE_H_
#define ADC_PRIVATE_H_

#define ADMUX           *((volatile u8*)0x27)
#define ADCSRA          *((volatile u8*)0x26)
#define ADCH            *((volatile u8*)0x25)
#define ADCL            *((volatile u8*)0x24)
#define ADC             *((volatile u16*)0x24)
#define SFIOR           *((volatile u8*)0x50)

#define IDLE            1
#define BUSY            2

#define ADC_VREF_AREF                 1
#define ADC_VREF_AVCC                 2
#define ADC_VREF_INTERNAL             3

#define ADC_RIGHT_ADJUST              1
#define ADC_LEFT_ADJUST               2

#define ADC_PRESCALER_2               1
#define ADC_PRESCALER_4               2
#define ADC_PRESCALER_8               3
#define ADC_PRESCALER_16              4
#define ADC_PRESCALER_32              5
#define ADC_PRESCALER_64              6
#define ADC_PRESCALER_128             7

#define ADC_AUTO_TRIGGER_DISABLE      1
#define ADC_AUTO_TRIGGER_ENABLE       2

#define ADC_FREE_RUNNING              0x00
#define ADC_ANALOG_COMPARATOR         0x20
#define ADC_EXTI0                     0x40
#define ADC_TIMER0_COMPARE            0x60
#define ADC_TIMER0_OVERFLOW           0x80
#define ADC_TIMER1_COMPARE_B          0xA0
#define ADC_TIMER1_OVERFLOW           0xC0
#define ADC_TIMER1_CAPTURE            0xE0

#endif

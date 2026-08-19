#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

#define TIME_OUT                      50000

/*
 * VREF Options:
 * - ADC_VREF_AREF
 * - ADC_VREF_AVCC
 * - ADC_VREF_INTERNAL
 */
#define ADC_VREF                      ADC_VREF_AVCC

/*
 * Data Adjustment Options:
 * - ADC_RIGHT_ADJUST
 * - ADC_LEFT_ADJUST
 */
#define ADC_ADJUST                    ADC_RIGHT_ADJUST

/*
 * Prescaler Options:
 * - ADC_PRESCALER_2
 * - ADC_PRESCALER_4
 * - ADC_PRESCALER_8
 * - ADC_PRESCALER_16
 * - ADC_PRESCALER_32
 * - ADC_PRESCALER_64
 * - ADC_PRESCALER_128
 */
#define ADC_PRESCALER                 ADC_PRESCALER_64

/*
 * Auto Trigger State:
 * - ADC_AUTO_TRIGGER_DISABLE
 * - ADC_AUTO_TRIGGER_ENABLE
 */
#define ADC_AUTO_TRIGGER_STATE        ADC_AUTO_TRIGGER_DISABLE

/*
 * Trigger Source (If Auto Trigger is ENABLED):
 * - ADC_FREE_RUNNING
 * - ADC_ANALOG_COMPARATOR
 * - ADC_EXTI0
 * - ADC_TIMER0_COMPARE
 * - ADC_TIMER0_OVERFLOW
 * - ADC_TIMER1_COMPARE_B
 * - ADC_TIMER1_OVERFLOW
 * - ADC_TIMER1_CAPTURE
 */
#define ADC_TRIGGER_SOURCE            ADC_FREE_RUNNING

#endif

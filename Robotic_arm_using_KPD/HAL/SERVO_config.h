#ifndef SERVO_CONFIG_H
#define SERVO_CONFIG_H

#define SERVO_MIN_PULSE_US           1000
#define SERVO_MAX_PULSE_US           2000
#define SERVO_MAX_ANGLE              180

#define SERVO_HW_PORT                DIO_PORTD
#define SERVO_HW_PIN1                DIO_PIN5
#define SERVO_HW_PIN2                DIO_PIN4

#define SERVO_SW_COUNT               4

#define SERVO_SW_PORTS               {DIO_PORTC, DIO_PORTC}
#define SERVO_SW_PINS                {DIO_PIN0, DIO_PIN1}

#define SERVO_ICR_TOP_VALUE          19999
#define SERVO_SW_PWM_COMPARE_VALUE   10
#define SERVO_PERIOD_TICKS           2000
#define SERVO_TICK_TIME_US           10

#endif

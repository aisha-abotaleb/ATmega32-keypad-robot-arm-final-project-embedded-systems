#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"
#include "../MCAL/TIMER1_interface.h"
#include "../MCAL/TIMER0_interface.h"
#include "../MCAL/GI_interface.h"

#include "SERVO_config.h"
#include "SERVO_private.h"
#include "SERVO_interface.h"

static u16 SERVO_u16SwPulse[SERVO_SW_COUNT] = {0};
static u8  SERVO_u8SwPorts[SERVO_SW_COUNT]  = SERVO_SW_PORTS;
static u8  SERVO_u8SwPins[SERVO_SW_COUNT]   = SERVO_SW_PINS;

void SERVO_voidInit(void)
{
    u8 Local_u8Iterator;

    DIO_voidSetPinDirection(SERVO_HW_PORT, SERVO_HW_PIN1, DIO_OUT);
    DIO_voidSetPinDirection(SERVO_HW_PORT, SERVO_HW_PIN2, DIO_OUT);

    for (Local_u8Iterator = 0; Local_u8Iterator < SERVO_SW_COUNT; Local_u8Iterator++)
    {
        DIO_voidSetPinDirection(SERVO_u8SwPorts[Local_u8Iterator], SERVO_u8SwPins[Local_u8Iterator], DIO_OUT);
    }

    TIMER1_voidInit();
    TIMER1_voidSetInputCaptureValue(SERVO_ICR_TOP_VALUE);

    TIMER0_voidInit();
    TIMER0_voidSetOcrTicks(SERVO_SW_PWM_COMPARE_VALUE);
    TIMER0_eSetCallBackCompare(SERVO_voidSwPwmHandler);

    GI_voidEnable();
}

void SERVO_voidSetAngle(u8 Copy_u8ServoId, u8 Copy_u8Angle)
{
    u32 Local_u32MappedValue;

    if (Copy_u8Angle <= SERVO_MAX_ANGLE)
    {
        Local_u32MappedValue = SERVO_MIN_PULSE_US + (((u32)Copy_u8Angle * (SERVO_MAX_PULSE_US - SERVO_MIN_PULSE_US)) / SERVO_MAX_ANGLE);

        if ((Copy_u8ServoId == SERVO_1) || (Copy_u8ServoId == SERVO_2))
        {
            SERVO_voidSetHwAngle(Copy_u8ServoId, Local_u32MappedValue);
        }
        else if ((Copy_u8ServoId >= 3) && (Copy_u8ServoId < (3 + SERVO_SW_COUNT)))
        {
            SERVO_voidSetSwAngle(Copy_u8ServoId, Local_u32MappedValue);
        }
    }
}

static void SERVO_voidSetHwAngle(u8 Copy_u8ServoId, u32 Copy_u32MappedValue)
{
    if (Copy_u8ServoId == SERVO_1)
    {
        TIMER1_voidSetCompareValueA((u16)Copy_u32MappedValue);
    }
    else if (Copy_u8ServoId == SERVO_2)
    {
        TIMER1_voidSetCompareValueB((u16)Copy_u32MappedValue);
    }
}

static void SERVO_voidSetSwAngle(u8 Copy_u8ServoId, u32 Copy_u32MappedValue)
{
    SERVO_u16SwPulse[Copy_u8ServoId - 3] = (u16)Copy_u32MappedValue;
}

static void SERVO_voidSwPwmHandler(void)
{
    static u16 Local_u16TickCounter = 0;
    u8 Local_u8Iterator;

    Local_u16TickCounter++;

    if (Local_u16TickCounter == SERVO_PERIOD_TICKS)
    {
        Local_u16TickCounter = 0;

        for (Local_u8Iterator = 0; Local_u8Iterator < SERVO_SW_COUNT; Local_u8Iterator++)
        {
            DIO_voidSetPinValue(SERVO_u8SwPorts[Local_u8Iterator], SERVO_u8SwPins[Local_u8Iterator], DIO_HIGH);
        }
    }

    for (Local_u8Iterator = 0; Local_u8Iterator < SERVO_SW_COUNT; Local_u8Iterator++)
    {
        if (Local_u16TickCounter == (SERVO_u16SwPulse[Local_u8Iterator] / SERVO_TICK_TIME_US))
        {
            DIO_voidSetPinValue(SERVO_u8SwPorts[Local_u8Iterator], SERVO_u8SwPins[Local_u8Iterator], DIO_LOW);
        }
    }
}

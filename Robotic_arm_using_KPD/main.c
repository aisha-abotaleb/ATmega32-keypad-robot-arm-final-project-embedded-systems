/*
 * main.c
 *
 *  Created on: 4/8/2026
 *      Author: Marwa
 */

/*

 * main_keypad_arm.c
 *
 * Single AVR: Controls a robotic arm with 4 servos using the KPD 4x4 keypad.
 *   - 1 base servo        -> left/right rotation
 *   - 2 arm servos        -> move together for forward/backward reach
 *   - 1 gripper servo     -> catch/release toggle
 *
 * LCD shows the current action.
 *
 * Keypad layout (from KPD_config.h):
 *      7  8  9  /
 *      4  5  6  *
 *      1  2  3  -
 *      C  0  =  +
 *
 * Key mapping used here:
 *   '8' -> Forward   (arm servos 1 & 2 together, PD5/OC1A + PD4/OC1B)
 *   '2' -> Backward  (arm servos 1 & 2 together, PD5/OC1A + PD4/OC1B)
 *   '4' -> Left      (base servo, PB3 / OC0)
 *   '6' -> Right     (base servo, PB3 / OC0)
 *   '5' -> Catch/Release toggle (gripper servo, PD7 / OC2)
 *
 *      Author: Marwa
 */

#include "LIB/STD_TYPES.h"
#include "LIB/BIT_MATH.h"
#include <util/delay.h>

#include "MCAL/DIO_interface.h"
#include "MCAL/GI_interface.h"
#include "MCAL/TIMER0_interface.h"
#include "MCAL/TIMER1_interface.h"
#include "MCAL/TIMER2_interface.h"

#include "HAL/KPD_interface.h"
#include "HAL/LCD_interface.h"

/* ---------- Definitions ---------- */
#define MAX_ANGLE            180UL
#define MIN_ANGLE              0UL
#define CENTER_ANGLE           90U
#define ANGLE_STEP               5U   /* degrees moved per key press */

#define GRIPPER_OPEN_ANGLE       0U
#define GRIPPER_CLOSED_ANGLE   180U

/* Servo OCR ranges */
#define MIN_OCR0_8BIT             125
#define MAX_OCR0_8BIT             250
#define MIN_OCR_8BIT             30
#define MAX_OCR_8BIT             60
#define MIN_OCR_16BIT       1000UL
#define MAX_OCR_16BIT       2000UL

/* Keypad key codes, taken from KPD_config.h layout */
#define KEY_FORWARD             '8'
#define KEY_BACKWARD            '2'
#define KEY_LEFT                '4'
#define KEY_RIGHT                '6'
#define KEY_GRIPPER              '5'
/* NO_PRESSED_KEY (255) comes from KPD_interface.h */

/* Servo indices */
#define SERVO_BASE                 0     /* PB3 (OC0)  - left/right rotation   */
#define SERVO_ARM1                 1     /* PD5 (OC1A) - forward/backward reach */
#define SERVO_ARM2                 2     /* PD4 (OC1B) - forward/backward reach */
#define SERVO_GRIPPER              3     /* PD7 (OC2)  - catch/release          */

/* ---------- Mapping functions ---------- */
static u8 MapAngleToOCR0_8(u8 angle)
{
    return MIN_OCR0_8BIT + ((u32)angle * (MAX_OCR0_8BIT - MIN_OCR0_8BIT)) / MAX_ANGLE;
}
static u8 MapAngleToOCR8(u8 angle)
{
    return MIN_OCR_8BIT + ((u32)angle * (MAX_OCR_8BIT - MIN_OCR_8BIT)) / MAX_ANGLE;
}

static u16 MapAngleToOCR16(u8 angle)
{
    return MIN_OCR_16BIT + ((u32)angle * (MAX_OCR_16BIT - MIN_OCR_16BIT)) / MAX_ANGLE;
}

/* ---------- Apply one angle to its servo ---------- */
static void ApplyAngle(u8 index, u8 angle)
{
    if (angle > MAX_ANGLE)
    {
        return;
    }

    switch (index)
    {
        case SERVO_BASE: /* OC0 */
            TIMER0_voidSetOcrTicks(MapAngleToOCR0_8(angle));
            break;
        case SERVO_ARM1: /* OC1A */
            TIMER1_voidSetCompareValueA(MapAngleToOCR16(angle));
            break;
        case SERVO_ARM2: /* OC1B */
            TIMER1_voidSetCompareValueB(MapAngleToOCR16(angle));
            break;
        case SERVO_GRIPPER: /* OC2 */
            TIMER2_voidSetOcrTicks(MapAngleToOCR8(angle));
            break;
    }
}

/* ---------- Clamp helper ---------- */
static u8 ClampAngle(s16 angle)
{
    if (angle < (s16)MIN_ANGLE) return (u8)MIN_ANGLE;
    if (angle > (s16)MAX_ANGLE) return (u8)MAX_ANGLE;
    return (u8)angle;
}

/* ---------- LCD status helper ---------- */
static void ShowStatus(u8 *Copy_u8Text)
{
    LCD_voidClearDisplay();
    LCD_voidSetPosition(0, 0);
    LCD_voidSendString(Copy_u8Text);
}

int main(void)
{
    u8 Local_u8Key;
    u8 Local_u8AngleBase      = CENTER_ANGLE;
    u8 Local_u8AngleArm       = CENTER_ANGLE; /* shared by ARM1 & ARM2 */
    u8 Local_u8GripperClosed  = 0; /* 0 = open, 1 = closed */

    /* ---------- 1 - Init servo pins ---------- */
    DIO_voidSetPinDirection(DIO_PORTB, DIO_PIN3, DIO_OUT);   // OC0  (Base)
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN5, DIO_OUT);   // OC1A (Arm 1)
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN4, DIO_OUT);   // OC1B (Arm 2)
    DIO_voidSetPinDirection(DIO_PORTD, DIO_PIN7, DIO_OUT);   // OC2  (Gripper)

    /* ---------- 2 - Init Timers ---------- */
    TIMER0_voidInit();
    TIMER0_voidSetCompareOutputMode(OC0_NON_INV);

    TIMER2_voidInit();
    TIMER2_voidSetCompareOutputMode(OC2_NON_INV);

    TIMER1_voidInit();
    TIMER1_voidSetCompareOutputModeA(OC1_NON_INV);
    TIMER1_voidSetCompareOutputModeB(OC1_NON_INV);
    TIMER1_voidSetInputCaptureValue(19999);   // 50Hz with 8MHz / 8 prescaler

    /* ---------- 3 - Init Keypad and LCD ---------- */
    KPD_voidInit();
    LCD_voidInit();

    GI_voidEnable();

    /* Move to a known starting position */
    ApplyAngle(SERVO_BASE, Local_u8AngleBase);
    ApplyAngle(SERVO_ARM1, Local_u8AngleArm);
    ApplyAngle(SERVO_ARM2, Local_u8AngleArm);
    ApplyAngle(SERVO_GRIPPER, GRIPPER_OPEN_ANGLE);

    ShowStatus((u8 *)"Ready");

    while (1)
    {
        Local_u8Key = KPD_u8GetPressedKey();

        switch (Local_u8Key)
        {
            case KEY_FORWARD:
                Local_u8AngleArm = ClampAngle((s16)Local_u8AngleArm + ANGLE_STEP);
                ApplyAngle(SERVO_ARM1, Local_u8AngleArm);
                ApplyAngle(SERVO_ARM2, Local_u8AngleArm);
                ShowStatus((u8 *)"Move: Forward");
                break;

            case KEY_BACKWARD:
                Local_u8AngleArm = ClampAngle((s16)Local_u8AngleArm - ANGLE_STEP);
                ApplyAngle(SERVO_ARM1, Local_u8AngleArm);
                ApplyAngle(SERVO_ARM2, Local_u8AngleArm);
                ShowStatus((u8 *)"Move: Backward");
                break;

            case KEY_RIGHT:
                Local_u8AngleBase = ClampAngle((s16)Local_u8AngleBase + ANGLE_STEP);
                ApplyAngle(SERVO_BASE, Local_u8AngleBase);
                ShowStatus((u8 *)"Move: Right");
                break;

            case KEY_LEFT:
                Local_u8AngleBase = ClampAngle((s16)Local_u8AngleBase - ANGLE_STEP);
                ApplyAngle(SERVO_BASE, Local_u8AngleBase);
                ShowStatus((u8 *)"Move: Left");
                break;

            case KEY_GRIPPER:
                Local_u8GripperClosed = !Local_u8GripperClosed;
                if (Local_u8GripperClosed)
                {
                    ApplyAngle(SERVO_GRIPPER, GRIPPER_CLOSED_ANGLE);
                    ShowStatus((u8 *)"Catch");
                }
                else
                {
                    ApplyAngle(SERVO_GRIPPER, GRIPPER_OPEN_ANGLE);
                    ShowStatus((u8 *)"Release");
                }
                break;

            case NO_PRESSED_KEY:
            default:
                /* no key pressed / unmapped key -> keep last status on screen */
                break;
        }

        _delay_ms(50);
    }

    return 0;
}

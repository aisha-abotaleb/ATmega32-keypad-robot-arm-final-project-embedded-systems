#ifndef SERVO_PRIVATE_H
#define SERVO_PRIVATE_H

static void SERVO_voidSetHwAngle(u8 Copy_u8ServoId, u32 Copy_u32MappedValue);
static void SERVO_voidSetSwAngle(u8 Copy_u8ServoId, u32 Copy_u32MappedValue);
static void SERVO_voidSwPwmHandler(void);

#endif

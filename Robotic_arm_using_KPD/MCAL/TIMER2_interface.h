#ifndef TIMER2_INTERFACE_H_
#define TIMER2_INTERFACE_H_

typedef enum
{
	OC2_DISCONNECTED = 0,
	OC2_TOGGLE       = 1,
	OC2_CLEAR        = 2,
	OC2_SET          = 3,
	OC2_NON_INV      = 4,
	OC2_INV          = 5
} OC2_Mode_e;

void TIMER2_voidInit(void);
void TIMER2_voidSetPreLoadTicks(u8 Copy_u8Ticks);
void TIMER2_voidSetOcrTicks(u8 Copy_u8Ticks);
STD_err_e TIMER2_eSetCallBackNormal(void (*Pfunc)(void));
STD_err_e TIMER2_eSetCallBackCompare(void (*Pfunc)(void));
void TIMER2_voidSetCompareOutputMode(OC2_Mode_e Copy_Mode);

#endif
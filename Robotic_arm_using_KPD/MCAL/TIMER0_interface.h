#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_

typedef enum
{
	OC0_DISCONNECTED = 0,
	OC0_TOGGLE       = 1,
	OC0_CLEAR        = 2,
	OC0_SET          = 3,
	OC0_NON_INV      = 4,
	OC0_INV          = 5
} OC0_Mode_e;

void TIMER0_voidInit(void);
void TIMER0_voidSetPreLoadTicks(u8 Copy_u8Ticks);
void TIMER0_voidSetOcrTicks(u8 Copy_u8Ticks);
STD_err_e TIMER0_eSetCallBackNormal(void (*Pfunc)(void));
STD_err_e TIMER0_eSetCallBackCompare(void (*Pfunc)(void));
void TIMER0_voidSetCompareOutputMode(OC0_Mode_e Copy_Mode);

#endif

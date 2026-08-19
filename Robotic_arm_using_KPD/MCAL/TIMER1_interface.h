#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_

typedef enum
{
	OC1_DISCONNECTED = 0,
	OC1_TOGGLE       = 1,
	OC1_CLEAR        = 2,
	OC1_SET          = 3,
	OC1_NON_INV      = 4,
	OC1_INV          = 5
} OC1_Mode_e;

typedef enum
{
	ICU_FALLING_EDGE = 0,
	ICU_RISING_EDGE  = 1
} ICU_Edge_e;

void TIMER1_voidInit(void);
void TIMER1_voidSetTimerValue(u16 Copy_u16Value);
u16 TIMER1_u16GetTimerValue(void);
void TIMER1_voidSetCompareValueA(u16 Copy_u16Value);
void TIMER1_voidSetCompareValueB(u16 Copy_u16Value);
void TIMER1_voidSetInputCaptureValue(u16 Copy_u16Value);
u16 TIMER1_u16GetInputCaptureValue(void);
void TIMER1_voidSetCompareOutputModeA(OC1_Mode_e Copy_Mode);
void TIMER1_voidSetCompareOutputModeB(OC1_Mode_e Copy_Mode);
void TIMER1_voidSetInputCaptureEdge(ICU_Edge_e Copy_Edge);
STD_err_e TIMER1_eSetCallBackNormal(void (*Pfunc)(void));
STD_err_e TIMER1_eSetCallBackCompareA(void (*Pfunc)(void));
STD_err_e TIMER1_eSetCallBackCompareB(void (*Pfunc)(void));
STD_err_e TIMER1_eSetCallBackCapture(void (*Pfunc)(void));

#endif

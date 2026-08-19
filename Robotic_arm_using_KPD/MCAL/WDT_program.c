#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "WDT_interface.h"
#include "WDT_private.h"

void WDT_voidEnable(void)
{
	SET_BIT(WDTCR, WDTCR_WDE);
}

void WDT_voidDisable(void)
{
	WDTCR |= (1 << WDTCR_WDTOE) | (1 << WDTCR_WDE);
	WDTCR = 0x00;
}

void WDT_voidSleep(u8 Copy_u8SleepCycles)
{
	if(Copy_u8SleepCycles <= 7)
	{
		WDTCR &= 0b11111000;
		WDTCR |= Copy_u8SleepCycles;
	}
}

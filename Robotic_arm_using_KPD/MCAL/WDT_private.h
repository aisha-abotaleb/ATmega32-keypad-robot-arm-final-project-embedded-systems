#ifndef WDT_PRIVATE_H_
#define WDT_PRIVATE_H_

#define WDT_NUM_CYCLES_16K		0
#define WDT_NUM_CYCLES_32K		1
#define WDT_NUM_CYCLES_64K		2
#define WDT_NUM_CYCLES_128K		3
#define WDT_NUM_CYCLES_256K		4
#define WDT_NUM_CYCLES_512K		5
#define WDT_NUM_CYCLES_1024K	6
#define WDT_NUM_CYCLES_2048K	7

#define WDTCR					*((volatile u8*)0x41)
#define WDTCR_WDTOE				4
#define WDTCR_WDE				3
#define WDTCR_WDP2				2
#define WDTCR_WDP1				1
#define WDTCR_WDP0				0

#endif

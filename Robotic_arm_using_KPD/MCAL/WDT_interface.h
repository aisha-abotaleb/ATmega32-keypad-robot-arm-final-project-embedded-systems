#ifndef WDT_INTERFACE_H_
#define WDT_INTERFACE_H_

/*
 * WDT Sleep Cycles Options:
 * WDT_NUM_CYCLES_16K    -> 16.3 ms
 * WDT_NUM_CYCLES_32K    -> 32.5 ms
 * WDT_NUM_CYCLES_64K    -> 65.0 ms
 * WDT_NUM_CYCLES_128K   -> 0.13 s
 * WDT_NUM_CYCLES_256K   -> 0.26 s
 * WDT_NUM_CYCLES_512K   -> 0.52 s
 * WDT_NUM_CYCLES_1024K  -> 1.0 s
 * WDT_NUM_CYCLES_2048K  -> 2.1 s
 */
#define WDT_NUM_CYCLES_16K		0
#define WDT_NUM_CYCLES_32K		1
#define WDT_NUM_CYCLES_64K		2
#define WDT_NUM_CYCLES_128K		3
#define WDT_NUM_CYCLES_256K		4
#define WDT_NUM_CYCLES_512K		5
#define WDT_NUM_CYCLES_1024K	6
#define WDT_NUM_CYCLES_2048K	7

void WDT_voidEnable(void);
void WDT_voidDisable(void);
void WDT_voidSleep(u8 Copy_u8SleepCycles);

#endif

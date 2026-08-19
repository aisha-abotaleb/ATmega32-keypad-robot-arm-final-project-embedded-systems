#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

#define ADC_CHANNEL_0           0
#define ADC_CHANNEL_1           1
#define ADC_CHANNEL_2           2
#define ADC_CHANNEL_3           3
#define ADC_CHANNEL_4           4
#define ADC_CHANNEL_5           5
#define ADC_CHANNEL_6           6
#define ADC_CHANNEL_7           7

void ADC_voidInit(void);
STD_err_e ADC_u16ConvertSynch(u8 Copy_u8Channel, u16 *Pu16Reading);
STD_err_e ADC_u16ConvertASynch(u8 Copy_u8Channel, u16 *Pu16Reading, void(*PtrFunc)(void));

#endif
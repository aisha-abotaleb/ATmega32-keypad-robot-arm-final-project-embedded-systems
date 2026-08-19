#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

#include "../MCAL/DIO_interface.h"

#include "KPD_interface.h"
#include "KPD_config.h"
#include "KPD_private.h"

#include <util/delay.h>

void KPD_voidInit(void)
{
	DIO_voidSetPinDirection(KPD_PORT, KPD_C0, DIO_OUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_C1, DIO_OUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_C2, DIO_OUT);
	DIO_voidSetPinDirection(KPD_PORT, KPD_C3, DIO_OUT);

	DIO_voidSetPinValue(KPD_PORT, KPD_C0, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_C1, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_C2, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_C3, DIO_HIGH);

	DIO_voidSetPinDirection(KPD_PORT, KPD_R0, DIO_IN);
	DIO_voidSetPinDirection(KPD_PORT, KPD_R1, DIO_IN);
	DIO_voidSetPinDirection(KPD_PORT, KPD_R2, DIO_IN);
	DIO_voidSetPinDirection(KPD_PORT, KPD_R3, DIO_IN);

	DIO_voidSetPinValue(KPD_PORT, KPD_R0, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_R1, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_R2, DIO_HIGH);
	DIO_voidSetPinValue(KPD_PORT, KPD_R3, DIO_HIGH);
}

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8Button = NO_PRESSED_KEY;
	u8 Local_u8PinState;
	
	static u8 Local_u8ColArr[COL_NUM] = {KPD_C0, KPD_C1, KPD_C2, KPD_C3};
	static u8 Local_u8RowArr[ROW_NUM] = {KPD_R0, KPD_R1, KPD_R2, KPD_R3};
	static u8 Local_u8KpdArr[ROW_NUM][COL_NUM] = KPD_VALUES;

	for(u8 Local_u8ColIter = 0; Local_u8ColIter < COL_NUM; Local_u8ColIter++)
	{
		DIO_voidSetPinValue(KPD_PORT, Local_u8ColArr[Local_u8ColIter], DIO_LOW);

		for(u8 Local_u8RowIter = 0; Local_u8RowIter < ROW_NUM; Local_u8RowIter++)
		{
			Local_u8PinState = DIO_u8GetPinValue(KPD_PORT, Local_u8RowArr[Local_u8RowIter]);

			if(Local_u8PinState == DIO_LOW)
			{
				_delay_ms(20);
				Local_u8PinState = DIO_u8GetPinValue(KPD_PORT, Local_u8RowArr[Local_u8RowIter]);

				if(Local_u8PinState == DIO_LOW)
				{
					Local_u8Button = Local_u8KpdArr[Local_u8RowIter][Local_u8ColIter];

					/*while(Local_u8PinState == DIO_LOW)
					{
						Local_u8PinState = DIO_u8GetPinValue(KPD_PORT, Local_u8RowArr[Local_u8RowIter]);
					}*/
				}
			}
		}

		DIO_voidSetPinValue(KPD_PORT, Local_u8ColArr[Local_u8ColIter], DIO_HIGH);
	}

	return Local_u8Button;
}

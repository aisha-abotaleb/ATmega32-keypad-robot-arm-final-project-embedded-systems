/*
* EEPROM_Program.c
*
*  Created on: Sep 11, 2025
*      Author: Dell
*/

//LIB
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"

//MCAL
#include "../MCAL/TWI_Private.h"
#include "../MCAL/TWI_Interface.h"


//HAL
#include "EEPROM_Private.h"
#include "EEPROM_Config.h"
#include "EEPROM_Interface.h"
#include "util/delay.h"

void EEPROM_Init()
{

	TWI_voidMasterInit(2);

}

void EEPROM_SendByte(u8 blockNumber, u8 address, u8 data)
{
	u8 Status;

	//Send Start Condition
	Status = TWI_u8SendStartCondition();
	if(Status == 1)
	{
		u8 EEPROM_Address = 0x50 | blockNumber;
		Status = TWI_u8SendSlaveAddress(EEPROM_Address,WRITE);

		if(Status == 1)
		{
			Status = TWI_u8MasterWriteData(address);
			if(Status == 1)
			{
				Status = TWI_u8MasterWriteData(data);
				if(Status == 1)
				{
					TWI_u8SendStopConditon();
					_delay_ms(5);
				}

			}

		}
	}


}

void EEPROM_RecieveByte(u8 blockNumber,u8 address, u8*recievedByte)
{
	u8 Status;

	//Send Start Condition
	Status = TWI_u8SendStartCondition();

	if(Status == 1)
	{
		u8 EEPROM_Address = 0x50 | blockNumber;
		Status = TWI_u8SendSlaveAddress(EEPROM_Address,WRITE);
		if(Status == 1)
		{
			Status = TWI_u8MasterWriteData(address);
			if(Status == 1)
			{
				Status = TWI_u8SendStartCondition();
				if(Status == 1)
				{
					Status = TWI_u8SendSlaveAddress(EEPROM_Address,READ);
					if(Status == 1)
					{
						Status = TWI_u8MasterReadData(recievedByte);
						if(Status == 1)
						{
							TWI_u8SendStopConditon();
							_delay_ms(5);
						}
					}
				}
			}
		}
	}


}

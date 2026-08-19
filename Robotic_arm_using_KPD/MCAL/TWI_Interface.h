/*
 * TWI_Interface.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Dell
 */

#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_

void TWI_voidMasterInit(u8 Master_Address);
void TWI_voidSlaveInit(u8 Salve_Address);
u8	 TWI_u8SendStartCondition(void);
u8	 TWI_u8SendSlaveAddress(u8 Slave_Address,u8 Mode);
u8	 TWI_u8MasterWriteData(u8 Data);
u8	 TWI_u8MasterReadData(u8* RecievedData);
u8	 TWI_u8SendStopConditon(void);
u8	 TWI_u8SendFrame(u8 Slave_Addresss,u8 SentData);
u8	 TWI_u8RecieveFrame(u8 Slave_Addresss,u8* RecievedData);

#endif /* TWI_INTERFACE_H_ */

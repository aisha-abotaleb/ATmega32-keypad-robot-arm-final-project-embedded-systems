/*
 * EEPROM_Interface.h
 *
 *  Created on: Sep 11, 2025
 *      Author: Dell
 */

#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_
void EEPROM_Init();
void EEPROM_SendByte(u8 blockNumber, u8 address, u8 data);
void EEPROM_RecieveByte(u8 blockNumber,u8 address, u8*recievedByte);

#endif /* EEPROM_INTERFACE_H_ */

/*
 * TWI_Private.h
 *
 *  Created on: Sep 10, 2025
 *      Author: Dell
 */

#ifndef TWI_PRIVATE_H_
#define TWI_PRIVATE_H_
//Status code for Each Operation
#define   START_ACK                  0x08      //Start has been sent
#define   REPEAT_START_ACK           0x10      //repeated Start
#define   SLAVE_ADD_WR_ACK           0x18      //Master transmit (Salve Address + write Request) ACK
#define   SLAVE_ADD_RD_ACK           0x40      //Master transmit (Salve Address + read Request) ACK
#define   MSTR_WR_BYTE_ACK           0x28      //Master transmit data ACK
#define   MSTR_RD_BYTE_ACK           0x50      //Master Recieved data with ACK
#define   MSTR_RD_BYTE_NACK          0x58      //Master Recieved data with not ACK
#define   SLAVE_ADD_RCVD_RD_REQ      0xA8      //Means Slave Address Recieved With read request
#define   SLAVE_ADD_RCVD_WR_REQ      0x60      //Means Slave Address Recieved With Write request
#define   SLAVE_DATA_Recieved        0x80      //Means a byte is recieved
#define   SLAVE_BYTE_Transmitted     0xB8      //Means that the Written is transmitted

#define WRITE						0
#define READ						1
#endif /* TWI_PRIVATE_H_ */

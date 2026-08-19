/*
 * TWI_Program.c
 *
 *  Created on: Sep 10, 2025
 *      Author: Dell
 */
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include "TWI_Register.h"
#include "TWI_Private.h"
#include "TWI_Config.h"
#include "TWI_Interface.h"

void TWI_voidMasterInit(u8 Master_Address){
	//SCL 100kbitps
	//cpu clk 8MHZ
	//TWBR = 32
	//Clear all bits of TWPS
	TWBR = 32;
	CLR_BIT(TWSR,TWSR_TWPS1);
	CLR_BIT(TWSR,TWSR_TWPS0);

	TWAR = Master_Address << 1;
	SET_BIT(TWCR,TWCR_TWEA);
	//enable to TWI hardware
	SET_BIT(TWCR,TWCR_TWEN);

}
void TWI_voidSlaveInit(u8 Salve_Address){

	//the slave does not generate the clock ,so it does not modify the configuration for the clock
	TWAR = Salve_Address << 1;
	//enable ack
	SET_BIT(TWCR,TWCR_TWEA);
	//enable to TWI hardware
	SET_BIT(TWCR,TWCR_TWEN);
}
u8	 TWI_u8SendStartCondition(void){
	u8 status = 0;

	//send start condition

	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWSTA) | (1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	//wait until transfer is done

	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	//check for status

	    u8 statusCode = TWSR & 0xF8;

	    if(statusCode == START_ACK || statusCode == REPEAT_START_ACK)
	    {
	        status = 1;
	    }
	    else
	    {
	        status = 0;
	    }
	    return status;
}
u8	 TWI_u8SendSlaveAddress(u8 Slave_Address,u8 Mode){

	TWDR=Slave_Address<<1;
	u8 status =1;
	if(Mode == WRITE){
		CLR_BIT(TWDR,0);
	}
	else if(Mode == READ){
		SET_BIT(TWDR,0);
	}
	else {
		status = 0;
	}
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	if((TWSR & 0xF8) == SLAVE_ADD_WR_ACK || (TWSR & 0xF8) == SLAVE_ADD_RD_ACK){
		status =1;
	}
	else {
		status =0;
	}
	return status;
}
u8	 TWI_u8MasterWriteData(u8 Data){
	TWDR=Data;
	u8 status =1 ;
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	if((TWSR & 0xF8) == MSTR_WR_BYTE_ACK){
		status = 1;
	}
	else{
		status = 0;
	}
	return status;

}
u8	 TWI_u8MasterReadData(u8* RecievedData){
	u8 status = 0;
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	while(GET_BIT(TWCR,TWCR_TWINT) == 0);

	if((TWSR & 0xF8) == MSTR_RD_BYTE_ACK){
		status = 1;
		*RecievedData=TWDR;
	}
	else{
		status = 0;
	}

	return status;
}
u8	 TWI_u8SendStopConditon(void){
	//send stop condition on bus
	//this will certainly succeed because at this point we are mastering the bus
	TWCR = (1<<TWCR_TWINT) | (1<<TWCR_TWSTO) | (1<<TWCR_TWEN);
	return 1;
}
u8	 TWI_u8SendFrame(u8 Slave_Addresss,u8 SentData){
	u8 status;
	//send start condition
	status = TWI_u8SendStartCondition();
	if(status == 1){
		status = TWI_u8SendSlaveAddress(Slave_Addresss,WRITE);
		if(status == 1){
				status = TWI_u8MasterWriteData(SentData);
				if(status == 1){
								status = TWI_u8SendStopConditon();


							}

			}
	}
	return status;

}
u8	 TWI_u8RecieveFrame(u8 Slave_Addresss,u8* RecievedData){
	u8 status;
	//send start condition
	status = TWI_u8SendStartCondition();
	if(status == 1){
		status = TWI_u8SendSlaveAddress(Slave_Addresss,READ);
		if(status == 1){
				status = TWI_u8MasterReadData(RecievedData);
				if(status == 1){
								status = TWI_u8SendStopConditon();


							}

			}
	}
	return status;
}

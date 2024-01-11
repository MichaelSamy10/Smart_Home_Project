/*
 * EEPROM_program.c
 *
 * Created: 26-Dec-23 2:44:21 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include <avr/delay.h>
#include "../../MCAL/TWI/TWI_interface.h"
#include "EEPROM_config.h"


void EEPROM_voidWriteByte(u8 Copy_u8Data,u16 Copy_u16Address)
{
	TWI_SendStartCond();
	
	TWI_SendSlaveAddressWithWrite(0b1010<<3 | A2_BIT<<2 | Copy_u16Address>>8);
	TWI_MasterSendDataWithAck((u8) Copy_u16Address);
	TWI_MasterSendDataWithAck(Copy_u8Data);
	
	
	TWI_SendStopCond();
	
	_delay_ms(10);
}


void EEPROM_voidReadByte(u8 *Copy_u8Ptr, u16 Copy_u16Address)
{
	TWI_SendStartCond();
	
	TWI_SendSlaveAddressWithWrite(0b1010<<3 | A2_BIT<<2 | Copy_u16Address>>8);
	TWI_MasterSendDataWithAck((u8) Copy_u16Address);
	/* Dummy write */
	//	TWI_MasterSendDataWithAck(0);
	
	TWI_SendRepeatedStartCond();
	/* read with Ack */
	TWI_SendSlaveAddressWithRead(0b1010<<3 | A2_BIT<<2 | Copy_u16Address>>8);
	TWI_MasterReceiveDataWithNack(Copy_u8Ptr);

	TWI_SendStopCond();

	_delay_ms(10);
}

/*
 * TWI_program.c
 *
 * Created: 26-Dec-23 11:01:48 AM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TWI_register.h"
#include "TWI_interface.h"
#include "TWI_config.h"
#include "TWI_private.h"



void TWI_voidMasterInit(u8 Copy_u8Address)
{
	if (Copy_u8Address != NO_ADDRESS)
	{
		TWAR = (Copy_u8Address << 1);
	}
	
	/* set prescalar to 1*/
	CLR_BIT(TWSR,TWPS0);
	CLR_BIT(TWSR,TWPS1);
	
	/* To get 400 KbPs speed*/
	TWBR = 2;
	
}


void TWI_voidSlaveInit(u8 Copy_u8Address)
{
	/* shift Slave address with 1 left as the address is 7 bits*/
	TWAR = (Copy_u8Address << 1);
}


TWI_ERROR_STATE TWI_SendStartCond(void)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;
	
	/* (TWINT)-> set Interrupt flag that indicates that start condition transmitted */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) != START)
	{
		/* Error in start condition */
		Local_ErrorState = START_CONDITION_ERROR;
	}

	return Local_ErrorState;
}

TWI_ERROR_STATE TWI_SendRepeatedStartCond(void)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;
	
	/* (TWINT)-> set Interrupt flag that indicates that start condition transmitted */
	TWCR = (1<<TWINT)|(1<<TWSTA)|(1<<TWEN);
	
	while(!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) != REPEATED_START)
	{
		/* Error in start condition */
		Local_ErrorState = REPEATED_START_ERROR;
	}

	return Local_ErrorState;
}

/*  Write with Ack*/
TWI_ERROR_STATE TWI_SendSlaveAddressWithWrite(u8 Copy_u8Address)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;

	/* shift left with 1 then clear bit 0 to write address(7-bit) in TWDR*/
	u8 Local_u8Address = (Copy_u8Address << 1);
	CLR_BIT(Local_u8Address,0);
	
	TWDR = Local_u8Address;
	
	/* clear flag and enable TWI and ACK*/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	while (!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != MT_SLA_ACK)
	{
		Local_ErrorState = SLAVE_ADDR_WITH_WRITE_ERROR;
	}

	return Local_ErrorState;
}

TWI_ERROR_STATE TWI_SendSlaveAddressWithRead(u8 Copy_u8Address)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;

	/* shift left with 1 then set bit 0 to Read address(7-bit) in TWDR*/
	u8 Local_u8Address = (Copy_u8Address << 1);
	SET_BIT(Local_u8Address,0);
	
	TWDR = Local_u8Address;
	
	/* clear flag and enable TWI*/
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA) ;
	
	while (!(TWCR & (1<<TWINT)));
	
	if ((TWSR & 0xF8) != MR_SLA_ACK)
	{
		Local_ErrorState = SLAVE_ADDR_WITH_READ_ERROR;
	}

	return Local_ErrorState;	
}

TWI_ERROR_STATE TWI_MasterSendDataWithAck(u8 Copy_u8Data)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;
	TWDR = Copy_u8Data;
	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	while (!(TWCR & (1<<TWINT)));	

	if ((TWSR & 0xF8) != MT_DATA_ACK)
	{
		Local_ErrorState = MASTER_SEND_WITH_ACK_ERROR;
	}

	return Local_ErrorState;
}

TWI_ERROR_STATE TWI_MasterSendDataWithNack(u8 Copy_u8Data)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;
	TWDR = Copy_u8Data;
	TWCR = (1<<TWINT) | (1<<TWEN);
	
	while (!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) != MT_DATA_NACK)
	{
		Local_ErrorState = MASTER_SEND_WITH_NACK_ERROR;
	}

	return Local_ErrorState;
}

TWI_ERROR_STATE TWI_MasterReceiveDataWithAck(u8 *Copy_u8Data)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;

	TWCR = (1<<TWINT) | (1<<TWEN) | (1<<TWEA);
	
	while (!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) != MR_DATA_ACK)
	{
		Local_ErrorState = MASTER_RECEIVE_WITH_ACK_ERROR;
	}

	*Copy_u8Data = TWDR;
	
	return Local_ErrorState;
}

TWI_ERROR_STATE TWI_MasterReceiveDataWithNack(u8 *Copy_u8Data)
{
	TWI_ERROR_STATE Local_ErrorState =  NO_ERROR;

	TWCR = (1<<TWINT) | (1<<TWEN) ;
	
	while (!(TWCR & (1<<TWINT)));

	if ((TWSR & 0xF8) != MR_DATA_NACK)
	{
		Local_ErrorState = MASTER_RECEIVE_WITH_NACK_ERROR;
	}

	*Copy_u8Data = TWDR;
	
	return Local_ErrorState;	
}

void TWI_SendStopCond(void)
{
	TWCR = (1<<TWINT)|(1<<TWEN)|(1<<TWSTO);

}


void TWI_voidStop()
{
	TWCR = (0<<TWEN);
}
/*
 * TWI_interface.h
 *
 * Created: 26-Dec-23 11:01:29 AM
 *  Author: MICHAEL
 */ 


#ifndef TWI_INTERFACE_H_
#define TWI_INTERFACE_H_


typedef enum 
{
	NO_ERROR,
	START_CONDITION_ERROR,
	REPEATED_START_ERROR,
	SLAVE_ADDR_WITH_WRITE_ERROR,
	SLAVE_ADDR_WITH_READ_ERROR,
	MASTER_SEND_WITH_ACK_ERROR,
	MASTER_SEND_WITH_NACK_ERROR,
	MASTER_RECEIVE_WITH_ACK_ERROR,
	MASTER_RECEIVE_WITH_NACK_ERROR,
	
}TWI_ERROR_STATE;


void TWI_voidMasterInit(u8 Copy_u8Address);

void TWI_voidSlaveInit(u8 Copy_u8Address);

TWI_ERROR_STATE TWI_SendStartCond(void);

TWI_ERROR_STATE TWI_SendRepeatedStartCond(void);

TWI_ERROR_STATE TWI_SendSlaveAddressWithWrite(u8 Copy_u8Address);

TWI_ERROR_STATE TWI_SendSlaveAddressWithRead(u8 Copy_u8Address);

TWI_ERROR_STATE TWI_MasterSendDataWithAck(u8 Copy_u8Data);

TWI_ERROR_STATE TWI_MasterSendDataWithNack(u8 Copy_u8Data);

TWI_ERROR_STATE TWI_MasterReceiveDataWithAck(u8 *Copy_u8Data);

TWI_ERROR_STATE TWI_MasterReceiveDataWithNack(u8 *Copy_u8Data);

void TWI_SendStopCond(void);

void TWI_voidStop();


#define NO_ADDRESS	0

#endif /* TWI_INTERFACE_H_ */
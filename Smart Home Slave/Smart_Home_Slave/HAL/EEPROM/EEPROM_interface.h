/*
 * EEPROM_interface.h
 *
 * Created: 26-Dec-23 7:07:52 PM
 *  Author: MICHAEL
 */ 


#ifndef EEPROM_INTERFACE_H_
#define EEPROM_INTERFACE_H_


void EEPROM_voidWriteByte(u8 Copy_u8Data,u16 Copy_u16Address);

void EEPROM_voidReadByte(u8 *Copy_u8Ptr, u16 Copy_u16Address);






#endif /* EEPROM_INTERFACE_H_ */
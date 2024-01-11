/*
 * KPD_interface.h
 *
 * Created: 11-Dec-23 12:00:08 PM
 *  Author: MICHAEL
 */ 


#ifndef KPD_INTERFACE_H_
#define KPD_INTERFACE_H_

void KPD_voidInit(void);

u8 KPD_u8GetPressedKey(void);

#define NOT_PRESSED 255

#endif /* KPD_INTERFACE_H_ */
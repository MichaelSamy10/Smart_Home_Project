/*
 * USART_interface.h
 *
 * Created: 25-Dec-23 9:42:54 AM
 *  Author: MICHAEL
 */ 


#ifndef USART_INTERFACE_H_
#define USART_INTERFACE_H_



void USART_voidInit(void);

void USART_voidSendData(u8 Copy_u8Data);

u8 USART_u8ReceiveData(void);


#endif /* USART_INTERFACE_H_ */
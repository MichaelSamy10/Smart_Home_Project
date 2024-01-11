/*
 * DIO_interface.h
 *
 *  Created on: Dec 6, 2023
 *      Author: MICHAEL
 */

#ifndef MCAL_DIO_INTERFACE_H_
#define MCAL_DIO_INTERFACE_H_


void DIO_voidInit(void);

u8 DIO_u8SetPinDirection(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Direction);
u8 DIO_u8SetPinValue(u8 Copy_u8Port, u8 Copy_u8Pin, u8 Copy_u8Value);
u8 DIO_u8SetPortDirection(u8 Copy_u8Port, u8 Copy_u8Direction);
u8 DIO_u8SetPortValue(u8 Copy_u8Port, u8 Copy_u8Value);
u8 DIO_u8GetPinValue(u8 copy_u8Port,u8 Copy_u8Pin, u8 *Copy_pu8Value);
u8 DIO_u8GetPortValue(u8 copy_u8Port, u8 *Copy_pu8Value);




#define DIO_u8INPUT			0
#define DIO_u8OUTPUT		1

#define DIO_u8ALL_INPUT		0
#define DIO_u8ALL_OUTPUT	0xFF

#define DIO_u8PORTA			1
#define DIO_u8PORTB			2
#define DIO_u8PORTC			3
#define DIO_u8PORTD			4

#define DIO_u8LOW			0
#define DIO_u8HIGH			1

#define DIO_u8ALL_LOW		0
#define DIO_u8ALL_HIGH		0xFF

#define DIO_u8PIN0			0
#define DIO_u8PIN1			1
#define DIO_u8PIN2			2
#define DIO_u8PIN3			3
#define DIO_u8PIN4			4
#define DIO_u8PIN5			5
#define DIO_u8PIN6			6
#define DIO_u8PIN7			7



#endif /* MCAL_DIO_INTERFACE_H_ */

/*
 * USART_program.c
 *
 * Created: 25-Dec-23 9:43:05 AM
 *  Author: MICHAEL
 */ 
#include "../../lib/BIT_MATH.h"
#include "../../lib/STD_TYPES.h"
#include "../DIO/DIO_interface.h"

#include "USART_config.h"
#include "USART_interface.h"
#include "USART_register.h"
#include "USART_private.h"


void USART_voidInit(void)
{
	/* Variable to access UCSRC register in one line*/
	u8 Local_u8UCSRC = 0b10000110;
	
	/* Set character size to 8-bit */
	CLR_BIT(UCSRB,UCSZ2);
	SET_BIT(Local_u8UCSRC,UCSZ0);
	SET_BIT(Local_u8UCSRC,UCSZ1);
	
	
	/* select UCSRC */
	SET_BIT(Local_u8UCSRC,URSEL);
	
	/* ASynchronous mode */
	CLR_BIT(Local_u8UCSRC,UMSEL);
		
	/* Select Parity mode */
	Local_u8UCSRC &= 0b11001111;
	Local_u8UCSRC |= PARITY;
	
	/* Select Stop bit (one)*/
	CLR_BIT(Local_u8UCSRC,USBS);
	
	/* write to register UCSRC*/
	UCSRC = Local_u8UCSRC;
	
	/* Baud rate = 9600 */ 
	UBRRL = 51;
	
	/* Enable Rx*/
	SET_BIT(UCSRB,RXEN);
	/* Enable Tx*/
	SET_BIT(UCSRB,TXEN);
	
}

void USART_voidSendData(u8 Copy_u8Data)
{
	while( (GET_BIT(UCSRA,UDRE)) != 1)
	{
		asm("NOP");
	}
	UDR = Copy_u8Data;
}

u8 USART_u8ReceiveData(void)
{
	while( GET_BIT(UCSRA,RXC) != 1)
	{
		asm("NOP");
	}
	return UDR;
}

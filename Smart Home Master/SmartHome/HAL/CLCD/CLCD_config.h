/*
 * CLCD_config.h
 *
 * Created: 10-Dec-23 11:45:04 AM
 *  Author: MICHAEL
 */ 


#ifndef CLCD_CONFIG_H_
#define CLCD_CONFIG_H_


/* Options:
	1- DIO_u8PORTA
	2- DIO_u8PORTB
	3- DIO_u8PORTC
	4- DIO_u8PORTD
*/

#define CLCD_CTRL_PORT	DIO_u8PORTC
#define CLCD_RS_PIN		DIO_u8PIN2
#define CLCD_RW_PIN		DIO_u8PIN3
#define CLCD_E_PIN		DIO_u8PIN4


#define CLCD_DATA_PORT	DIO_u8PORTA

/*Case of 4bit mode this is used*/
#define D4_ID DIO_u8PIN4
#define D5_ID DIO_u8PIN5
#define D6_ID DIO_u8PIN6
#define D7_ID DIO_u8PIN7


#define DISPLAY_CURSOR			CURSOR_ON

#define CLCD_MODE		FOUR_BIT

#endif /* CLCD_CONFIG_H_ */
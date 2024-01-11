/*
 * DIO_register.h
 *
 *  Created on: Dec 6, 2023
 *      Author: MICHAEL
 */

#ifndef MCAL_DIO_REGISTER_H_
#define MCAL_DIO_REGISTER_H_

#define PORTA *( (volatile u8 *) 0x3B)
#define DDRA  *( (volatile u8 *) 0x3A)
#define PINA  *( (volatile u8 *) 0x39)

/*
 * Port B Registers Definition
 */
#define PORTB *( (volatile u8 *) 0x38)
#define DDRB  *( (volatile u8 *) 0x37)
#define PINB  *( (volatile u8 *) 0x36)

/*
 * Port C Registers Definition
 */
#define PORTC *( (volatile u8 *) 0x35)
#define DDRC  *( (volatile u8 *) 0x34)
#define PINC  *( (volatile u8 *) 0x33)

/*
 * Port D Registers Definition
 */
#define PORTD *( (volatile u8 *) 0x32)
#define DDRD  *( (volatile u8 *) 0x31)
#define PIND  *( (volatile u8 *) 0x30)

#endif /* MCAL_DIO_REGISTER_H_ */

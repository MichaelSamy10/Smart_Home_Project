/*
 * main_config.h
 *
 * Created: 04-Jan-24 7:29:41 PM
 *  Author: MICHAEL
 */ 


#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_


/* Rooms Addresses in EEPROM */
#define ROOM1_ADDRESS						200
#define ROOM2_ADDRESS						201
#define ROOM3_ADDRESS						202
#define ROOM4_ADDRESS						203
#define FAN_ADDRESS							204
#define FAN_SPEED_ADDESS					205


#define ROOM1_PORT							DIO_u8PORTC
#define ROOM2_PORT							DIO_u8PORTC
#define ROOM3_PORT							DIO_u8PORTC
#define ROOM4_PORT							DIO_u8PORTC
#define FAN_PORT							DIO_u8PORTB

#define ROOM1_PIN							DIO_u8PIN2
#define ROOM2_PIN							DIO_u8PIN3
#define ROOM3_PIN							DIO_u8PIN4
#define ROOM4_PIN							DIO_u8PIN5
#define FAN_PIN								DIO_u8PIN3

#define SPI_ROOM1							0
#define SPI_ROOM2							1
#define SPI_ROOM3							2
#define SPI_ROOM4							3
#define SPI_FAN								5
#define SPI_RESET							6
#define SPI_ADMIN_PAGE						7
#define	SPI_GUEST_PAGE						8


#endif /* MAIN_CONFIG_H_ */
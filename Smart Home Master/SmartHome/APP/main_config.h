/*
 * main_config.h
 *
 * Created: 31-Dec-23 1:57:15 PM
 *  Author: MICHAEL
 */ 


#ifndef MAIN_CONFIG_H_
#define MAIN_CONFIG_H_


/* Delays */
#define LCD_CLR_DELAY						2000
#define USER_BLOCK_DELAY					20000
#define PASSWORD_HIDE_DELAY					300


/* Rooms Addresses in EEPROM */
#define ROOM1_ADDRESS						200
#define ROOM2_ADDRESS						201
#define ROOM3_ADDRESS						202
#define ROOM4_ADDRESS						203
#define FAN_ADDRESS							204
#define FAN_SPEED_ADDESS					205

/* SPI Rooms */
#define SPI_ROOM1							0
#define SPI_ROOM2							1
#define SPI_ROOM3							2
#define SPI_ROOM4							3
#define SPI_FAN								5
#define SPI_RESET							6
#define SPI_ADMIN_PAGE						7
#define	SPI_GUEST_PAGE						8


#endif /* MAIN_CONFIG_H_ */
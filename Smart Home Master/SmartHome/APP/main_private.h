/*
 * main_private.h
 *
 * Created: 02-Jan-24 9:51:52 AM
 *  Author: MICHAEL
 */ 


#ifndef MAIN_PRIVATE_H_
#define MAIN_PRIVATE_H_

/* EEPROM */
#define FIRST_LOGIN_ADDRESS					100
#define PASS_NOT_SET						0
#define PASS_SET							1


#define PASSWORD_DIGITS						4
#define PASSWORD_TRIES						3

#define RIGHT_PASSWORD						4
#define WRONG_PASSWORD						5

#define EEPROM_DEFAULT_ADDRESS				0xFF

/* Room Status*/
#define SWITCH_OFF							0
#define SWITCH_ON							1
#define FAN_CONTROL							2
#define RETURN								3

#define ADMIN_LOGIN_PAGE					0
#define GUEST_LOGIN_PAGE					1

#endif /* MAIN_PRIVATE_H_ */
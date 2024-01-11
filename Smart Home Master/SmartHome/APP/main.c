/*
 * SmartHome.c
 *
 * Created: 31-Dec-23 12:33:42 PM
 * Author : MICHAEL
 */ 
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <util/delay.h>
#include "main_config.h"
#include "main_private.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../HAL/CLCD/CLCD_interface.h"
#include "../HAL/KPD/KPD_interface.h"
#include "../MCAL/TWI/TWI_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/USART/USART_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/SPI/SPI_interface.h"


void firstLoginPage();
u8 loginMode(void);
u8 passwordCheck(u8 passArr[PASSWORD_DIGITS],u8 Copy_u8CopmareAddress);
void room_control(u8 *roomFlag,u8 Copy_u8RoomAddress);
void fan_control(u8 *fanFlag);
void room_status();
void guestPage();
void adminPage();


/* passCounter -> variable to make password 4 digits only */
u8 passCounter = 0;
u8 column=5;	// password position
u8 keyPressed;	//Keypad pressed key

int main(void)
{
	DIO_voidInit();
	CLCD_voidInit();
	KPD_voidInit();
	TWI_voidMasterInit(NO_ADDRESS);
	
	ADC_voidInit();
	SPI_voidInit();
	
	/* Welcome Home Screen*/
	CLCD_voidSendStringPosition("ITI",0,7);
	CLCD_voidSendStringPosition("SMART HOME",1,3);
	_delay_ms(LCD_CLR_DELAY);
	CLCD_voidClearDisplay();

    while (1) 
    {
	/* First time Login Page*/
		firstLoginPage();
	    /* loginMode Function returns the mode to be opened */
		u8 loginFlag=0,Local_u8LoginPageMode;
		while(loginFlag == 0)
		{
			/* First time Login Page*/
			firstLoginPage();
			Local_u8LoginPageMode = loginMode();
			switch(Local_u8LoginPageMode)
			{
				case ADMIN_LOGIN_PAGE:
					SPI_u8Transreceive(SPI_ADMIN_PAGE);
					/* adminPage function open Admin page*/
					 adminPage();
					break;
				case GUEST_LOGIN_PAGE:
					SPI_u8Transreceive(SPI_GUEST_PAGE);
					/* guestPage function open Guest page*/
					guestPage();
					break;	
				default:
					CLCD_voidClearDisplay();
					CLCD_voidSendString("Wrong Choice.");
					_delay_ms(LCD_CLR_DELAY);
					CLCD_voidClearDisplay();
					break;
			}
		} //End while(loginFlag==0)
		
	}	//End while(1)
}


/* Function to read address FIRST_LOGIN_ADDRESS -> (100) in EEPROM */	
void firstLoginPage(void)
{
	/* FIRST TIME LOGIN PAGE */
	/* 
	   firstLoginStatus -> status of login first time or not (0xFF,1) 
	   addresses that password will be saved (0,1,2,3)
	*/	
	u8 firstLoginStatus , address=0;
	passCounter=0;
	EEPROM_voidReadByte(&firstLoginStatus,FIRST_LOGIN_ADDRESS);
	/* Check if content of address 100 in EEPROM = 0xFF then this is first login time and then set password for the first time */
	if(firstLoginStatus != PASS_SET)
	{
		CLCD_voidSendString("Login for ");
		CLCD_voidSendStringPosition("First Time",1,0);
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
		column=12;
		CLCD_voidSendString("Set Admin Pass");
		CLCD_voidSendStringPosition("Admin Pass: ",1,0);
		/* This loop will exit after entering 4 numbers as Password is 4 digits only */
		while(passCounter<PASSWORD_DIGITS){
			keyPressed = NOT_PRESSED;
			while(keyPressed == NOT_PRESSED)	//repeat till the user press any key
			{
				keyPressed = KPD_u8GetPressedKey(); //get the user pressed button in keypad and save the value in keyPressed
			}
			/* Display keyPressed on LCD and after PASSWORD_HIDE_DELAY display '*' */
			CLCD_voidSendCharPosition(keyPressed,1,column);
			_delay_ms(PASSWORD_HIDE_DELAY);
			CLCD_voidSendCharPosition('*',1,column);
			column++;
	
			/* save Admin password in addresses from 0 -> 3 in EEPROM */
			EEPROM_voidWriteByte(keyPressed,address);
			address++;
			passCounter++;
		}
		
		passCounter=0;	address=4;	column=12;
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
		CLCD_voidSendString("Password Saved");
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
		CLCD_voidSendString("Set Guest Pass");
		CLCD_voidSendStringPosition("Guest Pass: ",1,0);
		while(passCounter<PASSWORD_DIGITS){
			keyPressed = NOT_PRESSED;
			while(keyPressed == NOT_PRESSED)	//repeat till the user press any key
			{
				keyPressed = KPD_u8GetPressedKey(); //get the user pressed button in keypad and save the value in keyPressed
			}
			/* Display keyPressed on LCD and after PASSWORD_HIDE_DELAY display '*' */
			CLCD_voidSendCharPosition(keyPressed,1,column);
			_delay_ms(PASSWORD_HIDE_DELAY);
			CLCD_voidSendCharPosition('*',1,column);
			column++;
			
			/* save Guest password in addresses from 4 -> 7 in EEPROM */
			EEPROM_voidWriteByte(keyPressed,address);
			address++;
			passCounter++;
		}	
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
		CLCD_voidSendString("Password Saved");
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();		
		
		/* Write PASS_SET(1) in address 100 in EEPROM to indicate status of password as it is set, then this page is not appeared again*/
		EEPROM_voidWriteByte(PASS_SET,FIRST_LOGIN_ADDRESS);

	}
	
}


/* return the login page (admin/guest)*/
u8 loginMode(void)
{		
	/* 
		AdminPassArr[4] -> array to add password entered by the user then compare with Admin password saved in EEPROM
		GuestPassArr[4] -> array to add password entered by the user then compare with Guest password saved in EEPROM
		loginFlag -> status of entered password 
	*/	
	u8 AdminPassArr[PASSWORD_DIGITS],GuestPassArr[PASSWORD_DIGITS],Local_u8LoginPageMode,loginFlag=WRONG_PASSWORD;
	/* LOGIN PAGE */
	while(loginFlag == WRONG_PASSWORD){
		/* MODE SELECTION */
		CLCD_voidClearDisplay();
		CLCD_voidSendString("Select Mode :");
		CLCD_voidSendStringPosition("0-Admin 1-Guest",1,0);
		keyPressed = NOT_PRESSED;
		while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
		{
			keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
		}
		
		switch(keyPressed)
		{
			case '0': //Admin
				/* Check for Admin password to login */
				loginFlag = passwordCheck(AdminPassArr,0);
				Local_u8LoginPageMode = ADMIN_LOGIN_PAGE;
				break;
			case '1': //Guest
				loginFlag = passwordCheck(GuestPassArr,4);
				Local_u8LoginPageMode = GUEST_LOGIN_PAGE;
				break;	
			default:	// if user press any other key
				CLCD_voidClearDisplay();
				CLCD_voidSendString("Wrong Choice.");
				_delay_ms(LCD_CLR_DELAY);
				CLCD_voidClearDisplay();
				break;	
		}
	}
	return Local_u8LoginPageMode;
}


/* Function to Check password */
u8 passwordCheck(u8 passArr[PASSWORD_DIGITS],u8 Copy_u8CopmareAddress)
{
	u8 loginFlag=WRONG_PASSWORD ,Local_u8CompareAddress;
	passCounter=0;
	while(loginFlag == WRONG_PASSWORD)
	{
			CLCD_voidClearDisplay();
			CLCD_voidSendString("Enter Password");
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8LOW);
			DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);
			column=5;	//password position
			/* Enter password to login */
			CLCD_voidMoveCursor(1,column);
			while(passCounter<PASSWORD_DIGITS){
				keyPressed = NOT_PRESSED;
				while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
				{
					keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
				}
				passArr[passCounter]=keyPressed;//add the entered character to the pass array
				CLCD_voidSendCharPosition(keyPressed,1,column);
				_delay_ms(PASSWORD_HIDE_DELAY);
				CLCD_voidSendCharPosition('*',1,column);
				column++;
				passCounter++;
			}
			passCounter = 0;
			/*
				compareVal-> value in EEPROM to be compared 
				compareArrIndx -> index of array that holds tha password
				compareAddress -> address to be compared with array elements
			*/
			u8 compareVal,compareArrIndx=0;
			/* compare with password saved in EEPROM */
			Local_u8CompareAddress = Copy_u8CopmareAddress;
			while(passCounter<PASSWORD_DIGITS){
 				EEPROM_voidReadByte(&compareVal,Local_u8CompareAddress);
				if(compareVal == passArr[compareArrIndx])
					passCounter++;
				else{
					passCounter = WRONG_PASSWORD;
				}
				compareArrIndx++; Local_u8CompareAddress++;
			}
			/* check if the loop exit for entering right password (passCounter = RIGHT_PASSWORD) or wrong password (passCounter = WRONG_PASSWORD) */
			if(passCounter == RIGHT_PASSWORD){
				_delay_ms(LCD_CLR_DELAY);
				CLCD_voidClearDisplay();
				CLCD_voidSendString("Right Password");
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8HIGH);	//TurnOn Green Led
				_delay_ms(LCD_CLR_DELAY);
				CLCD_voidClearDisplay();
				/* Change password flag to exit from login page and go to Rooms page*/
				loginFlag = RIGHT_PASSWORD;
				//DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN0,DIO_u8LOW);
				SPI_u8Transreceive(RIGHT_PASSWORD);
			}
			else if(passCounter == WRONG_PASSWORD)
			{
				static s8 passTries = PASSWORD_TRIES; // Number of tries is 3
				_delay_ms(LCD_CLR_DELAY);
				CLCD_voidClearDisplay();
				CLCD_voidSendString("Wrong Password");
				passTries--;
				SPI_u8Transreceive(WRONG_PASSWORD);	// Send WRONG_PASSWORD to turn on buzzer
				CLCD_voidMoveCursor(1,0);
				CLCD_voidSendString("Tries Left: ");	// display Number of Tries left for the user to enter password
				CLCD_voidSendNum(passTries);	
				_delay_ms(LCD_CLR_DELAY);
				loginFlag = WRONG_PASSWORD;	passCounter = 0;
				/* No tries left then the user will be blocked for 20 Sec */
				if(passTries == 0){
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8HIGH);	// TurnOn Red led
					CLCD_voidClearDisplay();
					CLCD_voidSendString("Block For 20 Second");
					/* delay for 20 sec to Block the user */
					_delay_ms(USER_BLOCK_DELAY);
					CLCD_voidClearDisplay();
					/* Then return to enter password another time */
					loginFlag = WRONG_PASSWORD;	passCounter = 0; passTries=PASSWORD_TRIES;
				}
			}			
		}	// End LOGIN PAGE		

	return loginFlag;
}


/* Function to control every Room */
void room_control(u8 *roomFlag,u8 Copy_u8RoomAddress)
{
	u8 keyPressed;
	/* Read Status of the room from its address in EEPROM */
	u8 Local_u8RoomStatus;
	EEPROM_voidReadByte(&Local_u8RoomStatus,Copy_u8RoomAddress);
	switch(Copy_u8RoomAddress)
	{
		case ROOM1_ADDRESS: CLCD_voidClearDisplay(); CLCD_voidSendString("Room1 S:"); break;
		case ROOM2_ADDRESS: CLCD_voidClearDisplay(); CLCD_voidSendString("Room2 S:"); break;
		case ROOM3_ADDRESS: CLCD_voidClearDisplay(); CLCD_voidSendString("Room3 S:"); break;
		case ROOM4_ADDRESS: CLCD_voidClearDisplay(); CLCD_voidSendString("Room4 S:"); break;
	}
	/* in case of 0 -> S: OFF , in case of 1 -> S:ON*/
	if(Local_u8RoomStatus == SWITCH_OFF || Local_u8RoomStatus == EEPROM_DEFAULT_ADDRESS)
	{
		CLCD_voidSendString("OFF");
	}
	else if(Local_u8RoomStatus == SWITCH_ON)
	{
		CLCD_voidSendString("ON");
	}
	CLCD_voidSendStringPosition("1-ON 2-OFF 0-RET",1,0);
	keyPressed = NOT_PRESSED;
	while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
	{
		keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
	}
	/* Choose ON(1) or OFF(2) or Return to Rooms menu(0)*/
	switch(keyPressed)
	{
		case '1':	// Switch_ON
			EEPROM_voidWriteByte(SWITCH_ON,Copy_u8RoomAddress);	// Write status 1 in Room address in EEPROM
			*roomFlag = 1;
			//DIO_u8SetPinValue(Copy_u8RoomPort,Copy_u8RoomPin,DIO_u8HIGH);	
			SPI_u8Transreceive(SWITCH_ON);
			break;
		case '2':	// Switch_OFF
			EEPROM_voidWriteByte(SWITCH_OFF,Copy_u8RoomAddress); // Write status 0 in Room address in EEPROM
			*roomFlag = 1;
			//DIO_u8SetPinValue(Copy_u8RoomPort,Copy_u8RoomPin,DIO_u8LOW);
			SPI_u8Transreceive(SWITCH_OFF);
			break;
		case '0':	// Return to Rooms Page
			SPI_u8Transreceive(RETURN);
			*roomFlag = 1;
			break;
		default:	// if user press any other key
			CLCD_voidClearDisplay();
			CLCD_voidSendString("Wrong Choice.");
			_delay_ms(LCD_CLR_DELAY);
			break;
	}
}


/* Function to control Fan using Potentiometer*/
void fan_control(u8 *fanFlag)
{
	u16 Local_u16FanSpeed;
	u8 Local_u8FanStatus;
	/* Read Status of the Fan from its address (FAN_ADDRESS) in EEPROM */
	EEPROM_voidReadByte(&Local_u8FanStatus,FAN_ADDRESS);
	
	CLCD_voidClearDisplay();
	
	/* in case of 0 -> S: OFF , in case of 1 -> S:ON*/
	CLCD_voidSendString("Fan S:");
	if(Local_u8FanStatus == SWITCH_OFF || Local_u8FanStatus == EEPROM_DEFAULT_ADDRESS)
	{
		CLCD_voidSendString("OFF");
	}
	else if(Local_u8FanStatus == SWITCH_ON)
	{
		CLCD_voidSendString("ON");
	}
	
	CLCD_voidSendStringPosition("0-RET ",0,11);
	CLCD_voidSendStringPosition("1-CONTROL 2-OFF",1,0);
	keyPressed = NOT_PRESSED;
	while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
	{
		keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
	}
	/* Choose CONTROL(1) or OFF(2) or Return(0)*/
	switch(keyPressed)
	{
		case '1':	// CONTROL
			SPI_u8Transreceive(FAN_CONTROL);	
			EEPROM_voidWriteByte(SWITCH_ON,FAN_ADDRESS); // Write status SWITCH_ON(1) in Fan address in EEPROM
			
			break;
		
		case '2':	// Switch_OFF
			SPI_u8Transreceive(SWITCH_OFF);
			EEPROM_voidWriteByte(SWITCH_OFF,FAN_ADDRESS);	// Write status SWITCH_OFF0 in Fan address in EEPROM
			*fanFlag = 1;
			break;
		case '0':	//Return
			SPI_u8Transreceive(RETURN);
			*fanFlag = 1;
			break;
		
		default: // if user press any other key
			CLCD_voidClearDisplay();
			CLCD_voidSendString("Wrong Choice.");
			_delay_ms(LCD_CLR_DELAY);
			break;
	}
}


void guestPage()
{
		TWI_voidStop(); // STOP TWI
		CLCD_voidSendString("Choose Room ");
		CLCD_voidSendStringPosition("to Control",1,6);
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
		
		/* ROOMS PAGE*/
		u8 RoomsFlag = 0;
		while(RoomsFlag == 0)
		{
			CLCD_voidClearDisplay();
			CLCD_voidSendStringPosition("1:Room1  2:Room2",0,0);
			CLCD_voidSendStringPosition("3:Room3  4:Room4",1,0);
			keyPressed = NOT_PRESSED;
			while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
			{
				keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
			}		
			switch(keyPressed)	
			{
				case '1':	//Room1
					CLCD_voidClearDisplay();
					u8 room1Flag=0;
					while (room1Flag == 0)
					{
						/*  room1Flag -> Room1 Flag and return as a pointer to exit from loop */
						SPI_u8Transreceive(SPI_ROOM1);
						room_control(&room1Flag,ROOM1_ADDRESS);	//Room1 Control Page
					}
				break; 
				
				case '2':	//Room2
					CLCD_voidClearDisplay();
					u8 room2Flag=0;
					while (room2Flag == 0)
					{
						/*  room2Flag -> Room2 Flag and return as a pointer to exit from loop */	
						SPI_u8Transreceive(SPI_ROOM2);
						room_control(&room2Flag,ROOM2_ADDRESS);	//Room2 Control Page
					}				
				break;
				case '3':  //Room3
					CLCD_voidClearDisplay();
					u8 room3Flag=0;
					while (room3Flag == 0)
					{
						/*  room3Flag -> Room3 Flag and return as a pointer to exit from loop */
						SPI_u8Transreceive(SPI_ROOM3);
						room_control(&room3Flag,ROOM3_ADDRESS);	//Room3 Control Page
					}			
				break;
				case '4':	//Room4
					CLCD_voidClearDisplay();
					u8 room4Flag=0;
					while (room4Flag == 0)
					{
						/*  room4Flag -> Room4 Flag and return as a pointer to exit from loop */	
						SPI_u8Transreceive(SPI_ROOM4);
						room_control(&room4Flag,ROOM4_ADDRESS);	//Room4 Control Page
					}			
				break;
				case 'C':	//Return to mode selection page
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);	//TurnOff Green Led
					SPI_u8Transreceive(SPI_RESET);
					RoomsFlag = 1;	
					break;
					
				default: // if user press any other key 
					CLCD_voidClearDisplay();
					CLCD_voidSendString("Wrong Choice.");
					_delay_ms(LCD_CLR_DELAY);
				break;		
			}
		}	//End ROOM PAGE	
}


void adminPage()
{
		TWI_voidStop(); // STOP TWI
		CLCD_voidSendString("Choose Room ");
		CLCD_voidSendStringPosition("to Control",1,6);
		_delay_ms(LCD_CLR_DELAY);
		CLCD_voidClearDisplay();
	
		/* ROOMS PAGE*/
		u8 RoomsFlag1 = 0,RoomsFlag2 = 1;
		while(RoomsFlag1 == 0)
		{
			CLCD_voidClearDisplay();
			CLCD_voidSendStringPosition("1:Room1  2:Room2",0,0);
			CLCD_voidSendStringPosition("3:Room3  4:More",1,0);
			keyPressed = NOT_PRESSED;
			while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
			{
				keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
			}		
			switch(keyPressed)	
			{
				case '1':	//Room1
					CLCD_voidClearDisplay();
					u8 room1Flag=0;
					while (room1Flag == 0)
					{
						/*  room1Flag -> Room1 Flag and return as a pointer to exit from loop */
						SPI_u8Transreceive(SPI_ROOM1);
						room_control(&room1Flag,ROOM1_ADDRESS);	//Room1 Control Page
					}
				break; 
				
				case '2':	//Room2
					CLCD_voidClearDisplay();
					u8 room2Flag=0;
					while (room2Flag == 0)
					{
						/*  room2Flag -> Room2 Flag and return as a pointer to exit from loop */
						SPI_u8Transreceive(SPI_ROOM2);	//Room2
						room_control(&room2Flag,ROOM2_ADDRESS);	//Room2 Control Page
					}				
				break;
				case '3':  //Room3
					CLCD_voidClearDisplay();
					u8 room3Flag=0;
					while (room3Flag == 0)
					{
						/*  room3Flag -> Room3 Flag and return as a pointer to exit from loop */
						SPI_u8Transreceive(SPI_ROOM3);	//Room2
						room_control(&room3Flag,ROOM3_ADDRESS);	//Room3 Control Page
					}			
				break;
				case '4':	//More
					RoomsFlag2 = 0;
					//ROOM PAGE 2
					while(RoomsFlag2 == 0)
					{
						CLCD_voidClearDisplay();
						CLCD_voidSendStringPosition("1:Room4	   2:Fan",0,0);
						CLCD_voidSendStringPosition("3:Reset	   4:Ret",1,0);
						keyPressed = NOT_PRESSED;
						while (keyPressed == NOT_PRESSED)	//repeat till the user press any key
						{
							keyPressed = KPD_u8GetPressedKey();		//if the user pressed any button in keypad save the value in keyPressed
						}		
						switch(keyPressed)	
						{
							case '1':	//Room4
								CLCD_voidClearDisplay();
								u8 room4Flag=0;
								while (room4Flag == 0)
								{
									/*  room4Flag -> Room4 Flag and return as a pointer to exit from loop */
									SPI_u8Transreceive(SPI_ROOM4);	//Room4
									room_control(&room4Flag,ROOM4_ADDRESS);	//Room4 Control Page
								}
							break; 
							
							case '2':	//Fan
								CLCD_voidClearDisplay();
								u8 fanFlag=0;  
								SPI_u8Transreceive(SPI_FAN);	//FAN
								while (fanFlag == 0)
								{
									fan_control(&fanFlag);
								}

							break;
							case '3':	//Reset Pass
								SPI_u8Transreceive(SPI_RESET);	
								EEPROM_voidWriteByte(PASS_NOT_SET,FIRST_LOGIN_ADDRESS);
								DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);	//TurnOff Green Led
								RoomsFlag2=1;
								RoomsFlag1=1;
								CLCD_voidClearDisplay();
							break;
							
							case '4':	//Return
								RoomsFlag2 = 1;
								break;
							case 'C':	//return to mode selection page
								DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);	//TurnOff Green Led
								SPI_u8Transreceive(SPI_RESET);
								RoomsFlag2 = 1;
								RoomsFlag1 = 1;
							break;							
							default: // if user press any other key 
								CLCD_voidClearDisplay();
								CLCD_voidSendString("Wrong Choice.");
								_delay_ms(LCD_CLR_DELAY);
							break;		
						} // End switch
					}	//End while(RoomsFlag2 == 1)		
					
				break;
				case 'C':	//return to mode selection page
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);	//TurnOff Green Led
					SPI_u8Transreceive(SPI_RESET);
					RoomsFlag1 = 1;
					break;
				default: // if user press any other key 
					CLCD_voidClearDisplay();
					CLCD_voidSendString("Wrong Choice.");
					_delay_ms(LCD_CLR_DELAY);
				break;		
			}
		}	//End ROOM PAGE 1	
}




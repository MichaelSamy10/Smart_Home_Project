/*
 * Smart_Home_Slave.c
 *
 * Created: 04-Jan-24 6:49:32 PM
 * Author : MICHAEL
 */ 
#include "../LIB/STD_TYPES.h"
#include "../LIB/BIT_MATH.h"
#include <util/delay.h>

#include "main_config.h"
#include "main_private.h"

#include "../MCAL/DIO/DIO_interface.h"
#include "../MCAL/TWI/TWI_interface.h"
#include "../HAL/EEPROM/EEPROM_interface.h"
#include "../MCAL/SPI/SPI_interface.h"
#include "../MCAL/TIMER0/TIMER0_interface.h"
#include "../MCAL/ADC/ADC_interface.h"
#include "../MCAL/GIE/GIE_interface.h"


void room_status();
void room_control(u8 Copy_u8RoomPort,u8 Copy_u8RoomPin);
void fan_control();
void adminPage();
void guestPage();
void reset();
void fan_check();


u8 keyPressed , fanControlFlag;
u8 fanFlag =0;

int main(void)
{
	DIO_voidInit();
	TIMER0_voidInit();
	ADC_voidInit();
	SPI_voidInit();
	GIE_voidEnable();
	TWI_voidMasterInit(NO_ADDRESS);

	
u8 loginFlag=0,Local_u8LoginPageMode;

    while (1) 
    {
		while(loginFlag == 0)
		{
			/* check for saved password */
			u8 password_check = WRONG_PASSWORD;
			while(password_check == WRONG_PASSWORD)
			{
				password_check = SPI_u8Transreceive(0);
				if(password_check == WRONG_PASSWORD)
				{
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8HIGH);	// TurnON Buzzer
					_delay_ms(500);
					DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN6,DIO_u8LOW);	// TurnOFF Buzzer
				}
			}
		 /* the mode to be opened */
			Local_u8LoginPageMode = SPI_u8Transreceive(0);
			switch(Local_u8LoginPageMode)
			{
				case SPI_ADMIN_PAGE: //Admin
					/* Check for Admin password to login */
						adminPage();
						break;
				case SPI_GUEST_PAGE: //Guest
						guestPage();
					break;
			}
		}
	}
}

/* Function to read last status of every Room when opening Rooms Page*/
void room_status()
{
	u8 Local_u8Room1Status,Local_u8Room2Status,Local_u8Room3Status,Local_u8Room4Status,Local_u8FanStatus;
	EEPROM_voidReadByte(&Local_u8Room1Status,ROOM1_ADDRESS);
	EEPROM_voidReadByte(&Local_u8Room2Status,ROOM2_ADDRESS);
	EEPROM_voidReadByte(&Local_u8Room3Status,ROOM3_ADDRESS);
	EEPROM_voidReadByte(&Local_u8Room4Status,ROOM4_ADDRESS);
	EEPROM_voidReadByte(&Local_u8FanStatus,FAN_ADDRESS);

	if(Local_u8Room1Status == SWITCH_ON) DIO_u8SetPinValue(ROOM1_PORT,ROOM1_PIN,DIO_u8HIGH);
	if(Local_u8Room2Status == SWITCH_ON) DIO_u8SetPinValue(ROOM2_PORT,ROOM2_PIN,DIO_u8HIGH);
	if(Local_u8Room3Status == SWITCH_ON) DIO_u8SetPinValue(ROOM3_PORT,ROOM3_PIN,DIO_u8HIGH);
	if(Local_u8Room4Status == SWITCH_ON) DIO_u8SetPinValue(ROOM4_PORT,ROOM4_PIN,DIO_u8HIGH);
	if(Local_u8FanStatus == SWITCH_ON)
	{
		u16 Local_u16FanSpeed = ADC_u16ReadChannel(CHANNEL_0);
		TIMER0_voidStart();
		TIMER0_voidSetCompareValue(Local_u16FanSpeed/4);
	}
		
}


/* Function to control every Room */
void room_control(u8 Copy_u8RoomPort,u8 Copy_u8RoomPin)
{
	u8 roomFlag =0;	
	u8 keyPressed ;
		while(roomFlag == 0)
		{
			keyPressed = SPI_u8Transreceive(0);
			/* Choose ON(1) or OFF(2) or Return to Rooms menu(0)*/
			switch(keyPressed)
			{
				case SWITCH_ON:	// Switch_ON
					DIO_u8SetPinValue(Copy_u8RoomPort,Copy_u8RoomPin,DIO_u8HIGH);
					roomFlag=1;
					break;
				case SWITCH_OFF: // Switch_OFF
					DIO_u8SetPinValue(Copy_u8RoomPort,Copy_u8RoomPin,DIO_u8LOW);
					roomFlag=1;
					break;
				case RETURN: // Return
					roomFlag=1;
					break;
					
				}
		}
}

/* Function to control Fan */
void fan_control()
{
	u16 Local_u16FanSpeed;
	fanFlag=0;
	while(fanFlag == 0)
	{
		keyPressed = SPI_u8Transreceive(0);
		/* Choose FAN_CONTROL(1) or OFF(2) or Return to Rooms menu(0)*/
		switch(keyPressed)
		{
			case FAN_CONTROL:	// Fan_Control
				fanControlFlag=0;
				/*CallBack Function*/
				SPI_voidCallBack(fan_check);
				TIMER0_voidStart();
				/*Enable interrupt*/
				SPI_voidEnableInterrupt();
				while(fanControlFlag == 0)
				{
					/* Read fan speed from Potentiometer using ADC Channel 0*/
					Local_u16FanSpeed = ADC_u16ReadChannel(CHANNEL_0);
					TIMER0_voidSetCompareValue(Local_u16FanSpeed/4);
				}
				break;
			case SWITCH_OFF: // Switch_OFF
				DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8HIGH);	//TurnOff ROOM1
				TIMER0_voidSetCompareValue(SWITCH_OFF);
				fanFlag=1;
				break;
			case RETURN: // return
				fanFlag=1;
				break;
		}
	}		
}


void adminPage()
{
		_delay_ms(700);
		room_status();
		
		TWI_voidStop(); //Stop TWI 
		/* ROOMS PAGE*/
		u8 RoomsFlag = 0;
		while(RoomsFlag == 0)
		{
			u8 keyPressed = SPI_u8Transreceive(0);
			u8 room1Flag=0;
			u8 room2Flag=0;
			u8 room3Flag=0;
			u8 room4Flag=0;
			u8 fanFlag=0;

			switch(keyPressed)	
			{
				case SPI_ROOM1:	//Room1
					while (room1Flag == 0)
					{
						/*  room1Flag -> Room1 Flag to exit from this page */
						room_control(ROOM1_PORT,ROOM1_PIN);	//Room1 Control
						room1Flag=1;
					}
					break; 
				
				case SPI_ROOM2:	//Room2
			 		while (room2Flag == 0)
					{		
						/*  room2Flag -> Room2 Flag to exit from this page */
						room_control(ROOM2_PORT,ROOM2_PIN);	//Room2 Control Page
						room2Flag=1;		
					}				
					break;
					
				case SPI_ROOM3:  //Room3
					while (room3Flag == 0)
					{
						/*  room3Flag -> Room3 Flag to exit from this page */
						room_control(ROOM3_PORT,ROOM3_PIN);	//Room3 Control Page
						room3Flag = 1;
					}			
					break;
					
				case SPI_ROOM4:  //Room4
					while (room4Flag == 0)
					{
						/*  room4Flag -> Room4 Flag to exit from this page */
						room_control(ROOM4_PORT,ROOM4_PIN);	//Room4 Control Page
						room4Flag = 1;
					}			
					break;
							
				case SPI_FAN:	//Fan
					while (fanFlag == 0)
					{
						/*  fanFlag -> Fan Flag to exit from this page */
						 fan_control();
						 fanFlag=1;
					}

				break;
				
				case SPI_RESET:
					/* Switch off all Rooms*/
					reset();
					RoomsFlag=1;
					break;	
			} // End switch
				
			
		}	//End ROOM PAGE 1	
}

void guestPage()
{
	_delay_ms(700);
	room_status();
	
	TWI_voidStop(); //Stop TWI
	/* ROOMS PAGE*/
	u8 RoomsFlag = 0;
	while(RoomsFlag == 0)
	{
		u8 keyPressed = SPI_u8Transreceive(0);
		u8 room1Flag=0;
		u8 room2Flag=0;
		u8 room3Flag=0;
		u8 room4Flag=0;

		switch(keyPressed)
		{
			case SPI_ROOM1:	//Room1
				while (room1Flag == 0)
				{
					/*  room1Flag -> Room1 Flag to exit from this page */
					room_control(ROOM1_PORT,ROOM1_PIN);	//Room1 Control
					room1Flag=1;
				}
				break;
			
			case SPI_ROOM2:	//Room2
				while (room2Flag == 0)
				{
					/*  room2Flag -> Room2 Flag to exit from this page */
					room_control(ROOM2_PORT,ROOM2_PIN);	//Room2 Control Page
					room2Flag=1;
				}
				break;
			case SPI_ROOM3:  //Room3
				while (room3Flag == 0)
				{
					/*  room3Flag -> Room3 Flag to exit from this page */
					room_control(ROOM3_PORT,ROOM3_PIN);	//Room3 Control Page
					room3Flag = 1;
				}
				break;
			case SPI_ROOM4:  //Room4
				while (room4Flag == 0)
				{
					/*  room4Flag -> Room4 Flag to exit from this page */
					room_control(ROOM4_PORT,ROOM4_PIN);	//Room4 Control Page
					room4Flag = 1;
				}
				break;
			
			case SPI_RESET:
				RoomsFlag=1;
				break;
		} // End switch
		
		
	}	//End ROOM PAGE 1
}

void reset()
{
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN2,DIO_u8LOW);	//TurnOff ROOM1
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN3,DIO_u8LOW);	//TurnOff ROOM2
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN4,DIO_u8LOW);	//TurnOff ROOM3
	DIO_u8SetPinValue(DIO_u8PORTC,DIO_u8PIN5,DIO_u8LOW);	//TurnOff ROOM4
	TIMER0_voidSetCompareValue(SWITCH_OFF);					//TurnOff FAN
}


void fan_check()
{

	u8 data = SPI_u8ReceiveAsynch();
	if(data == SWITCH_OFF){
		_delay_ms(100);
		TIMER0_voidSetCompareValue(0);
		_delay_ms(100);
		TIMER0_voidStop();
		fanControlFlag =1;
		fanFlag=1;
	}

	SPI_voidDisableInterrupt();
}
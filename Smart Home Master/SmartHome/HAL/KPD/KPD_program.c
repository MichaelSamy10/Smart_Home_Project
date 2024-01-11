/*
 * KPD_program.c
 *
 * Created: 11-Dec-23 12:01:04 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <avr/delay.h>

#include "../../MCAL/DIO/DIO_interface.h"

#include "KPD_config.h"
#include "KPD_interface.h"
#include "KPD_private.h"


void KPD_voidInit()
{
	/* Activate Pull-up for rows, and init the columns with high */
	DIO_u8SetPortValue(KPD_PORT,DIO_u8ALL_HIGH);
	
}

u8 KPD_u8GetPressedKey(void)
{
	u8 Local_u8KPDMappedArr[4][4]= { 
		{ '7'  , '8' , '9' , '/' },
		{ '4'  , '5' , '6' , '*' },
		{ '1'  , '2' , '3' , '-' },
		{ 'C' , '0' , '=' , '+' }		
	};
	
	u8 Local_u8Key = NOT_PRESSED;
	u8 Local_u8PinValue;
	
	for(u8 Col=0;Col<4;Col++)
	{
		DIO_u8SetPinValue(KPD_PORT,Col,DIO_u8LOW);
		
		for(u8 Row=0;Row<4;Row++)
		{
			/* (Row+4) for reading higher bits in Port */ 
			DIO_u8GetPinValue(KPD_PORT,Row + 4,&Local_u8PinValue);
			if(Local_u8PinValue == 0)
			{
				Local_u8Key = Local_u8KPDMappedArr[Row][Col];
				_delay_ms(3);
				while(Local_u8PinValue == 0)
				{
					DIO_u8GetPinValue(KPD_PORT,Row + 4,&Local_u8PinValue);
				}			
			}
		}
		DIO_u8SetPinValue(KPD_PORT,Col,DIO_u8HIGH);
	}
	return Local_u8Key;
}

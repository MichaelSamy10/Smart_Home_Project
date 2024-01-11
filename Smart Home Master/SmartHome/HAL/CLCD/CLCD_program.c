/*
 * CLCD_program.c
 *
 * Created: 10-Dec-23 11:47:51 AM
 *  Author: MICHAEL
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"
#include <avr/delay.h>
#include "../../MCAL/DIO/DIO_interface.h"

#include "CLCD_interface.h"
#include "CLCD_config.h"
#include "CLCD_private.h"


void CLCD_voidSendCommand(u8 copy_u8Command)
{
	/* RS = 0 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8LOW);
	/* RW = 0 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8LOW);
	
	#if (CLCD_MODE == EIGHT_BIT)
		/* Send Command */
		DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Command);
		
		/* Enable */
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);

		/* delay */
		_delay_ms(2);

		/* Disable */
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW);	
	
	#else
		
		///*Sending the higher nibble*/
		DIO_u8SetPinValue(CLCD_DATA_PORT, D4_ID, GET_BIT(copy_u8Command, DIO_u8PIN4));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D5_ID, GET_BIT(copy_u8Command, DIO_u8PIN5));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D6_ID, GET_BIT(copy_u8Command, DIO_u8PIN6));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D7_ID, GET_BIT(copy_u8Command, DIO_u8PIN7));
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);
		
		_delay_ms(1);
		/*Sending the lower nibble*/
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW); /*Falling edge to perform the instruction*/
		
		DIO_u8SetPinValue(CLCD_DATA_PORT, D4_ID, GET_BIT(copy_u8Command, DIO_u8PIN0));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D5_ID, GET_BIT(copy_u8Command, DIO_u8PIN1));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D6_ID, GET_BIT(copy_u8Command, DIO_u8PIN2));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D7_ID, GET_BIT(copy_u8Command, DIO_u8PIN3));
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);
		_delay_ms(2);

		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW); /*Falling edge to perform the instruction*/
		
		#endif

}

void CLCD_voidSendCharacter(u8 copy_u8Char)
{
	/* RS = 1 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RS_PIN,DIO_u8HIGH);
	/* RW = 0 */
	DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_RW_PIN,DIO_u8LOW);
	
	#if (CLCD_MODE == EIGHT_BIT)
		/* Send Data */
		DIO_u8SetPortValue(CLCD_DATA_PORT,copy_u8Char);
		
		/* Enable */
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);
		/* delay */
		_delay_ms(2);
		
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW);
	#else
		/*Sending the higher nibble*/
		DIO_u8SetPinValue(CLCD_DATA_PORT, D4_ID, GET_BIT(copy_u8Char, DIO_u8PIN4));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D5_ID, GET_BIT(copy_u8Char, DIO_u8PIN5));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D6_ID, GET_BIT(copy_u8Char, DIO_u8PIN6));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D7_ID, GET_BIT(copy_u8Char, DIO_u8PIN7));
	
		/* Enable */
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);
		/* delay */
		_delay_ms(1);
		
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW);
		
		/*Sending the lower nibble*/
		DIO_u8SetPinValue(CLCD_DATA_PORT, D4_ID, GET_BIT(copy_u8Char, DIO_u8PIN0));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D5_ID, GET_BIT(copy_u8Char, DIO_u8PIN1));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D6_ID, GET_BIT(copy_u8Char, DIO_u8PIN2));
		DIO_u8SetPinValue(CLCD_DATA_PORT, D7_ID, GET_BIT(copy_u8Char, DIO_u8PIN3));
		/* Enable */
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8HIGH);
		/* delay */
		_delay_ms(2);
			
		DIO_u8SetPinValue(CLCD_CTRL_PORT,CLCD_E_PIN,DIO_u8LOW);
		#endif
	
	
}

void CLCD_voidInit(void)
{
	_delay_ms(35);
	
	#if (CLCD_MODE == EIGHT_BIT)
		/* Function set (8 bits mode ,2 lines , 5*7) */
		CLCD_voidSendCommand(0b00111000);
		/* Display ON/OFF  */
		CLCD_voidSendCommand(DISPLAY_CURSOR);
		/* Clear display  */
		CLCD_voidSendCommand(0b00000001);

		
	#else
		/* Function set (4 bits mode ,2 lines , 5*7) */
		CLCD_voidSendCommand(0b00000010);
		CLCD_voidSendCommand(0b00101000);
		/* Display ON/OFF  */
		CLCD_voidSendCommand(DISPLAY_CURSOR);
		
		/* Clear display  */
		CLCD_voidSendCommand(0b0000001);
		_delay_ms(1);
		
	#endif
}

void CLCD_voidSendString(char *copy_pcString)
{
	u8 Local_u8Iterator=0;
	while ( copy_pcString[Local_u8Iterator] != '\0')
	{
		CLCD_voidSendCharacter(copy_pcString[Local_u8Iterator]);
		Local_u8Iterator++;
	}
}

void CLCD_voidClearDisplay(void)
{
	#if CLCD_MODE == EIGHT_BIT
		CLCD_voidSendCommand(0b00000001);	
	#else
		CLCD_voidSendCommand(0b0000001);
		_delay_ms(1);
	#endif
}

void CLCD_voidMoveCursor(u8 copy_u8Row, u8 copy_u8Col)
{
		u8 Local_u8Address = copy_u8Col + copy_u8Row*(0x40);
		SET_BIT(Local_u8Address,7);
		CLCD_voidSendCommand(Local_u8Address);
}

void CLCD_voidSendNum(s32 copy_u8Num)
{
	u8 Local_u8Digits[10],flag=0;
	s8 i=0;
	
	if(copy_u8Num == 0){
		CLCD_voidSendCharacter('0');
	}
	if(copy_u8Num < 0){
		copy_u8Num = copy_u8Num * -1;
		flag = 1;
	}
	while(copy_u8Num != 0)
	{
		Local_u8Digits[i] = copy_u8Num % 10;
		copy_u8Num = copy_u8Num / 10;
		i++;
	}
	i--;

	if(flag == 1){
		CLCD_voidSendCharacter('-');
	}

	while(i >=0 )
	{
		CLCD_voidSendCharacter(Local_u8Digits[i]+'0');
		i--;
	}

}

void CLCD_Custom_Char(u8 loc, u8 *msg)
{
    u8 i;
    if(loc<8)
    {
     CLCD_voidSendCommand(0x40 + (loc*8));  /* Command 0x40 and onwards forces the device to point CGRAM address */
       for(i=0;i<8;i++)  /* Write 8 byte for generation of 1 character */
           CLCD_voidSendCharacter(msg[i]);      
    }   
		/* Return cursor to home*/
		CLCD_voidSendCommand(0x80);
	
}

void CLCD_voidCursorShift(u8 copy_u8CursorDir)
{
	switch(copy_u8CursorDir)
	{
		case 0:	CLCD_voidSendCommand(0b00010000); break;
		case 1:	CLCD_voidSendCommand(0b00010100); break;
		case 2:	CLCD_voidSendCommand(0b00011000); break;
		case 3:	CLCD_voidSendCommand(0b00011100); break;
		
	}
	
}



void CLCD_voidSendCharPosition(u8 copy_u8Char,u8 copy_u8Row, u8 copy_u8Col)
{
	/* Set cursor poisiton */
	CLCD_voidMoveCursor(copy_u8Row,copy_u8Col);
	CLCD_voidSendCharacter(copy_u8Char);
	
}



void CLCD_voidSendNumPosition(s32 copy_u8Num,u8 copy_u8Row, u8 copy_u8Col)
{
	/* Set cursor poisiton */
	CLCD_voidMoveCursor(copy_u8Row,copy_u8Col);
	CLCD_voidSendNum(copy_u8Num);
	
}

void CLCD_voidSendStringPosition(char *copy_pcString,u8 copy_u8Row, u8 copy_u8Col)
{
	CLCD_voidMoveCursor(copy_u8Row,copy_u8Col);
	CLCD_voidSendString(copy_pcString);
}
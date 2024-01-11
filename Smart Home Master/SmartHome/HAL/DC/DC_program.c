/*
 * DC_program.c
 *
 * Created: 12-Dec-23 10:15:31 AM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"
#include "../../MCAL/DIO/DIO_interface.h"

#include "DC_config.h"
#include "DC_interface.h"
#include "DC_private.h"


void DC_voidRotateCW(void)
{
	DIO_u8SetPinValue(DC_PORT,DC_PIN0,DIO_u8LOW);
	DIO_u8SetPinValue(DC_PORT,DC_PIN1,DIO_u8HIGH);
	
}

void DC_voidRotateACW(void)
{
	DIO_u8SetPinValue(DC_PORT,DC_PIN1,DIO_u8LOW);
	DIO_u8SetPinValue(DC_PORT,DC_PIN0,DIO_u8HIGH);
	
}

void DC_voidStop(void)
{
	DIO_u8SetPinValue(DC_PORT,DC_PIN0,DIO_u8LOW);
	DIO_u8SetPinValue(DC_PORT,DC_PIN1,DIO_u8LOW);
	
}


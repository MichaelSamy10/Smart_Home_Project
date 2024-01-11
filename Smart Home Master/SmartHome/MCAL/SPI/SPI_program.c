/*
 * SPI_program.c
 *
 * Created: 24-Dec-23 9:18:19 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "../DIO/DIO_interface.h"

#include "SPI_register.h"
#include "SPI_config.h"
#include "SPI_interface.h"
#include "SPI_private.h"


void SPI_voidInit()
{
	SET_BIT(SPCR,MSTR);
	#if SCK_FREQUENCY == CLOCK_RATE_4
		CLR_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
	#elif SCK_FREQUENCY == CLOCK_RATE_16
		SET_BIT(SPCR,SPR0);
		CLR_BIT(SPCR,SPR1);
		CLR_BIT(SPSR,SPI2X);
	#endif
	
	
	SET_BIT(SPCR,SPE);

}

u8 SPI_u8Transreceive(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while( (GET_BIT(SPSR,SPIF)) != 1);
	return SPDR;
	
}


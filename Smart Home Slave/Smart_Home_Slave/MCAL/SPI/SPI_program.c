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


void(*GlobalSpiPtrFunc)(void) = NULL;


void SPI_voidInit()
{
	CLR_BIT(SPCR,MSTR);


	/* Enable SPI */
	SET_BIT(SPCR,SPE);

}

u8 SPI_u8Transreceive(u8 Copy_u8Data)
{
	SPDR = Copy_u8Data;
	while( GET_BIT(SPSR,SPIF) != 1);
	return SPDR;
	
}


void SPI_voidTransmitAsynch(u8 Copy_u8Data,void(*PtrFunc)(void))
{
	SET_BIT(SPCR,SPIE);
	SPDR = Copy_u8Data;
	GlobalSpiPtrFunc = PtrFunc;
	
}

u8 SPI_u8ReceiveAsynch()
{
	return SPDR;
}

void SPI_voidCallBack(void(*PtrFunc)(void)){
	GlobalSpiPtrFunc = PtrFunc;
}

void SPI_voidEnableInterrupt()
{
	SET_BIT(SPCR,SPIE);
}

void SPI_voidDisableInterrupt()
{
	CLR_BIT(SPCR,SPIE);
}

/* SPI ISR */
void __vector_12(void)__attribute__((signal));

void __vector_12(void){
		GlobalSpiPtrFunc();
}
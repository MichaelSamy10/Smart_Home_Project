/*
 * GIE_program.c
 *
 * Created: 13-Dec-23 2:59:48 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "GIE_interface.h"
#include "GIE_register.h"


void GIE_voidEnable(void)
{
	SET_BIT(SREG,7);
}

void GIE_voidDisable(void)
{
	CLR_BIT(SREG,7);	
}
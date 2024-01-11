/*
 * WDT_program.c
 *
 *  Created on: Dec 21, 2023
 *      Author: MICHAEL
 */

#include "../../LIB/STD_TYPES.h"
#include "../../LIB/BIT_MATH.h"

#include "WDT_register.h"
#include "WDT_private.h"
#include "WDT_interface.h"
#include "WDT_config.h"




void WDT_voidEnable()
{
	SET_BIT(WDTCR,WDE);
}

void WDT_voidDisable()
{
	/* critical section */
	GIE_voidDisable();
	WDTCR = (1<<WDTOE) | (1<<WDE);
	WDTCR = 0;
	GIE_voidEnable();
}

void WDT_voidSleep(u8 Copy_u8Time)
{
	WDTCR &= 0b11111000;
	WDTCR |= Copy_u8Time;
}

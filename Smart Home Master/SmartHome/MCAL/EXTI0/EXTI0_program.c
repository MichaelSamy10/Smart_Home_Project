/*
 * EXTI0_program.c
 *
 * Created: 13-Dec-23 1:26:19 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "EXTI0_private.h"
#include "EXTI0_config.h"
#include "EXTI0_interface.h"
#include "EXTI0_register.h"

static void (*EXTI0_pvCallBack)(void) = NULL;

void EXTI0_voidInit(void)
{
	/* Select Sense control*/
	#if (SENSE == LOW_LEVEL)
		CLR_BIT(MCUCR,1);
		CLR_BIT(MCUCR,0);
	#elif (SENSE == ANY_CHANGE) 
		CLR_BIT(MCUCR,1);
		SET_BIT(MCUCR,0);
	#elif (SENSE == FALLING_EDGE)
		SET_BIT(MCUCR,1);
		CLR_BIT(MCUCR,0);
	#elif (SENSE == RISING_EDGE)
		SET_BIT(MCUCR,1);
		SET_BIT(MCUCR,0);
		
	#endif
	/* Enable EXTI0*/
	SET_BIT(GICR,6);
}

void EXTI0_voidEnable(void)
{
	SET_BIT(GICR,6);
}

void EXTI0_voidDisable(void)
{
	CLR_BIT(GICR,6);
}

void EXTI0_voidSetSenseControl(u8 Copy_u8Sense)
{
	switch(Copy_u8Sense)
	{
		case LOW_LEVEL:
			CLR_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
			break;
		case ANY_CHANGE:
			CLR_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
			break;
		case FALLING_EDGE:
			SET_BIT(MCUCR,1);
			CLR_BIT(MCUCR,0);
			break;
		case RISING_EDGE:
			SET_BIT(MCUCR,1);
			SET_BIT(MCUCR,0);
			break;
	}
}

void EXTI0_voidSetCallBack(void (*Copy_pvCallBack)(void))
{
	EXTI0_pvCallBack = Copy_pvCallBack;
}


void __vector_1(void)__attribute__((signal));

void __vector_1(void)
{
	if(EXTI0_pvCallBack != NULL)
	{
		EXTI0_pvCallBack();
	}

}
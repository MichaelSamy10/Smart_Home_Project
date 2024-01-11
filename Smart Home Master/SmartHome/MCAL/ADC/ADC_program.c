/*
 * ADC_program.c
 *
 * Created: 18-Dec-23 10:10:49 AM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "ADC_register.h"
#include "ADC_config.h"
#include "ADC_interface.h"
#include "ADC_private.h"

void ADC_voidInit(void)
{
	#if VREF == AREF
		CLR_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	
	#elif VREF == AVCC
		SET_BIT(ADMUX,REFS0);
		CLR_BIT(ADMUX,REFS1);
	
	#elif VREF == INTERNAL_VOLTAGE
		SET_BIT(ADMUX,REFS0);
		SET_BIT(ADMUX,REFS1);		
		
	#endif
	
	/* Select Adjustment */
	CLR_BIT(ADMUX,ADLAR);
	
	/* Select Prescaler */
	ADCSRA &= 0b11111000;
	ADCSRA |= PRESCALER;

	
	/* Enable */ 
	SET_BIT(ADCSRA,ADEN);
	
}

u16 ADC_u16ReadChannel(u8 Copy_u8Channel)
{
	/* Select Channel */
	ADMUX &= 0b11100000;
	ADMUX |= Copy_u8Channel;
	
	/* Start conversion */
	SET_BIT(ADCSRA,ADSC);
	
	/* Polling */
	while( (GET_BIT(ADCSRA,ADIF)) != 1)
	{
		/* No operation */
		asm("NOP");
	}
	
	/* Clear Flag by writing one*/ 
	SET_BIT(ADCSRA,ADIF);

	return ADCW;
}

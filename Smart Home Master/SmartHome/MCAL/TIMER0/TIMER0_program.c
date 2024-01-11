/*
 * TIMER0_program.c
 *
 * Created: 19-Dec-23 2:02:18 PM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMER0_register.h"
#include "TIMER0_config.h"
#include "TIMER0_interface.h"
#include "TIMER0_private.h"


void(*GlobalOvPtrFunc)(void) = NULL;
void(*GlobalCtcPtrFunc)(void) = NULL;
u16 G_u16OvfCounts;
u16 G_u16CtcCounts;

void TIMER0_voidInit()
{
	/* TODO the TIMER0_MODE in masking
		Complete the comments readable
	*/
	
	#if TIMER0_COUNTER_MODE == TIMER
		/* Choose TIMER Mode using bit masking*/
		TCCR0 &= 0xB7;	// 0b10110111
		TCCR0 |= TIMER0_MODE;


		#if TIMER0_MODE == TIMER0_CTC_MODE
			/* Control OC0 pin in CTC mode */
			TCCR0 &= 0xCF;	// 0b11001111
			TCCR0 |= CTC_OC0_PIN;
					
		#elif TIMER0_MODE == TIMER0_PHASE_CORRECT_PWM	
			/* Control OC0 pin in Phase correct PWM mode */
			TCCR0 &= 0xCF;	// 0b11001111
			TCCR0 |= PWM_OC0_PIN;
			
		#elif TIMER0_MODE == TIMER0_FAST_PWM
			/* Control OC0 pin in Fast PWM mode */
			TCCR0 &= 0xCF;	// 0b11001111
			TCCR0 |= PWM_OC0_PIN;
		#endif

	#elif TIMER0_COUNTER_MODE == COUNTER
		/* Choose TIMER0 Mode using bit masking*/
		TCCR0 &= 0xF8;	// 0b11111000
		TCCR0 |= COUNTER0_SENSE;


		
	#endif

}

void TIMER0_voidOVSetIntervalSynchronous(u16 Copy_16Counts)
{
	for(u16 Local_Iterator=0;Local_Iterator<Copy_16Counts;Local_Iterator++)
	{
		while(GET_BIT(TIFR,TOV0) != 1);
		SET_BIT(TIFR,TOV0);
	}
}

void TIMER0_voidOVSetIntervalSynchronousMS(u16 Copy_u16MilliSec)
{
	/* prescaler 8*/
	u16 L_u16Counts = (Copy_u16MilliSec / 256 )* 1000 ;

	for(u16 Local_Iterator=0;Local_Iterator<L_u16Counts;Local_Iterator++)
	{
		while(GET_BIT(TIFR,TOV0) != 1);
		SET_BIT(TIFR,TOV0);
	}
}

void TIMER0_voidOVSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void))
{
	SET_BIT(TIMSK,TOIE0);
	GlobalOvPtrFunc = PtrFunc;
	G_u16OvfCounts = Copy_u16Counts;
}

void TIMER0_voidOVSetIntervalASynchronousMS(u16 Copy_u16MilliSec,void(*PtrFunc)(void))
{
	u16 L_u16Counts = (Copy_u16MilliSec / 256 )* 1000 ;
	
	SET_BIT(TIMSK,TOIE0);
	GlobalOvPtrFunc = PtrFunc;
	G_u16OvfCounts = L_u16Counts;

}

void TIMER0_voidCTCSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void))
{
	SET_BIT(TIMSK,OCIE0);
	GlobalCtcPtrFunc = PtrFunc;
	G_u16CtcCounts = Copy_u16Counts;
}

void TIMER0_voidCTCSetIntervalASynchronousMS(u16 Copy_u16MilliSec , void(*PtrFunc)(void))
{
	u16 L_u16Counts = (Copy_u16MilliSec / 256 )* 1000 ;
	SET_BIT(TIMSK,OCIE0);
	GlobalCtcPtrFunc = PtrFunc;
	G_u16CtcCounts = L_u16Counts;
}

void TIMER0_voidSetCompareValue(u16 Copy_u16CompVal)
{
	OCR0 = Copy_u16CompVal;
}

void TIMER0_voidSetPreloadValue(u16 Copy_u16PreloadVal)
{
	TCNT0 = Copy_u16PreloadVal;
}

void TIMER0_voidStart(void)
{
	/* Set prescaler ,so TIMER0 starts counting*/
	
	/* bit Masking */
	TCCR0  &= 0xF8; //0b11111000
	TCCR0 |= TIMER0_PRESCALER;
		
}

void TIMER0_voidStop(void)
{
		CLR_BIT(TCCR0,CS00);
		CLR_BIT(TCCR0,CS01);
		CLR_BIT(TCCR0,CS02);
}


/* TODO callback functions for over flow and CTC*/

void TIMER0_voidCallBack_OVF(void(*PtrFunc)(void)){
	GlobalOvPtrFunc = PtrFunc;
}


void TIMER0_voidCallBack_CTC(void(*PtrFunc)(void)){
	GlobalCtcPtrFunc = PtrFunc;
}



/* Normal Mode ISR */
void __vector_11(void)__attribute__((signal));

void __vector_11(void){
	static u16 LS_Iterator=0;

	if(LS_Iterator == G_u16OvfCounts)
	{
		if(GlobalOvPtrFunc != NULL)
		{
			GlobalOvPtrFunc();
			LS_Iterator = 0;
		}
	}
	LS_Iterator++;
}


/* CTC ISR */
void __vector_10(void)__attribute__((signal));

void __vector_10(void){
	static u16 LS_Iterator=0;

	if(LS_Iterator == G_u16CtcCounts)
	{
		if(GlobalCtcPtrFunc != NULL)
		{
			GlobalCtcPtrFunc();
			LS_Iterator = 0;
		}
	}
	LS_Iterator++;
}
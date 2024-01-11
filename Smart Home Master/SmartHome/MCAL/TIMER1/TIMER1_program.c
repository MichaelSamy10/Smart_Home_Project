/*
 * TIMER1_program.c
 *
 * Created: 21-Dec-23 9:18:31 AM
 *  Author: MICHAEL
 */ 
#include "../../LIB/BIT_MATH.h"
#include "../../LIB/STD_TYPES.h"

#include "TIMER1_register.h"
#include "TIMER1_config.h"
#include "TIMER1_interface.h"
#include "TIMER1_private.h"


void(*GlobalOvPtrFuncTimer1)(void) = NULL;
void(*GlobalCtcPtrFuncCompA)(void) = NULL;
void(*GlobalCtcPtrFuncCompB)(void) = NULL;
u16 G_u16OvfCountsTimer1;
u16 G_u16CtcCountsCompA;
u16 G_u16CtcCountsCompB;

void TIMER1_voidInit()
{
	#if TIMER1_COUNTER_MODE == TIMER
	/* Choose TIMER Mode */
	/* TODO Continue other modes... */
		#if TIMER1_MODE == TIMER1_NORMAL_MODE
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			CLR_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
		
		#elif TIMER1_MODE == TIMER1_CTC_MODE_OCR1A
			CLR_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			/* Control OC1A pin in CTC mode */
			TCCR1A &= 0x3F;	// 0b00111111
			TCCR1A |= CTC_OC1A_PIN;
			/* Control OC1B pin in CTC mode */
			TCCR1A &= 0xCF;	// 0b11001111
			TCCR1A |= CTC_OC1B_PIN;
	
		#elif TIMER1_MODE == TIMER1_FAST_PWM_8BIT
			SET_BIT(TCCR1A,WGM10);
			CLR_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			/* Control OC1A pin in PWM mode */
			TCCR1A &= 0x3F;	// 0b00111111
			TCCR1A |= PWM_OC1A_PIN;
			/* Control OC1B pin in PWM mode */
			TCCR1A &= 0xCF;	// 0b11001111
			TCCR1A |= PWM_OC1B_PIN;
		
		#elif TIMER1_MODE == TIMER1_FAST_PWM_10BIT
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			CLR_BIT(TCCR1B,WGM13);
			/* Control OC1A pin in PWM mode */
			TCCR1A &= 0x3F;	// 0b00111111
			TCCR1A |= PWM_OC1A_PIN;
			/* Control OC1B pin in PWM mode */
			TCCR1A &= 0xCF;	// 0b11001111
			TCCR1A |= PWM_OC1B_PIN;		
		
				
		#elif TIMER1_MODE == TIMER1_FAST_PWM_ICR1
			CLR_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);	
			/* Control OC1A pin in PWM mode */
			TCCR1A &= 0x3F;	// 0b00111111
			TCCR1A |= PWM_OC1A_PIN;
			/* Control OC1B pin in PWM mode */
			TCCR1A &= 0xCF;	// 0b11001111
			TCCR1A |= PWM_OC1B_PIN;


		#elif TIMER1_MODE == TIMER1_FAST_PWM_OCR1A
			SET_BIT(TCCR1A,WGM10);
			SET_BIT(TCCR1A,WGM11);
			SET_BIT(TCCR1B,WGM12);
			SET_BIT(TCCR1B,WGM13);
			/* Control OC1A pin in PWM mode */
			TCCR1A &= 0x3F;	// 0b00111111
			TCCR1A |= PWM_OC1A_PIN;
			/* Control OC1B pin in PWM mode */
			TCCR1A &= 0xCF;	// 0b11001111
			TCCR1A |= PWM_OC1B_PIN;
					
		#endif
		

	#elif TIMER1_COUNTER_MODE == COUNTER
		/* Choose TIMER1 Mode using bit masking*/
		TCCR1B &= 0xF8;	// 0b11111000
		TCCR1B |= COUNTER1_SENSE;

	
	#endif

	
}

void TIMER1_voidOVSetIntervalSynchronous(u16 Copy_u16Counts)
{
	for(u16 Local_Iterator=0;Local_Iterator<Copy_u16Counts;Local_Iterator++)
	{
		while(GET_BIT(TIFR,TOV1) != 1);
		SET_BIT(TIFR,TOV1);
	}
}

void TIMER1_voidOVSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void))
{
	SET_BIT(TIMSK,TOIE1);
	GlobalOvPtrFuncTimer1 = PtrFunc;
	G_u16OvfCountsTimer1 = Copy_u16Counts;	
}

/* This function not working.. */
void TIMER1_voidOVSetIntervalASynchronousMS(u16 Copy_u16MilliSec,void(*PtrFunc)(void))
{
	u16 L_u16Counts = (Copy_u16MilliSec / 65536 )* 1000 ;
	
	SET_BIT(TIMSK,TOIE1);
	GlobalOvPtrFuncTimer1 = PtrFunc;
	G_u16OvfCountsTimer1 = L_u16Counts;
	
}

void TIMER1_voidCTCSetIntervalASynchronousCompA(u16 Copy_u16Counts , void(*PtrFunc)(void))
{
	SET_BIT(TIMSK,OCIE1A);
	GlobalCtcPtrFuncCompA = PtrFunc;
	G_u16CtcCountsCompA = Copy_u16Counts;
}

void TIMER1_voidCTCSetIntervalASynchronousMsCompA(u16 Copy_u16MilliSec , void(*PtrCOMPA)(void))
{
	u16 L_u16Counts = (Copy_u16MilliSec / 65536 )* 1000 ;
		
	SET_BIT(TIMSK,OCIE1A);

	GlobalCtcPtrFuncCompA = PtrCOMPA;
	G_u16CtcCountsCompA = L_u16Counts;
}

void TIMER1_voidCTCSetIntervalASynchronousMsCompB(u16 Copy_u16MilliSec , void(*PtrCOMPB)(void))
{
	u16 L_u16Counts = (Copy_u16MilliSec / 65536 )* 1000 ;
	
	SET_BIT(TIMSK,OCIE1B);

	GlobalCtcPtrFuncCompB = PtrCOMPB;
	G_u16CtcCountsCompB = L_u16Counts;
}

void TIMER1_voidSetPreloadValue(u16 Copy_u16PreloadVal)
{
	TCNT1 = Copy_u16PreloadVal;
}

void TIMER1_voidSetOCR1A(u16 Copy_u16Ocr1A)
{
	OCR1A = Copy_u16Ocr1A;
}

void TIMER1_voidSetOCR1B(u16 Copy_u16Ocr1B)
{
	OCR1B = Copy_u16Ocr1B;
}

void TIMER1_voidSetICR(u16 Copy_u16IcrVal)
{
	ICR1 = Copy_u16IcrVal;
}

void TIMER1_voidStart(void)
{
	/* Set prescaler ,so TIMER1 starts counting*/
	
	/* bit Masking */
	TCCR1B  &= 0xF8; //0b11111000
	TCCR1B |= TIMER1_PRESCALER;
}

void TIMER1_voidStop(void)
{
		CLR_BIT(TCCR1B,CS10);
		CLR_BIT(TCCR1B,CS11);
		CLR_BIT(TCCR1B,CS12);
}


/* Timer1 CAPT ISR */
void __vector_6(void)__attribute__((signal));

void __vector_6(void){
	
	
}

/* Timer1 COMPA ISR */
void __vector_7(void)__attribute__((signal));

void __vector_7(void){
	static u16 LS_Iterator=0;

	if(LS_Iterator == G_u16CtcCountsCompA)
	{
		if(GlobalCtcPtrFuncCompA != NULL)
		{
			GlobalCtcPtrFuncCompA();
			LS_Iterator = 0;
		}
	}
	LS_Iterator++;
}

/* Timer1 COMPB ISR */
void __vector_8(void)__attribute__((signal));

void __vector_8(void){
	static u16 LS_Iterator=0;

	if(LS_Iterator == G_u16CtcCountsCompB)
	{
		if(GlobalCtcPtrFuncCompB != NULL)
		{
			GlobalCtcPtrFuncCompB();
			LS_Iterator = 0;
		}
	}
	LS_Iterator++;
}


/* Timer1 normal mode ISR*/
void __vector_9(void)__attribute__((signal));

void __vector_9(void){
	static u16 LS_Iterator=0;

	if(LS_Iterator == G_u16OvfCountsTimer1)
	{
		if(GlobalOvPtrFuncTimer1 != NULL)
		{
			GlobalOvPtrFuncTimer1();
			LS_Iterator = 0;
		}
	}
	LS_Iterator++;
}
/*
 * TIMER1_private.h
 *
 * Created: 21-Dec-23 9:18:02 AM
 *  Author: MICHAEL
 */ 


#ifndef TIMER1_PRIVATE_H_
#define TIMER1_PRIVATE_H_


/* TIMER1 Counter Selection */
#define TIMER										0
#define COUNTER										1

/* Counter prescaler options */
#define COUNTER1_SENSE_RISING							0b00000111
#define COUNTER1_SENSE_FALLING							0b00000110


/*Prescalar Options*/

#define TIMER1_PRESCALER_1								0b00000001
#define TIMER1_PRESCALER_8								0b00000010
#define TIMER1_PRESCALER_64								0b00000011
#define TIMER1_PRESCALER_256							0b00000100
#define TIMER1_PRESCALER_1024							0b00000101


/* TIMER0 Mode Options */
#define TIMER1_NORMAL_MODE							0
#define TIMER1_PHASE_CORRECT_PWM_8BIT				1
#define TIMER1_PHASE_CORRECT_PWM_9BIT				2
#define TIMER1_PHASE_CORRECT_PWM_10BIT				3
#define TIMER1_CTC_MODE_OCR1A						4
#define TIMER1_FAST_PWM_8BIT						5
#define TIMER1_FAST_PWM_9BIT						6
#define TIMER1_FAST_PWM_10BIT						7
#define TIMER1_PHASE_FREQ_CORRECT_PWM_ICR1			8
#define TIMER1_PHASE_FREQ_CORRECT_PWM_OCR1A			9
#define TIMER1_PHASE_CORRECT_PWM_ICR1				10
#define TIMER1_PHASE_CORRECT_PWM_OCR1A				11
#define TIMER1_CTC_MODE_ICR1						12
#define TIMER1_FAST_PWM_ICR1						14
#define TIMER1_FAST_PWM_OCR1A						15




/* OC1A pin options in CTC mode */
#define  CTC_OC1A_DISABLE						0b00000000
#define  CTC_OC1A_TOOGLE						0b01000000
#define  CTC_OC1A_CLEAR							0b10000000
#define  CTC_OC1A_SET							0b11000000

/* OC1B pin options in CTC mode */
#define  CTC_OC1B_DISABLE						0b00000000
#define  CTC_OC1B_TOOGLE						0b00010000
#define  CTC_OC1B_CLEAR							0b00100000
#define  CTC_OC1B_SET							0b00110000

/* OC1A pin options in PWM mode */
#define  PWM_OC1A_DISABLE						0b00000000
#define  PWM_OC1A_TOOGLE						0b01000000
#define  PWM_OC1A_NON_INVERTED					0b10000000
#define  PWM_OC1A_INVERTED						0b11000000

/* OC1B pin options in PWM mode */
#define  PWM_OC1B_DISABLE						0b00000000
#define  PWM_OC1B_TOOGLE						0b00010000
#define  PWM_OC1B_NON_INVERTED					0b00100000
#define  PWM_OC1B_INVERTED						0b00110000




#endif /* TIMER1_PRIVATE_H_ */
/*
 * TIMER0_private.h
 *
 * Created: 19-Dec-23 2:01:52 PM
 *  Author: MICHAEL
 */ 


#ifndef TIMER0_PRIVATE_H_
#define TIMER0_PRIVATE_H_

/* TIMER0 Counter Selection */
#define TIMER						0
#define COUNTER						1


/* TIMER0 Mode Options */
#define TIMER0_NORMAL_MODE			0
#define TIMER0_PHASE_CORRECT_PWM	0b01000000
#define TIMER0_CTC_MODE				0b00001000
#define TIMER0_FAST_PWM				0b01001000

/*Prescalar Options*/

#define PRESCALER_1								1
#define PRESCALER_8								2
#define PRESCALER_64							3
#define PRESCALER_256							4
#define PRESCALER_1024							5


/* Counter prescaler options */
#define COUNTER0_SENSE_RISING					0b00000111
#define COUNTER0_SENSE_FALLING					0b00000110

/* OC0 pin options in CTC mode */
#define  CTC_OC0_DISABLE						0
#define  CTC_OC0_TOOGLE							0b00010000
#define  CTC_OC0_CLEAR							0b00100000
#define  CTC_OC0_SET							0b00110000

/* OC0 pin options in PWM mode */
#define PWM_OC0_DISABLE							0
#define PWM_OC0_NON_INVERTED					0b00100000
#define PWM_OC0_INVERTED						0b00110000


#endif /* TIMER0_PRIVATE_H_ */
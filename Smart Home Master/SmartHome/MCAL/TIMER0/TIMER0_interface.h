/*
 * TIMER0_interface.h
 *
 * Created: 19-Dec-23 2:02:05 PM
 *  Author: MICHAEL
 */ 


#ifndef TIMER0_INTERFACE_H_
#define TIMER0_INTERFACE_H_


void TIMER0_voidInit();

/* 
	Function parameters -> number of overflows 
	Function polling to Normal mode (No interrupt)
*/
void TIMER0_voidOVSetIntervalSynchronous(u16 Copy_u16Counts);

/* 
	Function parameters -> number of overflows , pointer to function
	Function to enable TIMER0 normal mode interrupt 
*/

void TIMER0_voidOVSetIntervalSynchronousMS(u16 Copy_u16MilliSec);

void TIMER0_voidOVSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void));

void TIMER0_voidOVSetIntervalASynchronousMS(u16 Copy_u16MilliSec,void(*PtrFunc)(void));

/* 
	Function parameters -> number of overflows , pointer to function
	Function to enable TIMER0 CTC mode interrupt 
*/
void TIMER0_voidCTCSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void));

void TIMER0_voidCTCSetIntervalASynchronousMS(u16 Copy_u16MilliSec , void(*PtrFunc)(void));

void TIMER0_voidSetCompareValue(u16 Copy_u16CompVal);

void TIMER0_voidSetPreloadValue(u16 Copy_u16PreloadVal);

/* Start TIMER0 peripheral by setting the prescaler*/
void TIMER0_voidStart(void);

/* Stop TIMER0 peripheral */
void TIMER0_voidStop(void);


/* 
 * Normal mode call back function 
 * Function paramters -> pointer to function 
 * Function set call back to exceute ISR of normal mode
*/
void TIMER0_voidCallBack_OVF(void(*PtrFunc)(void));

/* 
 * CTC mode call back function 
 * Function paramters -> pointer to function
 * Function set call back to exceute ISR of CTC mode
*/
void TIMER0_voidCallBack_CTC(void(*PtrFunc)(void));


#endif /* TIMER0_INTERFACE_H_ */
/*
 * TIMER1_interface.h
 *
 * Created: 21-Dec-23 9:18:15 AM
 *  Author: MICHAEL
 */ 


#ifndef TIMER1_INTERFACE_H_
#define TIMER1_INTERFACE_H_


void TIMER1_voidInit();

void TIMER1_voidOVSetIntervalSynchronous(u16 Copy_u16Counts);

void TIMER1_voidOVSetIntervalASynchronous(u16 Copy_u16Counts , void(*PtrFunc)(void));

void TIMER1_voidOVSetIntervalASynchronousMS(u16 Copy_u16MilliSec,void(*PtrFunc)(void));

void TIMER1_voidCTCSetIntervalASynchronousCompA(u16 Copy_u16Counts , void(*PtrFunc)(void));

void TIMER1_voidCTCSetIntervalASynchronousMsCompA(u16 Copy_u16MilliSec , void(*PtrCOMPA)(void));

void TIMER1_voidCTCSetIntervalASynchronousMsCompB(u16 Copy_u16MilliSec , void(*PtrCOMPB)(void));

void TIMER1_voidSetPreloadValue(u16 Copy_u16PreloadVal);

void TIMER1_voidSetOCR1A(u16 Copy_u16Ocr1A);

void TIMER1_voidSetOCR1B(u16 Copy_u16Ocr1B);

void TIMER1_voidSetICR(u16 Copy_u16IcrVal);

void TIMER1_voidStart(void);

void TIMER1_voidStop(void);



#endif /* TIMER1_INTERFACE_H_ */
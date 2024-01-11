/*
 * EXTI0_interface.h
 *
 * Created: 13-Dec-23 1:25:32 PM
 *  Author: MICHAEL
 */ 


#ifndef EXTI0_INTERFACE_H_
#define EXTI0_INTERFACE_H_


void EXTI0_voidInit(void);

void EXTI0_voidEnable(void);

void EXTI0_voidDisable(void);

void EXTI0_voidSetSenseControl(u8 Copy_u8Sense);

void EXTI0_voidSetCallBack(void (*Copy_pvCallBack)(void));

#define LOW_LEVEL		1
#define ANY_CHANGE		2
#define FALLING_EDGE	3
#define RISING_EDGE		4


#endif /* EXTI0_INTERFACE_H_ */
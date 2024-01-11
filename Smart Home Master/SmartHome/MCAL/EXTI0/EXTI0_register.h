/*
 * EXTI0_register.h
 *
 * Created: 13-Dec-23 1:26:05 PM
 *  Author: MICHAEL
 */ 


#ifndef EXTI0_REGISTER_H_
#define EXTI0_REGISTER_H_

#define MCUCR *( (volatile u8*) 0x55)	

#define	ISC00	0
#define	ISC01	1
#define	ISC10	2
#define	ISC11	3
 

#define MCUCSR *( (volatile u8*) 0x54)

#define	ISC2	6

#define GICR *( (volatile u8*) 0x5B)

#define GIFR *( (volatile u8*) 0x5A)


#endif /* EXTI0_REGISTER_H_ */
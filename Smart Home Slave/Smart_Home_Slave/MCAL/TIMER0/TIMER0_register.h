/*
 * TIMER0_register.h
 *
 * Created: 19-Dec-23 2:01:27 PM
 *  Author: MICHAEL
 */ 


#ifndef TIMER0_REGISTER_H_
#define TIMER0_REGISTER_H_

#define TCCR0 *( (volatile u8 *) 0x53)

#define CS00   0
#define CS01   1
#define CS02   2
#define WGM01  3
#define COM00  4
#define COM01  5
#define WGM00  6
#define FOC0   7


#define TCNT0 *( (volatile u8 *) 0x52)

#define OCR0 *( (volatile u8 *) 0x5C)

#define TIMSK *( (volatile u8 *) 0x59)

#define TOIE0 0
#define OCIE0 1

#define TIFR *( (volatile u8 *) 0x58)

#define TOV0 0
#define OCF0 1

#endif /* TIMER0_REGISTER_H_ */
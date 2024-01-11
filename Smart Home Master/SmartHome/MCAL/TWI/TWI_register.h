/*
 * TWI_register.h
 *
 * Created: 26-Dec-23 11:01:19 AM
 *  Author: MICHAEL
 */ 


#ifndef TWI_REGISTER_H_
#define TWI_REGISTER_H_


#define TWBR *( (volatile u8 *) 0x20)

#define TWBR0  0
#define TWBR1  1
#define TWBR2  2
#define TWBR3  3
#define TWBR4  4
#define TWBR5  5
#define TWBR6  6
#define TWBR7  7


#define TWCR *( (volatile u8 *) 0x56)

#define TWIE	0
#define TWEN	2
#define TWWC	3
#define TWSTO	4
#define TWSTA	5
#define TWEA	6
#define TWINT	7


#define TWSR *( (volatile u8 *) 0x21)

#define TWPS0  0
#define TWPS1  1
#define TWPS3  3
#define TWPS4  4
#define TWPS5  5
#define TWPS6  6
#define TWPS7  7


#define TWAR *( (volatile u8 *) 0x22)

#define TWGCE  0
#define TWA0   1
#define TWA1   2
#define TWA2   3
#define TWA3   4
#define TWA4   5
#define TWA5   6
#define TWA6   7


#define TWDR *( (volatile u8 *) 0x23)

#define TWD0  0
#define TWD1  1
#define TWD2  2
#define TWD3  3
#define TWD4  4
#define TWD5  5
#define TWD6  6
#define TWD7  7

#endif /* TWI_REGISTER_H_ */
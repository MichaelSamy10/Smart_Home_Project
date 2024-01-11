/*
 * ADC_interface.h
 *
 * Created: 18-Dec-23 10:09:52 AM
 *  Author: MICHAEL
 */ 


#ifndef ADC_INTERFACE_H_
#define ADC_INTERFACE_H_

void ADC_voidInit(void);

u16 ADC_u16ReadChannel(u8 Copy_u8Channel);


#define CHANNEL_0		0
#define CHANNEL_1		1
#define CHANNEL_2		2
#define CHANNEL_3		3
#define CHANNEL_4		4
#define CHANNEL_5		5
#define CHANNEL_6		6
#define CHANNEL_7		7


#endif /* ADC_INTERFACE_H_ */
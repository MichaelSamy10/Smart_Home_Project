/*
 * ADC_config.h
 *
 * Created: 18-Dec-23 10:29:27 AM
 *  Author: MICHAEL
 */ 


#ifndef ADC_CONFIG_H_
#define ADC_CONFIG_H_

/* Reference Selection Options 
	AREF - AVCC - INTERNAL_VOLTAGE
*/
#define	VREF	AVCC

/* Prescalar options 
DIVIDE_BY_2 - DIVIDE_BY_4 - DIVIDE_BY_8-  DIVIDE_BY_16 - DIVIDE_BY_32 - DIVIDE_BY_64 - DIVIDE_BY_128
*/
#define PRESCALER	DIVIDE_BY_8

#endif /* ADC_CONFIG_H_ */
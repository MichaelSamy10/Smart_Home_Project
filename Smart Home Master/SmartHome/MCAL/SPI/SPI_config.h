/*
 * SPI_config.h
 *
 * Created: 24-Dec-23 9:17:43 PM
 *  Author: MICHAEL
 */ 


#ifndef SPI_CONFIG_H_
#define SPI_CONFIG_H_


/* Clock Polarity options
	1-CPOL_LEADING_RISING
	2-CPOL_RISING_LEADING
 */

#define CLOCK_POLARITY CPOL_LEADING_RISING


/* Clock Rate Frequency 
	1-CLOCK_RATE_4
	2-CLOCK_RATE_16
	3-CLOCK_RATE_64
*/

#define SCK_FREQUENCY	CLOCK_RATE_16



#endif /* SPI_CONFIG_H_ */
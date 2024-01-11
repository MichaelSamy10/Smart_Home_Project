/*
 * WDT_register.h
 *
 *  Created on: Dec 21, 2023
 *      Author: MICHAEL
 */

#ifndef MCAL_WDT_WDT_REGISTER_H_
#define MCAL_WDT_WDT_REGISTER_H_

#define WDTCR *((volatile u8 *) 0x41)

#define WDE 3
#define WDTOE 4

#endif /* MCAL_WDT_WDT_REGISTER_H_ */

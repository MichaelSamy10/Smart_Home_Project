/*
 * USART_register.h
 *
 * Created: 25-Dec-23 9:42:40 AM
 *  Author: MICHAEL
 */ 


#ifndef USART_REGISTER_H_
#define USART_REGISTER_H_

#define UCSRA *( (volatile u8 *) 0x2B)

#define MPCM  0
#define U2X   1
#define PE	  2
#define DOR   3
#define FE    4
#define UDRE  5
#define TXC	  6
#define RXC   7


#define UCSRB *( (volatile u8 *) 0x2A)

#define TXB8   0
#define RXB8   1
#define UCSZ2  2
#define TXEN   3
#define RXEN   4
#define UDRIE  5
#define TXCIE  6
#define RXCIE  7


#define UCSRC *( (volatile u8 *) 0x40)

#define UCPOL   0
#define UCSZ0   1
#define UCSZ1   2
#define USBS    3
#define UPM0    4
#define UPM1    5
#define UMSEL   6
#define URSEL   7


#define UBRRH *( (volatile u8 *) 0x40)
#define UBRRL *( (volatile u8 *) 0x29)


#define UDR *( (volatile u8 *) 0x2C)




#endif /* USART_REGISTER_H_ */

#ifndef KEYPAD_H_
#define KEYPAD_H_

#include "std_macros.h"

/*
K0  '7', '8', '9', '\\',
K1	'4', '5', '6', '*',
K2	'1', '2', '3', '-',
K3	'c', '0', '=', '+'
	K4	  K5   K6   K7
*/
#define KEYPAD_INIT						  \
					DDRB   = 0b11110000; \
			     	PORTB  = 0b00001111;  


#define K0 READ_BIT(PINB,0)
#define K1 READ_BIT(PINB,1)
#define K2 READ_BIT(PINB,2)
#define K3 READ_BIT(PINB,3)
		
#define K4(x) if(x==1)  SET_BIT(PORTB,4); else CLR_BIT(PORTB,4);
#define K5(x) if(x==1)  SET_BIT(PORTB,5); else CLR_BIT(PORTB,5);
#define K6(x) if(x==1)  SET_BIT(PORTB,6); else CLR_BIT(PORTB,6);
#define K7(x) if(x==1)  SET_BIT(PORTB,7); else CLR_BIT(PORTB,7);

void KEYPAD_init(void);

uint8_t KEYPAD_read(void);
 
#endif
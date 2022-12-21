#ifndef std_macro_H_
#define std_macro_H_

#include <avr/io.h>

#define F_CPU 16000000UL

#include <util/delay.h>
#include <avr/interrupt.h>

#define SET_BIT(Value,bit) 		(Value |=  (1<<bit))
#define CLR_BIT(Value,bit)  	(Value &= ~(1<<bit))
#define TOG_BIT(Value,bit)  	(Value ^=  (1<<bit))
#define READ_BIT(Value,bit)		((Value>>bit)& 1)

typedef unsigned char uint8;
typedef unsigned short uint16;
typedef unsigned long uint32;

typedef signed char int8;
typedef signed short int16;
typedef signed long int32;


#endif
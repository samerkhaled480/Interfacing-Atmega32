

#ifndef SEVEN_SEG_H_
#define SEVEN_SEG_H_

#include "../../app/std_macros.h"

#define SEVEN_SEG_DATA_DDR DDRB
#define SEVEN_SEG_EN_DDR DDRA

#define SEVEN_SEG_DATA_PORT PORTB   
#define SEVEN_SEG_EN_PORT PORTA


void SS_init(void);
void SS_SELECT(uint8_t data);
void SS_Single_DISPLAY(uint8_t SevenSegOrder , uint8_t data);



#endif 

#ifndef LCD_H_
#define LCD_H_

#include "std_macros.h"
#include <avr/io.h>
#include <util/delay.h>

#define LCD_RS_PIN 7
#define LCD_EN_PIN 6

#define LCD_D7_PIN 2
#define LCD_D6_PIN 3
#define LCD_D5_PIN 4
#define LCD_D4_PIN 5 

#define LCD_INIT_PINS DDRA |= 0b11111100;																   

#define LCD_EN(x) if(x==1)  SET_BIT(PORTA,LCD_EN_PIN); else CLR_BIT(PORTA,LCD_EN_PIN);
#define LCD_RS(x) if(x==1)  SET_BIT(PORTA,LCD_RS_PIN); else CLR_BIT(PORTA,LCD_RS_PIN);
														 
#define LCD_D7(x) if(x==1)  SET_BIT(PORTA,LCD_D7_PIN);    else CLR_BIT(PORTA,LCD_D7_PIN);
#define LCD_D6(x) if(x==1)  SET_BIT(PORTA,LCD_D6_PIN);    else CLR_BIT(PORTA,LCD_D6_PIN);
#define LCD_D5(x) if(x==1)  SET_BIT(PORTA,LCD_D5_PIN);    else CLR_BIT(PORTA,LCD_D5_PIN);
#define LCD_D4(x) if(x==1)  SET_BIT(PORTA,LCD_D4_PIN);	 else CLR_BIT(PORTA,LCD_D4_PIN);
	  							
					  												 
void LCD_init(void);
void LCD_write_command(uint8 command);
void LCD_write_data (uint8 character);
void LCD_write_string(uint8 * string);
void LCD_write_num(int32 number);


#endif
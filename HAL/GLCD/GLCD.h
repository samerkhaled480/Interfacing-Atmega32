#ifndef __GLCD_H__
#define __GLCD_H__

#include"../../app/std_macros.h"

#define GLCD_DATA_PORT      PORTB
#define GLCD_CONTROL_PORT   PORTA

#define GLCD_DATA_PORT_DIR      DDRB
#define GLCD_CONTROL_PORT_DIR   DDRA

#define RS     0
#define EN     3
#define CS1    1
#define CS2    2
#define RST    4

/* Command List

0x3f = Turn on GLCD page
0x0c = Enable GLCD page

*/


void GLCD_Init();

void GLCD_SelectChip(uint8 selection); // 0x00 of 0x0f or 0xf0 or 0xff

void GLCD_SelectPage(uint8 selection);//from 0 to 7

void GLCD_GoToXY(uint8 x , uint8 y);// x 0-127 , y 0-7

void GLCD_CmdWrite(uint8 cmd);

void GLCD_DataWrite(uint8 data);

void GLCD_DisplayChar(uint8 *ptr_array);

void GLCD_DispalyNum(uint32 num, uint8 x , uint8 y);

void GLCD_DispalyString(uint8 **ptr_arry ,uint8 arr_size , uint8 x , uint8 y);


#endif


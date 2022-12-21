/*
 * TIMER1.h
 *
 * Created: 22-Aug-22 1:28:36 AM
 *  Author: Samer
 */ 


#ifndef TIMER1_H_
#define TIMER1_H_

#include "std_macros.h"


void TIMER1_PWM_OC1A_init(void);
void TIMER1_PWM_OC1A_duty(uint8 duty);

/*
void TIMER1_PWM_OC1B_init(void);
void TIMER1_PWM_OC1B_duty(uint8 duty);
*/

void TIMER1_ICU_init(void);
uint16 TIMER1_ICU_ReadCycle(void);
uint8 TIMER1_ICU_ReadFreq(uint16 *High , uint16 * Cycle);

void TIMER1_stop(void);



#endif
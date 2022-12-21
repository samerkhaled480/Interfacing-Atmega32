
#ifndef TIMER0_H_
#define TIMER0_H_

#include "../../app/std_macros.h"

extern void(*Timer0_OVF_isr_p)(void);
extern void(*Timer0_CTC_isr_p)(void);

/*****************************************************************************
* Function Name: TIMER0_normaMode_init
* Purpose      : init timer in normal mode with  prescaler
* Parameters   : selection of required prescaler . values from 1 to 5 
				 represent available prescaler  
* Return value : void
*****************************************************************************/
void Timer0_NormalMode_init(uint8 prescaler_select);

/*****************************************************************************
* Function Name: TIMER0_CTC_init
* Purpose      : init timer in CTC with  prescaler
* Parameters   : OCR value(top limit to compare) and selection of required
				 prescaler . values from 1 to 5  represent available prescaler  
* Return value : void
*****************************************************************************/
void Timer0_CTC_init(uint8 OC , uint8 prescaler_select);

/*****************************************************************************
* Function Name: Timer0_FreqGenerator
* Purpose      : create a frequency using timer0 on Pin PB3
* Parameters   : OCR value(top limit to compare) , selection of required
				prescaler . values from 1 to 5  represent available prescaler 
* Return value : void
*****************************************************************************/
void Timer0_FreqGene(uint8 OC , uint8 prescaler_select);


/*****************************************************************************
* Function Name: void TIMER0_PWM_OC0_init
* Purpose      : initialize pwm mode on timer0 on Pin PB3 
* Parameters   : prescaler value from 1 to 5
* Return value : void
*****************************************************************************/
void TIMER0_PWM_OC0_init(uint8 prescaler_select);

/*****************************************************************************
* Function Name: Timer0_FreqGenerator
* Purpose      : create a frequency using timer0 on Pin PB3
* Parameters   : OCR value(top limit to compare) , selection of required
				prescaler . values from 1 to 5  represent available prescaler 
* Return value : void
*****************************************************************************/
void TIMER0_PWM_OC0_duty(uint8 duty);

/*****************************************************************************
* Function Name: Timer0_stop
* Purpose      : stop all functionalities of timer0  
* Parameters   : void
* Return value : void
*****************************************************************************/
void Timer0_stop(void);

#endif
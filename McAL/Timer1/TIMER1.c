
#include "TIMER1.h"


void TIMER1_PWM_OC1A_init(void)
{
	// set OC1A Pin as output //
	SET_BIT(DDRD,5);
	// set non-inverting mode //
	CLR_BIT(TCCR1A,COM1A0);
	SET_BIT(TCCR1A,COM1A1);
	// select wave generation mode to fast pwm 10-bit
	SET_BIT(TCCR1A,WGM10);
	SET_BIT(TCCR1A,WGM11);
	SET_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	// set prescaler to no prescaler //
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
}

/*
duty = (100 * (max-1) * OCR1A
*/

void TIMER1_PWM_OC1A_duty(uint8 duty)
{
	OCR1A = duty * 10.23;
}


void TIMER1_stop(void)
{
	CLR_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);
}


void TIMER1_ICU_init(void)
{
	// select wave generation mode to normal mode
	CLR_BIT(TCCR1A,WGM10);
	CLR_BIT(TCCR1A,WGM11);
	CLR_BIT(TCCR1B,WGM12);
	CLR_BIT(TCCR1B,WGM13);
	
	//disable ICU noise canceling //
	CLR_BIT(TCCR1B,ICNC1);
	
	// set prescaler to no prescaler //
	SET_BIT(TCCR1B,CS10);
	CLR_BIT(TCCR1B,CS11);
	CLR_BIT(TCCR1B,CS12);	
}

uint16 TIMER1_ICU_ReadCycle(void)
{
	uint16 t=0;

	//clear flag by writing logic 1 to its location
	SET_BIT(TIFR,ICF1);
	//set ICU edge select to rising edge  //
	SET_BIT(TCCR1B,ICES1);
	
	while(READ_BIT(TIFR,ICF1) == 0);
	t = ICR1;
	
	//clear flag by writing logic 1 to its location
	SET_BIT(TIFR,ICF1);
	
	while(READ_BIT(TIFR,ICF1) == 0);
	t = ICR1 - t;
	if(ICR1 > t)
	{
		return t;
	}
	else
	{
		return 0;
	}
}


uint8 TIMER1_ICU_ReadFreq(uint16 *High , uint16 * Cycle)
{
	uint16 t1 = 0 , t2 = 0 , t3 = 0;
	
	//set timer counter register to 0//
	TCNT1 = 0;
	
	//clear flag by writing logic 1 to its location
	SET_BIT(TIFR,ICF1);
	//set ICU edge select to rising edge  //
	SET_BIT(TCCR1B,ICES1);
	
	while(READ_BIT(TIFR,ICF1) == 0);
	t1 = ICR1;
	
	//clear flag by writing logic 1 to its location
	SET_BIT(TIFR,ICF1);
	//set ICU edge select to falling  edge  //
	CLR_BIT(TCCR1B,ICES1);
	
	while(READ_BIT(TIFR,ICF1) == 0);
	t2 = ICR1;
	
	//clear flag by writing logic 1 to its location
	SET_BIT(TIFR,ICF1);
	//set ICU edge select to rising edge  //
	SET_BIT(TCCR1B,ICES1);
	
	while(READ_BIT(TIFR,ICF1) == 0);
	t3 = ICR1;
	
	if(t3 > t2 && t2 > t1)
	{
		*High  = t2-t1;
		*Cycle = t3 - t1;
		return 1;
	}
	else return 0 ;
}
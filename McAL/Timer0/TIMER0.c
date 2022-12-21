/*
 * TIMER0.c
 *
 * Created: 19-Aug-22 11:18:24 PM
 *  Author: Samer
 */ 

#include "TIMER0.h"

void (*Timer0_OVF_isr_p)(void);
void (*Timer0_CTC_isr_p)(void);

void Timer0_NormalMode_init(uint8 prescaler_select)
{
	switch(prescaler_select)
	{
		case 1:{
			//set prescaler to no prescaler
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 2:{
			//set prescaler to 8
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 3:{
			//set prescaler to 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 4:{
			//set prescaler to 256
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
		case 5:{
			//set prescaler to 1024
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
	}
	//activate force output compare
	SET_BIT(TCCR0,FOC0);
	//set timer0 to normal mode 
	CLR_BIT(TCCR0,WGM00);
	CLR_BIT(TCCR0,WGM01);
	// Enable OVF interrupt for timer0
	SET_BIT(TIMSK,TOIE0); 
	//enable global interrupt
	SET_BIT(SREG,7);	
	 
}

void Timer0_CTC_init(uint8 OC , uint8 prescaler_select)
{	
	//activate force output compare
	SET_BIT(TCCR0,FOC0);
	//set timer0 to CTC mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//Load value of OCR
	OCR0 = OC;
	// Enable output compare(OC) interrupt for timer0
	SET_BIT(TIMSK,OCIE0);
	//enable global interrupt
	SET_BIT(SREG,7);
		
	switch(prescaler_select)
	{	
		case 1:{
			//set prescaler to no prescaler
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 2:{
			//set prescaler to 8
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 3:{
			//set prescaler to 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 4:{
			//set prescaler to 256
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
		case 5:{
			//set prescaler to 1024
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
	}
	
}

/*
 (OCR_value+1) * prescaler * 10^-3/timer_freq * count = req_period_in_msec
 
 //assume value for ocr or count to get the other one and iterate till reach integer value for both 
 */

void Timer0_FreqGene(uint8 OC , uint8 prescaler_select)
{
	//activate force output compare
	SET_BIT(TCCR0,FOC0);
	//set timer0 to CTC mode
	CLR_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
	//enable OC0 Pin toggle 
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
	//load value of OCR
	OCR0 = OC;
	// set OC0 as output
	SET_BIT(DDRB, 3);
	//set prescaler
	
	switch(prescaler_select)
	{
		case 1:{
			//set prescaler to no prescaler
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 2:{
			//set prescaler to 8
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 3:{
			//set prescaler to 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 4:{
			//set prescaler to 256
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
		case 5:{
			//set prescaler to 1024
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
	}
		
}



void TIMER0_PWM_OC0_init(uint8 prescaler_select)
{
	// set OC0 Pin as output //
	SET_BIT(DDRB,3);
	
	// set non-inverting and toggle OC0 mode //
	CLR_BIT(TCCR0,COM00);
	SET_BIT(TCCR0,COM01);
	
	// select wave generation mode to fast pwm
	SET_BIT(TCCR0,WGM00);
	SET_BIT(TCCR0,WGM01);
		
	switch(prescaler_select)
	{
		case 1:{
			//set prescaler to no prescaler
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 2:{
			//set prescaler to 8
			CLR_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 3:{
			//set prescaler to 64
			SET_BIT(TCCR0,CS00);
			SET_BIT(TCCR0,CS01);
			CLR_BIT(TCCR0,CS02);
		}break;
		case 4:{
			//set prescaler to 256
			CLR_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
		case 5:{
			//set prescaler to 1024
			SET_BIT(TCCR0,CS00);
			CLR_BIT(TCCR0,CS01);
			SET_BIT(TCCR0,CS02);
		}break;
	}			
}


void TIMER0_PWM_OC0_duty(uint8 duty)
{
	OCR0 = duty * 2.55;
}


void Timer0_stop(void)
{
	
	CLR_BIT(TCCR0,CS00);
	CLR_BIT(TCCR0,CS01);
	CLR_BIT(TCCR0,CS02);
	//disable OC0 Pin and restore normal port operations 
	SET_BIT(TCCR0,COM00);
	CLR_BIT(TCCR0,COM01);
}


ISR(TIMER0_OVF_vect){
	Timer0_OVF_isr_p();
}

ISR(TIMER0_COMP_vect){
	Timer0_CTC_isr_p();
}
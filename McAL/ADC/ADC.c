

#include "ADC.h"

void ADC_init(void)
{
	//st ADC ref. voltage to AREF//
	CLR_BIT(ADMUX,REFS0);
	CLR_BIT(ADMUX,REFS1);
	//enable ADC //
	SET_BIT(ADCSRA,ADEN);
	//set prescaler to 128//
	SET_BIT(ADCSRA,ADPS0);
	SET_BIT(ADCSRA,ADPS1);
	SET_BIT(ADCSRA,ADPS2);
	//enable interrupted //
	//SET_BIT(ADCSRA,ADIE);
	//enable global interrupt //
	//SET_BIT(SREG,7);
	//Right adjust result //
	CLR_BIT(ADMUX,ADLAR);

	
}

uint16 ADC_read(uint8 channel)
{
	if(channel == 0)	 { ADMUX |= 0b000; }
	else if(channel == 1){ ADMUX |= 0b001; }
	else if(channel == 2){ ADMUX |= 0b010; }
	else if(channel == 3){ ADMUX |= 0b011; }
	else if(channel == 4){ ADMUX |= 0b100; }
	else if(channel == 5){ ADMUX |= 0b101; }
	else if(channel == 6){ ADMUX |= 0b110; }
	else if(channel == 7){ ADMUX |= 0b111; }

	//start conversion//.
	SET_BIT(ADCSRA,ADSC);
	
	while(READ_BIT(ADCSRA,ADSC) == 1);
	return ADC;
}


void ADC_StartConcv(uint8 channel)
{
	if(channel == 0)	 { ADMUX |= 0b000; }
	else if(channel == 1){ ADMUX |= 0b001; }
	else if(channel == 2){ ADMUX |= 0b010; }
	else if(channel == 3){ ADMUX |= 0b011; }
	else if(channel == 4){ ADMUX |= 0b100; }
	else if(channel == 5){ ADMUX |= 0b101; }
	else if(channel == 6){ ADMUX |= 0b110; }
	else if(channel == 7){ ADMUX |= 0b111; }

	//start conversion//.
	SET_BIT(ADCSRA,ADSC);
}

/*
ISR(ADC_vect)
{
	ADC_isr_p(); 
}
*/

#ifndef ADC_H_
#define ADC_H_

#include "../../app/std_macros.h"


void ADC_init(void);

uint16 ADC_read(uint8 channed);



extern void(*ADC_isr_p)(void);
void ADC_StartConcv(uint8 channel);



#endif
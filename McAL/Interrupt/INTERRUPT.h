
#ifndef __INTERRUPT_H
#define __INTERRUPT_H

#include "../../app/std_macros.h"



#define ENABLE_GLOBAL_INTTERUPT SET_BIT(SREG,7)
#define DISABLE_GLOBAL_INTERRUPT CLR_BIT(SREG,7)

#define ENABLE_INT0 SET_BIT(GICR,6)
#define ENABLE_INT1 SET_BIT(GICR,7)
#define ENABLE_INT2 SET_BIT(GICR,5)

#define DISABLE_INT0 CLR_BIT(GICR,6)
#define DISABLE_INT1 CLR_BIT(GICR,7)
#define DISABLE_INT2 CLR_BIT(GICR,5)


/* 
input 0 for rising edge
input 1 for falling edge
input 2 for any logical change
input 3 for low level only
*/

enum trigger_types{
    
    rising_edge ,
    falling_edge,
    any_logic_change,
    low_level_only
};

void INT0_init(uint8_t trigger_type);
/*
input 0 for rising edge
input 1 for falling edge
input 2 for any logical change
input 3 for low level only
*/
void INT1_init(uint8_t trigger_type);
/*
input 0 for rising edge
input 1 for falling edge
*/
void INT2_init(uint8_t trigger_type);


#endif

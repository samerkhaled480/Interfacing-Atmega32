
#include "INTERRUPT.h"


void INT0_init( uint8_t trigger_type )
{
    switch (trigger_type)
    {
        case rising_edge:
        {
            SET_BIT(MCUCR,ISC00);
            SET_BIT(MCUCR,ISC01);

        }break;

        case falling_edge:
        {
            CLR_BIT(MCUCR,ISC00);
            SET_BIT(MCUCR,ISC01);
        }break;

        case any_logic_change:
        {
            CLR_BIT(MCUCR,ISC01);
            SET_BIT(MCUCR,ISC00);
        }break;

        case low_level_only :
        {
            CLR_BIT(MCUCR,ISC01);
            CLR_BIT(MCUCR,ISC00);

        }
    }
}


void INT1_init(uint8_t trigger_type)
{
      switch (trigger_type)
    {
        case rising_edge:
        {
            SET_BIT(MCUCR,ISC10);
            SET_BIT(MCUCR,ISC11);

        }break;

        case falling_edge:
        {
            CLR_BIT(MCUCR,ISC10);
            SET_BIT(MCUCR,ISC11);
        }break;

        case any_logic_change:
        {
            CLR_BIT(MCUCR,ISC11);
            SET_BIT(MCUCR,ISC10);
        }break;

        case low_level_only :
        {
            CLR_BIT(MCUCR,ISC11);
            CLR_BIT(MCUCR,ISC10);

        }
    }

}

void INT2_init(uint8_t trigger_type)
{
       switch (trigger_type)
    {
        case rising_edge:
        {
            DISABLE_INT2;
            SET_BIT(MCUCSR,ISC10);

        }break;

        case falling_edge:
        {
            DISABLE_INT2;
            CLR_BIT(MCUCSR,ISC2);
        }
    }
}

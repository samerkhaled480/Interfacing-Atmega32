
#include "WDT.h"

void WDT_Start(void)
{
	//set WDT prescaler 2048K = 2.1 seconds 
	SET_BIT(WDTCR,WDP0);
	SET_BIT(WDTCR,WDP1);
	SET_BIT(WDTCR,WDP2);
	
	//enable WDT
	SET_BIT(WDTCR,WDE);
	
}

void WDT_Stop(void)
{
	WDTCR = 1<<WDTOE | 1<<WDE;
	WDTCR = 0;
	
}



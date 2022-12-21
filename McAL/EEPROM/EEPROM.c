
#include "EEPROM.h"

uint8_t EEPROM_read(uint16_t addr){
	while(READ_BIT(EECR,EEWE) == 1){}
	EEAR = addr;
	SET_BIT(EECR, EERE);
	return EEDR;
}

void EEPROM_write(uint16_t addr, uint8_t data){
	while(READ_BIT(EECR,EEWE) == 1){}
	EEAR = addr;
	EEDR = data;
	SET_BIT(EECR, EEMWE);
	SET_BIT(EECR, EEWE);
}

/* ImpBadge	
 * imp_eeprom.c
 * eeprom manager for an impbadge
 * copyright 2018 Hack for Satan
 */

#include "imp_eeprom.h"

unsigned char imp_eeprom_read(unsigned char address) {
	EEADR = address;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	EECON1bits.RD = 1;
	return EEDATA;
}

unsigned char imp_eeprom_write(unsigned char address, unsigned char data) {
	EECON1bits.WREN = 1;
	EEADR = address;
	EEDATA = data;
	EECON1bits.EEPGD = 0;
	EECON1bits.CFGS = 0;
	INTCONbits.GIE = 0;
	
	EECON2 = 0x55;
	EECON2 = 0xAA;
	EECON1bits.WR = 1;
	
	INTCONbits.GIE = 1;
	while (EECON1bits.WR) ;
	EECON1bits.WREN = 0;
	
	if (imp_eeprom_read(address) == data) return 0;
	else return 1;
}
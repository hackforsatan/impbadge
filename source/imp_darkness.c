/* ImpBadge	
 * imp_darkness.c
 * darkness manager for ImpBadge
 * copyright 2018 Hack for Satan
 */

#include "imp_darkness.h"

void dark_init() {
	TRISAbits.TRISA0 = 1;
	
	ADCON0 = 0b00000001;
	ADCON1 = 0b00000111;
	ADCON2 = 10110110;
	
	ADCON0bits.GO = 1;
	PIR1bits.ADIF = 0;
	PIE1bits.ADIE = 1;
};

void dark_stop() {
	ADCON0 = 0b00000000;
	ADCON1 = 0b00001111;
	
	PIE1bits.ADIE = 0;
	PIR1bits.ADIF = 0;
}

int get_darkness() {
	return dark_val;
}
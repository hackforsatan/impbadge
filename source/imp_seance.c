/* ImpBadge	
 * imp_seance.c
 * seance manager for an impbadge
 * copyright 2018 Hack for Satan
 */

#include "imp_seance.h"
void seance_init() {
	seance_buffer[0] = seance_id;
	
	
	TRISDbits.TRISD6 = 0;
	TRISDbits.TRISD7 = 1;
	TRISDbits.TRISD3 = 0; /* IMP Right 0 V */
	TRISDbits.TRISD4 = 0; /* IMP Right DATA */
	PORTDbits.RD6 = 0;
	PORTDbits.RD3 = 0;
	PORTDbits.RD4 = 1;	/* IMP Right idles HIGH */

	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
	
	/* set up timer 0: 
	 * off, 16-bit, instr. clock, no prescaler
	 * pre-load with 26,473 for 128 Hz interrupt
	 */
	unsigned short preload = 55770;
	T0CON = 0b00001000;
	TMR0H = preload >> 8;
	TMR0L = preload;
	TMR0IF = 0;
	TMR0IE = 1;
	TMR0ON = 1;
}

void seance_received_bit(unsigned char in_bit) {
	if (in_bit) {	/* bit = 1 */
		seance_temp |= 0x0001 << seance_write_bit_offset;
	} else {	/* bit = 0 */
		seance_temp &= (0x0001 << seance_write_bit_offset)^0xFFFF;
	}
	
	if (++seance_write_bit_offset == 16) {
		seance_write_bit_offset = 0;
		if (seance_temp >> 12 == 0x000B) {
			unsigned char last_zero_index = 0xFF;
			unsigned char found_this_word = FALSE;
			for (unsigned char i = 0; i < 5; i++) {
				if (seance_in_buffer[i] == seance_temp) found_this_word = TRUE;
				else if (!seance_in_buffer[i]) last_zero_index = i;
			}
			if (!found_this_word && last_zero_index != 0xFF) {
				seance_in_buffer[last_zero_index] = seance_temp;
			}
			set_display_bits((unsigned char)(seance_temp), 2);
		}
		seance_temp = 0x0000;
		sampling_on = FALSE;
		
		seance_validate();
	}
}

void seance_validate() {
	unsigned char last_zero_index = 0xFF;
	unsigned char found_my_id = FALSE;
	for (unsigned char i = 0; i < 5; i++) {
		seance_buffer[i] = seance_in_buffer[i];
		if (seance_buffer[i] == seance_id) found_my_id = TRUE;
		if (!seance_buffer[i]) {
			last_zero_index = i;
		}
	}
	if (last_zero_index == 0xFF) {
		if (!seance_complete) {
			seance_complete = TRUE;
			imp_eeprom_write(SEANCE_FLAG, TRUE);
			pent_fade_in();
		}
	}
	else if (!found_my_id) seance_buffer[last_zero_index] = seance_id;
}
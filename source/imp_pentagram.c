/* ImpBadge	
 * imp_pentagram.c
 * parallel LED driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_pentagram.h"

void pent_init(void) {
	TRISBbits.TRISB3 = 0;
	PORTBbits.RB3 = 0;
	
	PR2 = 0b10011100;	// Fpwm = 2 kHz
	T2CON = 0b00000011;	// Timer 2 OFF; Prescalar = 16
	
	pent_quickfade();
}

void pent_breathe(unsigned char up_delay_ms, unsigned char down_delay_ms) {
	T2CON |= (0x01<<2);
	
	unsigned short duty_cycle;
	
	for (duty_cycle = 0; duty_cycle < MAX_PENT_BRIGHTNESS; duty_cycle++) {
		CCPR2L = duty_cycle >> 2;
		CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
		__delay_ms(2);
	}
	for (duty_cycle = MAX_PENT_BRIGHTNESS; duty_cycle > 0; duty_cycle--) {
		CCPR2L = duty_cycle >> 2;
		CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
		__delay_ms(2);
	}
	duty_cycle = 0;
	CCPR2L = duty_cycle >> 2;
	CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
	
	T2CON &= 0b11111011;
}

void pent_quickfade(void) {
	T2CON |= (0x01<<2);
	unsigned short duty_cycle;
	for (duty_cycle = MAX_PENT_BRIGHTNESS; duty_cycle > 0; duty_cycle--) {
		CCPR2L = duty_cycle >> 2;
		CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
		__delay_ms(1);
	}
	duty_cycle = 0;
	CCPR2L = duty_cycle >> 2;
	CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
	T2CON &= 0b11111011;
	
}

void pent_fade_in() {
    is_pent_on = TRUE;
	T2CON |= (0x01<<2);
	unsigned short duty_cycle;
	for (duty_cycle = 0; duty_cycle < MAX_PENT_BRIGHTNESS; duty_cycle++) {
		CCPR2L = duty_cycle >> 2;
		CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
		__delay_ms(2);
	}
	
	/* CAUTION: Timer stays on */
}

void pent_fade_out() {
    is_pent_on = FALSE;
	T2CON |= (0x01<<2);
	unsigned short duty_cycle;
	for (duty_cycle = MAX_PENT_BRIGHTNESS; duty_cycle > 0; duty_cycle--) {
		CCPR2L = duty_cycle >> 2;
		CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
		__delay_ms(2);
	}
	duty_cycle = 0;
	CCPR2L = duty_cycle >> 2;
	CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
	T2CON &= 0b11111011;
}

void pent_set(unsigned short duty_cycle) {
	T2CON |= (0x01<<2);
	CCPR2L = duty_cycle >> 2;
	CCP2CON = ((duty_cycle << 4) + 0b00001100) & 0b00111111;
	if (!duty_cycle) {
        is_pent_on = FALSE;
		T2CON &= 0b11111011;
	} else is_pent_on = TRUE;
}
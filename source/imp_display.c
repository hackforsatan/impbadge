/* ImpBadge	
 * imp_display.c
 * shift register driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_display.h"

void display_init() {
	SR1_SER_TRIS = 0;
	SR1_RCLK_TRIS = 0;
	SR1_SCLK_TRIS = 0;
	SR1_SER = 0;
	SR1_RCLK = 0;
	SR1_SCLK = 0;
	
	SR2_SER_TRIS = 0;
	SR2_RCLK_TRIS = 0;
	SR2_SCLK_TRIS = 0;
	SR2_SER = 0;
	SR2_RCLK = 0;
	SR2_SCLK = 0;
	
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
}

void update_touch_display(unsigned char reg_num) {
	if (reg_num == 1) {
		SR1_RCLK = 0;					/* turn latch off */
		for (char i = 0; i < 8; i++) {
			SR1_SCLK = 0;				/* SCLK LOW */
			SR1_SER = ((sr1_display_bits >> i) & 0x01);	/* data bit i */
			SR1_SCLK = 1;				/* SCLK HIGH */
			__delay_ms(1);
			SR1_SCLK = 0;				/* SCLK LOW */
			SR1_SER = 0;				/* data low */
		}
		SR1_RCLK = 1;					/* turn latch on */
		__delay_ms(1);
		SR1_RCLK = 0;
	}
	if (reg_num == 2) {
		SR2_RCLK = 0;					/* turn latch off */
		for (char i = 0; i < 8; i++) {
			SR2_SCLK = 0;				/* SCLK LOW */
			SR2_SER = ((sr2_display_bits >> i) & 0x01);	/* data bit i */
			SR2_SCLK = 1;				/* SCLK HIGH */
			__delay_ms(1);
			SR2_SCLK = 0;				/* SCLK LOW */
			SR2_SER = 0;				/* data low */
		}
		SR2_RCLK = 1;					/* turn latch on */
		__delay_ms(1);
		SR2_RCLK = 0;
	}
};

void set_display_bits(unsigned char bits, unsigned char reg_num) {
	unsigned char flipped_bits = 0x00;
	for (int i = 0; i < 8; i++) {
		flipped_bits += ((bits >> i) & 0x01) << (7-i);
	}
	if (reg_num == 1) sr1_display_bits = flipped_bits;
	if (reg_num == 2) sr2_display_bits = flipped_bits;
	update_touch_display(reg_num);
}

void display_boot_animation() {
	for (unsigned char i = 0; i < 8; i++) {
		set_display_bits(0x01<<i, 1);
		set_display_bits(0x01<<i, 2);
		__delay_ms(50);
	}
	for (unsigned char i = 7; i > 0; i--) {
		set_display_bits(0x01<<i, 1);
		set_display_bits(0x01<<i, 2);
		__delay_ms(50); 
	}
	set_display_bits(0x01, 1);
	set_display_bits(0x01, 2);
	__delay_ms(50);
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
}

void display_animation_up() {
	for (unsigned char i = 7; i > 0; i--) {
		set_display_bits(0x01<<i, 1);
		set_display_bits(0x01<<i, 2);
		__delay_ms(50); 
	}
	set_display_bits(0x01, 1);
	set_display_bits(0x01, 2);
	__delay_ms(50);
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
	
}

void display_animation_down() {
	for (unsigned char i = 0; i < 8; i++) {
		set_display_bits(0x01<<i, 1);
		set_display_bits(0x01<<i, 2);
		__delay_ms(50);
	}
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
}

void display_menu_animation() {
	set_display_bits(0x00, 2); 
	for (unsigned char i = 0; i < 8; i++) {
		set_display_bits(0x01<<i, 1);
		__delay_ms(50);
	}
	set_display_bits(0x00, 1);
	__delay_ms(50);
	set_display_bits(0x01, 1);
}

void display_scripting_animation() {
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
	unsigned char i;
	for (i = 0; i < 11; i++) {
		set_display_bits(i, 1);
		__delay_ms(100);
	}
	__delay_ms(400);
	set_display_bits(i-1, 2);
	__delay_ms(500);
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
}

void display_invalid_input_animation() {
	set_display_bits(0xFF, 1);
	set_display_bits(0xFF, 2);
	__delay_ms(100);
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
	__delay_ms(100);
	set_display_bits(0xFF, 1);
	set_display_bits(0xFF, 2);
	__delay_ms(100);
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
}

void display_alchemy_animation() {
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
	
	unsigned char i;
	unsigned char out = 0;
	for (i = 0; i < 3; i++) {
		out += 0x01 << i;
		set_display_bits(out, 2);
		pent_quickfade();
	}
	set_display_bits(0x00, 1);
	set_display_bits(0x00, 2);
//	unsigned char i;
//	for (i = 0; i < 0x05; i++) {
//		set_display_bits(i, 1);
//		__delay_ms(100);
//	}
//	__delay_ms(400);
//	set_display_bits(0x01, 2);
//	for (i = 0; i < 0x0D; i++) {
//		set_display_bits(i, 1);
//		__delay_ms(100);
//	}
//	__delay_ms(400);
//	set_display_bits(0x03, 2);
//	for (i = 0; i < 0x09; i++) {
//		set_display_bits(i, 1);
//		__delay_ms(100);
//	}
//	__delay_ms(400);
//	set_display_bits(0x07, 2);
//	__delay_ms(500);
//	set_display_bits(0x00, 1);
//	set_display_bits(0x00, 2);
}




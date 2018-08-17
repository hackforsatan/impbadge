/* ImpBadge	
 * imp_display.h
 * shift register driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_DISPLAY_H
#define	IMP_DISPLAY_H

#include <xc.h>
#include <stdio.h>
#include "imp_config.h"
#include "imp_usart.h"
#include "imp_pentagram.h"

/* shift register 1 */
#define SR1_SER         PORTBbits.RB7       /* data */
#define SR1_SER_TRIS    TRISBbits.TRISB7
#define SR1_RCLK        PORTBbits.RB6       /* latch */
#define SR1_RCLK_TRIS   TRISBbits.TRISB6
#define SR1_SCLK        PORTBbits.RB5       /* clock */
#define SR1_SCLK_TRIS   TRISBbits.TRISB5

/* shift register 2 */
#define SR2_SER         PORTDbits.RD2       /* data */
#define SR2_SER_TRIS    TRISDbits.TRISD2
#define SR2_RCLK        PORTDbits.RD1       /* latch */
#define SR2_RCLK_TRIS   TRISDbits.TRISD1
#define SR2_SCLK        PORTDbits.RD0       /* clock */
#define SR2_SCLK_TRIS   TRISDbits.TRISD0


char sr1_display_bits = 0x00;
char sr2_display_bits = 0x00;

void display_init(void);
void update_touch_display(unsigned char);
void set_display_bits(unsigned char, unsigned char);
void display_boot_animation(void);
void display_animation_up(void);
void display_animation_down(void);
void display_menu_animation(void);
void display_scripting_animation(void);
void display_invalid_input_animation(void);
void display_alchemy_animation(void);

#endif	/* IMP_TOUCH_H */


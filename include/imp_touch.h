/* ImpBadge	
 * imp_touch.h
 * cap touch routines for PIC18F4520 and QT1110
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_TOUCH_H
#define	IMP_TOUCH_H

#include "imp_config.h"
#include "imp_usart.h"
#include "QT1110.h"
#include "imp_display.h"
#include "imp_screen.h"

#include <xc.h>

/* configuration */
#define _CHANGE	PORTBbits.RB0       /* interrupt pin */
#define TRIS_CHANGE	TRISBbits.TRISB0

/* parameters */
#define MAX_KEYS    11

/* macros */
#define FORWARD     0xFF
#define BACKWARD    0xBB

/* global variables */
unsigned char outstanding_key = FALSE;
unsigned char last_key_num = 0xEE;
unsigned char wheel_num = 0x00;
unsigned char wheel_greater[3] = {0x01, 0x02, 0x03};
unsigned char wheel_less[3] = {0x05, 0x06, 0x07};

/* types */
typedef enum {
    NO_BUTTON,
    ENTER,
    SCRY
} last_button_flag_t;

typedef enum {
    NORMAL,
    SCRY_CHOOSE,
    SCRY_EDIT,
    INACTIVE
} touch_mode_t;


/* function prototypes */
void touch_init(void);
void touch_interrupt(void);
void touch_normal_update(last_button_flag_t *);
void touch_choose_update(last_button_flag_t *, unsigned char *, unsigned char);
void touch_edit_update(last_button_flag_t *);
void touch_option_update(unsigned char, last_button_flag_t *);
void touch_mode_update(last_button_flag_t *);
void touch_combo_update(last_button_flag_t *);
void touch_alchemy_update(last_button_flag_t *);
void touch_blinky_update(last_button_flag_t *last_button_flag);
unsigned char get_wheel_direction(unsigned char);
void update_wheel_vectors(unsigned char);

#endif	/* IMP_TOUCH_H */


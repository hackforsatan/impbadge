/* ImpBadge	
 * imp_seance.h
 * seance manager for an impbadge
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_SEANCE_H
#define	IMP_SEANCE_H

#include "imp_config.h"
#include "imp_display.h"
#include "imp_modes.h"
#include "imp_usart.h"
#include "imp_pentagram.h"
#include <xc.h>

#define SHORT_TICKS         16
#define LONG_TICKS          2 * SHORT_TICKS
#define START_HALF_PERIODS  8
#define START_TICKS         START_HALF_PERIODS * SHORT_TICKS

unsigned short seance_id;

unsigned char half_periods_until_start = START_HALF_PERIODS;
unsigned char ticks_since_last_transition = 0;
unsigned char ticks_since_last_bit = 0;
unsigned short seance_buffer[5] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000
};
unsigned short seance_in_buffer[5] = {
    0x0000,
    0x0000,
    0x0000,
    0x0000,
    0x0000
};
unsigned char this_sample = 0x00;
unsigned char last_sample = 0x00;
unsigned char num_ticks_high = 0;
unsigned char countdown_ticks = LONG_TICKS+1;
unsigned char counting_down_to_sample = FALSE;
unsigned short *seance_read = seance_buffer;
unsigned short *seance_write = seance_in_buffer;
unsigned short seance_temp = 0x8001;
unsigned char seance_read_bit_offset = 0;
unsigned char seance_write_bit_offset = 0;
unsigned char sampling_on = FALSE;
unsigned char next_byte_valid = FALSE;
//unsigned char start_of_buffer = TRUE;

void seance_init(void);
void seance_received_bit(unsigned char);
void seance_validate(void);

#endif	/* IMP_SEANCE_H */


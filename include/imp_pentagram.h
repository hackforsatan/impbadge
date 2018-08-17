/* ImpBadge	
 * imp_pentagram.h
 * parallel LED driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_PENTAGRAM_H
#define	IMP_PENTAGRAM_H

#include "imp_config.h"
#include <xc.h>

#define MAX_PENT_BRIGHTNESS 625

unsigned char is_pent_on = FALSE;

void pent_init(void);
void pent_breathe(unsigned char, unsigned char);
void pent_quickfade(void);
void pent_fade_in(void);
void pent_fade_out(void);
void pent_set(unsigned short);

#endif	/* IMP_PENTAGRAM_H */


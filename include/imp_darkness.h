/* ImpBadge	
 * imp_darkness.h
 * darkness manager for ImpBadge
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_DARKNESS_H
#define	IMP_DARKNESS_H

#include "imp_config.h"
#include <xc.h>

int dark_val = 0;

void dark_init(void);
void dark_stop(void);

int get_darkness(void);

#endif	/* IMP_DARKNESS_H */


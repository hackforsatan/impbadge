/* ImpBadge	
 * imp_screen.h
 * serial screen buffers and whatnot
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_SCREEN_H
#define	IMP_SCREEN_H

#include "imp_usart.h"
#include "imp_config.h"
#include "imp_rpg.h"
#include <string.h>

#include <xc.h>

#define SCREEN_1_OPTION_1 "believe"
#define SCREEN_1_OPTION_2 "disbelieve"
#define SCREEN_1_OPTION_3 "call me by my true name"
#define SCREEN_1_OPTION_4 "return to the light"
#define SCREEN_1_OPTION_5 "This is option 5."
#define SCREEN_1_OPTION_6 "This is option 6."
#define SCREEN_1_OPTION_7 "This is option 7."
#define SCREEN_1_OPTION_8 "This is option 8."

void screen_init(void);
void screen_print(void);

#endif	/* IMP_SCREEN_H */


/* ImpBadge	
 * imp_modes.h
 * mode manager for ImpBadge
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_MODES_H
#define	IMP_MODES_H

#include "imp_usart.h"
#include "imp_config.h"
#include "imp_rpg.h"
#include "imp_eeprom.h"

#include <xc.h>

unsigned char seance_complete = FALSE;
unsigned char badge_complete = FALSE;

unsigned char badge_unlocked_modes = 5;

//typedef enum alchemy_reagents {   // TODO: Remove
//    ARSENIC,        /* 0 */
//    SILVER,         /* 1 */
//    SALT,           /* 2 */
//    BRIMSTONE,      /* 3 */
//    CINNABAR,       /* 4 */
//    GALENA,         /* 5 */
//    EARTH,          /* 6 */
//    ANTIMONY,       /* 7 */
//    INVALID_SYMBOL  /* 8 */
//} alchemy_reagents_t;

void menu_print_opts(void);
//char const *alchemy_get_reagent(alchemy_reagents_t);  // TODO: Remove
unsigned char alchemy_validate(void);

//const char *arsenic = "arsenic";  // TODO: Remove
//const char *silver = "silver";
//const char *salt = "salt";
//const char *brimstone = "brimstone";
//const char *cinnabar = "cinnabar";
//const char *galena = "galena";
//const char *earth = "earth";
//const char *antimony = "antimony";
//const char *invalid_symbol = "";

const char *impos_banner =
"        `-+syssssss+:`\r\n"
"     `+hy+-`      `-+yy+`\r\n"
"   `oh+mh/`        `/hN+ho`\r\n"
"  :d/  /Mdmy:    -smdM+  +d:\r\n"
" :m-    hm`/ymoomy/`dd    -m:\r\n"
"m:     .Ns`+dddd+.oN.     :m`\r\n"
"+d      `yMmo.  .omNy`      d+\r\n"
"y    -smsdm`     ddsmy:    yo\r\n"
"+d .omy/` -No    oN- `/yms- d+\r\n"
"mhdddhhhhhdMmhhdNdhhhhhdddhm`\r\n"
" :m-       `dd` hd        -m:\r\n"
"  :d+       -No/N-       +d:\r\n"
"   `oh/`     sNNo     `/ho`\r\n"
"     `+yy+-` `md` `-+yy+`\r\n"
"        `-+sssyysss+-`\r\n";

const char *infernal_banner =
"(0xFF returns to Badge Menu)\r\n\r\n"
"Selecting byte: 0x00\r\n";

unsigned char flag[3][3] = {
    {8, 8, 8},
    {8, 8, 8},
    {8, 8, 8}
};

const const const char alchemy_flags[20][3][3] = {
    {
        /* Code 1 */
        {3, 3, 2},
        {6, 3, 5},
        {2, 5, 4}
    },
    {
        /* Code 2 */
        {7, 5, 6},
        {2, 6, 8},
        {2, 8, 8}
    },
    {
        /* Code 3 */
        {6, 8, 8},
        {1, 4, 8},
        {3, 5, 4}
    },
    {
        /* Code 4 */
        {3, 6, 6},
        {3, 8, 8},
        {3, 3, 1}
    },
    {
        /* Code 5 */
        {3, 4, 6},
        {4, 3, 7},
        {5, 7, 5}
    },
    {
        /* Code 6: Non-random */
        {2, 6, 2},
        {3, 2, 8},
        {5, 8, 8}
    },
    {
        /* Code 7 */
        {5, 2, 7},
        {1, 3, 2},
        {4, 8, 8}
    },
    {
        /* Code 8 */
        {2, 8, 8},
        {4, 4, 8},
        {2, 4, 5}
    },
    {
        /* Code 9 */
        {4, 2, 1},
        {1, 8, 8},
        {6, 5, 7}
    },
    {
        /* Code 10 */
        {3, 6, 7},
        {7, 5, 6},
        {4, 5, 8}
    },
    {
        /* Code 11 */
        {5, 5, 1},
        {7, 5, 7},
        {3, 8, 8}
    },
    {
        /* Code 12 */
        {4, 7, 6},
        {6, 1, 8},
        {7, 3, 7}
    },
    {
        /* Code 13 */
        {2, 8, 8},
        {5, 3, 6},
        {5, 4, 3}
    },
    {
        /* Code 14 */
        {1, 1, 4},
        {4, 7, 5},
        {6, 6, 1}
    },
    {
        /* Code 15 */
        {4, 4, 3},
        {6, 6, 8},
        {3, 3, 7}
    },
    {
        /* Code 16 */
        {4, 7, 3},
        {7, 3, 2},
        {5, 6, 8}
    },
    {
        /* Code 17 */
        {2, 1, 3},
        {3, 1, 5},
        {7, 8, 8}
    },
    {
        /* Code 18: Badge completion */
        {3, 1, 6},
        {1, 8, 8},
        {3, 1, 6}
    },
    {
        /* Code 19: Seance completion */
        {4, 7, 7},
        {2, 8, 8},
        {2, 3, 4}
    },
    {
        /* Code 20: Booklet demo */
        {5, 4, 4},
        {6, 1, 2},
        {4, 4, 8}
    }
};


const char * const menu_opts[] = {
    "Blinky",
    "Infernal",
    "Asylum",
    "Alchemy",
    "Seance",
    "Shouts",
    "",
    ""
};

#endif	/* IMP_MODES_H */


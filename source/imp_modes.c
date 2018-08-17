/* ImpBadge	
 * imp_modes.c
 * mode manager for ImpBadge
 * copyright 2018 Hack for Satan
 */

#include "imp_modes.h"

void menu_print_opts() {
	for (char i = 0; i < badge_unlocked_modes; i++) {
		if (selected_option == i) printf("-> ");
		else printf("   ");
		printf("%s\r\n", menu_opts[i]);
	}
    
    for (char i = badge_unlocked_modes; i < 8; i++) {
        if (selected_option == i) printf("-> ");
        else printf("   ");
        printf("(unknown)\r\n");
    }
}

unsigned char alchemy_validate() {
	unsigned int i, j, k;
	unsigned char good_so_far = 1;
	for (i = 0; i < 20; i++) {
		if (imp_eeprom_read(ALCHEMY_FLAG_FLAGS+i)) i++;
		for (j = 0; j < 3; j++) {
			for (k = 0; k < 3; k++) {
				if (flag[j][k] == alchemy_flags[i][j][k])
					good_so_far = 1;
				else {
					good_so_far = 0;
					break;
				}
			}
			if (!good_so_far) break;
		}
		if (good_so_far) break;
	}
	if (good_so_far) {
		imp_eeprom_write(ALCHEMY_FLAG_FLAGS+i, 1);
		
		return i;
	}
	return 0xFF;
}

//char const *alchemy_get_reagent(alchemy_reagents_t reagent) { // TODO: Remove
//	switch (reagent) {
//	case ARSENIC:
//		return arsenic;
//		break;
//	case SILVER:
//		return silver;
//		break;
//	case SALT:
//		return salt;
//		break;
//	case BRIMSTONE:
//		return brimstone;
//		break;
//	case CINNABAR:
//		return cinnabar;
//		break;
//	case GALENA:
//		return galena;
//		break;
//	case EARTH:
//		return earth;
//		break;
//	case ANTIMONY:
//		return antimony;
//		break;
//	case INVALID_SYMBOL:
//		return invalid_symbol;
//		break;
//	default:
//		break;
//	}
//}
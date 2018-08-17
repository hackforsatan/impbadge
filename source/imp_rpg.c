/* ImpBadge	
 * imp_rpg.h
 * text manager for ImpBadge rpg
 * copyright 2018 Hack for Satan
 */

#include "imp_rpg.h"
#include "imp_modes.h"
#include "imp_display.h"

void rpg_print_desc() {
	set_display_bits(0xC0+rpg_state, 2);
	printf("%s\r\n", rpg_get_state_description(rpg_state));
	printf("\r\n");
}

void rpg_print_opts() {
	char i;
	for (i = 0; i < rpg_num_opts; i++) {
		if (selected_option == i) printf("-> ");
		else printf("   ");
		printf("%s\r\n", rpg_options[i]);
	}
	
	if (rpg_show_inventory && seance_complete) {
		printf("\r\nInventory:");
		if (!rpg_unlocked_items) printf(" (empty)\r\n");
		else printf("\r\n");
		for (i; i < rpg_num_opts + rpg_unlocked_items; i++) {
			if (selected_option == i) printf("-> ");
			else printf("   ");
			printf("Use %s\r\n", rpg_items[i-rpg_num_opts]);
		}
	}
}

char const *rpg_get_state_description(rpg_state_t state) {
	char **p = NULL;
	rpg_num_opts = 0;
    rpg_show_inventory = TRUE;
	char const *desc = NULL;
	switch (state) {
	case RPG_TRIGGER: /* 1 option */
		p = rpg_trigger_opts;
		desc = rpg_trigger;
        rpg_show_inventory = FALSE;
		break;
	case RPG_0: /* 3 options */
		p = rpg_0_opts;
		desc = rpg_0;
		break;
	case RPG_0_0: /* 2 options */
		p = rpg_0_0_opts;
		desc = rpg_0_0;
		break;
	case RPG_0_1: /* 2 options */
		p = rpg_0_1_opts;
		desc = rpg_0_1;
		break;
	case RPG_0_2: /* 2 options */
		p = rpg_0_2_opts;
		desc = rpg_0_2;
		break;
	case RPG_0_0_0: /* 1 option */
		p = rpg_0_0_0_opts;
		desc = rpg_0_0_0;
		break;
	case RPG_0_0_1: /* 1 option */
		p = rpg_0_0_1_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_0_0_1;
		break;
	case RPG_0_1_0: /* 1 option */
		p = rpg_0_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_0_1_0;
		break;
	case RPG_0_1_1: /* 1 option */
		p = rpg_0_1_1_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_0_1_1;
		break;
	case RPG_0_2_0: /* 1 option */
		p = rpg_0_2_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_0_2_0;
		break;
	case RPG_0_2_1: /* 1 option */
		p = rpg_0_2_1_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_0_2_1;
		break;
	case RPG_1: /* 2 options */
		p = rpg_1_opts;
		desc = rpg_1;
		break;
	case RPG_1_0: /* 1 option */
		p = rpg_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_1_0;
		break;
	case RPG_1_1: /* 2 options */
		p = rpg_1_1_opts;
		desc = rpg_1_1;
		break;
	case RPG_1_1_0: /* 1 option */
		p = rpg_1_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_1_1_0;
		break;
	case RPG_1_1_1: /* 3 options */
		p = rpg_1_1_1_opts;
		desc = rpg_1_1_1;
		break;
	case RPG_1_1_1_0: /* 1 option */
		p = rpg_1_1_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_1_1_1_0;
		break;
	case RPG_1_1_1_1: /* 1 option */
		p = rpg_1_1_1_1_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_1_1_1_1;
		break;
	case RPG_1_1_1_2: /* 1 option */
		p = rpg_1_1_1_2_opts;
		desc =  rpg_1_1_1_2;
		break;
	case RPG_2: /* 2 options */
		p = rpg_2_opts;
		desc = rpg_2;
		break;
	case RPG_2_0: /* 1 option */
		p = rpg_2_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_2_0;
		break;
	case RPG_2_1: /* 2 options */
		p = rpg_2_1_opts;
		desc = rpg_2_1;
		break;
	case RPG_2_1_0: /* 1 option */
		p = rpg_2_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_2_1_0;
		break;
	case RPG_2_1_1: /* 1 option */
		p = rpg_2_1_1_opts;
		desc = rpg_2_1_1;
		break;
	case RPG_3: /* 2 options */
		p = rpg_3_opts;
		desc = rpg_3;
		break;
	case RPG_3_0: /* 1 option */
		p = rpg_3_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_3_0;
		break;
	case RPG_3_1: /* 3 options */
		p = rpg_3_1_opts;
		desc = rpg_3_1;
		break;
	case RPG_3_1_0: /* 1 option */
		p = rpg_3_1_0_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_3_1_0;
		break;
	case RPG_3_1_1: /* 1 option */
		p = rpg_3_1_1_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_3_1_1;
		break;
	case RPG_3_1_2: /* 1 option */
		p = rpg_3_1_2_opts;
		desc = rpg_3_1_2;
		break;
	case RPG_4: /* 1 option */
		p = rpg_4_opts;
        rpg_show_inventory = FALSE;
		desc = rpg_4;
		break;
    case RPG_KEY:
        p = rpg_key_opts;
        rpg_show_inventory = FALSE;
        desc = rpg_key;
        break;
    case RPG_CUTTERS:
        p = rpg_cutters_opts;
        rpg_show_inventory = FALSE;
        desc = rpg_cutters;
        break;
    case RPG_HAMMER:
        p = rpg_hammer_opts;
        rpg_show_inventory = FALSE;
        desc = rpg_hammer;
        break;
    case RPG_ROPE:
        p = rpg_rope_opts;
        rpg_show_inventory = FALSE;
        desc = rpg_rope;
        break;
            
	default:
		break;
	}
	unsigned char i = 0;
	for (p, i; *p != 0; p++, i++) {
		strcpy(rpg_options[i], *p);
	}
	rpg_num_opts = i;
	
	return desc;
}

rpg_state_t rpg_get_next_state(unsigned char opt_num) {
	switch (rpg_state) {
	case RPG_TRIGGER: /* 1 option */
		return RPG_0;
		break;
	case RPG_0: /* 3 options */
		switch (opt_num) {
		case 0:
			return RPG_0_0;
			break;
		case 1:
			return RPG_0_1;
			break;
		case 2:
			return RPG_0_2;
			break;
        case 3:
			return RPG_KEY;
			break;
        case 4:
			return RPG_CUTTERS;
			break;
        case 5:
			return RPG_HAMMER;
			break;
        case 6:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_0_0: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_0_0_0;
			break;
		case 1:
			return RPG_0_0_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_0_1: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_0_1_0;
			break;
		case 1:
			return RPG_0_1_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_0_2: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_0_2_0;
			break;
		case 1:
			return RPG_0_2_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_0_0_0: /* 1 option */
		return RPG_1;
		break;
	case RPG_0_0_1: /* 1 option */
		return RPG_0;
		break;
	case RPG_0_1_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_0_1_1: /* 1 option */
		return RPG_0;
		break;
	case RPG_0_2_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_0_2_1: /* 1 option */
		return RPG_0;
		break;
	case RPG_1: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_1_0;
			break;
		case 1:
			return RPG_1_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_1_0: /* 1 option */
		RPG_0;
		break;
	case RPG_1_1: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_1_1_0;
			break;
        case 1:
			return RPG_1_1_1;
			break;
        case 2:
			return RPG_CUTTERS;
			break;
        case 3:
			return RPG_HAMMER;
			break;
        case 4:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_1_1_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_1_1_1: /* 3 options */
		switch (opt_num) {
		case 0:
			return RPG_1_1_1_0;
			break;
		case 1:
			return RPG_1_1_1_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_1_1_1_2;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_1_1_1_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_1_1_1_1: /* 1 option */
		return RPG_0;
		break;
	case RPG_1_1_1_2: /* 1 option */
		return RPG_2;
		break;
	case RPG_2: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_2_0;
			break;
		case 1:
			return RPG_2_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_2_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_2_1: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_2_1_0;
			break;
		case 1:
			return RPG_KEY;
			break;
        case 2:
			return RPG_CUTTERS;
			break;
        case 3:
			return RPG_2_1_1;
			break;
        case 4:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_2_1_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_2_1_1: /* 1 option */
		return RPG_3;
		break;
	case RPG_3: /* 2 options */
		switch (opt_num) {
		case 0:
			return RPG_3_0;
			break;
		case 1:
			return RPG_3_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_ROPE;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_3_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_3_1: /* 3 options */
		switch (opt_num) {
		case 0:
			return RPG_3_1_0;
			break;
		case 1:
			return RPG_3_1_1;
			break;
        case 2:
			return RPG_KEY;
			break;
        case 3:
			return RPG_CUTTERS;
			break;
        case 4:
			return RPG_HAMMER;
			break;
        case 5:
			return RPG_3_1_2;
			break;
		default:
			return RPG_0;
			break;
		}
		break;
	case RPG_3_1_0: /* 1 option */
		return RPG_0;
		break;
	case RPG_3_1_1: /* 1 option */
		return RPG_0;
		break;
	case RPG_3_1_2: /* 1 option */
		return RPG_4;
		break;
	case RPG_4: /* 1 option */
		return RPG_0;
		break;
    case RPG_KEY: /* 1 option */
		return RPG_0;
		break;
    case RPG_CUTTERS: /* 1 option */
		return RPG_0;
		break;
    case RPG_HAMMER: /* 1 option */
		return RPG_0;
		break;
    case RPG_ROPE: /* 1 option */
		return RPG_0;
		break;
	default:
		return RPG_0;
		break;
	}
}
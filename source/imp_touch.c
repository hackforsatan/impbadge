/* ImpBadge	
 * imp_touch.c
 * cap touch routines for PIC18F4520 and QT1110
 * copyright 2018 Hack for Satan
 */

#include "imp_touch.h"

void touch_init() {
	/* do we have access to setups? */
	if (qt_read_setups(sizeof(setup_block), (unsigned char *) &setup_block) == TRUE) {
		/* ---- MODIFY SETUP BLOCK HERE ---- */
		setup_block.SPI_EN = 0;
		setup_block.CRC = 0;
		setup_block.MODE = 1;
		setup_block.CHG	= 1;
		
		/* write modified setup block */
		if (qt_write_setups(sizeof(setup_block), (unsigned char *) &setup_block) == TRUE) {
			/* configure interrupt line for touch pads */
			TRIS_CHANGE = 1;		/* as input */
			INTCONbits.INT0IF = 0;		/* clear flag */
			INTCON2bits.INTEDG0 = 0;	/* falling edge */
			INTCONbits.INT0IE = 1;		/* enable */
			
			/* setups succeeded, go home */
			return;
		}
		
	}
	
	/* if we haven't returned yet, setups failed */
	while(1) {
		printf("ERROR: Cannot read or write QT setup block.\r\n");
	}
}

void touch_interrupt() {
	unsigned short key_status = 0;
	
	/* read status bytes into status buffer, then join keys */
	qt_key_status(sizeof(qt_status), qt_status);
	key_status = (qt_status[0]<<8) | qt_status[1];
	
	/* get the number of detected key so it can be checked later */
	unsigned char i = 0;
	for (i = 0; i < MAX_KEYS; i++) {
		if ((key_status >> i) == 1) {
			last_key_num = i;
			break;
		}
	}
	
	/* let everyone know a new key is waiting */
	outstanding_key = TRUE;
}

void touch_normal_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		set_display_bits(0x00, 2);	/* clear queue display */
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (wheel_num == 0xFF) {
				wheel_num = 0x00;
			} else {
				wheel_num++;
			}
		} else if (direction == BACKWARD) {
			if (wheel_num == 0x00) {
				wheel_num = 0xFF;
			} else {
				wheel_num--;
			}
		}
		set_display_bits(wheel_num, 1);
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num == 0x00;
		update_wheel_vectors(wheel_num);
	}
}

void touch_choose_update(last_button_flag_t *last_button_flag, unsigned char *instr_buff, unsigned char num_instructions) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (wheel_num < num_instructions - 1) {
				wheel_num++;
			}
		} else if (direction == BACKWARD) {
			if (wheel_num > 0x00) {
				wheel_num --;
			}
		}
		set_display_bits(instr_buff[wheel_num], 2);
		set_display_bits(wheel_num, 1);
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num == 0x00;
		update_wheel_vectors(wheel_num);
	}
}

void touch_edit_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (wheel_num == 0xFF) {
				wheel_num = 0x00;
			} else {
				wheel_num++;
			}
		} else if (direction == BACKWARD) {
			if (wheel_num == 0x00) {
				wheel_num = 0xFF;
			} else {
				wheel_num--;
			}
		}
		set_display_bits(wheel_num, 1);
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
	}
}

void touch_option_update(unsigned char num_options, last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (selected_option < num_options-1) {
				selected_option++;
			}
		} else {
			if (selected_option > 0) {
				selected_option--;
			}
		}
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	}  else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
	}
}

void touch_mode_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (wheel_num < 0x07) {
				wheel_num++;
			}
		} else if (direction == BACKWARD) {
			if (wheel_num > 0x00) {
				wheel_num--;
			}
		}
		set_display_bits(0x01 << wheel_num, 1);
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num == 0x00; // TODO: What happens if I fix this?
		update_wheel_vectors(wheel_num);
	}
}

void touch_combo_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		unsigned char direction = get_wheel_direction(last_key_num);
		if (direction == FORWARD) {
			if (wheel_num == 0xFF) {
				wheel_num = 0x00;
			} else {
				wheel_num++;
			}
		} else if (direction == BACKWARD) {
			if (wheel_num == 0x00) {
				wheel_num = 0xFF;
			} else {
				wheel_num--;
			}
		}
		set_display_bits(wheel_num, 1);
		update_wheel_vectors(last_key_num);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num = 0x00;
		update_wheel_vectors(wheel_num);
	}
}

void touch_alchemy_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
		wheel_num = 0x01 << last_key_num;
		set_display_bits(0x00, 1);
		__delay_ms(10);
		set_display_bits(wheel_num, 1);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num = 0x00;
		update_wheel_vectors(wheel_num);
	}
}

void touch_blinky_update(last_button_flag_t *last_button_flag) {
	outstanding_key = FALSE;
	if (last_key_num <= 0x07) {
		/* detected key is on wheel */
//		wheel_num = 0x01 << last_key_num;
//		set_display_bits(0x00, 1);
//		__delay_ms(10);
//		set_display_bits(wheel_num, 1);
	} else if (last_key_num == 0x08) {
		/* detected key is ENTER */
		*last_button_flag = ENTER;
	} else if (last_key_num == 0x09) {
		/* detected key is SCRY */
		*last_button_flag = SCRY;
		wheel_num = 0x00;
		update_wheel_vectors(wheel_num);
	}
}

unsigned char get_wheel_direction(unsigned char num) {
	int i;
	for (i = 0; i < 3; i++) {
		if (num == wheel_greater[i]) return FORWARD;
		if (num == wheel_less[i]) return BACKWARD;
	}
	return 0x00;
}

void update_wheel_vectors(unsigned char num) {
	switch (num) {
	case 0:
		wheel_greater[0] = 0x01;
		wheel_greater[1] = 0x02;
		wheel_greater[2] = 0x03;
		wheel_less[0] = 0x07;
		wheel_less[1] = 0x06;
		wheel_less[2] = 0x05;
		break;
	case 1:
		wheel_greater[0] = 0x02;
		wheel_greater[1] = 0x03;
		wheel_greater[2] = 0x04;
		wheel_less[0] = 0x00;
		wheel_less[1] = 0x07;
		wheel_less[2] = 0x06;
		break;
	case 2:
		wheel_greater[0] = 0x03;
		wheel_greater[1] = 0x04;
		wheel_greater[2] = 0x05;
		wheel_less[0] = 0x01;
		wheel_less[1] = 0x00;
		wheel_less[2] = 0x07;
		break;
	case 3:
		wheel_greater[0] = 0x04;
		wheel_greater[1] = 0x05;
		wheel_greater[2] = 0x06;
		wheel_less[0] = 0x02;
		wheel_less[1] = 0x01;
		wheel_less[2] = 0x00;
		break;
	case 4:
		wheel_greater[0] = 0x05;
		wheel_greater[1] = 0x06;
		wheel_greater[2] = 0x07;
		wheel_less[0] = 0x03;
		wheel_less[1] = 0x02;
		wheel_less[2] = 0x01;
		break;
	case 5:
		wheel_greater[0] = 0x06;
		wheel_greater[1] = 0x07;
		wheel_greater[2] = 0x00;
		wheel_less[0] = 0x04;
		wheel_less[1] = 0x03;
		wheel_less[2] = 0x02;
		break;
	case 6:
		wheel_greater[0] = 0x07;
		wheel_greater[1] = 0x00;
		wheel_greater[2] = 0x01;
		wheel_less[0] = 0x05;
		wheel_less[1] = 0x04;
		wheel_less[2] = 0x03;
		break;
	case 7:
		wheel_greater[0] = 0x00;
		wheel_greater[1] = 0x01;
		wheel_greater[2] = 0x02;
		wheel_less[0] = 0x06;
		wheel_less[1] = 0x05;
		wheel_less[2] = 0x04;
		break;
	default:
		break;
	}
}
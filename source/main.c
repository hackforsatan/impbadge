/* ImpBadge	
 * main.c
 * core routine for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_config.h"
#include "imp_usart.h"
#include "imp_display.h"
#include "imp_touch.h"
#include "imp_script.h"
#include "imp_pentagram.h"
#include "imp_rpg.h"
#include "imp_modes.h"
#include "imp_darkness.h"
#include "imp_seance.h"
#include "imp_eeprom.h"
#include "QT1110.h"

#include <xc.h>
#include <pic18f4520.h>

/* parameters */
#define INSTRUCTION_BUFFER_SIZE 256

/* types */
typedef enum {
	INVALID_MODE,
	SCRIPTING_MODE,
	SERIAL_RESPONSE_MODE,
	MENU_MODE,
	SEANCE_MODE,
	BLINKY_MODE,
	COMBO_MODE,
    SHOUTS_MODE
} badge_mode_t;

typedef enum {
	BLINKY_CLOCK,
	BLINKY_WAVE,
	BLINKY_CHASE,
	BLINKY_MORSE,
	BLINKY_NIGHTLIGHT,
    BLINKY_PENTAGRAM_ON,
	BLINKY_BREATHE,
} blinky_t;

/* function prototypes */
void imp_init(void);
void blinky_mode(last_button_flag_t *, badge_mode_t *);
void blinky_clock(void);
void blinky_nightlight(void);
void blinky_morse(void);
void blinky_breathe(void);
void blinky_chase(void);
void blinky_wave(void);
void blinky_pent_on(void);
void command_mode(unsigned char *, last_button_flag_t *, badge_mode_t *, touch_mode_t *);
void handle_command(badge_mode_t *);
void waiting_on_mode_change(last_button_flag_t *, badge_mode_t *);
void prepare_badge_menu(badge_mode_t *);
void serial_response_mode(last_button_flag_t *, badge_mode_t *);
void alchemy_mode(last_button_flag_t *, badge_mode_t *);
void seance_mode(badge_mode_t *);
void shouts_mode(badge_mode_t *);

void interrupt high_priority imp_isr_high(void);
//void interrupt low_priority imp_isr_low(void);

/* globals */
//unsigned char instr_buff[INSTRUCTION_BUFFER_SIZE] = {
//    IMP_LBL,
//    0x01,
//    IMP_MOVVW, 0xF0,
////    IMP_ADDVW, 0x01,
//    IMP_MOVWR, IMP_DISP,
//    IMP_DS, 0x01,
//    IMP_MOVVW, 0x0F,
////    IMP_ADDVW, 0x01,
//    IMP_MOVWR, IMP_DISP,
//    IMP_DS, 0x01,
//    IMP_BR,
//    0x01,
//    IMP_END
//}; // TODO: Replace with {IMP_END}
unsigned char instr_buff[INSTRUCTION_BUFFER_SIZE] = {IMP_END};
unsigned char *instr_read_ptr, *instr_write_ptr = instr_buff;
blinky_t blinky = BLINKY_CLOCK;
unsigned char blinky_count = 0;
unsigned short blinky_time = 0;
unsigned short seance_ticks = 0;
unsigned char seance_clock = 0x00;

void main() {
	badge_mode_t badge_mode = MENU_MODE;
	
	last_button_flag_t last_button_flag = NO_BUTTON;
	touch_mode_t touch_mode = NORMAL;
	
	imp_init();
	
	/* set up timer 0: 
	 * off, 16-bit, instr. clock, no prescaler
	 * pre-load with 26,473 for 128 Hz interrupt
	 */
	T0CON = 0b00001000;
	TMR0IF = 0;
	TMR0IE = 0;
	
	unsigned char wheel_temp = 0x00;
	
	while (1) {
		if (badge_mode == SCRIPTING_MODE) {
			TMR0ON = 0;
			command_mode(&wheel_temp, &last_button_flag, &badge_mode, &touch_mode);
		} else if (badge_mode == MENU_MODE) {
			TMR0ON = 1;
			waiting_on_mode_change(&last_button_flag, &badge_mode);
		} else if (badge_mode == SERIAL_RESPONSE_MODE) {
			TMR0ON = 0;
			serial_response_mode(&last_button_flag, &badge_mode);
		} else if (badge_mode == SEANCE_MODE) {
			seance_id = 0xB000 + (((TMR0H<<8)+TMR0L)>>4);
			TMR0ON = 0;
			if (seance_complete) pent_fade_in();
			seance_mode(&badge_mode);
		} else if (badge_mode == BLINKY_MODE) { 
			TMR0ON = 0;
			blinky_mode(&last_button_flag, &badge_mode);
		} else if (badge_mode == COMBO_MODE) {
			TMR0ON = 0;
			alchemy_mode(&last_button_flag, &badge_mode);
		} else if (badge_mode == SHOUTS_MODE) {
            TMR0ON = 0;
            shouts_mode(&badge_mode);
        } else {
			printf("ERROR: Invalid badge mode.\r\n");
		}
	}
}

void imp_init() {
	/* initialize peripherals */
	usart_init();
	display_init();
	display_menu_animation();
	qt_init();
	touch_init();
	usart_clr_screen();
	printf("%s\r\n", impos_banner);
	pent_init();
	selected_option = 0;
	
	/* ---- USING ONE INTERRUPT PRIORITY ... ---- */
	RCONbits.IPEN = 0;	/* only one priority */
	INTCONbits.GIE = 1;	/* enable interrupts */
	INTCONbits.PEIE = 1;
	
	/*---- ... OR, USING TWO INTERRUPT PRIORITIES ----*/
//	RCONbits.IPEN = 1;	/* two interrupt priorities */
//	INTCONbits.GIEH = 1;	/* enable high-priority interrupts */
//	INTCONbits.GIEL = 1;	/* enable low-priority interrupts */
	
	seance_complete = imp_eeprom_read(SEANCE_FLAG);
    badge_complete = imp_eeprom_read (BADGE_FLAG);
    if (imp_eeprom_read(BOOKLET_FLAG)) badge_unlocked_modes = 6;
    
    menu_print_opts();
    TRISDbits.TRISD6 = 0;   /* IMP Left 1 */
	TRISDbits.TRISD7 = 0;   /* IMP Left 2 */
	TRISDbits.TRISD3 = 0;   /* IMP Right 1 */
	TRISDbits.TRISD4 = 0;   /* IMP Right 2 */
}

void interrupt high_priority imp_isr_high(void) {
	if (INTCONbits.INT0IF) {
		touch_interrupt();
		INTCONbits.INT0IF = 0;
	} else if (INTCONbits.TMR0IF && INTCONbits.TMR0IE) {
		TMR0ON = 0;
		
		/* Seance receive: read incoming data into buffer and update buffer to send */
		last_sample = this_sample;
		this_sample = PORTDbits.RD7;
		
		/* if waiting for a start bit */
		if (!sampling_on) {
			if (last_sample && this_sample) num_ticks_high++;
			/* wait until HIGH for longer than T=LONG_TICKS */
			if (num_ticks_high > LONG_TICKS) {
				/* wait for next transition  (HIGH -> LOW) */
				if (last_sample && !this_sample) counting_down_to_sample = TRUE;
				/* wait longer than (1/2)T=SHORT_TICKS */
				if (counting_down_to_sample) countdown_ticks--;
				if (!countdown_ticks) {
					sampling_on = TRUE;
					countdown_ticks = LONG_TICKS+1;
					num_ticks_high = 0;
					counting_down_to_sample = FALSE;
					ticks_since_last_bit = SHORT_TICKS+1;
				}
			}
		} else { /* if not waiting for a start bit */
			/* if a transition occurred and time since last bit > (1/2)T=SHORT_TICKS */
			if (this_sample != last_sample && ticks_since_last_bit > SHORT_TICKS) {
				/* this is a bit; save it */
				ticks_since_last_bit = 0;
				seance_received_bit(this_sample);
			} else {
				ticks_since_last_bit++;
			}
		}
		
		/* Seance send: read from buffer and send over IMP right */
		if (++seance_ticks % 16 == 0) {
			seance_clock ^= 0xFF;
			if (half_periods_until_start) {
				if (half_periods_until_start == 2) {
					PORTDbits.RD4 = 0;
				}
				half_periods_until_start--;
			}
			else {
				PORTDbits.RD4 = ((*seance_read) >> seance_read_bit_offset) ^ seance_clock;
				//PORTDbits.RD4 = seance_clock;

				/* If clock transitioned to LOW this time, change the data */
				if (!seance_clock) {
					if (++seance_read_bit_offset == 16) {
						seance_read_bit_offset = 0;
						if (++seance_read == seance_buffer+5) {
							seance_read = seance_buffer;
						}
						set_display_bits((unsigned char)(*seance_read), 1);
						half_periods_until_start = START_HALF_PERIODS;
						PORTDbits.RD4 = 1;
					}
				}
			}
		}
		
		unsigned short preload = 55770;
		TMR0H = preload >> 8;
		TMR0L = preload;
		TMR0IF = 0;
		TMR0ON = 1;
	} else if (PIR1bits.TMR1IF && PIE1bits.TMR1IE) {
		TMR1ON = 0;
		switch (blinky) {
		case BLINKY_CLOCK:
			if (++blinky_count == 73) {
				blinky_count = 0;
				set_display_bits(++blinky_time>>8, 2);
				set_display_bits(blinky_time, 1);
			}
			break;
		case BLINKY_NIGHTLIGHT:
			break;
		default:
			break;
		}
		TMR1IF = 0;
		TMR1ON = 1;
	} else if (PIR1bits.ADIF && PIE1bits.ADIE) {
		dark_val = (ADRESH<<8)+ADRESL;
		PIR1bits.ADIF = 0;
		ADCON0bits.GO = 1;
	}
	
}

//void interrupt low_priority imp_isr_low(void) {
//	
//}

void command_mode(unsigned char *wheel_temp, last_button_flag_t *last_button_flag, badge_mode_t *badge_mode, touch_mode_t *touch_mode) {
	if (outstanding_key) {
		/* check the current mode and call the proper key handler */
		if (*touch_mode == SCRY_CHOOSE) {
			touch_choose_update(last_button_flag, instr_buff, instr_write_ptr - instr_buff);
			switch (*last_button_flag) {
			case NO_BUTTON: /* or wheel key */
				break;
			case ENTER:
				*wheel_temp = wheel_num;
				wheel_num = instr_buff[wheel_num];
				set_display_bits(wheel_num, 1);
				*touch_mode = SCRY_EDIT;
				printf("MODE: SCRY [edit] ...\r\n");
				break;
			case SCRY:
				display_scripting_animation();
				wheel_num = 0x00;
				*touch_mode = NORMAL;
				printf("MODE: NORMAL ...\r\n");
				break;
			default:
				break;
			}
		} else if (*touch_mode == SCRY_EDIT) {
			touch_edit_update(last_button_flag);
			switch (*last_button_flag) {
			case NO_BUTTON: /* or wheel key */
				break;
			case ENTER:
				instr_buff[*wheel_temp] = wheel_num;
				wheel_num = *wheel_temp;
				set_display_bits(instr_buff[wheel_num], 2);
				set_display_bits(wheel_num, 1);
				*touch_mode = SCRY_CHOOSE;
				printf("MODE: SCRY [choose] ...\r\n");
				pent_quickfade();
				break;
			case SCRY:
				wheel_num = *wheel_temp;
				set_display_bits(wheel_num, 1);
				*touch_mode = SCRY_CHOOSE;
				printf("MODE: SCRY [choose] ...\r\n");
				break;
			default:
				break;
			}
		} else { /* *touch_mode == NORMAL */
			touch_normal_update(last_button_flag);
			switch (*last_button_flag) {
			case NO_BUTTON: /* or wheel key */
				break;
			case ENTER:
				if (imp_check_type(wheel_num) == IMP_TYPE_COMMAND) {
					handle_command(badge_mode);
					break;
				}
				/* if command doesn't require special handling,
				 * add number to instruction buffer,
				 * then set buffer display with it */
				if (instr_write_ptr - instr_buff < INSTRUCTION_BUFFER_SIZE) {
					*instr_write_ptr = wheel_num;
					set_display_bits(*instr_write_ptr, 2);
					printf("Added %x to the instruction queue.\r\n", *instr_write_ptr);
					instr_write_ptr++;
					pent_quickfade();
				}
				break;
			case SCRY:
				if (instr_write_ptr > instr_buff) {
					wheel_num = instr_write_ptr - instr_buff;
					wheel_num--;
					set_display_bits(instr_buff[wheel_num], 2);
					set_display_bits(wheel_num, 1);
					*touch_mode = SCRY_CHOOSE;
					printf("MODE: SCRY [choose] ...\r\n");
				}
				break;
			default:
				break;
			}
		}

		*last_button_flag = NO_BUTTON;
	}
}

void handle_command(badge_mode_t *badge_mode) {
	if (wheel_num == IMP_MENU) {
		/* change to menu mode */
		prepare_badge_menu(badge_mode);
		return;
	}
	if (wheel_num == IMP_SVEEP) {
		/* save instruction queue to EEPROM */
        for (char i = 0; i < INSTRUCTION_BUFFER_SIZE; i++) {
            imp_eeprom_write(INFERNAL_SCRIPT+i, instr_buff[i]);
            if (instr_buff[i] == IMP_END) break;
        }
		return;
	}
	if (wheel_num == IMP_LDEEP) {
		/* load instruction queue from EEPROM */
        for (char i = 0; i < INSTRUCTION_BUFFER_SIZE; i++) {
            instr_buff[i] = imp_eeprom_read(INFERNAL_SCRIPT+i);
            if (instr_buff[i] == IMP_END) break;
        }
		return;
	}
	if (wheel_num == IMP_NUKE) {
		/* get confirmation, then nuke badge */
		// TODO: nuke
        for (int i = 0; i < 20; i++) {
            imp_eeprom_write(i, FALSE);
        }
        imp_eeprom_write(INFERNAL_SCRIPT, IMP_END);
        badge_complete = FALSE;
        seance_complete = FALSE;
        badge_unlocked_modes = 5;
        printf("Badge progress destroyed.\r\n");
        __delay_ms(1000);
        prepare_badge_menu(badge_mode);
		return;
	}
	if (wheel_num == IMP_RUN) {
        imp_reg_comp = 0;
        imp_reg_disp = 0;
        imp_reg_wheel = 0;
        imp_reg_wreg = 0;
        for (char i = 0; i < 16; i++) imp_regs[i] = 0;
		/* execute instruction queue */
        for (char i = 0; i < INSTRUCTION_BUFFER_SIZE; i++) {
            if (instr_buff[i] == IMP_END) {
                imp_run_script(instr_buff, i+1);
                break;
            }
        }
        PORTDbits.RD6 = 0;   /* IMP Left 1 */
        PORTDbits.RD7 = 0;   /* IMP Left 2 */
        PORTDbits.RD3 = 0;   /* IMP Right 1 */
        PORTDbits.RD4 = 0;   /* IMP Right 2 */
		return;
	}
}

void waiting_on_mode_change(last_button_flag_t *last_button_flag, badge_mode_t *badge_mode) {
	if (outstanding_key) {
		touch_mode_update(last_button_flag);
		switch (*last_button_flag) {
		case NO_BUTTON: /* or wheel key */
			selected_option = wheel_num;
			uart_clr_last_n_lines(8);
			menu_print_opts();
			break;
		case ENTER:
			switch (wheel_num) {
			case 0x00:
				usart_clr_screen();
				printf("===== BLINKY MODE =====\r\n");
				*badge_mode = BLINKY_MODE;
				break;
			case 0x01:
				usart_clr_screen();
				printf("%s\r\n", infernal_banner);
				*badge_mode = SCRIPTING_MODE;
				display_scripting_animation();
				break;
			case 0x02:
				usart_clr_screen();
				unsigned char count = 0;
				for (unsigned char i = 0; i < 10; i++) {
					if (imp_eeprom_read(ALCHEMY_FLAG_FLAGS+i)) if(++count >= 4) count = 4;
				}
				rpg_unlocked_items = count;
				*badge_mode = SERIAL_RESPONSE_MODE;
				selected_option = 0;
				set_display_bits('T', 2);
				set_display_bits('R', 1);
				rpg_print_desc();
				break;
			case 0x03:
				usart_clr_screen();
				printf("=== Alchemy Mode ===\r\n");
				*badge_mode = COMBO_MODE;
				display_alchemy_animation();
				break;
			case 0x04:
				usart_clr_screen();
				*badge_mode = SEANCE_MODE;
				set_display_bits(0x00, 1);
				set_display_bits(0x00, 2);
				break;
            case 0x05:
                if (badge_unlocked_modes > 5) {
                    usart_clr_screen();
                    *badge_mode = SHOUTS_MODE;
                    set_display_bits(0xC3, 1);
                    set_display_bits(0xC3, 2);
                    break;
                }
                /* Fall through */    
			default:
				display_invalid_input_animation();
				set_display_bits(0x01<<wheel_num, 1);
				break;
			}
			break;
		case SCRY:
			break;
		default:
			printf("ERROR: Invalid input.\r\n");
			break;
		}

		*last_button_flag = NO_BUTTON;
	}
}

void serial_response_mode(last_button_flag_t *last_button_flag, badge_mode_t *badge_mode) {
	rpg_print_opts();
	set_display_bits(0x01 << selected_option, 1);
	while(!outstanding_key)
		;
	if (rpg_show_inventory && seance_complete) {
		uart_clr_last_n_lines(rpg_num_opts+rpg_unlocked_items+2);
		touch_option_update(rpg_num_opts+rpg_unlocked_items, last_button_flag);
	} else {
		uart_clr_last_n_lines(rpg_num_opts);
		touch_option_update(rpg_num_opts, last_button_flag);
	}
	if (*last_button_flag == SCRY) {
		prepare_badge_menu(badge_mode);
	} else if (*last_button_flag == ENTER) {
		rpg_state = rpg_get_next_state(selected_option);
        if (rpg_state == RPG_4) {
            badge_complete = TRUE;
            imp_eeprom_write(BADGE_FLAG, TRUE);
        }
		selected_option = 0;
		usart_clr_screen();
		rpg_print_desc();
		pent_quickfade();
	}
	*last_button_flag = NO_BUTTON;
	// TODO: implement response via RX
	//usart_clr_rx();
}

void seance_mode(badge_mode_t *badge_mode) {
	seance_init();
	while (1) {
		if (outstanding_key && last_key_num == 0x09) {
			outstanding_key = 0;
			TMR0IE = 0;
			TMR0IF = 0;
			prepare_badge_menu(badge_mode);
			return;
		}
	}
}

void alchemy_mode(last_button_flag_t *last_button_flag, badge_mode_t *badge_mode) {
	wheel_num = 0x00;
	unsigned char out = 0;
	unsigned char validation_num = 0xFF;
	unsigned char digit_num = 0;
	unsigned char chunk_num = 0;
	unsigned char temp = 0x00;
	while (1) {
		if (outstanding_key) {
			touch_alchemy_update(last_button_flag);
			switch (*last_button_flag) {
			case NO_BUTTON: /* or wheel key */
				flag[chunk_num][digit_num] = last_key_num;
				if (++digit_num == 3) {
				/* fall through */
				} else break;
			case ENTER:
				out += 0x01 << chunk_num;
				set_display_bits(out, 2);
				digit_num = 0x00;
				set_display_bits(0x00, 1);
				/* increase chunk number until 3 
				 * then print, validate, and reset */
				if (++chunk_num == 3) {
					out = 0;
					chunk_num = 0;
//					printf("----\r\n"); // TODO: Remove
//					for (char i = 0; i < 3; i++) {
//						for (char j = 0; j < 3; j++) {
//							printf("%10s ", alchemy_get_reagent(flag[i][j]));
//						}
//						printf("\r\n");
//					}
					
					validation_num = alchemy_validate();
					if (validation_num == 0xFF) {
						printf("That formula is no good.\n\r");
						display_invalid_input_animation();
					} else {
//						printf("You have found formula #%d\r\n", validation_num+1); // TODO: Remove
                        printf("Transmogrification successful.\r\n");
                        if (validation_num == BOOKLET_FLAG) {
                            badge_unlocked_modes = 6; // TODO: Make this dynamic if more modes
                        } else if (validation_num == SEANCE_FLAG) {
                            seance_complete = TRUE;
                        } else if (validation_num == BADGE_FLAG) {
                            for (char i = 0; i < 20; i++) imp_eeprom_write(i, TRUE);
//                            imp_eeprom_write(SEANCE_FLAG, TRUE);  // TODO: Remove
//                            imp_eeprom_write(BOOKLET_FLAG, TRUE);
                            badge_unlocked_modes = 6;
                            seance_complete = TRUE;
                            badge_complete = TRUE;
                            printf("DEGREELESSNESS MODE ON\r\n");
                        } else if (validation_num < 10 && rpg_unlocked_items < 4) {
                            printf("Your toolbox feels heavier.\r\n");
                        }
						validation_num = 0xFF;
						display_alchemy_animation();
					}
					
					/* reset flag */
					for (char i = 0; i < 3; i++) {
						for (char j = 0; j < 3; j++) {
							flag[i][j] = 8;
						}
					}
				} else {
					pent_quickfade();
				}
				break;
			case SCRY:
				/* reset flag */
				for (char i = 0; i < 3; i++) {
					for (char j = 0; j < 3; j++) {
						flag[i][j] = 8;
					}
				}
				prepare_badge_menu(badge_mode);
				return;
				break;	
			default:
				break;
			}
			
		}
		*last_button_flag = NO_BUTTON;
	}
	
}

void shouts_mode(badge_mode_t *badge_mode) {
    printf("Shouts to:\r\n\r\n"
            "@RYANxSHEFFIELD\r\n"
            "@Team_Missing_No\r\n"
            "Angersock\r\n"
            "Numinit\r\n"
            "adderall\r\n"
            "\r\nTouch [scry] to return to badge menu.\r\n"
        );
    while(1) {
        if (outstanding_key && last_key_num == 0x09) {
			outstanding_key = 0;
			prepare_badge_menu(badge_mode);
            return;
        }
    }
}

void blinky_mode(last_button_flag_t *last_button_flag, badge_mode_t *badge_mode) {
	/* TODO: Blinky selection animation*/
	while (1) {
		set_display_bits(0b11001100, 1);
		set_display_bits(0b00110011, 2);
		__delay_ms(40);
		set_display_bits(0b00110011, 1);
		set_display_bits(0b11001100, 2);
		__delay_ms(40);
		if (outstanding_key) {
			touch_blinky_update(last_button_flag);
			switch (*last_button_flag) {
			case NO_BUTTON: /* or wheel key */
				blinky = last_key_num;
				set_display_bits(0x01<<blinky, 1);
				set_display_bits(0x00, 2);
				set_display_bits(0x00, 1);
				switch (blinky) {
				case BLINKY_CLOCK:
					blinky_clock();
					break;
				case BLINKY_NIGHTLIGHT:
					blinky_nightlight();
					if (is_pent_on) pent_set(0);
					break;
                case BLINKY_MORSE:
                    blinky_morse();
                    if (is_pent_on) pent_set(0);
                case BLINKY_BREATHE:
                    if (badge_complete) blinky_breathe();
                    break;
                case BLINKY_CHASE:
                    blinky_chase();
                    break;
                case BLINKY_WAVE:
                    blinky_wave();
                    break;
                case BLINKY_PENTAGRAM_ON:
                    if (seance_complete) blinky_pent_on();
                    break;
				default:
					break;
				}
				/* fall through */
			case SCRY:
				prepare_badge_menu(badge_mode);
				return;
				break;
			default:
				break;
			}
			*last_button_flag = NO_BUTTON;
		}
	}
}

void blinky_clock() {
	/* set up timer 1: 
	 * off, 16-bit, instr. clock, no prescaler
	 * pre-load with 26,473 for 128 Hz interrupt
	 */
	blinky_count = 0;
	blinky_time = 0;
	unsigned short preload = 0x00;
	T0CON = 0b1011000;	/* Interrupt every ~0.1s */
	TMR1H = preload >> 8;
	TMR1L = preload;
	TMR1IF = 0;
	TMR1IE = 1;
	TMR1ON = 1;
	
	while (1) {
		if (outstanding_key && last_key_num == 0x09) {
			TMR1IE = 0;
			TMR1ON = 0;
			TMR1IF = 0;
			outstanding_key = 0;
			return;
		}
	}
}

void blinky_nightlight() {
	unsigned short dark_temp = 0;
	unsigned char i;
	unsigned char byte_to_display[] = {
		0x00, 0xC0, 0xF0, 0xFC, 0xFF
	};
	dark_init();
	while (1) {
		dark_temp = dark_val;
		if (dark_temp < 100) dark_temp = 100;
		if (dark_temp > 800) dark_temp = 800;
		touch_interrupt();
		if (dark_temp <= 350) i = 4;
		else if (dark_temp <= 450) i = 3;
		else if (dark_temp <= 550) i = 2;
		else if (dark_temp <= 650) i = 1;
		else i = 0;
		
		set_display_bits(byte_to_display[i], 1);
		set_display_bits(byte_to_display[i], 2);
		if (i == 4 && seance_complete) pent_set(MAX_PENT_BRIGHTNESS);
		else if (is_pent_on) pent_set(0);
		
		if (outstanding_key && last_key_num == 0x09) {
			dark_stop();
			set_display_bits(0x00, 1);
			set_display_bits(0x00, 2);
			if (is_pent_on) pent_set(0);
			outstanding_key = 0;
			break;
		}
	}
	pent_quickfade();
}

void blinky_morse() {
//    unsigned char pent_on = FALSE;
    
    INTCONbits.GIE = 0;
    while (1) {
        unsigned short key_status = 0;
	
        qt_key_status(sizeof(qt_status), qt_status);
        key_status = (qt_status[0]<<8) | qt_status[1];
        if ((key_status >> 8) == 1) {
//            pent_set(MAX_PENT_BRIGHTNESS);
            set_display_bits(0xFF, 1);
            set_display_bits(0xFF, 2);
        } else if ((key_status >> 9) == 1) {
//            pent_set(0);
            set_display_bits(0x00, 1);
            set_display_bits(0x00, 2);
            outstanding_key = FALSE;
            INTCONbits.GIE = 1;
            return;
        } else {
//            pent_set(0);
            set_display_bits(0x00, 1);
            set_display_bits(0x00, 2);
        }
    }
}

void blinky_breathe() { // TODO: Rework Badge complete/Seance complete unlock states
//    if (badge_complete) {
//        set_display_bits(0xFF, 1);
//        set_display_bits(0xFF, 2);
//    }
    while (1) {
        if (outstanding_key && last_key_num == 0x09) {
            outstanding_key = FALSE;
            set_display_bits(0x00, 1);
            set_display_bits(0x00, 2);
            return;
        }
        pent_breathe(40, 40);
        __delay_ms(1000);
    }
}

void blinky_pent_on() {
    pent_fade_in();
    while (1) {
        if (outstanding_key && last_key_num == 0x09) {
            pent_fade_out();
            outstanding_key = FALSE;
            set_display_bits(0x00, 1);
            set_display_bits(0x00, 2);
            return;
        }
    }
}

void blinky_chase() {
    unsigned short out_byte = 0x00F0;
    char i;
    while(1) {
        if (outstanding_key && last_key_num == 0x09) {
            outstanding_key = FALSE;
            set_display_bits(0x00, 1);
            set_display_bits(0x00, 2);
            return;
        } 
        for (i = 0; i < 12; i++) {
            set_display_bits((out_byte<<i)>>8, 2);
            __delay_ms(20);
        }
        set_display_bits(0x00, 2);
        for (i = 0; i < 12; i++) {
            set_display_bits((out_byte<<(12-i))>>8, 1);
            __delay_ms(20);
        }
        set_display_bits(0x00, 1);
    }
}

void blinky_wave() {
    unsigned char out_bytes[] = {
        0b10000000,
        0b11000000,
        0b11100000,
        0b11110000,
        0b11111000,
        0b11111100,
        0b11111110,
        0b11111111
    };
    /* set up timer 1: 
	 * off, 16-bit, instr. clock, no prescaler
	 */
	T0CON = 0b1011000;
	TMR1IF = 0;
	TMR1IE = 0;
	TMR1ON = 1;
    
    char i;
    
    while (1) {
        unsigned char bound = TMR1L % 9;
        for (i = 0; i < bound; i++) {
            set_display_bits(out_bytes[i], 1);
            set_display_bits(out_bytes[i], 2);
            __delay_ms(50);
        }
        
        while (i--) {
            set_display_bits(out_bytes[i], 1);
            set_display_bits(out_bytes[i], 2);
            __delay_ms(50);
        }
        
        if (outstanding_key && last_key_num == 0x09) {
            TMR1ON = 0;
			TMR1IF = 0;
			outstanding_key = 0;
			return;
        }
    }
}

void prepare_badge_menu(badge_mode_t *badge_mode) {
	TRISDbits.TRISD6 = 0;   /* IMP Left 1 */
	TRISDbits.TRISD7 = 0;   /* IMP Left 2 */
	TRISDbits.TRISD3 = 0;   /* IMP Right 1 */
	TRISDbits.TRISD4 = 0;   /* IMP Right 2 */
	*badge_mode = MENU_MODE;
	wheel_num = 0x00;
	display_menu_animation();
	usart_clr_screen();
	printf("%s\r\n", impos_banner);
	selected_option = 0;
    pent_quickfade();
	menu_print_opts();
}
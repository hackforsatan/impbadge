/* ImpBadge	
 * imp_script.c
 * Infernal ISA to be interpreted by PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_script.h"

instruction_type_t imp_check_type(unsigned char instr) {
	if (instr == 0xDD || instr == 0xEE || instr == 0xFF || (instr >= 0xF3  && instr <= 0xF5))
		return IMP_TYPE_COMMAND;
	if (instr == 0x00 || instr > 0x80) return IMP_TYPE_ZERO;
	
	return IMP_TYPE_ONE;
}

void imp_run_script(unsigned char *instruction_queue, unsigned char N) {
//  TRISDbits.TRISD6 = 0;   /* IMP Left 1 */    // TODO: Remove
//	TRISDbits.TRISD7 = 0;   /* IMP Left 2 */
//	TRISDbits.TRISD3 = 0;   /* IMP Right 1 */
//	TRISDbits.TRISD4 = 0;   /* IMP Right 2 */
	PORTDbits.RD6 = 0;
    PORTDbits.RD7 = 0;
	PORTDbits.RD3 = 0;
	PORTDbits.RD4 = 0;
    
	program_ended = 0;
	/* initialize all registers and labels to 0x00 */
	unsigned char next_label_index = 0;
	unsigned char i;
	for (i = 0; i < MAX_LABELS; i++) {
		labels[i][0] = 0x00;
        labels[i][1] = 0x00;
        imp_regs[i] = 0x00;
	}
	
	/* crawl instruction queue for labels */
	for (i = 0; i < N; i++) {
		if (imp_check_type(instruction_queue[i]) == IMP_TYPE_ONE) {
			if (instruction_queue[i] == IMP_LBL && next_label_index < MAX_LABELS) {
				labels[next_label_index][0] = instruction_queue[i+1];
                labels[next_label_index][1] = i+1;
                next_label_index++;
			}
			i++;
		}
	}
	
	/* execute queue of instructions */
	for (i = 0; i < N; i++) {
		if (imp_check_type(instruction_queue[i]) == IMP_TYPE_ZERO) {
			i = imp_exec_type_zero(instruction_queue[i], i);
			if (program_ended) return;
		} else { /* IMP_TYPE_ONE */
			i = imp_exec_type_one(instruction_queue[i], instruction_queue[i+1], i);
		}
	}
}

unsigned char imp_exec_type_zero(unsigned char instr, unsigned char pc) {
	switch (instr) {
	case IMP_NOP:
		break;
	case IMP_CLR:
		imp_reg_wreg = 0x00;
		break;
	case IMP_INC:
		imp_reg_wreg++;
		break;
	case IMP_DEC:
		imp_reg_wreg--;
		break;
	case IMP_WINP:
		break;
	case IMP_MOVWC:
		imp_reg_comp = imp_reg_wreg;
		break;
	case IMP_END:
		program_ended = 1;
		break;
    case IMP_L1ON:
        PORTDbits.RD6 = 1;
        break;
    case IMP_L1OFF:
        PORTDbits.RD6 = 0;
        break;
    case IMP_L2ON:
        PORTDbits.RD7 = 1;
        break;
    case IMP_L2OFF:
        PORTDbits.RD7 = 0;
        break;
    case IMP_R1ON:
        PORTDbits.RD3 = 1;
        break;
    case IMP_R1OFF:
        PORTDbits.RD3 = 0;
        break;
    case IMP_R2ON:
        PORTDbits.RD4 = 1;
        break;
    case IMP_R2OFF:
        PORTDbits.RD4 = 0;
        break;
	default:
		break;
	}
    return pc;
}

unsigned char imp_exec_type_one(unsigned char instr, unsigned char arg, unsigned char pc) {
    unsigned char branch = FALSE;
	switch (instr) {
	case IMP_MOVVW:
		imp_reg_wreg = arg;
		break;
	case IMP_MOVRW:
		if (arg >= 0x00 && arg <= 0x0F) imp_reg_wreg = imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_wreg = imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_wreg = imp_reg_wheel;
        else if (arg == IMP_COMP) imp_reg_wreg = imp_reg_comp;
		break;
	case IMP_MOVWR:
		if (arg >= 0x00 && arg <= 0x0F) imp_regs[arg] = imp_reg_wreg;
        else if (arg == IMP_DISP) imp_reg_disp = imp_reg_wreg;
        else if (arg == IMP_WHEEL) imp_reg_wheel = imp_reg_wreg;
        else if (arg == IMP_COMP) imp_reg_comp = imp_reg_wreg;
		break;
	case IMP_MOVVC:
		imp_reg_comp = arg;
		break;
	case IMP_MOVRC:
		if (arg >= 0x00 && arg <= 0x0F) imp_reg_comp = imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_comp = imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_comp = imp_reg_wheel;
        else if (arg == IMP_WREG) imp_reg_comp = imp_reg_wreg;
		break;
	case IMP_LBL:
		/* already handled by label crawling routine */
		break;
	case IMP_BR:
        for (char j = 0; j < MAX_LABELS; j++) {
            if (labels[j][0] == arg) {
                pc = labels[j][1];
                branch = TRUE;
                break;
            }
        }
		break;
	case IMP_BEQ:
        if (imp_reg_wreg == imp_reg_comp) {
            for (char j = 0; j < MAX_LABELS; j++) {
                if (labels[j][0] == arg) {
                    pc = labels[j][1];
                    branch = TRUE;
                    break;
                }
            }
        }
		break;
	case IMP_BNE:
        if (imp_reg_wreg != imp_reg_comp) {
            for (char j = 0; j < MAX_LABELS; j++) {
                if (labels[j][0] == arg) {
                    pc = labels[j][1];
                    branch = TRUE;
                    break;
                }
            }
        }
		break;
	case IMP_BGT:
        if (imp_reg_wreg > imp_reg_comp) {
            for (char j = 0; j < MAX_LABELS; j++) {
                if (labels[j][0] == arg) {
                    pc = labels[j][1];
                    branch = TRUE;
                    break;
                }
            }
        }
		break;
	case IMP_BLT:
        if (imp_reg_wreg < imp_reg_comp) {
            for (char j = 0; j < MAX_LABELS; j++) {
                if (labels[j][0] == arg) {
                    pc = labels[j][1];
                    branch = TRUE;
                    break;
                }
            }
        }
		break;
	case IMP_INCR:
		if (arg >= 0x00 && arg <= 0x0F) imp_regs[arg]++;
        else if (arg == IMP_DISP) imp_reg_disp++;
        else if (arg == IMP_WHEEL) imp_reg_wheel++;
        else if (arg == IMP_COMP) imp_reg_comp++;
		break;
	case IMP_DECR:
		if (arg >= 0x00 && arg <= 0x0F) imp_regs[arg]--;
        else if (arg == IMP_DISP) imp_reg_disp--;
        else if (arg == IMP_WHEEL) imp_reg_wheel--;
        else if (arg == IMP_COMP) imp_reg_comp--;
		break;
	case IMP_CLRR:
		if (arg >= 0x00 && arg <= 0x0F) imp_regs[arg] = 0x00;
        else if (arg == IMP_DISP) imp_reg_disp = 0x00;
        else if (arg == IMP_WHEEL) imp_reg_wheel = 0x00;
        else if (arg == IMP_COMP) imp_reg_comp = 0x00;
		break;
	case IMP_ADDVW:
		imp_reg_wreg += arg;
		break;
	case IMP_ADDRW:
		if (arg >= 0x00 && arg <= 0x0F) imp_reg_wreg += imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_wreg += imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_wreg += imp_reg_wheel;
        else if (arg == IMP_COMP) imp_reg_wreg += imp_reg_comp;
		break;
	case IMP_BSL:
		imp_reg_wreg << arg;
		break;
	case IMP_BSR:
		imp_reg_wreg >> arg;
		break;
	case IMP_SUBVW:
		if (arg > imp_reg_wreg) imp_reg_wreg = arg - imp_reg_wreg;
		else imp_reg_wreg = imp_reg_wreg - arg;
		break;
	case IMP_SUBRW:
		if (arg >= 0x00 && arg <= 0x0F) {
			if (imp_regs[arg] > imp_reg_wreg)
				imp_reg_wreg = imp_regs[arg] - imp_reg_wreg;
			else imp_reg_wreg = imp_reg_wreg - imp_regs[arg];
		} else if (arg == IMP_DISP) {
            if (imp_reg_disp > imp_reg_wreg)
				imp_reg_wreg = imp_reg_disp - imp_reg_wreg;
			else imp_reg_wreg = imp_reg_wreg - imp_reg_disp;
        } else if (arg == IMP_WHEEL) {
            if (imp_reg_wheel > imp_reg_wreg)
				imp_reg_wreg = imp_reg_wheel - imp_reg_wreg;
			else imp_reg_wreg = imp_reg_wreg - imp_reg_wheel;
        } else if (arg == IMP_COMP) {
            if (imp_reg_comp > imp_reg_wreg)
				imp_reg_wreg = imp_reg_comp - imp_reg_wreg;
			else imp_reg_wreg = imp_reg_wreg - imp_reg_comp;
        }
		break;
	case IMP_DUS:
        for (char j = 0; j < arg; j++) __delay_us(1);
		break;
	case IMP_DMS:
        for (char j = 0; j < arg; j++) __delay_ms(1);
		break;
	case IMP_DS:
        for (char j = 0; j < arg; j++) __delay_ms(1000);
		break;
	case IMP_ANDVW:
        imp_reg_wreg &= arg;
		break;
	case IMP_ANDRW:
        if (arg >= 0x00 && arg <= 0x0F) imp_reg_wreg &= imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_wreg &= imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_wreg &= imp_reg_wheel;
        else if (arg == IMP_COMP) imp_reg_wreg &= imp_reg_comp;
		break;
	case IMP_ORVW:
        imp_reg_wreg |= arg;
		break;
	case IMP_ORRW:
        if (arg >= 0x00 && arg <= 0x0F) imp_reg_wreg |= imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_wreg |= imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_wreg |= imp_reg_wheel;
        else if (arg == IMP_COMP) imp_reg_wreg |= imp_reg_comp;
		break;
	case IMP_XORVW:
        imp_reg_wreg ^= arg;
		break;
	case IMP_XORRW:
        if (arg >= 0x00 && arg <= 0x0F) imp_reg_wreg ^= imp_regs[arg];
        else if (arg == IMP_DISP) imp_reg_wreg ^= imp_reg_disp;
        else if (arg == IMP_WHEEL) imp_reg_wreg ^= imp_reg_wheel;
        else if (arg == IMP_COMP) imp_reg_wreg ^= imp_reg_comp;
		break;
	default:
		break;
	}
    set_display_bits(imp_reg_disp, 2);
    set_display_bits(imp_reg_wheel, 1);
    
    if (!branch) return pc++;
    else return pc;
}

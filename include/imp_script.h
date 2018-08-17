/* ImpBadge	
 * imp_script.h
 * Infernal ISA to be interpreted by PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_SCRIPT_H
#define	IMP_SCRIPT_H

#include "imp_display.h"
#include "imp_config.h"

#include <xc.h>
//#include <pic18f4520.h>

/* immediate commands */
#define IMP_RUN     0xF5
#define IMP_SVEEP   0xF4
#define IMP_LDEEP   0xF3
#define IMP_DELEEP  0xEE
#define IMP_NUKE    0xDD
#define IMP_MENU    0xFF

/* zero-op instructions */
#define IMP_NOP     0x00
#define IMP_CLR     0xFD
#define IMP_INC     0xFC
#define IMP_DEC     0xFB
#define IMP_WINP    0xF8
#define IMP_MOVWC   0xFA
#define IMP_END     0xF9
#define IMP_L1ON    0xE1
#define IMP_L2ON    0xE2
#define IMP_R1ON    0xE3
#define IMP_R2ON    0xE4
#define IMP_L1OFF   0xE5
#define IMP_L2OFF   0xE6
#define IMP_R1OFF   0xE7
#define IMP_R2OFF   0xE8

/* one-op instructions */
#define IMP_MOVVW   0x01
#define IMP_MOVRW   0x02
#define IMP_MOVWR   0x03
#define IMP_MOVVC   0x04
#define IMP_MOVRC   0x05
#define IMP_LBL     0x06
#define IMP_BR      0x07
#define IMP_BEQ     0x08
#define IMP_BNE     0x09
#define IMP_BGT     0x0A
#define IMP_BLT     0x0B
#define IMP_INCR    0x0D
#define IMP_DECR    0x0E
#define IMP_CLRR    0x0F
#define IMP_ADDVW   0x10
#define IMP_ADDRW   0x11
#define IMP_BSL     0x12
#define IMP_BSR     0x13
#define IMP_SUBVW   0x14
#define IMP_SUBRW   0x15
#define IMP_DUS     0x16
#define IMP_DMS     0x17
#define IMP_DS      0x18
#define IMP_ANDVW   0x19
#define IMP_ANDRW   0x1A
#define IMP_ORVW    0x1B
#define IMP_ORRW    0x1C
#define IMP_XORVW   0x1D
#define IMP_XORRW   0x1E

/* registers */
#define IMP_DISP    0xFF
#define IMP_WHEEL   0xFE
#define IMP_COMP    0xFD
#define IMP_WREG    0xFC
#define IMP_R0      0x00
#define IMP_R1      0x01
#define IMP_R2      0x02
#define IMP_R3      0x03
#define IMP_R4      0x04
#define IMP_R5      0x05
#define IMP_R6      0x06
#define IMP_R7      0x07
#define IMP_R8      0x08
#define IMP_R9      0x09
#define IMP_R10     0x0A
#define IMP_R11     0x0B
#define IMP_R12     0x0C
#define IMP_R13     0x0D
#define IMP_R14     0x0E
#define IMP_R15     0x0F

/* parameters */
#define MAX_LABELS  16
unsigned char program_ended = 1;

/* types */
typedef enum {
	IMP_TYPE_COMMAND,
	IMP_TYPE_ZERO,
	IMP_TYPE_ONE,
    IMP_TYPE_NOP
} instruction_type_t;

/* data */
unsigned char labels[MAX_LABELS][2];
unsigned char imp_reg_disp = 0;
unsigned char imp_reg_comp = 0;
unsigned char imp_reg_wreg = 0;
unsigned char imp_reg_wheel = 0;
unsigned char imp_regs[16];

/* function prototypes */
instruction_type_t imp_check_type(unsigned char);
unsigned char imp_exec_type_zero(unsigned char, unsigned char);
unsigned char imp_exec_type_one(unsigned char, unsigned char, unsigned char);
void imp_run_script(unsigned char *, unsigned char);

#endif	/* IMP_SCRIPT_H */


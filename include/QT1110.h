/* ImpBadge	
 * QT1110.h
 * Configure AT-QT1110-AU using PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef QT1110_H
#define	QT1110_H

#include <xc.h>
#include "imp_config.h"
#include "imp_spi.h"
#include "imp_usart.h"

/* configuration */
#define TRIS_RESET  TRISCbits.TRISC2
#define SPI_RESET   PORTCbits.RC2

#define CHIP_ID             0x57
#define TIME_BETWEEN_BYTES	__delay_us(200)

/* enable or disable crc */
//#define ENABLE_CRC

/* commands */
#define CMD_SEND_SETUPS     0x01        // Configures the device to receive setup data
#define CMD_CALIBRATE_ALL   0x03        // Calibrates all keys
#define CMD_RESET           0x04        // Resets the device
#define CMD_SLEEP           0x05        // Sleep Mode
#define CMD_STORE_EEPROM    0x0A        // Stores RAM Setups to EEPROM
#define CMD_RESTORE_EEPROM  0x0B        // Copies EEPROM setups to RAM
#define CMD_ERASE_EEPROM    0x0C        // Erase EEPROM setups
#define CMD_RECOVER_EEPROM  0x0D        // Restores last EEPROM settings after erase
#define CMD_SEND_FIRST_KEY  0xC0        // Returns the first detected key
#define CMD_SEND_ALL_KEYS   0xC1        // Returns all keys
#define CMD_DEVICE_STATUS   0xC2        // Returns the device status
#define CMD_EEPROM_CRC      0xC3        // Returns the EEPROM CRC
#define CMD_RAM_CRC         0xC4        // Returns RAM CRC
#define CMD_ERROR_KEYS      0xC5        // Returns the error keys
#define CMD_DETECT_STATES   0xC6        // Returns the detect output states
#define CMD_LAST_COMMAND    0xC7        // Returns the last command send
#define CMD_READ_SETUPS     0xC8        // Returns the Setup Data
#define CMD_DEVICE_ID       0xC9        // Returns the device ID
#define CMD_FIRMWARE_VERSION 0xCA       // Returns the Firmware version

/* type definitions */
typedef struct {
    /* Address 0: Device Mode */
    unsigned char REPEAT_TIME : 4;      /* multiple of 16ms; 0=free run */
    unsigned char SYNC : 1;             /* SYNC trigger: 0=level, 1=edge */
    unsigned char SIG : 1;              /* 0=serial, 1=parallel acquisition of touch signals */
    unsigned char MODE : 1;             /* 0 = 7-key, 1 = 11-key */
    unsigned char KEY_AC : 1;           /* trigger source: 0=SYNC pin, 1=timed */
    
    /* Address 1: Guard Key / Comms Options */
    unsigned char CRC : 1;              /* 0=disable, 1=enable */
    unsigned char CHG : 1;              /* 0=Data mode, 1=Touch mode */
    unsigned char SPI_EN : 1;           /* QuickSPI: 0=disable, 1=enable */
    unsigned char GD_EN : 1;            /* guard key: 0=disable, 1=enable */
    unsigned char GUARD_KEY : 4;        /* key to be used as guard, 0-10 */
    
    /* Address 2: Detect Integrator Limit, Drift Hold Time */
    unsigned char DHT : 4;              /* multiple of 180ms (up to 2400 ms) */ 
    unsigned char DIL : 4;              /* range: 1-15 */
    
    /* Address 3: Positive Threshold, Positive Hysteresis */
    unsigned char PHYST : 2;            /* 0=No reduction, 1=12.5%, 2=25%, 3=37.5% */
    unsigned char PTHR : 6;             /* counts above reference */
    
    /* Address 4: Positive Drift Compensation */
    unsigned char PDRIFT : 8;           /* 0 to 127; multiple of 160ms */
    
    /* Address 5: Positive Recalibration Delay */
    unsigned char PRD : 8;              /* 0 to 127; multiple of 160ms */
    
    /* Address 6: Lower Burst Limit */
    unsigned char LBL : 8;
    
    /* Address 7-8: Adjacent Key Suppression mask */
    unsigned char AKS_8 : 1;
    unsigned char AKS_9 : 1;
    unsigned char AKS_10 : 1;
    unsigned char AKS_unused : 5;
    unsigned char AKS_0 : 1;
    unsigned char AKS_1 : 1;
    unsigned char AKS_2 : 1;
    unsigned char AKS_3 : 1;
    unsigned char AKS_4 : 1;
    unsigned char AKS_5 : 1;
    unsigned char AKS_6 : 1;
    unsigned char AKS_7 : 1;
    
    /* Address 9-15: Detect0 - Detect6 PWM */
    unsigned char OUT_DETECT0 : 4;
    unsigned char IN_DETECT0 : 4;
    unsigned char OUT_DETECT1 : 4;
    unsigned char IN_DETECT1 : 4;
    unsigned char OUT_DETECT2 : 4;
    unsigned char IN_DETECT2 : 4;
    unsigned char OUT_DETECT3 : 4;
    unsigned char IN_DETECT3 : 4;
    unsigned char OUT_DETECT4 : 4;
    unsigned char IN_DETECT4 : 4;
    unsigned char OUT_DETECT5 : 4;
    unsigned char IN_DETECT5 : 4;
    unsigned char OUT_DETECT6 : 4;
    unsigned char IN_DETECT6 : 4;
    
    /* Address 16: LED detect hold time */
    unsigned char LED_DETECT_HOLD_TIME : 8;
    
    /* Address 17: LED Fade / Key to LED */
    unsigned char LED_1 : 1;
    unsigned char LED_2 : 1;
    unsigned char LED_3 : 1;
    unsigned char LED_4 : 1;
    unsigned char LED_5 : 1;
    unsigned char LED_6 : 1;
    unsigned char FADE : 0;
    
    /* Address 18: LED Latch */
    unsigned char LATCH_1 : 1;
    unsigned char LATCH_2 : 1;
    unsigned char LATCH_3 : 1;
    unsigned char LATCH_4 : 1;
    unsigned char LATCH_5 : 1;
    unsigned char LATCH_6 : 1;
    unsigned char LED_Latch_unused : 1;
    
    /* Address 19-29: Negative Threshold, Negative Hysteresis */
    unsigned char KEY_0_NHYST : 2;
    unsigned char KEY_0_NTHR : 6;
    unsigned char KEY_1_NHYST : 2;
    unsigned char KEY_1_NTHR : 6;
    unsigned char KEY_2_NHYST : 2;
    unsigned char KEY_2_NTHR : 6;
    unsigned char KEY_3_NHYST : 2;
    unsigned char KEY_3_NTHR : 6;
    unsigned char KEY_4_NHYST : 2;
    unsigned char KEY_4_NTHR : 6;
    unsigned char KEY_5_NHYST : 2;
    unsigned char KEY_5_NTHR : 6;
    unsigned char KEY_6_NHYST : 2;
    unsigned char KEY_6_NTHR : 6;
    unsigned char KEY_7_NHYST : 2;
    unsigned char KEY_7_NTHR : 6;
    unsigned char KEY_8_NHYST : 2;
    unsigned char KEY_8_NTHR : 6;
    unsigned char KEY_9_NHYST : 2;
    unsigned char KEY_9_NTHR : 6;
    unsigned char KEY_10_NHYST : 2;
    unsigned char KEY_10_NTHR : 6;
    
    /* Address 30: Extend Pulse Time */
    unsigned char LOW_TIME : 4;
    unsigned char HIGH_TIME : 4;
    
    /* Address 31-41: NDRIFT / NRD */
    unsigned char KEY0_NRD : 4;
    unsigned char KEY0_NDRIFT : 4;
    unsigned char KEY1_NRD : 4;
    unsigned char KEY1_NDRIFT : 4;
    unsigned char KEY2_NRD : 4;
    unsigned char KEY2_NDRIFT : 4;
    unsigned char KEY3_NRD : 4;
    unsigned char KEY3_NDRIFT : 4;
    unsigned char KEY4_NRD : 4;
    unsigned char KEY4_NDRIFT : 4;
    unsigned char KEY5_NRD : 4;
    unsigned char KEY5_NDRIFT : 4;
    unsigned char KEY6_NRD : 4;
    unsigned char KEY6_NDRIFT : 4;
    unsigned char KEY7_NRD : 4;
    unsigned char KEY7_NDRIFT : 4;
    unsigned char KEY8_NRD : 4;
    unsigned char KEY8_NDRIFT : 4;
    unsigned char KEY9_NRD : 4;
    unsigned char KEY9_NDRIFT : 4;
    unsigned char KEY10_NRD : 4;
    unsigned char KEY10_NDRIFT : 4;
} setup_block_t;

/* external variables */
extern setup_block_t setup_block;
extern unsigned char qt_status[2];
extern unsigned char CRC_en;

/* function prototypes */
void qt_check_comms(void);
unsigned char qt_control_cmd(unsigned char cmd);
unsigned char qt_report_req(unsigned char cmd, unsigned char num_bytes, unsigned char *addr);
unsigned char qt_set(unsigned char cmd, unsigned char set_data);
unsigned char qt_get(unsigned char cmd, unsigned char *read_ptr);
void qt_init(void);
unsigned char qt_read_setups(unsigned char read_length, unsigned char *read_ptr);
unsigned char qt_write_setups(unsigned char write_length, unsigned char *write_ptr);
unsigned char qt_key_status(unsigned char read_length, unsigned char *read_ptr);
void qt_reset(void);
unsigned short CRC16_calc(unsigned short, unsigned char);
unsigned char CRC8_calc(unsigned char, unsigned char);

#endif	/* QT1110_H */


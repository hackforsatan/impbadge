/* ImpBadge	
 * imp_spi.h
 * SPI driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_SPI_H
#define	IMP_SPI_H

#include <xc.h>
#include "imp_config.h"

/* pins */
#define SPI_SCK		LATCbits.LATC3      /* clock */
#define TRIS_SCK	TRISCbits.TRISC3
#define SPI_MOSI	LATCbits.LATC5      /* serial output (MOSI) */
#define TRIS_MOSI	TRISCbits.TRISC5
#define SPI_MISO	PORTCbits.RC4       /* serial input (MISO) */
#define TRIS_MISO	TRISCbits.TRISC4
#define SPI_SS		LATAbits.LATA5      /* !SS */
#define TRIS_SS		TRISAbits.TRISA5

/* parameters */
#define SS_DELAY	__delay_us(1)

void spi_init(void);
unsigned char spi(unsigned char);

#endif	/* IMP_SPI_H */


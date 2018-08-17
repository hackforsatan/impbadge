/* ImpBadge	
 * imp_spi.c
 * SPI driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_spi.h"

void spi_init(void) {
	/* configure pin directions */
	TRIS_SCK = 0;
	TRIS_MOSI = 0;
	TRIS_MISO = 1;
	TRIS_SS = 0;
	
	/* configure SPI */
	SPI_SS = 1;	/* _SS idles HIGH */
	SSPSTAT = 0b10000000;	/* sample at end of output; transmit on idle -> active */
	SSPCON1 = 0b00110010;	/* enable SPI; SCK idles HIGH @ Fosc/64 */
}

unsigned char spi(unsigned char byte) {
	SPI_SS = 0;
	SS_DELAY;
	SSPBUF = byte;
	while (!SSPSTATbits.BF)
		;
	byte = SSPBUF;
	SPI_SS = 1;
	return byte;
}


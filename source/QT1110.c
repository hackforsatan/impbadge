
/* ImpBadge	
 * QT1110.c
 * Configure AT-QT1110-AU using PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "QT1110.h"

#define IDLE_STATUS_CODE	0x55
#define NULL_BYTE		0x00
#define CRC_OPTION		0x91

/* global variables */
setup_block_t setup_block;

unsigned char qt_status[2];

/* function definitions */
void qt_init(void) {
	/* initialize SPI peripheral for Fosc = 20 MHz (/16) */
	spi_init();
	
	/* configure the RESET pin as output */
	TRIS_RESET = 1;

	/* reset idles HIGH */
	SPI_RESET = 1;
	
	/* wait for QT to start up */
	__delay_ms(200);
	
	qt_check_comms();
}

void qt_check_comms(void) {	
	unsigned char data;
	do {
		/* send command to read device ID */
		data = spi(CMD_DEVICE_ID);
		TIME_BETWEEN_BYTES;
	} while (data != CHIP_ID);
	
#ifdef ENABLE_CRC

	do {
		/* send command */
		data = spi(CRC_OPTION);
		TIME_BETWEEN_BYTES;
	} while (data != IDLE_STATUS_CODE);
	
	/* send data byte */
	spi(0x01);
	TIME_BETWEEN_BYTES;
	
#endif /* ENABLE_CRC */
	
	printf("[device 0x%x ... online]\r\n", data); // TODO: put in different variable
}

unsigned char qt_control_cmd(unsigned char cmd) {
	unsigned char result = TRUE;
	unsigned char data;
	
#ifdef ENABLE_CRC
	unsigned char CrcValue;
#endif

	do {
		/* send control command */
		data = spi(cmd);
		TIME_BETWEEN_BYTES;
	} while (data != IDLE_STATUS_CODE);
	
#ifdef ENABLE_CRC
	/* init crc value */
	CrcValue = 0;
	
	/* calculate crc */
	CrcValue = CRC8_calc(CrcValue, cmd);
	data = spi(CrcValue);
	
	/* verify received crc */
	if (data != CrcValue) {
		result = FALSE;
	}
#endif
	
	return result;
}

unsigned char qt_report_req(unsigned char cmd, unsigned char num_bytes, unsigned char *addr) {
	unsigned char result = TRUE;
	unsigned char data;
#ifdef ENABLE_CRC
	unsigned char CrcValue;
#endif
	do {
		/* send command */
		data = spi(cmd);
		TIME_BETWEEN_BYTES;
	} while (data != IDLE_STATUS_CODE);
	
#ifdef ENABLE_CRC
	/* init crc value */
	CrcValue = 0;
	/* calculate crc */
	CrcValue = CRC8_calc(CrcValue, cmd);
	
	/* send command byte crc and read crc byte sent from QT device */
	data = spi(CrcValue);
	
	/* verify the received crc */
	if (data != CrcValue) {
		/* command failed; return */
		return FALSE;
	}
	
	TIME_BETWEEN_BYTES;
	
	/* init crc value */
	CrcValue = 0;
#endif
	/* read the bytes */
	for (unsigned char i = 0; i < num_bytes; i++) {
		*addr = spi(NULL_BYTE);
#ifdef ENABLE_CRC
		CrcValue = CRC8_calc(CrcValue, *addr);
#endif
		/* increment the data pointer */
		addr++;
		TIME_BETWEEN_BYTES;
	}
	
#ifdef ENABLE_CRC
	/* read the crc byte */
	data = spi(NULL_BYTE);
	
	/* verify the received crc */
	if (data != CrcValue) {
		result = FALSE;
	}
	TIME_BETWEEN_BYTES;
#endif
	return result;
}

unsigned char qt_set(unsigned char cmd, unsigned char set_data) {
	unsigned char result = TRUE;
	unsigned char data;
#ifdef ENABLE_CRC
	unsigned char CrcValue;
#endif
	
	do {
		/* send command */
		data = spi(cmd);
		TIME_BETWEEN_BYTES;
	} while (data != IDLE_STATUS_CODE);
	
	/* send data */
	spi(set_data);
	
#ifdef ENABLE_CRC
	/* init crc value */
	CrcValue = 0;
	
	/* calculate crc */
	CrcValue = CRC8_calc(CrcValue, cmd);
	CrcValue = CRC8_calc(CrcValue, set_data);
	
	/* read the crc byte */
	data = spi(CrcValue);
	
	/* verify the received CRC */
	if (data != CrcValue) {
		result = FALSE;
	}
#endif
	return result;
}

unsigned char qt_get(unsigned char cmd, unsigned char *read_ptr) {
	return (qt_report_req(cmd, 1, read_ptr));
}

unsigned char qt_read_setups(unsigned char read_length, unsigned char *read_ptr) {
	/* read setup block */
	return (qt_report_req(CMD_READ_SETUPS, read_length, read_ptr));
}

unsigned char qt_write_setups(unsigned char write_length, unsigned char *write_ptr) {
	unsigned char result = TRUE;
	unsigned char data;
#ifdef ENABLE_CRC
	unsigned char CrcValue = 0;
#endif
	
	do {
		/* send setup command */
		data = spi(CMD_SEND_SETUPS);
		TIME_BETWEEN_BYTES;
	} while (data != IDLE_STATUS_CODE);
	
#ifdef ENABLE_CRC
	/* calculate crc */
	CrcValue = CRC8_calc(CrcValue, CMD_SEND_SETUPS);
#endif
	
	/* send data byte by byte */
	for (int i = 0; i < write_length; i++) {
		data = spi(*write_ptr);
#ifdef ENABLE_CRC
		/* calculate crc */
		CrcValue = CRC8_calc(CrcValue, *write_ptr);
#endif
		/* increment write data pointer */
		write_ptr++;
		
		/* delay needed between multi-byte transmissions */
		TIME_BETWEEN_BYTES;
	}
	
#ifdef ENABLE_CRC
	/* send crc byte */
	data = spi(CrcValue);
	
	/* verify the received crc */
	if (data != CrcValue) {
		result = FALSE;
	}
#endif
	return result;
}

unsigned char qt_key_status(unsigned char read_length, unsigned char *read_ptr) {
	/* read detection status of all keys */
	return (qt_report_req(CMD_SEND_ALL_KEYS, read_length, read_ptr));
}

void qt_reset(void) {
	/* pull low */
	SPI_RESET = 0;
	__delay_ms(1);
	
	/* pull high to resume normal operation */
	SPI_RESET = 1;
}

unsigned short CRC16_calc(unsigned short wCRC, unsigned char cVal) {
	unsigned char c;
	unsigned short cPoly;
	
	wCRC = (wCRC ^ (unsigned short)((unsigned short)cVal << 8));
	cPoly = (unsigned short)0x1021;
	
	c = (unsigned char)8;
	
	do {
		if (wCRC & (unsigned short)0x8000) {
			wCRC = (unsigned short)(wCRC << 1) ^ cPoly;
		} else {
			wCRC = (unsigned short)(wCRC << 1);
		}
	} while (--c);
	
	return(wCRC);
}

unsigned char CRC8_calc(unsigned char crc, unsigned char data) {
	unsigned char index;
	unsigned char fb;
	index = 8;
	
	do {
		fb = (crc ^ data) & 0x01u;
		data >>= 1u;
		crc >>= 1u;
		if (fb) {
			crc ^= 0x8c;
		}
	} while (--index);
	
	return crc;
}
/* ImpBadge	
 * imp_usart.c
 * USART driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#include "imp_usart.h"

/* get a working printf */
void putch(unsigned char data) {
	while (!TXSTAbits.TRMT) /* wait until transmitter is ready */
		continue;
	
	TXREG = data;		/* send one character */
}

void usart_init() {
	/* USART configuration */
	TRISCbits.RC7 = 1;		/* RX is INPUT */
	TRISCbits.RC6 = 0;		/* TX is OUTPUT */
	SPBRG = 129;			/* high speed: 9600 baud for Fosc = 20 MHz */
	TXSTAbits.SYNC = 0;		/* asynchronous mode */
	TXSTAbits.BRGH = 1;		/* high speed baud rate */
	TXSTAbits.TX9 = 0;		/* 8-bit transmit */
	RCSTAbits.RX9 = 0;		/* 8-bit receive */
	RCSTAbits.SPEN = 1;		/* enable RX and TX */
	RCSTAbits.CREN = 1;		/* enable continuous receive */
	TXSTAbits.TXEN = 1;		/* enable transmitter */
	
	/* set up USART interrupts*/
	IPR1bits.RCIP = 0;		/* RX set as low priority interrupt */
	//PIE1bits.RCIE = 1;		/* enable interrupt on RX */
	//PIE1bits.TXIE = 0;		/* disable interrupt on TX */
	
	printf("%c%c%c", 27, 'p');
	
}

/* ensure RX buffer is empty */
void usart_clr_rx() {
	volatile char c;
	c = RCREG;
	c = RCREG;
	c = RCREG;
}

void usart_clr_screen() {
	printf("%c%c%c%c%c%c%c", 27, '[', '2', 'J', 27, '[', 'H');
}

void uart_clr_last_n_lines(unsigned char n) {
	char del_to_end[] = {27, '[', 'J','\0'};
	for (unsigned char i = 0; i < n; i++) {
		printf("%c%c%c%c", 27, '[', 'A');
	}
	printf("\r");
	//printf("%c%c%c%c", 27, '[', n, 'A');
	printf("%s", del_to_end);
}

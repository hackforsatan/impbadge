/* ImpBadge	
 * imp_usart.h
 * USART driver for PIC18F4520
 * copyright 2018 Hack for Satan
 */

#ifndef IMP_USART_H
#define	IMP_USART_H

#include <xc.h>
#include <stdio.h>              /* access to printf() */

/* function prototypes */
void putch(unsigned char);      /* re-route stdout */
void usart_init(void);          /* configuration for USART */
void usart_clr_rx(void);        /* clear FIFO buffer for clean receive */
void usart_clr_screen(void);
void uart_clr_last_n_lines(unsigned char n);

char ansi_clr[] = {27, '[', '2', 'J', 27, '[', 'H', '\0'};

#endif	/* IMP_USART_H */


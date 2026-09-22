#ifndef UART_H
#define UART_H

#include "base.h"

#define UART0_BASE  (PERIPHERAL_BASE + 0x201000)

#define UART_DR     (UART0_BASE + 0x00)
#define UART_FR     (UART0_BASE + 0x18)
#define UART_IBRD   (UART0_BASE + 0x24)
#define UART_FBRD   (UART0_BASE + 0x28)
#define UART_LCRH   (UART0_BASE + 0x2C)
#define UART_CR     (UART0_BASE + 0x30)
#define UART_IFLS   (UART0_BASE + 0x34)
#define UART_IMSC   (UART0_BASE + 0x38)
#define UART_RIS    (UART0_BASE + 0x3c)
#define UART_MIS    (UART0_BASE + 0x40)
#define UART_ICR    (UART0_BASE + 0x44)

#define UART_EN         (1 << 0)
#define UART_TXE        (1 << 8)
#define UART_RXE        (1 << 9)
#define UART_TXFF       (1 << 5)
#define UART_RXFE       (1 << 4)
#define UART_FEN        (1 << 4)
#define UART_WLEN_8BIT  (3 << 5)
#define UART_RXIM       (1 << 4)

void uart_init(void);
void uart_putc(char c);
void uart_puts(char *msg);
char uart_getc(void);
void uart_gets(char *msg);

#endif

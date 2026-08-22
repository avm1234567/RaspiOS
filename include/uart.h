#ifndef UART_H
#define UART_H

#define UART0_BASE 0xFE201000
#define UART_DR (UART0_BASE + 0x00)
#define UART_FR (UART0_BASE + 0x18)
#define UART_CR (UART0_BASE + 0x30)
#define UART_LCRH (UART0_BASE + 0x2c)
#define UART_IBRD (UART0_BASE + 0x24)
#define UART_FBRD (UART0_BASE +0x28)

#define UART_EN (1<<0)
#define UART_TXE (1<<8)
#define UART_RXE (1<<9)
#define UART_TXFF (1<<5)
#define UART_RXFE (1<<4)
#define UART_FEN (1<<4)
#define UART_WLEN_8BIT (3<<5)

void uart_init(void);
void uart_putc(char c);
void uart_puts(char *msg);
char uart_getc(void);
void uart_gets(char *msg);

#endif

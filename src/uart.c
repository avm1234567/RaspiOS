#include "uart.h"
#include <stdint.h>

void uart_init(void)
{
	*(volatile uint32_t*)UART_CR = (0<<0);
	*(volatile uint32_t*)UART_IBRD = 0x1A;
	*(volatile uint32_t*)UART_FBRD = 0x03;
	*(volatile uint32_t*)UART_LCRH = UART_FEN | UART_WLEN_8BIT;
	*(volatile uint32_t*)UART_CR = UART_EN | UART_TXE | UART_RXE;
}

void uart_putc(char c)
{
	while(*(volatile uint32_t*)UART_FR & UART_TXFF){}

	*(volatile uint32_t*)UART_DR = c;
}

void uart_puts(char *msg)
{
	int i = 0;
	while(msg[i] != '\0')
	{
		uart_putc(msg[i]);
		i++;
	}
	msg[i] = '\0';
}


#include "uart.h"

void uart_init(void)
{
	REG(UART_CR) = (0 << 0);
	REG(UART_IBRD) = 0x1A;
	REG(UART_FBRD) = 0x03;
	REG(UART_LCRH) = UART_FEN | UART_WLEN_8BIT;
	REG(UART_CR) = UART_EN | UART_TXE | UART_RXE;
}

void uart_putc(char c)
{
	while(REG(UART_FR) & UART_TXFF){}

	REG(UART_DR) = c;
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

char uart_getc(void)
{
	while(REG(UART_FR) & UART_RXFE);
	return REG(UART_DR);
}

void uart_gets(char *msg)
{
	char ch;
	while(1)
	{
		ch = uart_getc();
		if(ch == '\r')
		{
			break;
		}
		*msg = ch;
		msg++;
	}
	*msg = '\0';
}

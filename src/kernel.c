#include "uart.h"
void kernel_main() {
    char msg[20];
    uart_init();
    uart_putc('b');
    uart_puts("Hello");
    while (1) {
		uart_gets(msg);
		uart_puts(msg);
	}
}

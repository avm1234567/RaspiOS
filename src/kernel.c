#include "uart.h"
void kernel_main() {

    uart_init();
    uart_putc('b');
    uart_puts("Hello");
    while (1) {

	}
}

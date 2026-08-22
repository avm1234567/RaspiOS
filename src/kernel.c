#include "uart.h"
void kernel_main() {

    uart_init();
    uart_putc('b');
    while (1) {

	}
}

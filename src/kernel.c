#include "uart.h"
#include "timer.h"
void kernel_main() {
    char msg[20];
    uart_init();
    timer_init();
    asm volatile("msr daifclr, #2");
    uart_putc('b');
    uart_puts("Hello");
    while (1) {
		uart_gets(msg);
		uart_puts(msg);
	}
}

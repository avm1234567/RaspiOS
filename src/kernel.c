#include "uart.h"
#include "timer.h"
#include "scheduler.h"
void kernel_main() {
    char msg[20];
    uart_init();
    uint64_t el;
    asm volatile("mrs %0, CurrentEL" : "=r"(el));
    el = (el >> 2) & 3;
    uart_putc('0' + el);
    scheduler_init();
    timer_init();
    asm volatile("msr daifclr, #2");
    uart_putc('b');
    uart_puts("Hello");
    start_scheduler();
}

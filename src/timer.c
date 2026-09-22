#include "timer.h"
#include "uart.h"

void timer_init(void)
{
    REG(TIMER_CNTRL0) = CNT_V_IRQ;
    uint32_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    asm volatile("msr cntv_tval_el0, %0" : : "r"(freq));
    asm volatile("msr cntv_ctl_el0, %0" : : "r"(1));
}

void handle_irq(void)
{
    uart_puts("Timer interrupt occurred!\n");
    uint32_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    asm volatile("msr cntv_tval_el0, %0" : : "r"(freq));
}
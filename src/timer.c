#include "timer.h"
#include "uart.h"
#include "scheduler.h"

uint64_t system_ticks = 0;

void timer_init(void)
{
    REG(GICD_CTLR) = 1;
    REG(GICC_CTLR) = 1;
    REG(GICC_PMR) = 0xFF;
    REG(GICD_ISENABLER0) |= (1 << TIMER_IRQ_ID);
    uint32_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    asm volatile("msr cnthp_tval_el2, %0" : : "r"(freq));
    asm volatile("msr cnthp_ctl_el2, %0" : : "r"(1));
    uint64_t hcr;
    asm volatile("mrs %0, hcr_el2" : "=r"(hcr));
    hcr |= (1 << 4); // IMO bit = Route physical IRQs to EL2
    asm volatile("msr hcr_el2, %0" : : "r"(hcr));
}

void handle_irq(void)
{
    uint32_t iar = REG(GICC_IAR);
    uart_puts("Timer interrupt occurred!\n");
    uint32_t freq;
    asm volatile("mrs %0, cntfrq_el0" : "=r"(freq));
    asm volatile("msr cnthp_tval_el2, %0" : : "r"(freq));
    REG(GICC_EOIR) = iar;
    system_ticks++;
}
#ifndef TIMER_H
#define TIMER_H

#include "base.h"

#define TIMER_BASE (PERIPHERAL_BASE + 0x1800000)

#define TIMER_CNTRL0 (TIMER_BASE + 0X40)
#define TIMER_CNTRL1 (TIMER_BASE + 0X44)
#define TIMER_CNTRL2 (TIMER_BASE + 0X48)
#define TIMER_CNTRL3 (TIMER_BASE + 0X4C)

#define CNT_V_IRQ (1 << 3)

void timer_init(void);
void handle_irq(void);

#endif 
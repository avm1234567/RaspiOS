#ifndef TIMER_H
#define TIMER_H

#include "base.h"

#define GIC_BASE (PERIPHERAL_BASE + 0x1840000)
#define GICD_BASE (GIC_BASE + 0x1000)
#define GICC_BASE (GIC_BASE + 0x2000)

#define  GICD_CTLR  (GICD_BASE + 0x000)
#define GICD_ISENABLER0  (GICD_BASE + 0x100)
#define GICC_CTLR  (GICC_BASE + 0x000)
#define GICC_PMR  (GICC_BASE + 0x004)
#define GICC_IAR  (GICC_BASE + 0x00C)
#define GICC_EOIR  (GICC_BASE + 0x010)

#define TIMER_IRQ_ID 26
void timer_init(void);
void handle_irq(void);

#endif 
#ifndef GPIO_H
#define GPIO_H

#include "base.h"

#define GPIO_BASE  (PERIPHERAL_BASE + 0x200000)

#define GPFSEL0    (GPIO_BASE + 0x00)
#define GPFSEL1    (GPIO_BASE + 0x04)
#define GPFSEL2    (GPIO_BASE + 0x08)
#define GPFSEL3    (GPIO_BASE + 0x0C)
#define GPFSEL4    (GPIO_BASE + 0x10)
#define GPFSEL5    (GPIO_BASE + 0x14)
#define GPSET0     (GPIO_BASE + 0x1C)
#define GPSET1     (GPIO_BASE + 0x20)
#define GPCLR0     (GPIO_BASE + 0x28)
#define GPCLR1     (GPIO_BASE + 0x2C)
#define GPLEV0     (GPIO_BASE + 0x34)
#define GPLEV1     (GPIO_BASE + 0x38)

#define GPIO_INPUT  0
#define GPIO_OUTPUT 1

#define GPIO_ALT0   4
#define GPIO_ALT1   5
#define GPIO_ALT2   6
#define GPIO_ALT3   7
#define GPIO_ALT4   3
#define GPIO_ALT5   2

volatile uint32_t *gpio_fsel[6] = {
    (volatile uint32_t *)GPFSEL0,
    (volatile uint32_t *)GPFSEL1,
    (volatile uint32_t *)GPFSEL2,
    (volatile uint32_t *)GPFSEL3,
    (volatile uint32_t *)GPFSEL4,
    (volatile uint32_t *)GPFSEL5
};

volatile uint32_t *gpio_fset[2]={
    (volatile uint32_t *)GPSET0,
    (volatile uint32_t *)GPSET1
};

volatile uint32_t *gpio_fclr[2]={
    (volatile uint32_t *)GPCLR0,
    (volatile uint32_t *)GPCLR1
};
volatile uint32_t *gpio_flev[2]={
    (volatile uint32_t *)GPLEV0,
    (volatile uint32_t *)GPLEV1
};

void gpio_set_fucntion(uint32_t pin, uint32_t function);
void gpio_toggle(uint32_t pin);


#endif
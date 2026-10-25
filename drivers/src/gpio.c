#include "gpio.h"
#include <stdint.h>

void gpio_set_fucntion(uint32_t pin, uint32_t function) {
    uint32_t reg = pin / 10;
    uint32_t shift = (pin % 10) * 3;
    *gpio_fsel[reg] &= ~(0b111 << shift);
    *gpio_fsel[reg] |= (function << shift);
}

void  gpio_toggle(uint32_t pin)
{
    uint32_t reg = pin / 32;
    uint32_t bit = pin % 32;
    if(*gpio_flev[reg] & (1<< bit)){
    *gpio_fclr[reg] = (1 << bit);
    }
    else{
        *gpio_fset[reg] = (1 << bit); 
    }
}


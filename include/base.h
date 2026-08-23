#ifndef BASE_H
#define BASE_H

#include <stdint.h>

#define PERIPHERAL_BASE     0xFE000000

#define REG(addr)   (*(volatile uint32_t *)(addr))

#endif

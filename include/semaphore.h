#ifndef SEMAPHORE_H
#define SEMAPHORE_H

#include "scheduler.h"
#include <stdint.h>

typedef struct {
    volatile int value;
    int max_value;
} Semaphore;

void semaphore_init(Semaphore* sem, int initial_value, int max_value);
void semaphore_wait(Semaphore* sem);
void semaphore_post(Semaphore* sem);

#endif
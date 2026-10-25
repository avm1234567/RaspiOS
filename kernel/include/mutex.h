#ifndef MUTEX_H
#define MUTEX_H

#include "scheduler.h"

typedef struct {
    volatile int locked;
    TCB* owner;
} Mutex;

void mutex_init(Mutex* mutex);
void mutex_lock(Mutex* mutex);
void mutex_unlock(Mutex* mutex);

#endif
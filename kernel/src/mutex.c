#include "scheduler.h"
#include "mutex.h"
#include "uart.h"
#include <stddef.h>

void mutex_init(Mutex* mutex) {
    mutex->locked = 0;
    mutex->owner = NULL;
}

void mutex_lock(Mutex* mutex) {
    while(1){
        asm volatile("msr daifset, #2"); // Disable interrupts
        if(mutex->locked ==0){
            mutex->locked = 1;
            mutex->owner = current_task;
            asm volatile("msr daifclr, #2"); // Enable interrupts
            return;
        }
        else{
            asm volatile("msr daifclr, #2"); // Enable interrupts
            yield(); // Yield control to the scheduler

        }
    }
}

void mutex_unlock(Mutex* mutex){
    asm volatile("msr daifset, #2"); // Disable interrupts
    if(mutex->owner == current_task){
        mutex->locked = 0;
        mutex->owner = NULL;
    }
    else{
        uart_puts("Error: Mutex unlock attempted by non-owner task\n");
    }
    asm volatile("msr daifclr, #2"); // Enable interrupts
}
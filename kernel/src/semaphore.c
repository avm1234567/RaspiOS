#include "scheduler.h"
#include "semaphore.h"

void semaphore_init(Semaphore* sem, int initial_value, int max_value) {
    sem->value = initial_value;
    sem->max_value = max_value;
}

void semaphore_wait(Semaphore* sem) {
    while(1){
        asm volatile("msr daifset, #2"); // Disable interrupts
        if(sem->value > 0){
            sem->value--;
            asm volatile("msr daifclr, #2"); // Enable interrupts
            return;
        }
        else{
            asm volatile("msr daifclr, #2"); // Enable interrupts
            yield(); // Yield control to the scheduler
        }
    }
}

void semaphore_post(Semaphore* sem) {
    asm volatile("msr daifset, #2");
    if(sem->value < sem->max_value){
        sem->value++;
    }
    else{
        // Optionally handle the case where the semaphore is already at max value
    }
    asm volatile("msr daifclr, #2"); // Enable interrupts
}
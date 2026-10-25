#include "scheduler.h"
#include <stdint.h>
#include "uart.h"
#include "mutex.h"
#include "semaphore.h"

// Define private stacks for tasks
uint64_t task_a_stack[512];
uint64_t task_b_stack[512];

// Define TCBs for tasks
TCB tcb_a;
TCB tcb_b;

// Pointer tracking the current task
TCB* current_task;

Mutex mutex;
Semaphore item_sem;

void task_a(void) 
{
    while (1) {
        mutex_lock(&mutex);
        uart_puts("Task A is running\n");
        uart_puts("Producing an item...\n");
        mutex_unlock(&mutex);
        semaphore_post(&item_sem);
        for (volatile int i = 0; i < 1000000; i++); // Delay
        yield(); // Yield control to the scheduler
    }
}

void task_b(void) 
{
    while (1) {
        mutex_lock(&mutex);
        uart_puts("Task B is running\n");
        uart_puts("Consuming an item...\n");
        uart_puts("Task B: going to sleep for 1 ticks...\n");
        mutex_unlock(&mutex);
        semaphore_wait(&item_sem);
        sleep_ticks(1); // Sleep for 1 ticks
        mutex_lock(&mutex);
        uart_puts("Task B: woke up from sleep!\n");
        uart_puts("Consumed an item!\n");
        mutex_unlock(&mutex);
    }
}

void scheduler_init(void){
    uint64_t *sp_a = &task_a_stack[512];
    mutex_init(&mutex);
    semaphore_init(&item_sem, 0, 5);
    sp_a = sp_a - 32;
    sp_a[30] = (uint64_t)task_a; // Set the return address to task_a
    sp_a[31] = (uint64_t)task_a; // Set the frame pointer to task_a
    tcb_a.sp = (uint64_t)sp_a;
    tcb_a.state = TASK_READY; // Initialize task_a state

    uint64_t *sp_b = &task_b_stack[512];
    sp_b = sp_b - 32;
    sp_b[30] = (uint64_t)task_b; // Set the return address to task_b
    sp_b[31] = (uint64_t)task_b; // Set the frame pointer to task_b
    tcb_b.sp = (uint64_t)sp_b;
    tcb_b.state = TASK_READY; // Initialize task_b state

    current_task = &tcb_a; // Start with task_a
}

void schedule(void) {
    // 1. Identify the candidate
    TCB* next_task = (current_task == &tcb_a) ? &tcb_b : &tcb_a;

    // 2. Check if next_task's alarm went off
    if (next_task->state == TASK_SLEEPING && system_ticks >= next_task->wakeup_time) {
        next_task->state = TASK_READY;
    }

    // 3. Switch ONLY if next_task is ready!
    if (next_task->state == TASK_READY) {
        current_task = next_task;
    }
    // If next_task is still sleeping, current_task remains untouched!
}

void sleep_ticks(uint64_t ticks) {
    current_task->state = TASK_SLEEPING;
    current_task->wakeup_time = system_ticks + ticks;
    yield(); // Yield control to the scheduler
}
#ifndef TASK_H
#define TASK_H

#include <stdint.h> 

#define MAX_TASKS 8
#define TASK_READY 0
#define TASK_SLEEPING 1

typedef struct{
    uint64_t sp;
    volatile int state; // TASK_READY, TASK_SLEEPING
    uint64_t wakeup_time; // Time when the task should wake up
    int task_id;
    char name[16]; // Task name for debugging
    uint32_t priority; // Task priority for scheduling
} TCB;

TCB* task_create(void (*entry_point)(void), const char* name);

#endif
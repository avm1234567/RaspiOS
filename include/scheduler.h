#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#define TASK_READY 0
#define TASK_SLEEPING 1
extern uint64_t system_ticks;

typedef struct {
    uint64_t sp;
    volatile int state;
    uint64_t wakeup_time;
}TCB;

extern TCB* current_task;

void task_a(void);
void task_b(void);
void scheduler_init(void);
void schedule(void);
void sleep_ticks(uint64_t ticks);
void start_scheduler(void);
void yield(void);

#endif
#ifndef SCHEDULER_H
#define SCHEDULER_H

#include <stdint.h>
#include "task.h"

extern uint64_t system_ticks;
extern TCB* current_task;

void task_a(void);
void task_b(void);
void scheduler_init(void);
void schedule(void);
void sleep_ticks(uint64_t ticks);
void start_scheduler(void);
void yield(void);

#endif
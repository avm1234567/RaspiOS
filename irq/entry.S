.macro kernel_entry

    sub sp, sp, #256
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]

    // Save the Link Register (x30)
    str x30, [sp, #16 * 15]
    mrs x22, elr_el2
    str x22, [sp, #248] //
.endm


.macro kernel_exit
        // Restore ELR first (before general registers overwrite x22)
        ldr x22, [sp, #248]
        msr elr_el2, x22

        // Load registers in pairs back from the stack
        ldp x0, x1, [sp, #16 * 0]
        ldp x2, x3, [sp, #16 * 1]
        ldp x4, x5, [sp, #16 * 2]
        ldp x6, x7, [sp, #16 * 3]
        ldp x8, x9, [sp, #16 * 4]
        ldp x10, x11, [sp, #16 * 5]
        ldp x12, x13, [sp, #16 * 6]
        ldp x14, x15, [sp, #16 * 7]
        ldp x16, x17, [sp, #16 * 8]
        ldp x18, x19, [sp, #16 * 9]
        ldp x20, x21, [sp, #16 * 10]
        ldp x22, x23, [sp, #16 * 11]
        ldp x24, x25, [sp, #16 * 12]
        ldp x26, x27, [sp, #16 * 13]
        ldp x28, x29, [sp, #16 * 14]

        // Restore the Link Register
        ldr x30, [sp, #16 * 15]

        // Give the 256 bytes back to the stack pointer
        add sp, sp, #256

        // Return from the exception/interrupt!
        eret
.endm

.macro handle_invalid_entry
    kernel_entry
    1:  b 1b
    .endm

    .align 11       // Table must be aligned to 2048 bytes (0x800)
    .global vectors // Make this visible to other files
vectors:
    // --- Row 1: Interrupts from Current EL with SP0 (Ignore) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; handle_invalid_entry  // IRQ
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

        // --- Row 2: Interrupts from Current EL with SPx (THIS IS US!) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; b el2_irq_handler     // IRQ (branch out to avoid 128-byte overflow)
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

        // --- Row 3: Interrupts from a Lower EL (AArch64) (Ignore for now) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; handle_invalid_entry  // IRQ
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

        // --- Row 4: Interrupts from a Lower EL (AArch32) (Ignore) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; handle_invalid_entry  // IRQ
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

// ---- IRQ handler lives outside the vector table ----
el2_irq_handler:
    kernel_entry                // 1. Save all registers
    bl handle_irq               // 2. Clear the timer + acknowledge GIC
    ldr x0, =current_task       // 3. Save old task's stack pointer
    ldr x1, [x0]
    mov x2, sp
    str x2, [x1]
    bl schedule                  // 4. Swap current_task pointer
    ldr x0, =current_task       // 5. Load new task's stack pointer
    ldr x1, [x0]
    ldr x2, [x1]
    mov sp, x2
    kernel_exit                 // 6. Restore registers and eret

.global start_scheduler
start_scheduler:
    // 1. Tell CPU: on eret, run at EL2 with interrupts unmasked
    mov x0, #0x9
    msr spsr_el2, x0

    // 2. Load the first task's saved stack pointer into sp
    ldr x0, =current_task
    ldr x1, [x0]            // x1 = &tcb_a
    ldr x2, [x1]            // x2 = tcb_a.sp (the forged task_a_stack)
    mov sp, x2              // Switch CPU stack pointer to Task A!

    // 3. Pop the forged registers and eret into Task A!
    kernel_exit

.global yield
yield:
    msr daifset, #2 //Mask interrupt briefly to avoid race conditions

    sub sp, sp, #256
    stp x0, x1, [sp, #16 * 0]
    stp x2, x3, [sp, #16 * 1]
    stp x4, x5, [sp, #16 * 2]   
    stp x6, x7, [sp, #16 * 3]
    stp x8, x9, [sp, #16 * 4]
    stp x10, x11, [sp, #16 * 5]
    stp x12, x13, [sp, #16 * 6]
    stp x14, x15, [sp, #16 * 7]
    stp x16, x17, [sp, #16 * 8]
    stp x18, x19, [sp, #16 * 9]
    stp x20, x21, [sp, #16 * 10]
    stp x22, x23, [sp, #16 * 11]
    stp x24, x25, [sp, #16 * 12]
    stp x26, x27, [sp, #16 * 13]
    stp x28, x29, [sp, #16 * 14]
    str x30, [sp, #16 * 15] // Save the Link Register (x30)

    str x30, [sp, #248] // Save the ELR (x30) to the stack
    
    ldr x0, =current_task
    ldr x1, [x0]            // x1 = &tcb_a
    mov x2, sp              // x2 = current stack pointer
    str x2, [x1]            // Save current stack pointer to current task's TCB

    bl schedule              // Call the scheduler to switch tasks

    ldr x0, =current_task
    ldr x1, [x0]            // x1 = &tcb_a
    ldr x2, [x1]            // x2 = tcb_a.sp
    mov sp, x2              // Switch CPU stack pointer to new task's stack

    kernel_exit             // Restore registers and return to the new task
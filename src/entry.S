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
.endm


.macro kernel_exit
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
    .align 7                        // IRQ (Timer interrupt jumps here!)
        kernel_entry                // 1. Take screenshot
        bl handle_irq               // 2. Call our C function to handle it
        kernel_exit                 // 3. Restore screenshot and resume
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

        // --- Row 3: Interrupts from a User App (AArch64) (Ignore for now) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; handle_invalid_entry  // IRQ
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError

        // --- Row 4: Interrupts from a User App (AArch32) (Ignore) ---
    .align 7; handle_invalid_entry  // Synchronous
    .align 7; handle_invalid_entry  // IRQ
    .align 7; handle_invalid_entry  // FIQ
    .align 7; handle_invalid_entry  // SError
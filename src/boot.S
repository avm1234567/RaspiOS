.section ".text.boot"

.global _start
_start:
mrs x0,mpidr_el1    // Get the CPU ID
and x0,x0,#0xFF     // Mask to get the CPU number
cbz x0,master       // Check if CPU 0 , if yes jump to master

proc_hang:
b proc_hang         // Infinite loop for other CPUs

master:
ldr x0, =stack_top  // Load the stack_top address into x0
mov sp,x0           

// Zero the BSS section
ldr x0, =bss_begin
ldr x1, =bss_end
1:  cmp x0, x1
    b.ge 2f
    str xzr, [x0], #8
    b 1b
2:

ldr x0, =vectors     // Load the address of the exception vector table
msr vbar_el1, x0      // Set the vector base address register
bl kernel_main  
b proc_hang         // If kernel_main returns, hang

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
bl kernel_main  

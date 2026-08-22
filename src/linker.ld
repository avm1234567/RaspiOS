ENTRY(_start)

SECTIONS
{
    . = 0x80000;

    .text.boot : { *(.text.boot) }
    .text      : { *(.text) }
    .rodata    : { *(.rodata) }
    .data      : { *(.data) }

    . = ALIGN(16);
    bss_begin = .;
    .bss : { *(.bss*) *(COMMON) }
    bss_end = .;

    . = ALIGN(16);
    . = . + 0x4000;
    stack_top = .;
}

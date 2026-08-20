SECTIONS
{
    . = 0x80000;

    .text.boot : { *(.text.boot) }
    .text      : { *(.text) }
    .rodata    : { *(.rodata) }
    .data      : { *(.data) }

    bss_begin = .;
    .bss : { *(.bss) }
    bss_end = .;

    . = . + 0x4000;
    stack_top = .;
}

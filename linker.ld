ENTRY(init)
OUTPUT_FORMAT("binary")
SECTIONS {
    . = 0x7c00;
    .text :
    {
        *(.init)
        *(.text)
    }
    .rodata :
    {
        *(.rodata)
    }
    .data :
    {
        *(.data)
    }
    .bss :
    {
        *(.bss)
    }
}
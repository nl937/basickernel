ENTRY(init)
SECTIONS{
    . = 1M;
    KERNEL_BEGIN = .;
    .text :
    {
        *(.multiboot)
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
    KERNEL_END = .;
	KERNEL_SIZE = KERNEL_END - KERNEL_BEGIN;
}
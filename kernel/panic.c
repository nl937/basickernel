#include "interrupts.h"
#include "../console/console.h"
#include "../stdlib/stdio.h"

char* exceptions[32] = {
    "Divide-by-zero",
    "Debug",
    "Non-maskable Interrupt",
    "Breakpoint",
    "Overflow",
    "Bound Range Exceeded",
    "Invalid Opcode",
    "Device Not Available",
    "Double Fault",
    "Coprocessor Segment Overrun",
    "Invalid TSS",
    "Segment Not Present",
    "Stack-Segment Fault",
    "General Protection Fault",
    "Page Fault",
    "Reserved",
    "x87 Floating-Point Exception",
    "Alignment Check",
    "Machine Check",
    "SIMD Floating-Point Exception",
    "Virtualization Exception",
    "Control Protection Exception",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Reserved",
    "Hypervisor Injection Exception",
    "VMM Communication Exception",
    "Security Exception",
    "Reserved"
};

void panic(registers_t panicregisters){
    console_setcolor(0x40);
    printf("\nException occured!\n");
    printf("Kernel panic!\n");
    printf(exceptions[panicregisters.int_no]);
    printf("\n");
    printf("DS:  %08x", panicregisters.ds);
    printf(" EDI: %08x \n", panicregisters.edi);
    printf("ESI: %08x ", panicregisters.esi);
    printf("EBP: %08x \n", panicregisters.ebp);
    printf("ESP: %08x ", panicregisters.esp);
    printf("EBX: %08x \n", panicregisters.ebx);
    printf("ECX: %08x ", panicregisters.ecx);
    printf("EAX: %08x \n", panicregisters.eax);
    printf("EIP: %08x ", panicregisters.eip);
    printf("CS:  %08x \n", panicregisters.cs);
    printf("SS:  %08x", panicregisters.ss);
    asm("hlt");
}
#include "idt.h"
#include "interrupts.h"
#include "../console/console.h"

struct idt_entry idt_table[256];
struct idt_descriptor idt_pointer;

static void idt_create_entry(unsigned char num, unsigned int base, unsigned short sel, unsigned char flags){
    idt_table[num].offset_low = base & 0xFFFF;
    idt_table[num].offset_high = (base >> 16) & 0xFFFF;
    idt_table[num].selector = sel;
    idt_table[num].always0 = 0;
    idt_table[num].flags = flags;
}

void idt_load(){
    idt_pointer.limit = 2047;
    idt_pointer.base = (unsigned int)&idt_table;
    idt_create_entry(0, (unsigned int)isr0, 0x08, 0x8E);
    idt_create_entry(1, (unsigned int)isr1, 0x08, 0x8E);
    idt_create_entry(2, (unsigned int)isr2, 0x08, 0x8E);
    idt_create_entry(3, (unsigned int)isr3, 0x08, 0x8E);
    idt_create_entry(4, (unsigned int)isr4, 0x08, 0x8E);
    idt_create_entry(5, (unsigned int)isr5, 0x08, 0x8E);
    idt_create_entry(6, (unsigned int)isr6, 0x08, 0x8E);
    idt_create_entry(7, (unsigned int)isr7, 0x08, 0x8E);
    idt_create_entry(8, (unsigned int)isr8, 0x08, 0x8E);
    idt_create_entry(9, (unsigned int)isr9, 0x08, 0x8E);
    idt_create_entry(10, (unsigned int)isr10, 0x08, 0x8E);
    idt_create_entry(11, (unsigned int)isr11, 0x08, 0x8E);
    idt_create_entry(12, (unsigned int)isr12, 0x08, 0x8E);
    idt_create_entry(13, (unsigned int)isr13, 0x08, 0x8E);
    idt_create_entry(14, (unsigned int)isr14, 0x08, 0x8E);
    idt_create_entry(15, (unsigned int)isr15, 0x08, 0x8E);
    idt_create_entry(16, (unsigned int)isr16, 0x08, 0x8E);
    idt_create_entry(17, (unsigned int)isr17, 0x08, 0x8E);
    idt_create_entry(18, (unsigned int)isr18, 0x08, 0x8E);
    idt_create_entry(19, (unsigned int)isr19, 0x08, 0x8E);
    idt_create_entry(20, (unsigned int)isr20, 0x08, 0x8E);
    idt_create_entry(21, (unsigned int)isr21, 0x08, 0x8E);
    idt_create_entry(22, (unsigned int)isr22, 0x08, 0x8E);
    idt_create_entry(23, (unsigned int)isr23, 0x08, 0x8E);
    idt_create_entry(24, (unsigned int)isr24, 0x08, 0x8E);
    idt_create_entry(25, (unsigned int)isr25, 0x08, 0x8E);
    idt_create_entry(26, (unsigned int)isr26, 0x08, 0x8E);
    idt_create_entry(27, (unsigned int)isr27, 0x08, 0x8E);
    idt_create_entry(28, (unsigned int)isr28, 0x08, 0x8E);
    idt_create_entry(29, (unsigned int)isr29, 0x08, 0x8E);
    idt_create_entry(30, (unsigned int)isr30, 0x08, 0x8E);
    idt_create_entry(31, (unsigned int)isr31, 0x08, 0x8E);
    asm("sti");
    idt_final((unsigned int)&idt_pointer);
    console_write("[ OK ] IDT loaded\n");
}
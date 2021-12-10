#include "idt.h"
#include "interrupts.h"
#include "../io/io.h"
#include "../console/console.h"

struct idt_entry idt[256];
struct idt_ptr idt_pointer;

void idt_create_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags){
    idt[num].base_low  = base & 0xFFFF;
    idt[num].base_high = (base >> 16) & 0xFFFF;
    idt[num].flags = flags;
    idt[num].always0 = 0;
    idt[num].kernelseg = sel;
}

void idt_install(){
    idt_pointer.limit = 2047;
    idt_pointer.base = (int)&idt;
    for(int i = 0; i < 255; i++){
        //Fix interrupts!
        idt_create_entry(i, (int)isrzero, 0x08, 0x8E);
    }
    io_portwrite(0x21, 0xFD);
    asm("sti");
    idt_create_entry(9, (int)isrzero, 0x08, 0x8E);
    console_write("[ OK ] Keyboard IRQ 0x09 created\n");
    idt_load(idt_pointer);
    console_write("[ OK ] IDT loaded\n");
}
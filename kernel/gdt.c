#include "gdt.h"
#include "../console/console.h"

struct gdt_entry gdt_table[5];
struct gdt_descriptor gdt_pointer;

static void gdt_create_entry(unsigned short num, unsigned int base, unsigned int limit, unsigned char access, unsigned char flags){
    gdt_table[num].base_low = base & 0xFFFF;
    gdt_table[num].base_mid = (base >> 16) & 0xFF;
    gdt_table[num].base_high = (base >> 24) & 0xFF;
    gdt_table[num].limit_low = limit & 0xFFFF;
    gdt_table[num].limit_flags = (limit >> 16) & 0x0F;
    gdt_table[num].limit_flags |= flags & 0xF0;
    gdt_table[num].access = access;
}

void gdt_load(){
    gdt_create_entry(0, 0, 0, 0, 0);
    gdt_create_entry(1, 0, 0xFFFFF, 0x9A, 0xCF);
    gdt_create_entry(2, 0, 0xFFFFF, 0x92, 0xCF);
    gdt_create_entry(3, 0, 0xFFFFF, 0xFA, 0xCF);
    gdt_create_entry(4, 0, 0xFFFFF, 0xF2, 0xCF);
    gdt_pointer.size = 39;
    gdt_pointer.offset = (unsigned int)&gdt_table;
    gdt_final((unsigned int)&gdt_pointer);
    console_writestatus(1, "GDT loaded");
}
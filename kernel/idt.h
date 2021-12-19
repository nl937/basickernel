struct idt_descriptor{
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

struct idt_entry{
    unsigned short offset_low;
    unsigned short selector;
    unsigned char always0;
    unsigned char flags;
    unsigned short offset_high;
} __attribute__((packed));

void idt_load();
void idt_final(unsigned int);
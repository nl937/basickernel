struct idt_entry {
    unsigned short base_low;
    unsigned short kernelseg;
    unsigned char always0;
    unsigned char flags;
    unsigned short base_high;
} __attribute__((packed));

struct idt_ptr {
    unsigned short limit;
    unsigned int base;
} __attribute__((packed));

void idt_create_entry(unsigned char num, unsigned long base, unsigned short sel, unsigned char flags);
void idt_install();
void idt_load(struct idt_ptr idt_pointer);
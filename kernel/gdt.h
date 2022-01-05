struct gdt_descriptor{
    unsigned short size;
    unsigned int offset;
} __attribute__((packed));

struct gdt_entry{
    unsigned short limit_low;
    unsigned short base_low;
    unsigned char base_mid;
    unsigned char access;
    unsigned char limit_flags;
    unsigned char base_high;
} __attribute__((packed));

void gdt_load();
void gdt_final(unsigned int);
#include "pmm.h"
#include "../stdlib/stdio.h"
#include "../stdlib/string.h"
#include "../boot/multiboot.h"
#include "../console/console.h"
#include <stddef.h>

//Block size is 4096 bytes (4kb pages)
#define pmm_blocksize 4096
unsigned long* pmm_bitmap;
unsigned long memsize;
unsigned long blocks_used;
unsigned long blocks_max;
unsigned long blocks_free;
extern unsigned long *KERNEL_BEGIN;
extern unsigned long *KERNEL_END;
extern unsigned long *KERNEL_END_PHYS;
extern unsigned int KERNEL_SIZE;

void pmm_init(multiboot_info_t* mbd){
    printf("Initializing memory manager\n");
    printf("Total upper memory: %dkB\n", mbd->mem_upper);
    memsize = mbd->mem_upper + mbd->mem_lower;
    pmm_bitmap = (unsigned long*)KERNEL_END;
    blocks_max = (memsize * 1024) / pmm_blocksize;
    blocks_used = 0;
    printf("Blocks initialized: %d\n", blocks_max);
    printf("Kernel start: %08x, ", &(KERNEL_BEGIN));
    printf("Kernel end: %08x\n", &(KERNEL_END));
    //Protect low memory, kernel, and the PMM memory bitmap
    pmm_deinit_region(0, (unsigned long)&KERNEL_BEGIN);
    pmm_deinit_region((unsigned long*)&KERNEL_BEGIN, (unsigned long)&(KERNEL_SIZE) + (blocks_max / 8));
    printf("Blocks free: %d\n", blocks_max - blocks_used);
}

void pmm_map_set(int bit){
    pmm_bitmap[bit/32] |= (1 << (bit % 32));
}

void pmm_map_unset(int bit){
    pmm_bitmap[bit/32] &= ~ (1 << (bit % 32));
}

int pmm_map_test(unsigned long bit){
    return pmm_bitmap[bit/32] & (1 << (bit % 32));
}

int pmm_first_free(){
    for(unsigned long i = 0; i < blocks_max/32; i++){
        if(pmm_bitmap[i] != 0xFFFFFFFF){
            for(int t = 0; t < 32; t++){
                int bit = 1 << t;
                if(!(pmm_bitmap[i] & bit)){
                    return i*32+t;
                }
            }
        }
    }
    return 0;
}

void pmm_init_region(unsigned long* addr, unsigned long size){
    unsigned int block_num = (unsigned long)addr / 4096;
    unsigned int blocks = size / 4096;
    for(; blocks > 0; blocks--){
        pmm_map_unset(block_num++);
        blocks_used--;
    }
    pmm_map_set(0);
}

void pmm_deinit_region(unsigned long* addr, unsigned long size){
    unsigned long block_num = (unsigned long)addr / 4096;
    unsigned int blocks = size / 4096;
    for(; blocks > 0; blocks--){
        pmm_map_set(block_num++);
        blocks_used++;
    }
    pmm_map_set(0);
}

void* pmm_allocate_page(){
    if(blocks_used == blocks_max){
        printf("PPM: Out of memory");
        pmm_panic();
    }
    unsigned long block = pmm_first_free();
    pmm_map_set(block);
    blocks_used++;
    return (void*)(block * pmm_blocksize);
}

void* pmm_allocate_pages(unsigned int num){
    if(blocks_used == blocks_max){
        printf("PPM: Out of memory");
        pmm_panic();
    }
    unsigned long block = pmm_first_free();
    for(unsigned int i = 0; i < num; i++){
        pmm_map_set(block + i);
    }
    return (void*)(block * pmm_blocksize);
}

void pmm_deallocate_page(unsigned long ptr){
    blocks_used--;
    unsigned long block = ptr/pmm_blocksize;
    pmm_map_unset(block);
}

void pmm_deallocate_pages(unsigned long ptr, int num){
    unsigned long block = ptr/pmm_blocksize;
    for(int i = 0; i < num; i++){
        pmm_map_unset(block + i);
    }
}

void pmm_panic(){
    console_setcolor(0x40);
    printf("\nOut of memory!\n");
    printf("Kernel panic!\n");
    asm("hlt");
}
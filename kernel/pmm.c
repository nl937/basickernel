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
    memsize = mbd->mem_upper + mbd->mem_lower;
    blocks_max = (memsize * 1024) / pmm_blocksize;
    pmm_bitmap = &KERNEL_END + 1;
    printf("[PMM] Starting....\n");
    printf("[PMM] Kernel begin: %08x\n", &KERNEL_BEGIN);
    printf("[PMM] Kernel end: %08x\n", &KERNEL_END);
    printf("[PMM] Total memory: %dkb\n", mbd->mem_upper);
    printf("[PMM] Total blocks: %d\n", blocks_max);
    pmm_deinit_region(0x0, &KERNEL_END + 0x00001000);
    printf("[PMM] Blocks free: %d\n", blocks_max - blocks_used);
    printf("[PMM] Allocate test: 0x%08x\n", (unsigned long)pmm_allocate_page());
}

void pmm_map_set(int bit){
    pmm_bitmap[bit / 32] |= (1 << (bit % 32));
}

void pmm_map_unset(int bit){
    pmm_bitmap[bit / 32] &= ~ (1 << (bit % 32));
}

int pmm_map_test(unsigned long bit){
    return pmm_bitmap[bit / 32] & (1 << (bit % 32));
}

int pmm_first_free(){
    for(unsigned long i = 0; i < blocks_max / 32; i++){
        if(pmm_bitmap[i] != 0xFFFFFFFF){
            for(int j = 0; j < 32; j++){
                int bit = 1 << j;
                if(!(pmm_bitmap[i] & bit)){
                    return i*4*8+j;
                }
            }
        }
    }
    return -1;
}

void pmm_init_region(unsigned long addr, unsigned long size){
    int start_block = addr / pmm_blocksize;
    int blocks = size / pmm_blocksize;
    for(int i = start_block; i < start_block + blocks; i++){
        pmm_map_unset(i);
        blocks_used++;
    }
    pmm_map_set(0);
}

void pmm_deinit_region(unsigned long addr, unsigned long size){
    int start_block = addr / pmm_blocksize;
    int blocks = size / pmm_blocksize;
    for(int i = start_block; i < start_block + blocks; i++){
        pmm_map_set(i);
        blocks_used++;
    }
}

void* pmm_allocate_page(){
    if(blocks_used == blocks_max){
        pmm_panic();
    }
    int first_free = pmm_first_free();
    pmm_map_set(first_free);
    unsigned long addr = first_free * pmm_blocksize;
    blocks_used++;
    return (void*)addr;
}

void* pmm_allocate_pages(unsigned int num){

}

void pmm_deallocate_page(unsigned long ptr){
    int block = ptr / pmm_blocksize;
    pmm_map_unset(block);
    blocks_used--;
}

void pmm_deallocate_pages(unsigned long ptr, int num){

}

void pmm_panic(){
    console_setcolor(0x40);
    printf("\nOut of memory!\n");
    printf("Kernel panic!\n");
    asm("hlt");
}
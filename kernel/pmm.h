#include "../boot/multiboot.h"

void pmm_init(multiboot_info_t* mbd);

void pmm_map_set(int bit);

void pmm_map_unset(int bit);

int pmm_map_test(unsigned long bit);

int pmm_first_free();

void pmm_init_region(unsigned long addr, unsigned long size);

void pmm_deinit_region(unsigned long addr, unsigned long size);

void* pmm_allocate_page();

void* pmm_allocate_pages(unsigned int num);

void pmm_deallocate_page(unsigned long ptr);

void pmm_deallocate_pages(unsigned long ptr, int num);

void pmm_panic();
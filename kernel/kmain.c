#include "../boot/multiboot.h"
#include "../drv/fb.h"
#include "../console/console.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "interrupts.h"
#include "idt.h"
#include "gdt.h"
#include "timer.h"
#include "../drv/ata.h"
#include "../stdlib/string.h"
#include "../stdlib/stdio.h"
#include "pmm.h"

void kmain(multiboot_info_t* mbd, unsigned int magic){
    printf("0x%08x",magic);
    console_clear();
    console_setcolor(0x09);
    printf(" **      **                           \n\
/**     /**                           \n\
/**     /**  **        ******   ******\n\
/****** /** **  ***** **////** **//// \n\
/**///**/****  ///// /**   /**//***** \n\
/**  /**/**/**       /**   /** /////**\n\
/****** /**//**      //******  ****** \n\
/////   //  //        //////  //////  \n");
    console_setcolor(0x0F);
    printf("Booting kernel\n");
    gdt_load();
    idt_load();
    interrupt_pic_init();
    timer_init();
    pmm_init(mbd);
    ata_init();
    printf("kshell > ");
    while(1==1){
        if(console_cursor_x == 0){
            char* buffer = console_buffer_fetch();
            if(strcmp(buffer, "about\n") == 0){
                printf("bk-os 0.01\n");
            }
            else if(strcmp(buffer, "clear\n") == 0){
                console_clear();
            }
            else if(strcmp(buffer, "panic\n") == 0){
                asm("int $0x3");
            }
            else if(strcmp(buffer, "memtest\n") == 0){
                printf("Allocate test: %08x\n", pmm_allocate_page());
            }
            else if(strcmp(buffer, "readtest\n") == 0){
                unsigned int *test = pmm_allocate_page();
                printf("Allocated 0x%08x\n", test);
                printf("Sector test\n");
                ata_read_sectors(test, 1, 1);
                for(int i = 0; i < 256; i++){
                    printf("%02x ", test[i] & 0x00FF);
                    printf("%02x ", test[i] >> 8);
                }
            }
            else{
                printf("command not found\n");
            }
            console_buffer_clear();
            printf("kshell > ");
        }
    }
}
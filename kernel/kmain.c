#include "../drv/fb.h"
#include "../console/console.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "interrupts.h"
#include "idt.h"
#include "gdt.h"

void kmain(){
    console_clear();
    console_setcolor(0x0F);
    console_write("####     ####                              \n\
#  #     #  #              ######   #######\n\
#  ####  #  ####  ####### ##    ##  #     #\n\
      ## #  #  #  #     # #  ##  # #  #####\n\
#  ##  # #    ##  ####### #  ##  # ##    ##\n\
#  ##  # #  #  ##         #  ##  # #####  #\n\
#     ## #  ##  #         ##    ## #     ##\n\
 # ####  ########          ######  ####### \n\n");
    gdt_load();
    idt_load();
    interrupt_pic_init();
    while(1==1){

    }
}
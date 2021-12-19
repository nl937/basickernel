#include "../drv/fb.h"
#include "../drv/keyboard.h"
#include "../console/console.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "idt.h"

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
    idt_load();
    asm("int $0x04");
}
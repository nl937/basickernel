#include "../console/console.h"
#include "interrupts.h"
void interrupt_handler(registers_t regstatus){
    if(regstatus.int_no < 32){
        console_setcolor(0x40);
        console_write("Exception occured!\n");
        console_write("Kernel panic!\n");
        asm("hlt");
    }
}
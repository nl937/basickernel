#include "interrupts.h"
#include "../io/io.h"
#include "../console/console.h"

void isr_handler(){
    io_portwrite(0x21, 0x20);
    console_write("Interrupt occured!\n");
}

void exception_handler(){
    console_write("Exception occured, panic!");
    asm("hlt");
}
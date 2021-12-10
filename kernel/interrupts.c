#include "interrupts.h"
#include "../console/console.h"

void isr_handler(){
    console_write("Interrupt triggered!");
}
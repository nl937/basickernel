#include "interrupts.h"
#include "../drv/fb.h"

void isr_handler(){
    fb_writechar("E", 0xF, 0x0, 1, 1);
}
#include "../drv/fb.h"
#include "../drv/keyboard.h"
#include "../console/console.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "interrupts.h"
#include "idt.h"

void kmain(){
    //Interrupts do not work!
    //idt_install();
    console_clear();
}
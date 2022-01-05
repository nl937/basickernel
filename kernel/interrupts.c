#include "../console/console.h"
#include "interrupts.h"
#include "../io/io.h"
#include "../drv/keyboard.h"

unsigned long ticks = 0;
unsigned char shift;

void interrupt_handler(registers_t regstatus){
    if(regstatus.int_no < 32){
        console_setcolor(0x40);
        console_write("Exception occured!\n");
        console_write("Kernel panic!\n");
        asm("hlt");
    }
    else if(regstatus.int_no == 32){
        //IRQ0 is the PIT
        //TODO: Implement a proper timer system
    }
    else if(regstatus.int_no == 33){
        unsigned char keycode = io_portread(0x60);
        if(keycode < 0x81){
            if(keycode == 0x0E){
                console_backspace();
            }
            //Shift key doesn't work :(
            /*
            else if((keycode == 0x2A) | (keycode == 0x36)){
                shift = 1;
            }
            else if((keycode == 0xAA) | (keycode == 0xB6)){
                shift = 0;
            }*/
            else{/*
                if(shift == 1){
                    console_writechar(keyboard_keymap_shift[keycode]);
                }
                else{
                    console_writechar(keyboard_keymap[keycode]);
                }*/
                console_writechar(keyboard_keymap[keycode]);
            }
        }
    }
    io_portwrite(0x20, 0x20);
    return;
}

void interrupt_pic_init(){
    unsigned char mask1 = io_portread(0x21);
    unsigned char mask2 = io_portread(0xA1);
    io_portwrite(0x20, 0x10 | 0x01);
    io_portwrite(0xA0, 0x10 | 0x01);
    io_portwrite(0x21, 0x20);
    io_portwrite(0xA1, 0x28);
    io_portwrite(0x21, 4);
    io_portwrite(0xA1, 2);
    io_portwrite(0x21, 0x01);
    io_portwrite(0xA1, 0x01);
    io_portwrite(0x21, mask1);
    io_portwrite(0xA1, mask2);
    console_writestatus(1, "Master and Slave PICs reconfigured and masked");
}
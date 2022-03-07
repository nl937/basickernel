#include "../console/console.h"
#include "interrupts.h"
#include "../io/io.h"
#include "../drv/keyboard.h"
#include "../stdlib/stdio.h"
#include "timer.h"
#include "panic.h"

void interrupt_handler(registers_t regstatus){
    if(regstatus.int_no < 32){
        panic(regstatus);
    }
    else if(regstatus.int_no == 32){
        //Implement tick system for sleep() calls
        timer_increment();
    }
    else if(regstatus.int_no == 33){
        unsigned char keycode = io_portread_b(0x60);
        if(keycode < 0x81){
            if(keycode == 0x0E){
                console_backspace();
                console_buffer_pop();
            }
            else{
                console_buffer_append(keyboard_keymap[keycode]);
                console_writechar(keyboard_keymap[keycode]);
            }
        }
    }
    io_portwrite_b(0x20, 0x20);
    return;
}

void interrupt_pic_init(){
    unsigned char mask1 = io_portread_b(0x21);
    unsigned char mask2 = io_portread_b(0xA1);
    io_portwrite_b(0x20, 0x10 | 0x01);
    io_portwrite_b(0xA0, 0x10 | 0x01);
    io_portwrite_b(0x21, 0x20);
    io_portwrite_b(0xA1, 0x28);
    io_portwrite_b(0x21, 4);
    io_portwrite_b(0xA1, 2);
    io_portwrite_b(0x21, 0x01);
    io_portwrite_b(0xA1, 0x01);
    io_portwrite_b(0x21, mask1);
    io_portwrite_b(0xA1, mask2);
    console_writestatus(1, "Master and Slave PICs reconfigured and masked");
}
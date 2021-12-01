#include "../drv/fb.h"
#include "../drv/keyboard.h"
#include "../io/io.h"
#include "../io/serial.h"
#include "../image.h"

#define COM1 0x3F8

void kmain(){
    char* string = "Hello World!";
    fb_clearscreen_text();
    serial_init(COM1, 2);
    serial_configure_line(COM1);
    serial_configure_buffers(COM1);
    serial_configure_modem(COM1);
    int i;
    while(i < 12){
        if(serial_transfer_fifo_empty(COM1)){
            serial_write(COM1, &(string[i]));
            fb_writechar(&(string[i]), 0xF, 0x0, i, 0);
        }
        i++;
    }
    keyboard_init();
}
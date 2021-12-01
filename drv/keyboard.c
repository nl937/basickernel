#include "../io/io.h"

void keyboard_init(){
    io_portwrite(0x64, 0xAE);
}

char keyboard_keypressed(){
    if((io_portread(0x64) & 0x01) == 0x01){
        return 0xFF;
    }
    else{
        return 0x00;
    }
}

char keyboard_getkey(){
    char key = io_portread(0x60);
    return key;
}
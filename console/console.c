#include "../drv/fb.h"

char console_cursor_x = 0;

char console_cursor_y = 0;

unsigned char console_color = 0x0F;

void console_init(){
    fb_clearscreen_text();
    fb_movecursor(0);
}

void console_setcolor(unsigned char color){
    console_color = color;
}

void console_clear(){
    fb_clearscreen_text();
    console_cursor_x = 0;
    console_cursor_y = 0;
    fb_movecursor(0);
}

void console_scroll(){
    short* vga = (short*)0xB8000;
    short blank = 0x0F20;
    if(console_cursor_y >= 25){
        for(int i = 0; i < 1920; i++){
            vga[i] = vga[i+80];
        }
        for(int i = 1920; i < 2000; i++){
            vga[i] = blank;
        }
        console_cursor_y = 24;
    }
}

void console_writechar(char c){
    short* vga = (short*)0xB8000;
    if(c == '\n'){
        console_cursor_x = 0;
        console_cursor_y++;
    }
    else if (console_cursor_x >= 80){
        console_cursor_x = 0;
        console_cursor_y++;
    }
    else{
        vga[(console_cursor_y * 80) + console_cursor_x] = (console_color << 8) | c;
        console_cursor_x++;
    }
    console_scroll();
    fb_movecursor((console_cursor_y * 80) + console_cursor_x);
}

void console_write(char* c){
    int i = 0;
    while(c[i]){
        console_writechar(c[i++]);
    }
}
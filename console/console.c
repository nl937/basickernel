#include "../drv/fb.h"

char console_cursor_x = 0;

char console_cursor_y = 0;

unsigned char console_color = 0x0F;

char console_buffer[256];

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

void console_backspace(){
    short* vga = (short*)0xB8000;
    console_cursor_x = console_cursor_x - 1;
    vga[(80*console_cursor_y) + console_cursor_x] = 0x00;
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

void console_writestatus(char status, char* message){
    if(status == 0){
        console_setcolor(0x04);
        console_write("[ FAIL ] ");
    }
    if(status == 1){
        console_setcolor(0x0A);
        console_write("[ OK ] ");
    }
    console_setcolor(0x0F);
    console_write(message);
    console_writechar('\n');
}

void console_buffer_append(char c){
    int i;
    for(i = 0; i < 256; i++){
        if(console_buffer[i] == '\0'){
            break;
        }
        else{
            continue;
        }
    }
    console_buffer[i] = c;
    console_buffer[i+1] = '\0';
}

char* console_buffer_fetch(){
    return console_buffer;
}

void console_buffer_clear(){
    console_buffer[0] = '\0';
}

void console_buffer_pop(){
    int i;
    for(i = 0; i < 256; i++){
        if(console_buffer[i] == '\0'){
            break;
        }
        else{
            continue;
        }
    }
    console_buffer[i-1] = '\0';
}
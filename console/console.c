#include "../drv/fb.h"
#include "../boot/multiboot.h"
#include "../io/io.h"
#include "../io/serial.h"

#define CONSOLE_WIDTH 80
#define CONSOLE_HEIGHT 25

int console_cursor_x = 0;

int console_cursor_y = 0;

unsigned char console_color = 0x0F;

char console_buffer[256];

short console_textbuffer[CONSOLE_WIDTH * CONSOLE_HEIGHT];

void console_init(){
    //fb_clearscreen_text();
    fb_movecursor(0);
}

void console_setcolor(unsigned char color){
    console_color = color;
}

void console_flush(int type){
    if(type == 0){
        short* vga = (short*)0xB8000;
        vga[(CONSOLE_WIDTH * console_cursor_y) + console_cursor_x - 1] = console_textbuffer[(CONSOLE_WIDTH * console_cursor_y) + console_cursor_x - 1];
    }
    else if(type == 1){
        short* vga = (short*)0xB8000;
        for(int i = 0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; i++){
            vga[i] = console_textbuffer[i];
        }
    }
}

void console_clear(){
    console_cursor_x = 0;
    console_cursor_y = 0;
    for(int i = 0; i < CONSOLE_WIDTH * CONSOLE_HEIGHT; i++){
        console_textbuffer[i] = 0x0000;
    }
    console_flush(1);
}

void console_backspace(){
    console_cursor_x = console_cursor_x - 1;
    console_textbuffer[(CONSOLE_WIDTH*console_cursor_y) + console_cursor_x] = 0x0000;
    console_flush(0);
}

void console_scroll(){
    if(console_cursor_y >= CONSOLE_HEIGHT){
        for(int i = 0; i < (CONSOLE_WIDTH * CONSOLE_HEIGHT); i++){
            console_textbuffer[i] = console_textbuffer[i+CONSOLE_WIDTH];
        }
        for(int i = (CONSOLE_WIDTH * CONSOLE_HEIGHT); i < (CONSOLE_WIDTH * CONSOLE_HEIGHT) + CONSOLE_WIDTH; i++){
            console_textbuffer[i] = 0x0000;
        }
        console_cursor_y = CONSOLE_HEIGHT - 1;
        console_flush(1);
    }
    else{
        console_flush(0);
    }
}

void console_writechar(char c){
    if(c == '\n'){
        console_cursor_x = 0;
        console_cursor_y++;
    }
    else if (console_cursor_x >= CONSOLE_WIDTH){
        console_cursor_x = 0;
        console_cursor_y++;
        console_textbuffer[(console_cursor_y * CONSOLE_WIDTH) + console_cursor_x] = (console_color << 8) | c;
        console_cursor_x++;
    }
    else if(c != '\n'){
        console_textbuffer[(console_cursor_y * CONSOLE_WIDTH) + console_cursor_x] = (console_color << 8) | c;
        console_cursor_x++;
    }
    console_scroll();
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
    else if(status == 1){
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
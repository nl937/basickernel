#include "../io/io.h"
#include "fb.h"
//I/O ports
#define FB_COMMAND_PORT         0x3D4
#define FB_DATA_PORT            0x3D5
//I/O port commands
#define FB_HIGH_BYTE_COMMAND    14
#define FB_LOW_BYTE_COMMAND     15

unsigned char* vga;
int pitch;
int pixelwidth;

//VGA text mode
void fb_writechar(char* input, unsigned char back, unsigned char fore, int x, int y){
    short* vga = (short*)0xB8000;
    short color = ((back << 4) | fore) << 8;
    vga[(y*80)+x] = color | input[0];
}

void fb_clearscreen_text(){
    for(int y = 0; y < 2000; y++){
        short* vga = (short*)0xB8000;
        vga[y] = 0x0000;
    }
}

void fb_movecursor(unsigned short position){
    io_portwrite_b(FB_COMMAND_PORT, FB_HIGH_BYTE_COMMAND);
    io_portwrite_b(FB_DATA_PORT, ((position >> 8) & 0x00FF));
    io_portwrite_b(FB_COMMAND_PORT, FB_LOW_BYTE_COMMAND);
    io_portwrite_b(FB_DATA_PORT, position & 0x00FF);
}

//VGA graphics mode
void fb_clearscreen_graphics(unsigned long* fb, int p, int pix){
    vga = (unsigned char*)fb;
    pitch = p;
    pixelwidth = pix;
    for(int y = 0; y < 480; y++){
        for(int x = 0; x < 640; x++){
            fb_writepixel(x, y, 0x03);
        }
    }
}

void fb_writepixel(int x, int y, unsigned char color){
    vga[(pitch*y)+(x * (pixelwidth/8))] = color;
}
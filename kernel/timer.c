#include "../io/io.h"
#include "../console/console.h"

unsigned long ticks = 0; 

void timer_init(){
    io_portwrite_b(0x43, 0x36);
    io_portwrite_b(0x40, 0x54);
    io_portwrite_b(0x40, 0x02);
    console_writestatus(1, "2000hz PIT started");
    ticks = 0;
}

unsigned long timer_fetchticks(){
    return ticks;
}

void timer_increment(){
    ticks++;
}
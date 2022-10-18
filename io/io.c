#include "io.h"

void io_portwrite_b(unsigned short port, unsigned char data){
    __asm__ volatile("outb %0, %1" : : "a" (data), "Nd" (port));
}

unsigned char io_portread_b(unsigned short port){
    unsigned char data;
    __asm__ volatile("inb %1, %0" : "=a" (data) : "Nd" (port));
    return data;
}

void io_portwrite_w(unsigned short port, unsigned int data){
    __asm__ volatile("outw %w0, %w1" : : "a" (data), "Nd" (port));
}
unsigned int io_portread_w(unsigned short port){
    unsigned int data;
    __asm__ volatile("inw %w1, %w0" : "=a" (data) : "Nd" (port));
    return data;
}

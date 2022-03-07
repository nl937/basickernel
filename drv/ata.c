#include "../io/io.h"
#include "ata.h"
#include "../console/console.h"

static void ata_wait_bsy();
//static void ata_wait_drq();

void ata_init(){
    ata_wait_bsy();
    //Detect drives
    io_portwrite_b(0x1F6, 0xA0);
    io_portwrite_w(0x1F2, 0x0000);
    io_portwrite_w(0x1F3, 0x0000);
    io_portwrite_w(0x1F4, 0x0000);
    io_portwrite_w(0x1F5, 0x0000);
    io_portwrite_b(0x1F7, 0xEC);
    if(io_portread_b(0x1F7) == 0x00){
        console_writestatus(0, "ATA PIO: No drives found");
    }
    else{

    }
}
/*
void* ata_read_sectors(unsigned int lba, unsigned short sectors, unsigned int* target){
    return 0;
}

void ata_write_sectors(unsigned int lba, unsigned short secors, unsigned int* origin){
}
*/
static void ata_wait_bsy(){
    while(io_portread_b(0x1F7) != 0){}
}

/*static void ata_wait_drq(){
    while(io_portread_b(0x1F7) != 1){}
}*/
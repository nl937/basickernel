#include "../io/io.h"
#include "ata.h"
#include "../console/console.h"
#include "../stdlib/stdio.h"

static void ata_wait_bsy();
static void ata_wait_drq();

int ata_init(){
    if(io_portread_b(0x1F7) == 0xFF){
        console_writestatus(0, "ATA-PIO: No drives found");
        return 1;
    }
    else{
        return 0;
    }
}

void ata_read_sectors(unsigned int target_address, unsigned int LBA, unsigned char sectors){
    printf("0x%08x\n", target_address);
    io_portwrite_b(0x1F6, 0xE0 | ((LBA >> 24) & 0x0F));
    io_portwrite_b(0x1F1, 0x00);
    io_portwrite_b(0x1F2, sectors);
    io_portwrite_b(0x1F3, (unsigned char)LBA);
    io_portwrite_b(0x1F4, (unsigned char)(LBA >> 8));
    io_portwrite_b(0x1F5, (unsigned char)(LBA >> 16));
    io_portwrite_b(0x1F7, 0x20);
    ata_wait_bsy();
    ata_wait_drq();
    unsigned int* data = target_address;
    for(int s = 0; s < sectors; s++){
        ata_wait_bsy();
        ata_wait_drq();
        for(int a = 0; a < 256; a++){
            data[(s * 256) + a] = io_portread_w(0x1F0);
        }
    }
}

static void ata_wait_bsy(){
    while(io_portread_b(0x1F7) & 0x80);
}

static void ata_wait_drq(){
    while(!(io_portread_b(0x1F7) & 0x40));
}
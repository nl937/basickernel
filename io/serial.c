#include "io.h"

#define SERIAL_DATA_PORT(base)          (base)
#define SERIAL_FIFO_COMMAND_PORT(base)  (base + 2)
#define SERIAL_LINE_COMMAND_PORT(base)  (base + 3)
#define SERIAL_MODEM_COMMAND_PORT(base) (base + 4)
#define SERIAL_LINE_STATUS_PORT(base)   (base + 5)
#define SERIAL_LINE_ENABLE_DLAB         0x80

void serial_init(unsigned short com, unsigned short divisor){
    io_portwrite(SERIAL_LINE_COMMAND_PORT(com), SERIAL_LINE_ENABLE_DLAB);
    io_portwrite(SERIAL_DATA_PORT(com), (divisor >> 8) & 0x00FF);
    io_portwrite(SERIAL_DATA_PORT(com), divisor & 0x00FF);
}

void serial_configure_line(unsigned short com){
    io_portwrite(SERIAL_LINE_COMMAND_PORT(com), 0x03);
}

void serial_configure_buffers(unsigned short com){
    io_portwrite(SERIAL_FIFO_COMMAND_PORT(com), 0xC7);
}

void serial_configure_modem(unsigned short com){
    io_portwrite(SERIAL_MODEM_COMMAND_PORT(com), 0x03);
}

int serial_transfer_fifo_empty(unsigned short com){
    return io_portread(SERIAL_LINE_STATUS_PORT(com)) & 0x20;
}

void serial_write(unsigned short com, char* data){
    io_portwrite(com, data[0]);
}
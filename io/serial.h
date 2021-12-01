void serial_init(unsigned short com, unsigned short divisor);
void serial_configure_line(unsigned short com);
void serial_configure_buffers(unsigned short com);
void serial_configure_modem(unsigned short com);
int serial_transfer_fifo_empty(unsigned short com);
void serial_write(unsigned short port, char* data);
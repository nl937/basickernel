//Sends the given data to the given I/O port.
void io_portwrite_b(unsigned short port, unsigned char data);
unsigned char io_portread_b(unsigned short port);
void io_portwrite_w(unsigned short port, unsigned int data);
unsigned int io_portread_w(unsigned short port);
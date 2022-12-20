#include "../boot/multiboot.h"

void console_writechar(char c);

void console_write(char* c);

void console_clear();

void console_scroll();

void console_setcolor(unsigned char color);

void console_backspace();

void console_writestatus(char status, char* message);

void console_buffer_append(char c);

char* console_buffer_fetch();

void console_buffer_clear();

void console_buffer_pop();

extern char console_cursor_x;
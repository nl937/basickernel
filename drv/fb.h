void fb_writechar(char* input, unsigned char back, unsigned char fore, int x, int y);

void fb_clearscreen_text();

void fb_movecursor(unsigned short position);

void fb_clearscreen_graphics();

void fb_writepixel(int x, int y, unsigned char color);

void fb_writechar_bitmap(int num, int x, int y);
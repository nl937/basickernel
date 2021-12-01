//Write character to VGA text buffer
void fb_writechar(char* input, unsigned char back, unsigned char fore, int x, int y);
//Clear VGA text buffer
void fb_clearscreen_text();
//Move cursor
void fb_movecursor(unsigned short position);
//Clear VGA graphics buffer
void fb_clearscreen_graphics();
//Draw pixel
void fb_writepixel(int x, int y, unsigned char color);
//Draw bitmap character
void fb_writechar_bitmap(int num, int x, int y);
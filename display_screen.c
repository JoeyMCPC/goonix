// goonal/screen.c
#include <stdint.h>
#include <stddef.h>
#include "../include/screen.h"

void draw_char(struct limine_framebuffer *fb, char c, int x, int y, uint32_t color)
{
	// gets the character for the character 
	uint8_t *glyph = font8x8_basic[(int)c];
	
	// stupid array shit 
    for (int row = 0; row < 8; row++) 
    {
        for (int col = 0; col < 8; col++) 
	{
            if ((glyph[row] >> (7 - col)) & 1) 
	    {
		    // draws the character with a cool color
                size_t px = (y + row) * (fb->pitch / 4) + (x + col);
                ((uint32_t*)fb->address)[px] = color;
            }
        }
    }
}

// repeated use of draw_char
void draw_string(struct limine_framebuffer *fb, const char *str, int x, int y, uint32_t color); 
{
	for (int i = 0; str[i]; i++) 
	{
        	draw_char(fb, str[i], x + i * 8, y, color); // 8 px per char
   	}
}

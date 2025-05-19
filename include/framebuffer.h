#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>
#include "limine.h"

// Init function (call in kmain after Limine framebuffer is available)
void fb_terminal_init(struct limine_framebuffer *fb_ptr);

// Text rendering
void fb_terminal_putchar(char c);
void fb_terminal_writestring(const char* str);

// Pixel drawing
void fb_put_pixel(int x, int y, uint32_t color);

// Character drawing
void fb_draw_char(char c, int px, int py, uint32_t fg, uint32_t bg);


void clear_framebuffers(uint32_t color);

#endif


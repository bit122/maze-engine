#ifndef FRAMEBUFFER_H
#define FRAMEBUFFER_H

#include <stdint.h>

#define COLOR_BLACK     0x000000
#define COLOR_RED       0xFF0000
#define COLOR_GREEN     0x00FF00
#define COLOR_YELLOW    0xFFFF00
#define COLOR_BLUE      0x0000FF
#define COLOR_MAGENTA   0xFF00FF
#define COLOR_CYAN      0x00FFFF
#define COLOR_WHITE     0xFFFFFF
#define COLOR_GRAY      0xAAAAAA

int fb_init();
void fb_set_color(uint32_t color);
void fb_set_pos(int x, int y);
void fb_print(const char* s);
void fb_println(const char* s);

#endif
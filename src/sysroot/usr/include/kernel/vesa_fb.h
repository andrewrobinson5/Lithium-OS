#ifndef __VESA_FB_H
#define __VESA_FB_H

#include <kernel/mboot.h>
#include <stdint.h>

enum colors // DEPRECATED
{
    BLACK = 0,
    BLUE = 0x0000EE,
    GREEN = 0x00AA00,
    CYAN = 0x30d5c8,
    RED = 0xCC0000,
    MAGENTA = 0x770077,
    BROWN = 0x964B00,
    LIGHT_GREY = 0xBBBBBB,
    DARK_GREY = 0x777777,
    LIGHT_BLUE = 0x7777FF,
    LIGHT_GREEN = 0x00FF00,
    LIGHT_CYAN = 0x00FFFF,
    LIGHT_RED = 0xFF4444,
    LIGHT_MAGENTA = 0xDD00DD,
    LIGHT_BROWN = 0xffff00,
    WHITE = 0xFFFFFF,
};

int  fb_screenW;
int  fb_screenH;
void initVBE(struct mboot_info*);
void putPix(int, int, uint32_t);
void drawBG (uint32_t color);
void putRect (int x1, int y1, int x2, int y2, uint32_t color);
//void putLine( int x0, int y0, int x1, int y1, uint32_t color );

#endif

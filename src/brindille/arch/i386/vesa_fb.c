#include <stdint.h>
#include <kernel/mboot.h>
#include <kernel/vesa_fb.h>
//VBE Linear frame buffer small driver.
uint8_t *framebuffer;
uint32_t fbpitch;
uint8_t  fbbpp;
int fb_screenW;
int fb_screenH;

void putPix(int x,int y,uint32_t color)
{
	unsigned where = x*(fbbpp/8) + y*fbpitch;
	framebuffer[where + 0]= color;              // BLUE
	framebuffer[where + 1] = (color >> 8);   // GREEN
	framebuffer[where + 2] = (color >> 16);  // RED
}

void putRect ( int x1, int y1, int x2, int y2, uint32_t color )
{
	for (int y = y1; y < y2; y++) {
		for (int x = x1; x < x2; x++) {
			putPix( x, y, color );
		}
	}
}

void drawGradient ( uint32_t color1, uint32_t color2 )
{
	for(int s = 0; s<255; s++;)
	{
		for(int h = 0; h<255; h++;)
		{
			putPix(s, h, );
		}
	}

}

void drawBG (uint32_t color)
{
	putRect ( 0, 0, fb_screenW, fb_screenH, color );
}

/*void putLine( int x0, int y0, int x1, int y1, uint32_t color )
{
	double x = x1 - x0;
	double y = y1 - y0;
	double length = sqrt( x*x + y*y );
	double addx = x / length;
	double addx = y / length;
	x = x0;
	y = y0;
	
	for ( i = 0; i < length; i += 1) {
		putPix( x, y, color );
		x += addx;
		y += addy;
	}
}*/

/*
Initializing VESA mode. You'll need a Multiboot struct to work, because it's using info from it.
*/
void initVBE(struct mboot_info *mboot)
{
   //First, get the LFB address from MB info struct.
   framebuffer = (uint8_t*)(int)(mboot->framebuffer_addr);
   //Then get the pitch.
   fbpitch=mboot->framebuffer_pitch;
   //Then BPP.
   fbbpp=mboot->framebuffer_bpp;
   //And, finally, screen width and height.
   fb_screenW = mboot->framebuffer_width ;
   fb_screenH = mboot->framebuffer_height;
}

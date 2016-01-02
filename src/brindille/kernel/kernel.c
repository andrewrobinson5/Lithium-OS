#include <kernel/mboot.h>
#include <kernel/vesa_fb.h>
#include "../arch/i386/idt.h"
#include "../arch/i386/pic.h"
#include <kernel/serial.h>

void kernel_main(struct mboot_info *mboot)
{
	init_serial();

	idt_initialize();
	pic_initialize();

	initVBE(mboot);

	write_serial("Test");
	
	drawBG ( 0xFFE082 );
	putRect (120, 120, 604, 604, 0xB71C1C);
	putRect (120, 120, 380, 480, 0x455A64);
	
	putLine( 230, 125, 850, 850, 0x2196F3 );
}

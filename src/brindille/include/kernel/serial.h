#ifndef _KERNEL_SERIAL_H
#define _KERNEL_SERIAL_H

#include <kernel/portio.h>

void init_serial();
void write_serial(char a);

#endif

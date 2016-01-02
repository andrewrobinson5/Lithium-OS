#include <kernel/portio.h>
#include <kernel/serial.h>

#define PORT 0x3f8   /* COM1 */
 
void init_serial() {
	outport8(PORT + 1, 0x00);    // Disable all interrupts
	outport8(PORT + 3, 0x80);    // Enable DLAB (set baud rate divisor)
	outport8(PORT + 0, 0x03);    // Set divisor to 3 (lo byte) 38400 baud
	outport8(PORT + 1, 0x00);    //                  (hi byte)
	outport8(PORT + 3, 0x03);    // 8 bits, no parity, one stop bit
	outport8(PORT + 2, 0xC7);    // Enable FIFO, clear them, with 14-byte threshold
	outport8(PORT + 4, 0x0B);    // IRQs enabled, RTS/DSR set
}

int is_transmit_empty() {
	return inport8(PORT + 5) & 0x20;
}
 
void write_serial(char a) {
	while (is_transmit_empty() == 0);
 
	outport8(PORT,a);
}

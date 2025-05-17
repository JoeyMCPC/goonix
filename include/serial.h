#ifndef SERIAL_H
#define SERIAL_H

#include <stdint.h>
#include <stddef.h>

#define COM1 0x3F8  // COM1 base port

void serial_init(void);
int serial_is_transmit_fifo_empty(void);
void serial_write_char(char a);
void serial_write_string(const char* str);

#endif


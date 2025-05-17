#include "serial.h"

static inline void outb(uint16_t port, uint8_t val) {
    asm volatile ( "outb %0, %1" : : "a"(val), "Nd"(port) );
}

static inline uint8_t inb(uint16_t port) {
    uint8_t ret;
    asm volatile ( "inb %1, %0" : "=a"(ret) : "Nd"(port) );
    return ret;
}

void serial_init(void) {
    outb(COM1 + 1, 0x00); // Disable all interrupts
    outb(COM1 + 3, 0x80); // Enable DLAB (set baud rate divisor)
    outb(COM1 + 0, 0x03); // Set divisor to 3 (lo byte) 38400 baud
    outb(COM1 + 1, 0x00); //                  (hi byte)
    outb(COM1 + 3, 0x03); // 8 bits, no parity, one stop bit
    outb(COM1 + 2, 0xC7); // Enable FIFO, clear them, with 14-byte threshold
    outb(COM1 + 4, 0x0B); // IRQs enabled, RTS/DSR set
}

int serial_is_transmit_fifo_empty() {
    return inb(COM1 + 5) & 0x20;
}

void serial_write_char(char a) {
    while (serial_is_transmit_fifo_empty() == 0);
    outb(COM1, a);
}

void serial_write_string(const char* str) {
    while (*str) {
        if (*str == '\n') {
            // First \r\n to start a new line
            serial_write_char('\r');
            serial_write_char('\n');
            // Second \r\n to create a blank line
            serial_write_char('\r');
            serial_write_char('\n');
        } else {
            serial_write_char(*str);
        }
        str++;
    }

}


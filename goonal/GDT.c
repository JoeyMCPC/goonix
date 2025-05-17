#include "GDT.h"
#include <stdint.h>
#include "goonal.h"
#define GDT_SIZE 3
uint8_t gdt[GDT_SIZE * 8];  // 8 bytes per entry
void encode_gdt_entry(uint8_t *target, struct GDT source) {
    // Limit is only relevant for legacy mode, but set it anyway
    if (source.limit > 0xFFFFF) {
        kerror("GDT cannot encode limits larger than 0xFFFFF");
    }

    // Encode limit (20 bits)
    target[0] = (source.limit & 0xFF);
    target[1] = (source.limit >> 8) & 0xFF;
    target[6] = (source.limit >> 16) & 0x0F;

    // Encode base (only first 32 bits used)
    target[2] = source.base & 0xFF;
    target[3] = (source.base >> 8) & 0xFF;
    target[4] = (source.base >> 16) & 0xFF;
    target[7] = (source.base >> 24) & 0xFF;

    // Access byte
    target[5] = source.access_byte;

    // Flags (upper nibble of byte 6)
    target[6] |= (source.flags << 4);
}

// gdtr 
struct GDTR gdtr;

// defining the segments
struct GDT null_entry = { .limit = 0, .base = 0, .access_byte = 0, .flags = 0 };

struct GDT code_entry = { .limit = 0xFFFFF, .base = 0, .access_byte = 0x9A, .flags = 0xA };

struct GDT data_entry = { .limit = 0xFFFFF, .base = 0, .access_byte = 0x92, .flags = 0xA };

 

void setup_gdt(void)
{
	// encode null segment 
	encode_gdt_entry(&gdt[0], null_entry);
	
	// encode code segment
	encode_gdt_entry(&gdt[8], code_entry);

	// encode data segment 
	encode_gdt_entry(&gdt[16], data_entry);
	// setup gtdr 
	gdtr.limit = sizeof(gdt) - 1;

	gdtr.base = (uint64_t)(uintptr_t)&gdt;

	gdt_load_and_jump(&gdtr);

	serial_write_string("GDT Loaded \n");

}



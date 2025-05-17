#ifndef GDT_H
#define GDT_H

#include <stdint.h>
#include <stddef.h>
// I still don't know what the fuck a GDT is but it is apparently important 
struct GDT {
    uint32_t base;
    uint32_t limit;
    uint8_t access_byte;
    uint8_t flags;
};


struct GDTEntry64 {
    uint16_t limit_low;
    uint16_t base_low;
    uint8_t  base_middle;
    uint8_t  access;
    uint8_t  granularity;
    uint8_t  base_high;
} __attribute__((packed));



void encode_gdt_entry(uint8_t *target, struct GDT source);
void setup_gdt(void);

// GDT descriptor struct
struct GDTR {
    uint16_t limit; 
    uint32_t base;
} __attribute__((packed));

extern void gdt_load_and_jump(struct GDTR* gdtr_ptr); // ASM function to load GDTR


#endif

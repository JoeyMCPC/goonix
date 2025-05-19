#include "goonal.h"
#include "interrupt.h"
#include "GDT.h"
#include <stdbool.h>






// actual describer
static idtr_t idtr;
// stuff needed to fix errors
static bool vectors[IDT_MAX_DESCRIPTORS];

// a pretty cool function
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags) {
    idt_entry_t* descriptor = &idt[vector];

    descriptor->isr_low        = (uint64_t)isr & 0xFFFF;
    descriptor->kernel_cs      = GDT_OFFSET_KERNEL_CODE;
    descriptor->ist            = 0;
    descriptor->attributes     = flags;
    descriptor->isr_mid        = ((uint64_t)isr >> 16) & 0xFFFF;
    descriptor->isr_high       = ((uint64_t)isr >> 32) & 0xFFFFFFFF;
    descriptor->reserved       = 0;
}

void exception_handler(int vector, uint64_t error_code) 
{
    // Print basic info
    serial_write_string("Exception: ");
    serial_write_char('0' + vector); // crude
    serial_write_string("\n");
    hcf();
}

void idt_init() {
    idtr.base = (uintptr_t)&idt[0];
    idtr.limit = (uint16_t)sizeof(idt_entry_t) * IDT_MAX_DESCRIPTORS - 1;

    for (uint8_t vector = 0; vector < 32; vector++) {
        idt_set_descriptor(vector, isr_stub_table[vector], 0x8E);
        vectors[vector] = true;
    }

    __asm__ volatile ("lidt %0" : : "m"(idtr)); // load the new IDT
    __asm__ volatile ("sti"); // set the interrupt flag
	serial_init();
	serial_write_string("IDT Loaded\n");
}


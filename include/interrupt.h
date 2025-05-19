#include "goonal.h"
#include "GDT.h"
#include <stdint.h>
#include <stdbool.h>

#ifndef IDT_MAX_DESCRIPTORS
#define IDT_MAX_DESCRIPTORS 256
#endif
// idt_entry_t 
typedef struct {
	uint16_t    isr_low;      // The lower 16 bits of the ISR's address
	uint16_t    kernel_cs;    // The GDT segment selector that the CPU will load into CS before calling the ISR
	uint8_t	    ist;          // The IST in the TSS that the CPU will load into RSP; set to zero for now
	uint8_t     attributes;   // Type and attributes; see the IDT page
	uint16_t    isr_mid;      // The higher 16 bits of the lower 32 bits of the ISR's address
	uint32_t    isr_high;     // The higher 32 bits of the ISR's address
	uint32_t    reserved;     // Set to zero
} __attribute__((packed)) idt_entry_t;

// idt
__attribute__((aligned(0x10))) 
static idt_entry_t idt[256]; // Create an array of IDT entries; aligned for performance


// describer 
typedef struct {
	uint16_t	limit;
	uint64_t	base;
} __attribute__((packed)) idtr_t;

// im pretty sure this is the function that puts everything in the table but im really not sure 
void idt_set_descriptor(uint8_t vector, void* isr, uint8_t flags);

// init function that is called in kmain()
void idt_init(void);

// interrupt.asm has this
extern void* isr_stub_table[];

// move to exception.h later. 
__attribute__((noreturn))
void exception_handler(int vector, uint64_t error_code);



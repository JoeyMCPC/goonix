#pragma once
#include <stdint.h>

#define FREE 0
#define USED 1
#define ERROR 0

typedef uintptr_t pageframe_t;

#define MAX_FRAMES 4096  // Adjust as needed
extern uint8_t frame_map[MAX_FRAMES];
extern size_t npages;
extern uintptr_t startframe;
pageframe_t kalloc_frame_int(void);
pageframe_t kalloc_frame(void);
void kfree_frame(pageframe_t a);


#include "goonal.h" // Trust me we need something from this frfr
#include <stdint.h>
#include "page_frame_allocation.h"

// cool stuff that is "needed" for ts to work :tilted_rose: :tilted_rose:

uint64_t startframe = 0x100000; // or whatever your memory manager expects
size_t npages = 4096;           // number of page frames
uint8_t frame_map[MAX_FRAMES] = { 0 };     // or 
// this is the address of memory where the kernal stops 
// we need to know this so we dont "accidentally" allocate some of the memory needed for the kernal
// to the gooning machine that is the GOOSH (i am writing this comment before that is made)
extern uint32_t end_of_kernel;
pageframe_t kalloc_frame_int() {
    for (uint32_t i = 0; i < npages; i++) {
        if (frame_map[i] == FREE) {
            frame_map[i] = USED;
            return startframe + (i * 0x1000);
        }
    }
    return ERROR;
}

// angry gcc fix
pageframe_t pre_frames[128];

pageframe_t kalloc_frame() {
    static uint8_t allocate = 1;
    static uint8_t pframe = 0;
    pageframe_t ret;

    if (pframe == 20) {
        allocate = 1;
    }

    if (allocate) {
        for (int i = 0; i < 20; i++) {
            pre_frames[i] = kalloc_frame_int();
        }
        pframe = 0;
        allocate = 0;
    }

    ret = pre_frames[pframe++];
    return ret;
}



// takes a memory address and frees it up 
void kfree_frame(pageframe_t addr) {
    if (addr < startframe) return; // prevent freeing invalid memory

    uint32_t index = (addr - startframe) / 0x1000;
    if (index < npages) {
        frame_map[index] = FREE;
    }
}


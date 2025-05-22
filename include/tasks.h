#ifndef TASKS_H
#define TASKS_H
#include "goonal.h"
#include "page_frame_allocation.h"
//#include "interrupt.h"
#include <string.h>
// task
typedef struct task task;  // Forward declaration so the function pointers can reference it

struct task {
    void* memory;
    void* (*start)(task* self); // start function
    void  (*run)(task* self);   // run function
    int   (*end)(task* self);   // end function
};

extern task test_task; // declare the instance
#endif

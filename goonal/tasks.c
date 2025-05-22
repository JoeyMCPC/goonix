#include "goonal.h"
#include "page_frame_allocation.h"
#include "tasks.h"
#include "framebuffer.h"
#include "serial.h"



void* test_task_start(task* self) 
{
	// allocates memory to the task
    	self->memory = (void*) (uintptr_t) kalloc_frame_int();

    	fb_terminal_writestring("Address for test_task: ");
    	print_hex64((uint64_t)self->memory);
    	fb_terminal_writestring("\n");

    	return self->memory;
}
// This does not work :tilted_rose:
void test_task_run(task* self) 
{
    	fb_terminal_writestring("Running test_task...\n");

    	char* mem = (char*)self->memory;
    	mem[0] = 42; // just modify memory to test
}

int test_task_end(task* self) 
{
    	fb_terminal_writestring("Ending test_task and freeing memory.\n");
	
    	kfree_frame((pageframe_t)self->memory); // free the memory

    	return 0;
}

// setting up the test-task
task test_task = {
    .memory = NULL,
    .start = test_task_start,
    .run = test_task_run,
    .end = test_task_end
};

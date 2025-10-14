// Edit this test any way you want or
// copy a different test and edit that 
// to test additional case

#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {

    // init_heap and ensure it does not produce error
    assert(init_heap(4096) == 0);
	disp_heap();

	// request a memory block allocation 
    void* ptr = alloc(8);
	disp_heap();

	// if the ptr is NULL, the alloc failed
    assert(ptr != NULL);             


	// free the memory allocated
	free_block(ptr);
	disp_heap();

    exit(0);
}

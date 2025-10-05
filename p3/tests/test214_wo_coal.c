// many odd sized allocations and interspersed frees
// tests pass if coalescing has not been implemented
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
	void *ptr[9];
   ptr[0] = alloc(1);
   ptr[1] = (alloc(5));
   ptr[2] = (alloc(8));
   ptr[3] = (alloc(18));
   ptr[4] = (alloc(80));

   assert(ptr[0] != NULL);
   assert(ptr[1] != NULL);
   assert(ptr[2] != NULL);
   assert(ptr[3] != NULL);
   assert(ptr[4] != NULL);
   
   assert(free_block(ptr[1]) == 0);
   assert(free_block(ptr[0]) == 0);
   assert(free_block(ptr[3]) == 0);
   
   assert(alloc(13) < ptr[4]);
   assert(alloc(1) < ptr[1]);

   assert((ptr[5] = alloc(4)) < ptr[2]);
   assert((ptr[6] = alloc(200)) > ptr[4]);
   assert((ptr[7] = alloc(300)) > ptr[6]);
   assert((ptr[8] = alloc(400)) > ptr[7]);

   assert(free_block(ptr[8]) == 0);
   assert(free_block(ptr[6]) == 0);
   assert(free_block(ptr[7]) == 0);

   assert((ptr[8] = alloc(400)) > ptr[7]);

   exit(0);
}

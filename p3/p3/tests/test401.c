// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[4];

   ptr[0] = alloc(800);
   assert(ptr[0] != NULL);

   ptr[1] = alloc(800);
   assert(ptr[1] != NULL);

   ptr[2] = alloc(800);
   assert(ptr[2] != NULL);

   ptr[3] = alloc(800);
   assert(ptr[3] != NULL);

   while (alloc(800) != NULL) {
	// just allocate space don't need to save ptr
   }  ;

   assert(free_block(ptr[0]) == 0);
   assert(free_block(ptr[1]) == 0);

	// this fails unless immediate coalesce with prev is working
   assert((ptr[1] = alloc(1600)) != NULL);


   exit(0);
}

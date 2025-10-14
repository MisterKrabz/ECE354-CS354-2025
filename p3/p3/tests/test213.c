// a few allocations in multiples of 4 bytes followed by frees
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {

   assert(init_heap(4096) == 0);
   void* rest = alloc(3908);

   void* ptr[8];

   ptr[0] = alloc(8);
   ptr[1] = alloc(8);
   ptr[2] = alloc(8);
   ptr[3] = alloc(8);
   ptr[4] = alloc(16);
   ptr[5] = alloc(16);
   ptr[6] = alloc(24);
   ptr[7] = alloc(24);

   // this alloc should fail
   assert(alloc(40) == NULL);

   assert(free_block(ptr[4]) == 0);
   assert(free_block(ptr[5]) == 0);
   assert(free_block(ptr[6]) == 0);

   // now, there should be a block with room
   void* fits = alloc(20); 
   assert(fits != NULL);

   exit(0);
}

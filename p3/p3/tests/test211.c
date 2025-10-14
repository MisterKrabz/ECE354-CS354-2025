// a few allocations in multiples of 4 bytes followed by frees
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void* ptr[8];

   ptr[0] = alloc(4);
   ptr[1] = alloc(4);
   ptr[2] = alloc(8);
   ptr[3] = alloc(8);
   ptr[4] = alloc(16);
   ptr[5] = alloc(16);
   ptr[6] = alloc(24);
   ptr[7] = alloc(24);

   assert(free_block(ptr[0]) == 0);
   assert(free_block(ptr[3]) == 0);
   assert(free_block(ptr[5]) == 0);
   assert(free_block(ptr[6]) == 0);

   ptr[3] = alloc(8);
   assert(ptr[3] < ptr[4]);

   ptr[0] = alloc(4);
   assert(ptr[0] < ptr[1]);

   exit(0);
}

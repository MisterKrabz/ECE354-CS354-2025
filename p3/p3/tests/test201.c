// a few allocations in multiples of 4 bytes followed by frees
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void* ptr[4];

   ptr[0] = alloc(4);
   ptr[1] = alloc(8);
   assert(free_block(ptr[0]) == 0);
   assert(free_block(ptr[1]) == 0);

   ptr[2] = alloc(16);
   ptr[3] = alloc(4);
   assert(free_block(ptr[2]) == 0);
   assert(free_block(ptr[3]) == 0);

   exit(0);
}

// many odd sized allocations and interspersed frees
// tests pass if immediate coalescing has been implemented
#include <stdio.h>
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[9];
   ptr[0] = alloc(1);
   ptr[1] = (alloc(5));
   ptr[2] = (alloc(8));
   void *p3 = ptr[3] = (alloc(14));
   assert(ptr[0] != NULL);
   assert(ptr[1] != NULL);
   assert(ptr[2] != NULL);
   assert(ptr[3] != NULL);
   
   assert(free_block(ptr[1]) == 0);
   assert(free_block(ptr[0]) == 0);
   assert(free_block(ptr[3]) == 0);
   
   assert((ptr[3] = alloc(23)) == p3);

   ptr[4] = (alloc(1));
   ptr[5] = (alloc(4));
   assert(ptr[4] != NULL);
   assert(ptr[5] != NULL);
   assert(free_block(ptr[5]) == 0);
   
   ptr[6] = (alloc(9));
   assert(ptr[6] != NULL);
   assert(ptr[6]==ptr[5]); // bc freeing ptr[5] coalesced with remaining free space

   ptr[7] = (alloc(33));
   assert(ptr[7] != NULL);
   
   assert(free_block(ptr[4]) == 0); // no coalesce

   ptr[8] = (alloc(55));
   assert(ptr[8] != NULL);

   assert(free_block(ptr[2]) == 0); // coalesce with prev free block arnheap start
   assert(free_block(ptr[7]) == 0); // coalesce with next free block
   assert(free_block(ptr[6]) == 0); // coalese with next free block

   // should find a best fit for alloc(5) before ptr[8]
   assert((ptr[5]=alloc(5)) < ptr[8]); // ptr[5] should find first free block

   exit(0);
}

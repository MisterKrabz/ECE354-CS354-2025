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

   while (alloc(800) != NULL)
     ;

   assert(free_block(ptr[2]) == 0);
   ptr[2] = alloc(2400);
   assert(ptr[2] == NULL);   // alloc fails

   assert(free_block(ptr[1]) == 0);
   ptr[2] = alloc(2400);
   assert(ptr[2] == NULL);  // alloc fails
   ptr[2] = alloc(1600);
   assert(ptr[2] != NULL);  // alloc succeeds

   assert(free_block(ptr[2]) == 0);
   assert(free_block(ptr[3]) == 0);
   ptr[2] = alloc(2400);
   assert(ptr[2] != NULL);

   exit(0);
}

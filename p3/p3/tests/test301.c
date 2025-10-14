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
   ptr[2] = alloc(1600);
   assert(ptr[2] == NULL);  // should fail, not enough room yet

   assert(free_block(ptr[1]) == 0); 

   // this will work if immed coalesce with next is working
   ptr[1] = alloc(1600);
   assert(ptr[1] != NULL);

   exit(0);
}

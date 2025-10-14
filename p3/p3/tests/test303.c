// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   void * ptr[5];

   ptr[0] = alloc(500);
   assert(ptr[0] != NULL);

   ptr[1] = alloc(500);
   assert(ptr[1] != NULL);

   ptr[2] = alloc(500);
   assert(ptr[2] != NULL);

   ptr[3] = alloc(500);
   assert(ptr[3] != NULL);

   ptr[4] = alloc(500);
   assert(ptr[4] != NULL);

   while (alloc(500) != NULL)
     ;

   assert(free_block(ptr[1]) == 0);
   assert(free_block(ptr[3]) == 0);
   ptr[3] = alloc(1300);
   assert(ptr[3] == NULL);  // fails no adj to coalesco

   assert(free_block(ptr[2]) == 0);

   ptr[3] = alloc(1300);
   assert(ptr[3] != NULL);  // if immed coal, this alloc succeeds

   exit(0);
}

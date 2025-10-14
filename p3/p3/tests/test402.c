// check for coalesce free space
#include <assert.h>
#include <stdlib.h>
#include <stdio.h>
#include "p3Heap.h"

int main() {

   int size = 1020;

   assert(init_heap(4096) == 0);

   void * ptr[15];
   ptr[0] = alloc(size);

   int i=1;
   while ( ptr[i-1] != NULL ) {
	   ptr[i++] = alloc(size);
   }

   free_block(ptr[1]);
   ptr[1] = alloc(size*2);
   assert(ptr[1] == NULL);

   free_block(ptr[2]);
   ptr[1] = alloc(size*2);
   assert(ptr[1] != NULL);

   exit(0);
}

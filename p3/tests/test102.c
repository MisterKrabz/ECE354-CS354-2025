// a few allocations in multiples of 4 bytes
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   assert(alloc(4) != NULL);
   assert(alloc(8) != NULL);
   assert(alloc(16) != NULL);
   assert(alloc(24) != NULL);
   exit(0);
}

// many odd sized allocations
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   assert(alloc(1) != NULL);
   assert(alloc(5) != NULL);
   assert(alloc(14) != NULL);
   assert(alloc(8) != NULL);
   assert(alloc(1) != NULL);
   assert(alloc(4) != NULL);
   assert(alloc(55) != NULL);
   assert(alloc(9) != NULL);
   assert(alloc(33) != NULL);
   exit(0);
}

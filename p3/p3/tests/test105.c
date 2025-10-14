// second allocation is too big to fit
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
   assert(init_heap(4096) == 0);
   assert(alloc(2048) != NULL);
   assert(alloc(2047) == NULL);
   exit(0);
}

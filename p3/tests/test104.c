// allocation is too big to fit
#include <assert.h>
#include <stdlib.h>
#include "p3Heap.h"

int main() {
    assert(init_heap(4096)  == 0);
    assert(alloc(1)    != NULL);
    assert(alloc(4095) == NULL);
    exit(0);
}

// many odd sized allocations checked for alignment
#include <assert.h>
#include <stdlib.h>
#include <stdint.h>
#include "p3Heap.h"

int main() {
    assert(init_heap(4096) == 0);
    void* ptr[9];
    ptr[0] = alloc(1);
    ptr[1] = alloc(14);
    ptr[2] = alloc(33);
    ptr[3] = alloc(8);
    ptr[4] = alloc(1);
    ptr[5] = alloc(4);
    ptr[6] = alloc(5);
    ptr[7] = alloc(9);
    ptr[8] = alloc(55);
   
    for (int i = 0; i < 9; i++) {
        assert(ptr[i] != NULL);
    }

    for (int i = 0; i < 9; i++) {
        assert(((int)ptr[i]) % 8 == 0);
    }
    exit(0);
}

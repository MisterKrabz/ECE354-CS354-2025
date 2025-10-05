///////////////////////////////////////////////////////////////////////////////
// DO NOT EDIT or SUBMIT this file
// Copyright 2020-2025 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Shared with permission, CS354 FALL 2025, Hina Mahmood
///////////////////////////////////////////////////////////////////////////////

#ifndef __p3Heap_h
#define __p3Heap_h

int   init_heap(int sizeOfRegion);
void  disp_heap();

void* alloc(int size);
int   free_block(void *ptr);

void* malloc(size_t size) {
    return NULL;
}

#endif // __p3Heap_h__


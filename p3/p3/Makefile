# Create the shared object libheap.so file
# 1. Compile p3Heap.c to create p3Heap.o    (ROF)
# 2. Make it a shared object file for tests/ (SOF)
# 3. Then, cd to tests and run tests there
p3Heap: p3Heap.c p3Heap.h
	gcc -g -c -Wall -m32 -fpic p3Heap.c
	gcc -shared -Wall -m32 -o libheap.so p3Heap.o

clean:
	rm -rf p3Heap.o libheap.so

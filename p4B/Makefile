# Note: csim requires a 64-bit x86-64 system 
CC = gcc
CFLAGS = -Wall -std=gnu99 -m64 -g

# Note: -lm links the math library (libm). 
all: csim.c
	$(CC) $(CFLAGS) -o csim csim.c -lm 

# Remove existing executable to ensure it is rebuilt
clean:
	rm -f csim

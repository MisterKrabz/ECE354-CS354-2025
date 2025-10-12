////////////////////////////////////////////////////////////////////////////////
// Main File:        p3Heap.c
// This File:        p3Heap.c
// Other Files:      
// Semester:         CS 354 Lecture 01? Fall 2025
// Grade Group:      gg06  (Canvas course -> People -> click on your name to see your gg#)
// Instructor:       
// 
// Author:           Patrick Wang
// Email:            pwang384@wisc.edu
// CS Login:         patrickw
//
///////////////////////////  OPTIONAL WORK LOG  //////////////////////////////
//  Document your work sessions here or on your copy http://tiny.cc/cs354-work-log
//  Keep track of commands, structures, and code that you have learned.
//  This will help you focus your review on what is new to you from each program.
//  There is no need to submit work log, unless we ask you to do so.
//////////////////// REQUIRED -- OTHER SOURCES OF HELP ///////////////////////// 
// Persons:          Identify persons by name, relationship to you, and email.
//                   Describe in detail the ideas and help they provided.
//
// Online sources:   Avoid web searches to solve your problems, but if you do
//                   search, be sure to include Web URLs and description of 
//                   of any information you find.
// 
// AI chats:         Save a transcript and submit with your project.
//////////////////////////// 80 columns wide ///////////////////////////////////

/////////////////////////////////////////////////////////////////////////////
//
// Copyright 2020-2025 Deb Deppeler based on work by Jim Skrentny
// Posting or sharing this file is prohibited, including any changes.
// Used with permission, CS354 FALL 2025, Hina Mahmood
//
/////////////////////////////////////////////////////////////////////////////

#include <unistd.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/mman.h>
#include <fcntl.h>
#include <string.h>
#include "p3Heap.h"

/*
 * This structure serves as the header for each allocated and free block.
 * It also serves as the footer for each free block.
 */
typedef struct blockHeader {           

    /*
     * 1) The size of each heap block must be a multiple of 8
     * 2) Heap blocks have blockHeaders that contain size and status bits
     * 3) Free heap blocks contain a footer, but we can use the blockHeader 
     *
     * All heap blocks have a blockHeader with size and status
     * Free heap blocks have a blockHeader as its footer with size only
     *
     * Status is stored using the two least significant bits
     *   Bit0 => least significant bit, last bit
     *   Bit0 == 0 => free block
     *   Bit0 == 1 => allocated block
     *
     *   Bit1 => second last bit 
     *   Bit1 == 0 => previous block is free
     *   Bit1 == 1 => previous block is allocated
     * 
     * Start Heap: 
     *  The blockHeader for the first block of heap is after skipping 4 bytes.
     *  This ensures alignment requirements can be met.
     * 
     * End Mark: 
     *  The end of the available memory is indicated using a size_status of 1.
     * 
     * Examples:
     * 
     * 1. Allocated block of size 24 bytes:
     *    Allocated Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 25
     *      If the previous block is allocated p-bit=1 size_status would be 27
     * 
     * 2. Free block of size 24 bytes:
     *    Free Block Header:
     *      If the previous block is free      p-bit=0 size_status would be 24
     *      If the previous block is allocated p-bit=1 size_status would be 26
     *    Free Block Footer:
     *      size_status should be 24
     */
    int size_status;

} blockHeader;         

/* Global variable - DO NOT CHANGE NAME or TYPE. 
 * It must point to the first block in the heap and is set by init_heap()
 * i.e., the block at the lowest address.
 */
blockHeader *heap_start = NULL;     

/* Size of heap allocation padded to round to the nearest page size.
 */
int alloc_size;

/*
 * Additional global variables may be added as needed below
 * TODO: add global variables as needed by your function
 */




/* 
 * Function for allocating 'size' bytes of heap memory.
 * Argument size: requested size for the payload
 * Returns address of allocated block (payload) on success.
 * Returns NULL on failure.
 *
 * This function must:
 * - Check size - Return NULL if size < 1 
 * - Determine block size rounding up to a multiple of 8 
 *   and possibly add padding as a result.
 *
 * - Use BEST-FIT PLACEMENT POLICY to chose a free block
 *
 * - If the BEST-FIT block that is found is exact size match
 *   - 1. Update all heap blocks as needed for any affected blocks
 *   - 2. Return the address of the allocated block payload
 *
 * - If the BEST-FIT block that is found is large enough to split 
 *   - 1. SPLIT the free block into two valid heap blocks:
 *         1. an allocated block
 *         2. a free block
 *         NOTE: both blocks must meet heap block requirements 
 *       - Update all heap block header(s) and footer(s) 
 *              as needed for any affected blocks.
 *   - 2. Return the address of the allocated block payload
 *
 *   Return NULL if unable to find and allocate block of required size
 *
 * Note: payload address that is returned is NOT the address of the
 *       block header. It is the address of the start of the 
 *       available memory for the requester.
 *
 * Tips: Be careful with pointer arithmetic and scale factors.
 */
void* alloc(int size) {     
	//TODO: Your code goes in here.
	if(size <= 0){
		return NULL;
	}

	int required_size = sizeof(blockHeader) + size;
	if (required_size % 8 != 0) {
        	required_size += (8 - (required_size % 8));
    	}

	if(required_size < 8){
		required_size += (8 - (required_size % 8));
	}

	blockHeader *current = heap_start;
	blockHeader *best_fit = NULL;
	int best_fit_size = -1;

	// Traverse the heap to find the smallest free block that is large enough.
	while (current->size_status != 1) { // Stop at the end mark.
    		int current_block_size = current->size_status & ~3; // Mask out status bits to get size.
    		int is_allocated = current->size_status & 1;

    		// Block must be FREE and LARGE ENOUGH to satisfy the request.
    		if (!is_allocated && current_block_size >= required_size) {
        		// Perfect fit found. This is the best we can do, so stop searching.
       			if (current_block_size == required_size) {
            			best_fit = current;
            			best_fit_size = current_block_size;
            			break;
        		}
        		// Not a perfect fit, but potentially a better fit than what we've seen.
        		if (best_fit == NULL || current_block_size < best_fit_size) {
            			best_fit = current;
            			best_fit_size = current_block_size;
        		}
    		}
    		// Move to the next block in the heap.
    		current = (blockHeader *)((char *)current + current_block_size);
	}

	// no right sized free block was found
	if(best_fit == NULL){
		return NULL;
	}

	int remaining_size = best_fit_size - required_size;

	// allocate that best fit free block
	if (remaining_size >= 8){
		int original_p_bit = best_fit -> size_status & 2;

		// Setup the allocated block
        	best_fit->size_status = required_size | original_p_bit | 1;

        	// Setup the new free block that follows
        	blockHeader *new_free_block = (blockHeader *)((char *)best_fit + required_size);
        	// The previous block is now allocated, so p-bit is 1 (value 2)
        	new_free_block->size_status = remaining_size | 2;

        	// Setup the footer for the new free block
        	blockHeader *footer = (blockHeader *)((char *)new_free_block + remaining_size - sizeof(blockHeader));
        	footer->size_status = remaining_size;
	}
	// if it is a perfect fit
	else{
		best_fit->size_status = best_fit->size_status | 1;
		blockHeader *next_block = (blockHeader *)((char *)best_fit + best_fit_size);
        	if (next_block->size_status != 1) {
            		next_block->size_status = next_block->size_status | 2;
        	}
	}

	return (void *)((char *)best_fit + sizeof(blockHeader));
}

/* 
 * Function for freeing up a previously allocated block.
 * Argument ptr: address of the block to be freed up.
 * Returns 0 on success.
 * Returns -1 on failure.
 * This function should:
 * - Return -1 if ptr is NULL.
 * - Return -1 if ptr is not a multiple of 8.
 * - Return -1 if ptr is outside of the heap space.
 * - Return -1 if ptr block is already freed.
 * - Update header(s) and footer as needed.
 *
 * If free results in two or more adjacent free blocks,
 * they will be immediately coalesced into one larger free block.
 * so free blocks require a footer (blockHeader works) to store the size
 *
 * TIP: work on getting immediate coalescing to work after your code 
 *      can pass the tests in partA and partB of tests/ directory.
 *      Submit code that passes partA and partB to Canvas before continuing.
 */                    
int free_block(void *ptr) {    
    //TODO: Your code goes in here.
	if(ptr == NULL || (unsigned long int) ptr % 8 != 0){
		return -1;
	}

	// Calculate the header address from payload pointer 
	blockHeader *header = (blockHeader *)((char *)ptr - sizeof(blockHeader));
	void* heap_end = (void *)heap_start + alloc_size;
	
	// Return -1 if ptr block is already freed 
	if(!(header->size_status & 1)){
		return -1;
	}

	// get the block's size and p-bit status 
	int size = header->size_status & ~3;
	int is_prev_alloc = header -> size_status & 2;

	// Check the next block to see if its free for coalescing 
	blockHeader *next_header = (blockHeader *)((char *)header + size);
    if ((void*)next_header < heap_end && !(next_header->size_status & 1)) {
        // Next block is free, add its size to the current block's size.
        size += (next_header->size_status & ~3);
    }

	// Check the previous block to see if it's free for coalescing.
    if (!is_prev_alloc) {
        // Previous block is free. Find its header via its footer.
        blockHeader *prev_footer = (blockHeader *)((char *)header - sizeof(blockHeader));
        int prev_size = prev_footer->size_status;
        
        // New starting point for the coalesced block is the previous block's header.
        header = (blockHeader *)((char *)header - prev_size);
        size += prev_size;
    }

	// Set the header for the new, possibly coalesced, free block.
    // Preserve the p-bit of the block where the new free space starts.
    header->size_status = size | (header->size_status & 2);

    // Set the footer for the new free block.
    blockHeader *footer = (blockHeader *)((char *)header + size - sizeof(blockHeader));
    footer->size_status = size;

	// Update the p-bit of the block that now follows our new free block.
    next_header = (blockHeader *)((char *)header + size);
    if ((void*)next_header < heap_end) {
        // The new preceding block is free, so set its p-bit to 0.
        next_header->size_status &= ~2;
    }

    return 0;
} 


/* 
 * Initializes the memory allocator.
 * Called ONLY once by a program.
 * Argument sizeOfRegion: the size of the heap space to be allocated.
 * Returns 0 on success.
 * Returns -1 on failure.
 */                    
int init_heap(int sizeOfRegion) {    

    static int allocated_once = 0; //prevent multiple myInit calls

    int   pagesize; // page size
    int   padsize;  // size of padding when heap size is not a multiple of page size
    void* mmap_ptr; // pointer to memory mapped area
    int   fd;

    blockHeader* end_mark;

    if (0 != allocated_once) {
        fprintf(stderr, 
                "Error:mem.c: InitHeap has allocated space during a previous call\n");
        return -1;
    }

    if (sizeOfRegion <= 0) {
        fprintf(stderr, "Error:mem.c: Requested block size is not positive\n");
        return -1;
    }

    // Get the pagesize from O.S. 
    pagesize = getpagesize();

    // Calculate padsize, as padding is required to round up sizeOfRegion 
    // to a multiple of pagesize
    padsize = sizeOfRegion % pagesize;
    padsize = (pagesize - padsize) % pagesize;

    alloc_size = sizeOfRegion + padsize;

    // Using mmap to allocate memory
    fd = open("/dev/zero", O_RDWR);
    if (-1 == fd) {
        fprintf(stderr, "Error:mem.c: Cannot open /dev/zero\n");
        return -1;
    }
    mmap_ptr = mmap(NULL, alloc_size, PROT_READ | PROT_WRITE, MAP_PRIVATE, fd, 0);
    if (MAP_FAILED == mmap_ptr) {
        fprintf(stderr, "Error:mem.c: mmap cannot allocate space\n");
        allocated_once = 0;
        return -1;
    }

    allocated_once = 1;

    // for double word alignment and end mark
    alloc_size -= 8;

    // Initially there is only one big free block in the heap.
    // Skip first 4 bytes for double word alignment requirement.
    heap_start = (blockHeader*) mmap_ptr + 1;

    // Set the end mark
    end_mark = (blockHeader*)((void*)heap_start + alloc_size);
    end_mark->size_status = 1;

    // Set size in header
    heap_start->size_status = alloc_size;

    // Set p-bit as allocated in header
    // Note a-bit left at 0 for free
    heap_start->size_status += 2;

    // Set the footer
    blockHeader *footer = (blockHeader*) ((void*)heap_start + alloc_size - 4);
    footer->size_status = alloc_size;

    return 0;
} 

/* STUDENTS MAY EDIT THIS FUNCTION, but do not change function header.
 * TIP: Review this implementation to see one way to traverse through
 *      the blocks in the heap.
 *
 * Can be used for DEBUGGING to help you visualize your heap structure.
 * It traverses heap blocks and prints info about each block found.
 * 
 * Prints out a list of all the blocks including this information:
 * No.      : serial number of the block 
 * Status   : free/used (allocated)
 * Prev     : status of previous block free/used (allocated)
 * t_Begin  : address of the first byte in the block (where the header starts) 
 * t_End    : address of the last byte in the block 
 * t_Size   : size of the block as stored in the block header
 */                     
void disp_heap() {     

    int    counter;
    char   status[6];
    char   p_status[6];
    char * t_begin = NULL;
    char * t_end   = NULL;
    int    t_size;

    blockHeader *current = heap_start;
    counter = 1;

    int used_size =  0;
    int free_size =  0;
    int is_used   = -1;

    fprintf(stdout, 
            "********************************** HEAP: Block List ****************************\n");
    fprintf(stdout, "No.\tStatus\tPrev\tt_Begin\t\tt_End\t\tt_Size\n");
    fprintf(stdout, 
            "--------------------------------------------------------------------------------\n");

    while (current->size_status != 1) {
        t_begin = (char*)current;
        t_size = current->size_status;

        if (t_size & 1) {
            // LSB = 1 => used block
            strcpy(status, "alloc");
            is_used = 1;
            t_size = t_size - 1;
        } else {
            strcpy(status, "FREE ");
            is_used = 0;
        }

        if (t_size & 2) {
            strcpy(p_status, "alloc");
            t_size = t_size - 2;
        } else {
            strcpy(p_status, "FREE ");
        }

        if (is_used) 
            used_size += t_size;
        else 
            free_size += t_size;

        t_end = t_begin + t_size - 1;

        fprintf(stdout, "%d\t%s\t%s\t0x%08lx\t0x%08lx\t%4i\n", counter, status, 
                p_status, (unsigned long int)t_begin, (unsigned long int)t_end, t_size);

        current = (blockHeader*)((char*)current + t_size);
        counter = counter + 1;
    }

    fprintf(stdout, 
            "--------------------------------------------------------------------------------\n");
    fprintf(stdout, 
            "********************************************************************************\n");
    fprintf(stdout, "Total used size = %4d\n", used_size);
    fprintf(stdout, "Total free size = %4d\n", free_size);
    fprintf(stdout, "Total size      = %4d\n", used_size + free_size);
    fprintf(stdout, 
            "********************************************************************************\n");
    fflush(stdout);

    return;  
} 

//		p3Heap.c		END OF FILE			202509
                                       

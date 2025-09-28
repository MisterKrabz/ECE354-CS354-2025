////////////////////////////////////////////////////////////////////////////////
// Main File:        my_magic_square.c
// This File:        my_magic_square.c
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

///////////////////////////////////////////////////////////////////////////////
// Copyright 2020 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, CS354 FALL 2025, Hina Mahmood
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

// Structure that represents a magic square
typedef struct {
	int size;           // dimension of the square
	int **magic_square; // ptr to 2D heap array that stores magic square values
} MagicSquare;

/* TODO:
 * Prompts the user for magic square's size, read size, and
 * check if it is an odd number >= 3 
 * If not valid size, display the required error message and exit
 *
 * return the valid number
 */
int getSize() {
	int size = 0;
	printf("%s", "Enter the magic square's size (odd integer >=3)\n");      
	scanf("%i", &size);
    if(size%2 == 0) {
		printf("Magic square size must be odd.\n");
		exit(1);
	}
	if(size < 3){
		printf("Magic square size must be >= 3.\n");
		exit(1);
	}
	return size;
} 

/* TODO:
 * Creates a magic square of size n on the heap
 *
 * May use the Siamese magic square algorithm or alternative
 * algorithm that produces a valid magic square 
 *
 * n - the number of rows and columns
 *
 * returns a pointer to the completed MagicSquare struct
 */
MagicSquare *generateMagicSquare(int n) {
	// initializing the magic square
	MagicSquare *ms = malloc(sizeof(MagicSquare));
	if(ms == NULL) {
		printf("Error: failed to allocate memory for MagicSquare struct.\n");
		exit(1);
	 }
	ms -> size = n;

	// allocate array of row pointers
	ms -> magic_square = malloc(sizeof(int*)* n);
	if(ms->magic_square == NULL){
		printf("Error: failed to allocate memory for magic square rows.\n");
		free(ms);
		exit(1);
	}

	// allocate rows
	for(int i = 0; i < n; i++){
		*(ms -> magic_square + i) = malloc(sizeof(int)*n);
		if(*(ms->magic_square + i) == NULL){
			for(int j = 0; j < i; j++){
				free(*(ms->magic_square + j));
			}
			free(ms -> magic_square);
			free(ms);
			exit(1);
		}
	}

	// set everything to 0
	for (int i = 0; i < n; i++){
		for(int j = 0; j < n; j++){
			*(*(ms->magic_square + i)+j) = 0;
		}
	}

	// starting position of the magic square 
	int row = 0;
	int col = n/2;

	for(int num = 1; num <= n * n; num++){
		*(*(ms-> magic_square + row) + col) = num;

		int next_row = row - 1;
		int next_col = col + 1;
	
		if(next_row < 0){
			next_row = n - 1;
		}
		
		if(next_col == n){
			next_col = 0;
		}

		if(*(*(ms -> magic_square + next_row) + next_col) != 0){
			row ++;
			if(row == n){
				row = 0;
			}
		} else{
			row = next_row;
			col = next_col;
		}
	}
	return ms;
}

/* TODO:  
 * Open a new file (or overwrite the existing file)
 * and write magic square values to the file
 * in a format specified in the assignment.
 *
 * See assignment for required file format.
 *
 * magic_square - the magic square to write to a file
 * filename - the name of the output file
 */
void fileOutputMagicSquare(MagicSquare *magic_square, char *filename) {
	FILE *output = fopen(filename, "w");
	if(output == NULL){
		printf("cant open file");
		exit(1);
	}
	
	fprintf(output, "%i\n", magic_square -> size);
	for(int i = 0; i < magic_square -> size; i++){
		for(int j = 0; j < magic_square -> size; j++){
			int value = *(*(magic_square->magic_square + i) + j);

        		if (j < (magic_square->size - 1)) {
            			fprintf(output, "%d,", value);
        		} else {
            			fprintf(output, "%d", value);
        		}
		}
		fprintf(output, "\n");
	}
	fclose(output);
}


/* TODO:
 * Calls other functions to generate a magic square 
 * of the user-specified size and outputs the
 * created square to the output filename.
 * 
 * Add description of required CLAs here
 */
int main(int argc, char **argv) {
	// TODO: Check input arguments to get output filename
	if(argc != 2){
		printf("Usage: ./my_magic_square <output_filename>\n");
		exit(1);
	}

	// TODO: Get magic square's size from user
	int size = getSize();

	// TODO: Generate a magic square by correctly interpreting 
	//       the algorithm(s) in the write-up or by writing on your own.  
	//       You must confirm that your program produces a 
	//       valid Magic Square. See the provided Wikipedia page link for
    //       description.
	MagicSquare *M = generateMagicSquare(size);
		
	// TODO: Output the magic square
	fileOutputMagicSquare(M, argv[1]);
	
	for(int i = 0; i < size; i++){
		free(*(M-> magic_square + i));
	}
	free(M -> magic_square);
	free(M);
	M = NULL;
	return 0;
} 

// 202509

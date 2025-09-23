////////////////////////////////////////////////////////////////////////////////
// Main File:        sequence.c
// This File:        sequence.c
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

int main(int argc, char *argv[]){
	if(argc != 5){
		printf("Usage: ./sequence n x0 m c   ==> where next value in sequence is computed as x1 = m * x0 + c\nwhere: n is a non-zero positive number of values in the sequence,\nx0 is an integer and is the first value in the sequence,\nm is an integer and is used as a multiplier of the previous term in the sequence, \nc is an integer and is added to the (m*previous) term");
		return 1;
	}

	int n = atoi(*(argv + 1));
	int x0 = atoi(*(argv+2));
	int m = atoi(*(argv+3));
	int c = atoi(*(argv + 4));

	for(int i = 0; i < n; i++){
		printf("%i", x0);
		int x = m * x0 + c;
		x0 = x;
		
		if(1+i != n){
			printf(",");
		}
	}

	printf("\n");

	return 0;
}

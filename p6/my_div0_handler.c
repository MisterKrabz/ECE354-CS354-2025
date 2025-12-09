////////////////////////////////////////////////////////////////////////////////
// Main File:        my_div0_handler.c
// This File:        my_div0_handler.c
// Other Files:      send_signal.c
// Semester:         CS 354 Lecture 01? Fall 2025
// Grade Group:      gg06  (Canvas course -> People -> click on your name to see your gg#)
// Instructor:       Professor Mahmood 
//
// Author:           patrick wang
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

////////////////////////////////////////////////////////////////////////////////
// Copyright 2019 Jim Skrentny
// Posting or sharing this file is prohibited, including any changes/additions.
// Used by permission, Dr. Hina Mahmood, FALL 2025
////////////////////////////////////////////////////////////////////////////////

#include <stdio.h>
#include <stdlib.h>
#include <signal.h>
#include <string.h>

int success_count = 0;

void handle_sigfpe(int sig){
	printf("Error: a division by 0 operation was attempted.\n");
	printf("Total number of operations completed successfully: %d\n", success_count);
	printf("The program will be terminated.\n");
 	exit(0);
}

void handle_sigint(int sig){
	printf("\nTotal number of operations completed successfully: %d\n", success_count);
	printf("The program will be terminated.\n");
	exit(0);
}

int main(){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_handler = handle_sigfpe;
	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	if(sigaction(SIGFPE, &sa, NULL) != 0){
		perror("Error registering SIGFPE");
		exit(1);
	}

	sa.sa_handler = handle_sigint;
	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("Error registering SIGINT");
		exit(1);
	}

	char buffer[100];

	while(1){
		int int1 = 0;
		int int2 = 0;
		printf("Enter first integer: ");
		if(fgets(buffer, 100, stdin) == NULL){
			break;
		}
		int1 = atoi(buffer);

		printf("Enter second integer: ");
        	if (fgets(buffer, 100, stdin) == NULL){
			 break;
		}
        	int2 = atoi(buffer);

		int quotient = int1/int2;
		int remainder = int1 % int2;

		printf("%d / %d is %d with a remainder of %d\n", int1, int2, quotient, remainder);
		success_count++;
	}

	return 0;
}

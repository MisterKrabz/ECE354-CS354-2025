////////////////////////////////////////////////////////////////////////////////
// Main File:        send_signal.c
// This File:        send_signal.c
// Other Files:      my_div0_handler.c
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
#include <string.h>
#include <signal.h>
#include <unistd.h>
#include <sys/types.h>

int main(int argc, char *argv[]){
	if(argc != 3){
		printf("Usage: send_signal -u <pid> to send SIGUSR1\n");
		printf("       send_signal -i <pid> to send SIGINT\n");
		exit(1);
	}

	int pid = atoi(argv[2]);
	if(pid <= 0){
		fprintf(stderr, "Invalid pid.\n");
		exit(1);
	}
	int result = 0;

	if(strcmp(argv[1], "-u") == 0){
		result = kill(pid, SIGUSR1);
	} else if(strcmp(argv[1], "-i") == 0){
		result = kill(pid, SIGINT);
	} else{
		printf("Invalid flag. Use -u or -i.\n");
		exit(1);
	}

	if(result != 0){
		perror("Error sending signal");
		exit(1);
	}

	return 0;
}

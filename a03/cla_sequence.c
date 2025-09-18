////////////////////////////////////////////////////////////////////////////////
// Main File:        cla_sequence.c
// This File:        cla_sequence.c
// Other Files:      
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

#include <stdio.h>
#include <stdlib.h> 

int main(int argc, char *argv[]) {
	if(argc != 3 || atoi(argv[1]) > atoi(argv[2])){
		printf("%s", "Usage: cla_sequence start_integer end_integer where start is less than end \n"); 
		return 1;
	}

	for(int i = atoi(argv[1]); i <= atoi(argv[2]); i++) {
		printf("%i", i);
		if(i+1 <= atoi(argv[2])){
			printf("%c", ',');
		}else{
			printf("%c", '\n');
		}
	}
	return 0;
}

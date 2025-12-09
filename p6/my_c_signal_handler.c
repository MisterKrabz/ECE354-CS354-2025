////////////////////////////////////////////////////////////////////////////////
// Main File:        my_c_signal_handler.c
// This File:        my_c_signal_handler.c
// Other Files:      send_signal.c my_div0_handler.c
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
#include <unistd.h>
#include <signal.h>
#include <time.h>
#include <string.h>

int alarm_seconds = 3;
int sigusr1_count = 0;

void handle_signalrm(int sig) {
	time_t current_time;

	if(time(&current_time) == (time_t) - 1){
		perror("error getting time");
		exit(1);
	}

	char *time_string = ctime(&current_time);

	if(time_string == NULL){
		perror("error converting time");
		exit(1);
	}

	printf("PID: %d CURRENT TIME: %s", getpid(), time_string);

	alarm(alarm_seconds);
}

void handle_sigusr1(int sig){
	printf("Received SIGUSR1, user signal 1 counted.\n");
	sigusr1_count++;
}

void handle_sigint(int sig){
	printf("\nSIGINT handled.\n");
	printf("SIGUSR1 was handled %d times. Exiting now.\n", sigusr1_count);
	exit(0);
}

int main (){
	struct sigaction sa;
	memset(&sa, 0, sizeof(sa));

	sa.sa_flags = SA_RESTART;
	sigemptyset(&sa.sa_mask);

	sa.sa_handler = handle_signalrm;
	if(sigaction(SIGALRM, &sa, NULL) != 0){
		perror("Error registering SIGALRM");
		exit(1);
	}

	sa.sa_handler = handle_sigusr1;
	if(sigaction(SIGUSR1, &sa, NULL) != 0){
		perror("Error registering SIGUSR1");
		exit(1);
	}

	sa.sa_handler = handle_sigint;
	if(sigaction(SIGINT, &sa, NULL) != 0){
		perror("Error registering SIGINT");
		exit(1);
	}

	printf("PID and current time: prints every 3 seconds.\n");
	printf("Type Ctrl-C to end the program.\n");

	alarm(alarm_seconds);

	while(1){

	}

	return 0;
}

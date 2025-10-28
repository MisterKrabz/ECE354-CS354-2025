////////////////////////////////////////////////////////////////////////////////
// Main File:        cache1D.c
// This File:        cache1D.c
// Other Files:
// Semester:         CS 354 Lecture 01? Fall 2025
// Grade Group:      gg06  (Canvas course -> People -> click on your name to see your gg#)
// Instructor:       Hina Mahmood
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
//
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

// Declare a global array of 100,000 integers
int arr[100000];

int main(){
	for(int i = 0; i < 100000; i++){
		arr[i] = i;
	}
	return 0;
}

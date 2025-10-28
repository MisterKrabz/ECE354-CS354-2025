////////////////////////////////////////////////////////////////////////////////
// Main File:        cache1D.c
// This File:        cache2Dclash.c
// Other Files:
// Semester:         CS 354 Lecture 01? Fall 2025
// Grade Group:      gg06  (Canvas course -> People -> click on your name to se>
// Instructor:       Hina Mahmood
//
// Author:           Patrick Wang
// Email:            pwang384@wisc.edu
// CS Login:         patrickw
//
///////////////////////////  OPTIONAL WORK LOG  //////////////////////////////
//  Document your work sessions here or on your copy http://tiny.cc/cs354-work->
//  Keep track of commands, structures, and code that you have learned.
//  This will help you focus your review on what is new to you from each progra>
//  There is no need to submit work log, unless we ask you to do so.
// 
//////////////////// REQUIRED -- OTHER SOURCES OF HELP ////////////////////////>
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

// has a two-dimensional global array of integers having dimensions 
// 128 rows x 8 columns
int arr2D[128][8];

int main(){
	for(int iteration = 0; iteration < 100; iteration ++){
		for(int row = 0; row < 128; row+=64){
			for(int col = 0; col < 8; col++){
				arr2D[row][col] = iteration + row + col;
			}
		}
	}
	return 0;
}

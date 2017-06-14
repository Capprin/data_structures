//========================================================
//
//  File Name:   main.cpp
//
//  Author: Christopher Painter-Wakefield 
//			Mark Baldwin
//
//  Course and Assignment:   CSCI262 Assignment 2 Maze Solver
//
//  Description:  This program reads and solves various mazes
//
//
//=========================================================

//----- Includes and Namesapce ----------

#include <iostream>
#include <string>

#include "maze_solver.h"

using namespace std;

//----------------------------------------------------------------------
//
// Name:  main()
//
// Description: Driver for Maze solver
//
// Inputs:
//	arg1 - maze filename
//	arg2 - S or Q (stack/queue)
//	arg3 - 'false' - circumvent pause
//
// Outputs:
//    returns 0
//
// Assumptions:
//    none
//
//----------------------------------------------------------------------
// You should not modify any of this code.  Changing it may cause
// difficulty for the grader.  Touch at your own risk!
int main(int argc, char* argv[]) {
	string infile;
	string s_or_q;
	bool do_pause = true;
	bool use_stack = true;

	// Check for command line arguments for maze filename and stack/queue
	// selection.  An optional third argument lets the grader circumvent
	// the pause between UI refreshes for automated testing purposes.
	if (argc >= 3) {
		infile = argv[1];
		s_or_q = argv[2];
		if (argc == 4 && string(argv[3]) == "false") do_pause = false;
	}
	else {
		cout << "Please enter a maze filename: ";
		getline(cin, infile);
		cout << "Please enter (S) to use a stack, or (Q) to use a queue: ";
		getline(cin, s_or_q);
	}

	if (toupper(s_or_q[0]) == 'Q') use_stack = false;

	// create the maze_solver object and run it with the user inputs
	maze_solver solver(infile, use_stack, do_pause);
	solver.initialize();
	solver.run();

	return 0;
} // end main


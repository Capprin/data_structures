//========================================================
//
//  File Name:   maze_solver.cpp
//
//  Author: Christopher Painter-Wakefield 
//			Mark Baldwin
//			Capprin Bass
//
//  Course and Assignment:   CSCI262 Assignment 2 Maze Solver
//
//  Description:   This code for the maze_solver class.  
//  This class will use stack-based depth first search or 
//  queue-based breadth first search to find a solution (if
//  possible) to a simple maze.
//
//=========================================================

#include "maze_solver.h"

#include <iostream>
#include <fstream>
#include <string>
#include <cstdlib>

using namespace std;

// TODO: read the complete assignment instructions before beginning.  Also look
// at maze_solver.h - you will need to modify it as well.  In this file you
// will need to complete three methods, and add any others as needed for your
// solution. 

// initialize()
// Find the start and goal points.  Push or enqueue the start point.  Set
// the boolean no_more_steps and goal_reached flags to false.
void maze_solver::initialize() {

	// Finds the location of the start and end points in the maze
	for (int r = 0; r < rows; r++) {
		for (int c = 0; c < columns; c++) {
			if (maze[r][c] == 'o') {
				startPos.row = r;
				startPos.col = c;
				if (endPos.set) break; //Breaks if the end position is already set
				startPos.set = true;
			}
			if (maze[r][c] == '*') {
				endPos.row = r;
				endPos.col = c;
				if (startPos.set) break; //Breaks if the start position is already set
				endPos.set = true;
			}
		}
		if (startPos.set && endPos.set) break; //Breaks if both are set; this way you don't waste time with unnecessary looping
	}

	push(startPos);

	no_more_steps = false;
	goal_reached = false;
}

// write_maze()
// Output the (partially or totally solved) maze on the provided output stream.
void maze_solver::write_maze(ostream& out) {
	for (int r = 0; r < rows; r++) {
		out << maze[r] << endl;
	}

}

// step()
// Take one step towards solving the maze, setting no_more_steps and 
// goal_reached as appropriate.  This implements the essential maze search
// algorithm; 
//
// Notes:
//
// - Your initial point should have been pushed/enqueued in the initialize()
//   method.  You should set the no_more_steps variable to true when there
//   are no more points in the stack/queue.  The run() method will not call step() once
//   no_more_steps is true.
//
// - You should write an '@' over every location you have tested,
//
// - Make sure you follow the order given in the assignment instructions for
//   adding points to your data structure - up, right, down, left - or your
//   final maze solution won't match the required solution.  Check against the
//   sample solutions provided.
void maze_solver::step() {
	point current_point = pop();

	point test_point;
	// Indexes through each of the four adjacent points
	for (int i = 1; i > -3; i--) { 
		// This is cool - uses sine and cosine to offset the current point by the right amount ea. time - this way I don't have a bunch of repeated code
		test_point.row = current_point.row - sin(PI*i / 2);
		test_point.col = current_point.col + cos(PI*i / 2);

		//If this point is in the bounds, then...
		if (test_point.row > 0 && test_point.row < rows) {
			if (test_point.col > 0 && test_point.col < columns) {
				char tmp = maze[test_point.row][test_point.col];
				if (tmp == '*') { //If the goal has been reached
					goal_reached = true;
					no_more_steps = true;
					return;
				}
				else if (tmp == '.') { //If you're at a normal point, replace your old one with an @ and push the new point to the stack/queue
					maze[test_point.row][test_point.col] = '@';
					push(test_point);
				}
			}
		}
	}

	if (empty()) no_more_steps = true;
}

// Pushes point to stack or queue depending on which data structure is in use
void maze_solver::push(point in) {
	if (use_stack) movementStack.push(in);
	else movementQueue.push(in);

}

// Pops point from stack or queue depending on which data structure is in use
// Removes, then pops, then returns removed value
point maze_solver::pop() {
	point ret;
	if (use_stack) {
		ret = movementStack.top();
		movementStack.pop();
	}
	else {
		ret = movementQueue.front();
		movementQueue.pop();
	}
	return ret;


}

// Checks to see if stack or queue is empty
bool maze_solver::empty() {
	if (use_stack) return movementStack.empty();
	return movementQueue.empty();
}


/***************************************************************************
    You should not need to modify code below this point.  Touch at your own
    risk!
****************************************************************************/

//------------------------------------------------------------------------
// Name:  maze_solver::maze_solver()
//
// Description: Default class constructor
//
// Arguments: 
//	string - file to be loaded
//	bool - Use a stack if true
//	bool - pause output
//
// Modifies: initializes class data
// 
// Returns: none
//
//--------------------------------------------------------------------
// Here's the constructor code.  You should not need to modify this, but you
// can if you want.  Right now it takes care of reading in the maze for you.
// The maze is stored as a Vector<string>, but you can change that if you wish.
maze_solver::maze_solver(string infile, bool use_stak, bool pause) {
	use_stack = use_stak;
	do_pause = pause;

	// parse out maze name for later use in creating output file name
	int pos = infile.find(".");
	if (pos == string::npos) {
		maze_name = infile;
	} else {
		maze_name = infile.substr(0, pos);
	}

	// open input file and read in maze
	ifstream fin(infile);
	if (!fin) {
		cerr << "Error opening input file \"" << infile << "\"; exiting." << endl;
		cin.get() ;
		exit(1);
	}

	fin >> rows >> columns;

	string row;
	getline(fin, row);
	for (int i = 0; i < rows; i++) {
		getline(fin, row);
		maze.push_back(row);
	}
	
	fin.close();
}

//------------------------------------------------------------------------
// Name:  maze_solver::run()
//
// Description: Drives the solution forward.
// While more steps are possible, run repeatedly calls step, then write_maze
// (on cout), then pause.Once there are no more steps, it prints a success /
// failure message to the user and writes the final maze to a solution file.
//
// Arguments: none
// 
// Returns: none
//
//--------------------------------------------------------------------
void maze_solver::run() {
	cout << "Solving maze '" << maze_name << "'." << endl;
	cout << "Initial maze: " << endl << endl;
	write_maze(cout);
	cout << endl;
	pause();

	// main loop
	while (!no_more_steps) {
		step();
		cout << endl;
		write_maze(cout);
		cout << endl;
		pause();
	}

	// final output to user
	cout << "Finished: ";
	if (goal_reached) {
		cout << "goal reached!" << endl;
	} else {
		cout << "no solution possible!" << endl;
	}

	// save solution file
	string outfile;
	if (use_stack) outfile = maze_name + "-stack-solution.txt";
	else outfile = maze_name + "-queue-solution.txt";
	
	ofstream fout(outfile);
	if (!fout) {
		cerr << "Could not open file \"" << outfile << "\" for writing." << endl;
		cerr << "Solution file could not be saved!" << endl;
		cin.get();
	}
	else {
		write_maze(fout);
		fout.close();
	}
	cin.get();
}  // end run

//------------------------------------------------------------------------
// Name:  maze_solver::pause()
//
// Description: If do_pause is set, pauses the output
//
// Arguments: none
// 
// Returns: none
//
//--------------------------------------------------------------------
void maze_solver::pause() {
	if (!do_pause) return;
	string foo;
	cout << "Hit Enter to continue...";
	getline(cin, foo);
} // end pause


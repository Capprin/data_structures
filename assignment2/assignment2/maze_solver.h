//========================================================
//
//  File Name:   maze_solver.h
//
//  Author: Christopher Painter-Wakefield 
//			Mark Baldwin
//			Capprin Bass
//
//  Course and Assignment:   CSCI262 Assignment 2 Maze Solver
//
//  Description:  Header for the maze_solver object
//
//=========================================================

#ifndef _MAZE_SOLVER_H
#define _MAZE_SOLVER_H

#define PI 3.14159265358979323846

#include <iostream>

// The provided code uses a Vector<string> to store the maze.
// You can change this if you wish.
// USING STD LIBRARY
#include <vector>

#include <stack>
#include <queue>

#include<math.h>

// Here is a Stanford library object that might make things a lot easier.   
//#include "point.h"

using namespace std;

// TODO: make sure you read all of the assignment instructions before you
// begin.  You need to modify/create the following methods of this class:
//    initialize()
//    step() 
//    write_maze()
// You will also need to add instance variables for your stack and queue 
// objects.  You may also add other instance variables or methods as needed 
// to effectively complete the task.

//Stores row,col information
struct point {
	int row;
	int col;
	bool set = false;
};

//----------------------------------------------------------------------
//
// Object maze_solver
//
// Description: Class to hold and manipulate a maze
//
//
//----------------------------------------------------------------------
class maze_solver {
public:
	// constructor
	maze_solver(string infile, bool use_stak, bool pause=false);

	// public methods
	void initialize();
	void run();
	// TODO: your own public methods or variables here?

private:	
	void step();
	void write_maze(ostream& out);
	void pause();

	//These universalize the accessing methods so I don't have to check use_stack every time
	void push(point in);
	point pop();
	bool empty();
	
	// instance variables
	string maze_name;
	bool use_stack;
	bool do_pause;

	int rows, columns;
	vector<string> maze;

	bool no_more_steps;
	bool goal_reached;
	
	// my variables
	point startPos;
	point endPos;

	stack<point> movementStack;
	queue<point> movementQueue;

	
};



#endif

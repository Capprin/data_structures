#pragma once
//========================================================
//
//  File Name:  animal.h
//
//  Author:  Mark Baldwin
//
//  Course and Assignment:  CSCI262 Assignment 6 Animal
//
//  Description:  This is the header file for animal object
//    It also includes the binary tree template
//
//=========================================================
#include <string>
#include <queue>
#include <iostream>
#include <fstream>

using namespace std;

//----------------------------------------------------------------------
//
// Template: binary_tree_node
//
// Description: template class to define a binary tree node
//         see lecture slides on structure
//
//----------------------------------------------------------------------
template <class T>
class binary_tree_node {
public:
	binary_tree_node() { left = NULL; right = NULL; }
	T data;
	binary_tree_node<T>* left;
	binary_tree_node<T>* right;
};

//----------------------------------------------------------------------
//
// Object animal_game
//
// Description: Class to hold and manipulate an animal game
//
//----------------------------------------------------------------------
class animal_game {
public:
	animal_game();				// constructor
	~animal_game();				// destructor
	bool load_game();		// loads the game tree, returns true if successful
	void play_game();			// plays a game
	bool save_game();		// saves the game tree, returns true if successful

private:
	// IMPORTANT NOTE:  The below data and methods were ones I found convienient for the problem.   However, 
	// there are dozens of ways to internally manage the problem that are equally good.   I'm including these
	// not to say that you should use them, but instead to let you think about some of the internals.

	string _data_file;			// contains the name of the current data file
	binary_tree_node<string>* _root; // pointer to the root node
	binary_tree_node<string>* _end_node;  // pointer to last node processed in playing game
	queue<string> _ques;  // vector containing a history of questions and answer as game is played (you may not want to do it this way)

	void read_preorder(binary_tree_node<string>* tree, ifstream &fin);	// recursive call to read data file
	void play_game_tree(binary_tree_node<string>* tree); // recursive call to walk through tree when playing game
	void write_preorder(binary_tree_node<string>* tree, ofstream &fout); // recursive call to write out the data file
	void delete_game_tree(binary_tree_node<string>* tree);  // recursive call to release memory
};
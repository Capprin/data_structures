//========================================================
//
//  File Name:  main.cpp
//
//  Author:  Mark Baldwin
//
//  Course and Assignment:  CSCI262 Assignment 6 Animal
//
//  Description:  This program plays guess the animal
//
//=========================================================

//----- Includes and Namespace ----------

#include <cstdlib>
#include "animal.h"

using namespace std;

//----------------------------------------------------------------------
//
// Name:  main()
//
// Description: CSCI262 Assignment 6 Animal main driver
//
// Inputs:
//    none
//
// Outputs:
//    returns 0 or -1
//
// Assumptions:
//    none
//
//----------------------------------------------------------------------
int main() {
	animal_game game;   // create the game object
	
	// read in the game tree
	if (game.load_game() == false) {
		cout << "ERROR: Unable to load the game tree." << endl;
		cin.get();
		return -1;
	}

	cout << "*************************" << endl;
	cout << "*                       *" << endl;
	cout << "*         ANIMAL        *" << endl;
	cout << "*                       *" << endl;
	cout << "*************************" << endl;

	// gameplay loop
	int choice;
	do {
		string tmp;

		cout << "Options" << endl;
		cout << "  1) Play the game" << endl;
		cout << "  2) Save the game" << endl;
		cout << "  3) Quit" << endl;
		cout << "Please make your selection: ";

		getline(cin, tmp);
		choice = atoi(tmp.c_str());

		switch (choice) {
		case 1:
			// play a game
			game.play_game();
			break;
		case 2:
			// save a game tree
			if (game.save_game() == false) {
				cout << "ERROR: Game tree save failed!" << endl;
			}
			break;
		case 3:
			break;
		default:
			cout << "Sorry, I don't understand." << endl << endl;
		}
	} while (choice != 3);

	// Note, the destructor for animal_game needs to clean up the memory.

	return 0;
}



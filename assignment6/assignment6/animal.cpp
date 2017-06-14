//========================================================
//
//  File Name:  animal.cpp
//
//  Author:  Capprin Bass
//
//  Course and Assignment:  CSCI262 Assignment 6 Animal
//
//  Description:  Contains all implementation for animal_game object
//
//=========================================================

#include "animal.h"

//Constructs object
animal_game::animal_game() {
	_root = new binary_tree_node<string>;
}

//Destructs object, releases all allocated memory
animal_game::~animal_game() {
	delete_game_tree(_root);
}

//Opens input file and reads preordered tree
bool animal_game::load_game() {
	cout << "Enter a filename to open or press ENTER to open animal.txt" << endl;
	string resp;
	getline(cin, resp);

	ifstream input;
	if (resp.length() == 0) input.open("animal.txt");
	else input.open(resp);

	if (!input.is_open()) return false;

	read_preorder(_root, input);

	input.close();
}

//Traverses the tree according to user preferences
void animal_game::play_game() {
	_ques = queue<string>(); //Empty queue on new play

	play_game_tree(_root);
	string tmp;
	getline(cin, tmp);

	char last_response = _ques.back().back();
	if (last_response == 'y' || last_response == 'Y') {
		cout << "I WIN!" << endl << endl;
	}
	else {
		cout << "I DON'T KNOW!" << endl << endl;

		cout << "Do you want to extend the game tree? [y/n]: ";
		string response;
		cin >> response;
		cout << endl;

		if (response != "n" && response != "N") {
			cout << "I asked the following:" << endl;
			while (!_ques.empty()) {
				cout << _ques.front() << endl;
				_ques.pop();
			}

			cout << "Enter your animal in the form of a question; e.g. \"Is it an octopus?\": ";
			string animal;
			getline(cin, tmp);
			getline(cin, animal);

			cout << "Now enter a question for which the answer is 'yes' for your new animal, and which does not contradict your previous answers : ";
			string question;
			getline(cin, question);

			string old_data = _end_node->data;
			_end_node->data = question;

			_end_node->left = new binary_tree_node<string>;
			_end_node->right = new binary_tree_node<string>;
			_end_node->left->data = animal;
			_end_node->right->data = old_data;

			cout << "Tree extended." << endl;
		}
	}
}

//Write tree to file in pre-order fashion
bool animal_game::save_game() {
	cout << "Enter a filename to save to or press ENTER to save to animal.txt" << endl;
	string resp;
	getline(cin, resp);

	ofstream output;
	if (resp.length() == 0) output.open("animal.txt");
	else output.open(resp);

	if (!output.is_open()) return false;

	write_preorder(_root, output);

	output.close();
}

//Recursively adds elements to tree from file in preorder
void animal_game::read_preorder(binary_tree_node<string>* tree, ifstream &fin) {
	string type;
	fin >> type;

	fin.ignore();

	string question;
	getline(fin, question);
	tree->data = question;

	if (type == "#Q") {
		tree->left = new binary_tree_node<string>;
		tree->right = new binary_tree_node<string>;
		read_preorder(tree->left, fin);
		read_preorder(tree->right, fin);
	}
}

//Recursively plays game based on user response
void animal_game::play_game_tree(binary_tree_node<string>*tree) {
	cout << tree->data << " [y/n]: ";
	string response;
	cin >> response;

	_ques.push(tree->data + " " + response);

	if (tree->left == NULL) {
		_end_node = tree;
		return;
	}
	if (response == "y" || response == "Y") {
		play_game_tree(tree->left);
	}
	else if (response == "n" || response == "N") {
		play_game_tree(tree->right);
	}
	else {
		cout << response << " is an invalid response. Defaulting to YES..." << endl;
		play_game_tree(tree->left);
	}
}

//Recursively traverses tree and writes to file in preorder
void animal_game::write_preorder(binary_tree_node<string>* tree, ofstream &fout) {
	if (tree->left == NULL) fout << "#A " << tree->data << endl;
	else {
		fout << "#Q " << tree->data << endl;
		write_preorder(tree->left, fout);
		write_preorder(tree->right, fout);
	}
}

//Traverses the tree and deletes all nodes (freeing memory)
void animal_game::delete_game_tree(binary_tree_node<string>* tree) {
	if (tree->left != NULL) {
		delete_game_tree(tree->left);
		delete_game_tree(tree->right);
	}
	delete tree;
}
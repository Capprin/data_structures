/////////////////////////////////////////////////////////////////////////////////////
//Author: Capprin Bass                                                             //
//                                                                                 //
//Assignment: Evil Hangman                                                         //
//                                                                                 //
//Description: Hangman program that cheats!                                        //
/////////////////////////////////////////////////////////////////////////////////////


#include <iostream>
#include <string>
#include <fstream>
#include <map>
#include <vector>
#include <queue>
#include <exception>

using namespace std;

int main() {

	cout << "Loading...." << endl;

	//Open file
	ifstream input_file("dictionary.txt");
	if (input_file.fail()) {
		cout << "Could not open dictionary.txt; Press any key to exit.";
		cin.get();
		return -1;
	}

	//Fill words map
	map<int, vector<string>> words;
	string str;
	while (!input_file.eof()) {
		input_file >> str;
		words[str.size()].push_back(str);
	}

	//Game loop
	while (true) {

		//Get the desired word length
		int len;
		while (true) {
			cout << "Enter a word length: ";
			cin >> len;
			cout << endl;

			try {
				words.at(len);
				break;
			}
			catch (exception& e) {
				cout << "Please enter a valid word length." << endl;
			}
		}

		//Get the desired number of guesses
		int guesses;
		while (true) {
			cout << "Enter a maximum number of guesses: ";
			cin >> guesses;
			cout << endl;

			if (guesses < 1) cout << "Please enter a valid number of guesses." << endl;
			else break;
		}

		//Get whether to use debug
		bool debug = false;
		string tmp;
		cout << "Do you want to use debug mode? [y/n]: ";
		cin >> tmp;
		if (tmp == "y") debug = true;

		//Set up word list
		queue<string> word_list;
		vector<string> words_vector = words[len];
		for (string s : words_vector) {
			word_list.push(s);
		}

		//Set up current word
		string current_word = "";
		for (int i = 0; i < len; i++) current_word += '-';

		//Game loop
		vector<char> guessed_letters; //Letters must be uppercase
		for (int g = guesses; g > 0; g--) {

			cout << "You have " << g << " guesses remaining." << endl;
			cout << "The current word is " << current_word << "." << endl;

			cout << "You have guessed the following letters so far: ";
			for (char c : guessed_letters) {
				cout << c << ' ';
			}
			cout << endl;

			if (debug) cout << "There are " << word_list.size() << " words remaining in the list." << endl << endl;

			//Letter entry
			char letter;
			bool quit = false;
			while (!quit) {
				cout << "Guess a letter: ";
				cin >> str;
				cout << endl;
				
				quit = true;

				//Ensure char
				if (str.length() != 1) {
					cout << "Please enter a single letter character." << endl;
					quit = false;
				}
				letter = str[0];

				//Check range
				if ((letter > 90 && letter < 97) || letter < 65 || letter > 122) {
					cout << "Please enter a valid letter character." << endl;
					quit = false;
				}
				if (letter > 96 && letter < 123) letter -= 32; //Make uppercase if not

				//Check to see if letter has already been guessed
				for (char c : guessed_letters) {
					if (c == letter) {
						cout << "Please enter a letter you have not already." << endl;
						quit = false;
						break;
					}
				}

				
			}
			guessed_letters.push_back(letter);

			//Populate word families
			map<string, vector<string>> families;
			while (!word_list.empty()) {
				string s = word_list.front();
				string key = "";
				for (char c : s) {
					if (c - 32 == letter) key += letter;
					else key += '-';
				}
				families[key].push_back(s);

				word_list.pop();
			}

			//Choose between the word families
			string key = "";
			int max = 0;
			for (const auto& pair : families) {
				if (pair.second.size() > max) {
					key = pair.first;
					max = pair.second.size();
				}
			}
			//If they guessed correctly, update current word
			if (key.compare(current_word) != 0) {
				for (int i = 0; i < current_word.length(); i++) {
					if (current_word[i] == '-' && key[i] != current_word[i]) current_word[i] = key[i];
				}
				g++;
			}

			//Update the word list
			for (string s : families[key]) {
				word_list.push(s);
			}

			//Winning
			for (int i = 0; i < current_word.length(); i++) {
				if (current_word[i] == '-') break;
				if (i == current_word.length() - 1) {
					cout << "You won!" << endl;
					g = 0;
				}
			}

		}

		cout << "Would you like to play again? [y/n]: ";
		cin >> str;
		if (str != "y") break;

		cout << endl << endl;
	}

	return 0;
}
/*
CSCI 262 Data Structures, Spring 2017, Project 4 - Markov

map_model.cpp

Method implementation for map-based markov implementation

Author: Capprin Bass

*/

#include "map_model.h"

//Sets up seed map for later use in passage generation
void map_model::initialize(std::string text, int order) {
	if (text[text.length() - 1] == ' ') text = text.substr(0, text.length() - 1); //Random space character, needs removal sometimes
	_data = text + text.substr(0, order); //Concatenates front to back; allows for rollover
	_order = order;

	//Initialize the map
	for (int i = 0; i < _data.length() - _order; i++) {
		std::string gram = _data.substr(i, _order); //Get current gram

		if (_grams.containsKey(gram)) {
			_grams[gram].push_back(_data[i + _order]); //Add next character to map if this gram exists
		}
		else {
			_grams.put(gram, Vector<char>(1, _data[i + _order])); //Add new character vector to map if the gram doesn't exist yet
		}
	}

}

//Generate <size> characters based on the seed map
std::string map_model::generate(int size) {
	int start = rand() % (_data.length() - _order); //Start at a random location
	std::string seed = _data.substr(start, _order); //Get a seed of the correct size from that location

	std::string ret;
	ret.reserve(size); //Pre-allocate the space we need

	for (int i = 0; i < size; i++) {
		char next =  _grams[seed][rand() % _grams[seed].size()]; //Randomly get the next char from the corresponding location in the map
		ret.push_back(next);
		seed = seed.substr(1) + next; //Advance the seed
	}

	return ret;
}
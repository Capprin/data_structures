/*
CSCI 262 Data Structures, Spring 2017, Project 4 - Markov

word_model.cpp

Method implementation for word-based markov implementation

Author: Capprin Bass

*/

#include "word_model.h"

//Splits a string into a vector based on a delimiter
Vector<std::string> word_model::delimit(std::string input, char delimiter) {
	std::string tmp = "";
	input += delimiter; //Add to end so you don't skip the last part of the string
	Vector<std::string> ret;
	for (char c : input) {
		if (c == delimiter && tmp != "") {
			ret.add(tmp);
			tmp = "";
		}
		else tmp += c;
	}

	return ret;
}

//Concatenates a vector into a string, separated by a delimiter
std::string word_model::concat(Vector<std::string> input, char delimiter) {
	std::string ret = "";
	for (std::string s : input) {
		ret += s;
		ret += delimiter;
	}
	ret = ret.substr(0, ret.length() - 1); //Remove final delimiter from the end of the string

	return ret;
}

//Sets up seed map for later use in passage generation
//Functionality mostly the same as map_model, but using Vector<std::string> instead of string, and std::string instead of char
void word_model::initialize(std::string text, int order) {
	_order = order;
	_data = delimit(text);
	for (int i = 0; i < _order; i++) {
		_data.add(_data[i]);
	}

	//Initialize the map
	for (int i = 0; i < _data.size() - _order; i++) {
		Vector<std::string> tmp;
		for (int j = i; j < i + _order; j++) {
			tmp.add(_data[j]);
		}
		std::string gram = concat(tmp);

		if (_grams.containsKey(gram)) {
			_grams[gram].add(_data[_order + i]);
		}
		else {
			_grams.put(gram, Vector<std::string>(1,_data[_order + i]));
		}

	}

}

//Generate <size> words based on the seed map
std::string word_model::generate(int size) {
	int start = rand() % (_data.size() - _order);
	Vector<std::string> seed;
	for (int i = start; i < start + _order; i++) {
		seed.add(_data[i]);
	}

	std::string ret;

	for (int i = 0; i < size; i++) {
		std::string key = concat(seed);
		std::string next = _grams[key][rand() % _grams[key].size()];
		ret += next + ' ';

		seed.remove(0); //Might completely screw up the time complexity
		seed.add(next);
	}

	return ret;
}
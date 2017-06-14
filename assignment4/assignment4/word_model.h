/*
CSCI 262 Data Structures, Spring 2017, Project 4 - Markov

word_model.h

Class declaration for word-based markov implementation

Author: Capprin Bass

*/

#pragma once

#include "markov.h"
#include "map.h"
#include "vector.h"

class word_model : public markov_model {
public:
	virtual void initialize(std::string text, int order);
	virtual std::string generate(int size);
protected:
	Vector<std::string> _data; //The choice to use vectors might affect the time complexity; although not by much
	int _order;
	Map<std::string, Vector<std::string>> _grams; //Stores vectors of strings corresponding to delimited string keys

	virtual Vector<std::string> delimit(std::string input, char delimiter = ' '); //Splits a string into a vector based on a delimiter
	virtual std::string concat(Vector<std::string> input, char delimiter = ' '); //Concatenates a vector into a string, separated by a delimiter
};
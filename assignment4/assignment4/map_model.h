/*
CSCI 262 Data Structures, Spring 2017, Project 4 - Markov

map_model.h

Class declaration for map-based markov implementation

Author: Capprin Bass

*/


#pragma once

#include "model.h"
#include "map.h"
#include "vector.h"

class map_model : public markov_model {
public:
	virtual void initialize(std::string text, int order);
	virtual std::string generate(int size);

protected:
	std::string _data;
	int _order;
	Map <std::string, Vector<char>> _grams; //Stores all following characters for a given seed
};
#ifndef SELECTORS_H
#define SELECTORS_H

#include <string>
#include <stdexcept>
#include <iostream>
using namespace std;

/**
 * Selectors:       SELECT selector FROM table
 * Table selectors: SELECT selector FROM table WHERE selector IN table
**/

namespace charUtils {
	bool isSpace(char chr);
	string getName(char*& str);
};

class Selector { 
	private:
		string name;
	public:
		Selector(char*& str);
		string getName();
};

class Table { 
	private:
		string name;
	public:
		Table(char*& str);
		string getName();
};

#endif 
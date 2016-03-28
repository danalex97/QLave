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
	bool isAlphaNum(char chr);
	string getName(char*& str);
	char* allocString(string from);
	string splitAt(char chr, char*& str);
};

class Selector { 
	private:
		string name;
	public:
		Selector(char*& str);
		Selector(string selector);
		string getName();
};

class Table { 
	private:
		string name;
	public:
		Table(char*& str);
		Table(string selector);
		string getName();
};

namespace tests_selector{
	void test1();
	void run();
};

#endif 
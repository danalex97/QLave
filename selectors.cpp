#include "selectors.h"
#include <cstring>

bool charUtils :: isSpace(char chr) {
	return chr == ' ' || chr == '\t';
}

bool charUtils :: isAlphaNum(char chr) {
	return (chr >= '0' && chr <= '9') 
		|| (chr >= 'a' && chr <= 'z') 
		|| (chr >= 'A' && chr <= 'Z');
}

string charUtils :: splitAt(char chr, char*& str) {
	string ans = "";
	while (isSpace(*str)) {
		++str;
	}
	while (*str != 0 && *str != chr) {
		ans += *str;
		++str;
	}
	return ans;
}

string charUtils :: getName(char*& str) {
	string out = "";
	while (isSpace(*str)) {
		++str;
	}
	if (*str == 0) {
		return "";
	}
	while (!isSpace(*str) && *str != 0 && *str != ')') {
		out += *str;
		++str;
	}
	return out;
}

char* charUtils :: allocString(string from) {
	char *input = (char*) malloc (from.length()+1);
	for (size_t i = 0; i < from.size(); ++i) {
		*(input + i) = from[i];
	}
	return input;
}

Selector :: Selector(string str) {
	name = str;
}

Selector :: Selector(char*& str) {
	name = charUtils :: getName(str);
}

Table :: Table(char*& str) {
	name = charUtils :: getName(str);
}

Table :: Table(string str) {
	name = str;
}

string Selector :: getName() {
	return name;
}

string Table :: getName() {
	return name;
}

void  tests_selector :: test1() {
	char *input = charUtils :: allocString("  nume  ");

	char *input1 = input;
	char *input2 = input;

	Selector sel1 = Selector(input);
	Table    sel2 = Table(input2);
	if (sel1.getName() != "nume" || sel2.getName() != "nume") {
		cerr << "Test 1 failed." << '\n';
	} else {
		cerr << "Test 1 passed." << '\n';
	}
}
	
void tests_selector :: run() {
	test1();
}
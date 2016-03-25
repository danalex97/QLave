#include "selectors.h"
#include <cstring>

bool charUtils :: isSpace(char chr) {
	return chr == ' ' || chr == '\t';
}

string charUtils :: getName(char*& str) {
	string out = "";
	while (isSpace(*str)) {
		++str;
	}
	if (*str == 0) {
		throw invalid_argument("Received null value on parsing.");
	}
	while (!isSpace(*str)) {
		out += *str;
		++str;
	}
	return out;
}

Selector :: Selector(char*& str) {
	name = charUtils :: getName(str);
}

Table :: Table(char*& str) {
	name = charUtils :: getName(str);
}

string Selector :: getName() {
	return name;
}

string Table :: getName() {
	return name;
}


namespace tests {
	void test1() {
		const char* from = "  nume  ";

		char *input = (char*) malloc (strlen(from)+1);
		memcpy (input, from, sizeof(from));

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
	
	void run() {
		test1();
	}
};

int main() {
	tests :: run();
}
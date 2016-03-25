#include "comp.h"
#include <map>
#include <stdexcept>

map<string, CompOp> comp_map = {
	{">" , GT},
	{">=", GE},
	{"<" , LT},
	{"<=", LE},
	{"=", EQ}
};

map<string, LogicOp> logic_map = {
	{"OR", OR},
	{"AND", AND}
};

/**
 * No validator implemented.
 * NOT - not yet supported.
**/

In :: In(char*& str) {
	lhs = new Selector( charUtils :: getName(str) );
	charUtils :: getName(str);
	rhs = new Table( charUtils :: getName(str) );
}

Comp :: Comp(char*& str) {
	lhs = new Selector( charUtils :: getName(str) );
	string op = charUtils :: getName(str);
	comp = comp_map[op];
	rhs = new Selector( charUtils :: getName(str) );
}

Comp :: Comp(Selector* selector) {
	lhs = selector;
}

Pred* Pred :: term(char*& str) {
	while (charUtils :: isSpace(*str)) {
		++str;
	}
	if (*str == 0) {
		return new Pred();
	}
	if (*str == '(') {
		++str;
		return new Pred(str);
	} else {
		Pred *pred = new Pred();
		
		char *aux = str;
		while (!charUtils :: isSpace(*aux)) {
			++aux;
		}
		string op = charUtils :: getName(aux);

		if (comp_map.find(op) != comp_map.end()) {
			pred -> comp = new Comp(str);
			return pred;
		} else if (op == "IN") {
			pred -> in = new In(str);
			return pred;
		} else {
			pred -> comp = new Comp(new Selector(charUtils :: getName(str)));
			return pred;
		}
	} 
}

Pred :: Pred(char*& str) {
	Pred *lhs = term(str);
	while (charUtils :: isSpace(*str)) {
		++str;
	}
	if (*str != 0) {
		string op = charUtils :: getName(str);
		if (logic_map.find(op) == logic_map.end()) {
			throw invalid_argument("Error on comparison parsing.");
		} else {
			this -> op = logic_map[op];
			rhs = new Pred(str);
		}
	}
}

Pred :: Pred() {
}

void tests_comp :: run() {

}

int main() {
	cerr<<"-------Test set 1--------\n";
	tests_selector :: run();
	cerr<<'\n';

	cerr<<"-------Test set 2--------\n";
	tests_comp :: run();
	cerr<<'\n';
}
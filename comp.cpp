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

map<CompOp, string> rev_comp_map = {
	{GT, ">" },
	{GE, ">="},
	{LT, "<" },
	{LE, "<="},
	{EQ, "=" }
};

map<string, LogicOp> logic_map = {
	{"OR", OR},
	{"AND", AND}
};


map<LogicOp, string> rev_logic_map = {
	{OR, "OR"},
	{AND, "AND"}
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
	rhs = nullptr;
}

Pred* Pred :: term(char*& str) {
	while (charUtils :: isSpace(*str)) {
		++str;
	}
	if (*str == 0) {
		return nullptr;
	}
	if (*str == '(') {
		++str;
		Pred *ans = new Pred(str);
		++str;
		return ans;
	} else {
		Pred *pred = new Pred();
		
		char *aux = str;
		while (!charUtils :: isSpace(*aux) && *aux != 0) {
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
	lhs = rhs = nullptr;
	lhs = term(str);
	while (charUtils :: isSpace(*str) && *str != 0) {
		++str;
	}
	if (*str != 0) {
		string op = charUtils :: getName(str);
		if (logic_map.find(op) == logic_map.end()) {
			rhs = nullptr;
		} else {
			this -> op = logic_map[op];
			rhs = new Pred(str);
		}
	} 
}

Pred :: Pred() {
	lhs = rhs = nullptr;
	comp = nullptr;
	in = nullptr;
}

string In :: toString() {
	if (this -> rhs != nullptr) {
		return this -> lhs -> getName() + " IN " + this -> rhs -> getName();
	} else {
		return this -> lhs -> getName();
	}
}

string Comp :: toString() {
	if (this -> rhs != nullptr) {
		return this -> lhs -> getName() + " " + rev_comp_map[this -> comp] + " " + this -> rhs -> getName();
	} else {
		return this -> lhs -> getName();
	}
}

string Pred :: toString() {
	if (this == nullptr) {
		return "";
	}
	if (rhs == nullptr) {
		if (lhs == nullptr) {
			if (comp != nullptr) { 
				return comp -> toString(); 
			} else {
				return in -> toString();
			}
		} else {
			return lhs -> toString();
		}
	}
	return "(" + lhs->toString() + " " + rev_logic_map[op] + " " + rhs->toString() + ")";
}

void tests_comp :: test(string idx, string in, string ans) {
	char *input = charUtils :: allocString(in);
	Pred *now = new Pred(input);
	if (now->toString() != ans) {
		cerr << "Test " + idx + " failed.\n"; 
	} else {
		cerr << "Test " + idx + " passed.\n"; 
	}
}

void tests_comp :: run() {
	tests_comp :: test("1", "(v <= v) AND (v >= v)", "(v <= v AND v >= v)");
	tests_comp :: test("2", "v AND (v OR v)", "(v AND (v OR v))");
	tests_comp :: test("3", "v AND v OR v", "(v AND (v OR v))");
	tests_comp :: test("4", "v IN v", "v IN v");
}

int main() {
	cerr<<"-------Test set 1--------\n";
	tests_selector :: run();
	cerr<<'\n';

	cerr<<"-------Test set 2--------\n";
	tests_comp :: run();
	cerr<<'\n';
}
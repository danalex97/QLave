#ifndef COMP_H
#define COMP_H

#include <vector>

#include "field.h"
#include "selectors.h"

using namespace std;

enum CompOp { 
	GT, 
	GE,
	LE,
	LT,
	EQ 
};

class Comp {
	private:
		Selector *lhs, *rhs;
		CompOp   comp;
	public:
		Comp(char*& str);
		Comp(Selector* selector);
};

enum LogicOp { 
	NOT, 
	AND,
	OR 
};

class In {
	private:
		Selector *lhs;
		Table    *rhs;
	public:
		In(char*& str);
};

/**
 * Predicates:
 *  - evaluates to true or false for each entry
 *
 * Supported operations:
 *  - s1 <= s2 (>, etc)
 *  - s1 in t1
 *  - s1 like pattern   - not implemented
**/
class Pred {
	private:
		Pred *lhs, *rhs;
		LogicOp op;

		Comp *comp;
		In   *in;
	public:
		Pred();
		Pred(char*& str);
		Pred* term(char*& str);
};

namespace tests_comp {
	void run();
};

#endif 
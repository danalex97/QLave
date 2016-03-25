#ifndef COMP_H
#define COMP_H

#include <vector>

#ifndef FIELD_H
#include "field.h"
#endif

using namespace std;

enum Comp { 
	GT, 
	LT,
	EQ 
};

struct Comparison {
	Field f1, f2;
	Comp comp;
	bool neg;
};

class Condition {
private:
	vector<Comparison> cond;
	
public:
};

#endif 
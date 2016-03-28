#ifndef FIELD_H
#define FIELD_H

#include <cstring>
#include <stdexcept>
#include <map>
using namespace std;

/**
 * The data kept in table entries. It can keep 3 types: integer, real or text.
**/

/** INTEGER types:
	- SHORT
	- INT
	- LONG
**/

/// DOES NOT CHECK FOR OVERFLOW.
template <class T> class Integer {
	private:
		T value;
		T parse_unsigned(string str, int left, int right);
	public:
		Integer(string str);
		T getValue();
};

/** REAL types:
	- FLOAT
	- DOUBLE
**/

/// DOES NOT CHECK FOR OVERFLOW.
template <class T> class Real {
	private:
		T value;
		T parse_unsigned(string str, int left, int right);
	public:
		Real(string str);
		T getValue();
};


/** TEXT types:
	- VARCHAR
	- CHAR    - not implemented
**/

/// DOES NOT CHECK FOR OVERFLOW.
template <class T> class Text {
	private:
		string value;
	public:
		Text(string str);
		string getValue();
};

template <class T> struct Type;

template <> struct Type<int>       : public Integer<int>       { using Integer<int>       :: Integer; };
template <> struct Type<long long> : public Integer<long long> { using Integer<long long> :: Integer; };
template <> struct Type<short>     : public Integer<short>     { using Integer<short>     :: Integer; };

template <> struct Type<float>  : public Real<float>  { using Real<float>  :: Real; };
template <> struct Type<double> : public Real<double> { using Real<double> :: Real; };

template <> struct Type<char> : public Text<char> { using Text<char> :: Text; };

namespace field_tests {
	template<class T, class S> struct TestBuilder {
		string out;
		S expected;
		string idx;
		bool has_result;

		TestBuilder(string idx, string out);
		TestBuilder(string idx, string out, S expected);
		void run();
	};
	void run();
	void type_infer_tests();
};

namespace infer_type {
	const string TYPES[6] = {"INT", "SHORT", "LONG", "FLOAT", "DOUBLE", "VARCHAR"};
	void* infer_type(string str, string input); 
	bool can_infer(string str);
};

#endif 
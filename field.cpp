#include "field.h"
#include <iostream>
#include <vector>

//////////////////////////////////////////////// INTEGER ///////////////////////////////////////////////

template<class T> T Integer<T> :: parse_unsigned(string str, int left, int right) {
	value = 0;
	if (left == right) {
		throw invalid_argument("Received null value on parsing.");
	}
	for (int i = left; i < right; ++i) {
		if (str[i] < '0' || str[i] > '9') {
			throw invalid_argument("Received bad data - integer.");
		}
		value *= 10;
		value += int(str[i]-'0');
	}
}

template<class T> Integer<T> :: Integer(string str) {
	value = 0;
	if (str.size() == 0) {
		throw invalid_argument("Received null value on parsing.");
	}
	if (str[0] == '-') {
		parse_unsigned(str, 1, str.size());
		value = -value;
	} else {
		parse_unsigned(str, 0, str.size());
	}
}

template<class T> T Integer<T> :: getValue() {
	return value;
}

//////////////////////////////////////////////// REAL ///////////////////////////////////////////////


template<class T> T Real<T> :: parse_unsigned(string str, int left, int right) {
	value = 0;
	int point_flag = 0;
	if (left == right) {
		throw invalid_argument("Received null value on parsing.");
	}
	if (str[left] == '.') {
		throw invalid_argument("Received point value on parsing.");
	}
	for (int i = left; i < right; ++i) {
		if (str[i] == '.') {
			if (point_flag) {
				throw invalid_argument("Multiple points.");
			} else {
				if (i + 1 == right) {
					throw invalid_argument("No value after point.");
				}
				point_flag = 1;
			}
			continue;
		}
		if (str[i] < '0' || str[i] > '9') {
			throw invalid_argument("Received bad data - real.");
		}
		value *= 10;
		value += int(str[i]-'0');
		if (point_flag) {
			point_flag++;
		}
	}
	while (point_flag > 1) {
		value /= 10;
		point_flag--;
	}
}

template<class T> Real<T> :: Real(string str) {
	value = 0;
	if (str.size() == 0) {
		throw invalid_argument("Received null value on parsing.");
	}
	if (str[0] == '-') {
		parse_unsigned(str, 1, str.size());
		value = -value;
	} else {
		parse_unsigned(str, 0, str.size());
	}
}

template<class T> T Real<T> :: getValue() {
	return value;
}

//////////////////////////////////////////////// TEXT ///////////////////////////////////////////////

template<class T> Text<T> :: Text(string str) {
	value = str;
}

template<class T> string Text<T> :: getValue() {
	return value;
}

////////////////////////////////////////////// TYPE INFER ///////////////////////////////////////////////

void* infer_type :: infer_type(string str, string input)
{
	if (str == "INT") {
		return new Type<int>(input);
	} else if (str == "SHORT") {
		return new Type<short>(input);
	} else if (str == "LONG") {
		return new Type<long long>(input);
	} else if (str == "FLOAT") {
		return new Type<float>(input);
	} else if (str == "DOUBLE") {
		return new Type<double>(input);
	} else {
		return new Type<char>(input);
	}
}

void field_tests :: type_infer_tests() {
	if ((new Type<int>("5"))->getValue() != ((Type<int>*)infer_type :: infer_type("INT", "5"))->getValue()) { 
	 	cerr << "Infer tests 1 failed." << '\n'; 
	} else if ((new Type<char>("ss"))->getValue() != ((Type<char>*)infer_type :: infer_type("VARCHAR", "ss"))->getValue()){ 
		cerr << "Infer tests 2 failed." << '\n'; 
	} else if ((new Type<double>("1.3"))->getValue() != ((Type<double>*)infer_type :: infer_type("DOUBLE", "1.3"))->getValue()){ 
		cerr << "Infer tests 3 failed." << '\n'; 
	} else {
		cerr << "Infer tests passed." << '\n'; 
	}
}

bool infer_type :: can_infer(string str) {
	for (string it : TYPES) {
		if (it == str) {
			return true;
		}
	}
	return false;
}

//////////////////////////////////////////////// TESTS ///////////////////////////////////////////////

template<class T, class S> field_tests :: TestBuilder<T, S> :: TestBuilder(string idx, string out) {
	this -> idx      = idx;
	this -> out      = out;

	has_result = false;
}

template<class T, class S> field_tests :: TestBuilder<T, S> :: TestBuilder(string idx, string out, S expected) {
	this -> idx      = idx;
	this -> out      = out;
	this -> expected = expected;
	
	has_result = true;
}

template<class T, class S> void field_tests :: TestBuilder<T, S> :: run() {
	if (has_result == false) {
		try {
			T v = T(out);
			cerr << "Reading test " + idx + " failed." << '\n';
		} catch(const invalid_argument& e) {
			cerr << "Reading test " + idx + " passed." << '\n';
		}
	} else {
		try {
			T v = T(out);
			if (v.getValue() == expected) {
				cerr << "Reading test " + idx + " passed." << '\n';
			} else {
				cerr << "Reading test " + idx + " failed." << '\n';
			}
		} catch(const invalid_argument& e) {
			cerr << "Reading test " + idx + " failed." << '\n';
		}
	}
}

void field_tests :: run() {
	TestBuilder<Integer<int>, int>("1", "-").run();
	TestBuilder<Integer<int>, int>("2", "").run();
	TestBuilder<Integer<int>, int>("3", "12", 12).run();
	TestBuilder<Integer<int>, int>("4", "12", 12).run();

	TestBuilder<Real<float>, float>("5", "-12", -12).run();
	TestBuilder<Real<float>, float>("6", "-12.12", -12.12).run();
	TestBuilder<Real<double>, double>("7", "-.1").run();
	TestBuilder<Real<double>, double>("8", "0.1", 0.1).run();
	TestBuilder<Real<double>, double>("9", "-0.").run();

	TestBuilder<Text<char>, string>("10", "lorem ipsum", "lorem ipsum").run();

	TestBuilder<Type<double>, double>("11", "-0.").run();
	TestBuilder<Type<char>, string>("12", "lorem ipsum", "lorem ipsum").run();

	field_tests :: type_infer_tests();
}
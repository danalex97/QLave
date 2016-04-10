#ifndef PARSER_H
#define PARSER_H

#include <iostream>
#include <fstream>
#include <sstream>
#include <vector>
#include <stdexcept>
using namespace std;

namespace Tests {
	static const int TESTS = 2;
	
	vector<string> TEST[TESTS] = {
		{
			"CREATE"
			" DATABASE test;",
			"USE test;"
		}
	};

	void run();
	void test_name_not_provided();
	void test_file_not_provided();
};

class Parser {
	private:
		ifstream *file_in;
		int vector_cursor;
		int mode;
		
		string line;
		string query;
		string acc;

		vector<string> lines;

		const char* STDINP_FILE = "parser.in";
		bool multi_line(string raw_data);
	public:
		static const int STDINP = 0;
		static const int STREAM = 1;
		static const int STRING = 2;

		Parser(int mode);
		void run();
		
		void build();
		void build(string file_name);
		void build(vector<string> lines);

		string get_mode();
		string* read_line();
		void parse(string line);
};

#endif 
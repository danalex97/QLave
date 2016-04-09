#include "parser.h"
#include "storage.h"

Parser :: Parser(int mode) {
	switch (mode) {
		case STDINP: 
			this -> mode = mode;
			this -> build();
			break;
		case STREAM: 
			this -> mode = mode;
			this -> build(Parser :: STDINP_FILE);
			break;
		case STRING: 
			this -> mode = mode;
			this -> build();
			break;
	}
}

void Parser :: build() {
	try {
		switch (mode) {
			case STDINP: 
				break;
			case STREAM: 
				throw runtime_error("File for read not provided.");
				break;
			case STRING:
				vector_cursor = 0; 
				break;
		}
	} catch (exception &e) {
		cerr << "Caught exception: " << e.what() << '\n';
		mode = Parser :: STDINP;
		cerr << "Using " << get_mode() << " for reading." << '\n';
		build();
	}
}

string Parser :: get_mode() {
	switch (mode) {
		case STDINP:
			return "STDINP"; 
			break;
		case STREAM: 
			return "STREAM"; 
			break;
		case STRING:
			return "STRING"; 
			break;
	} 
}

void Parser :: build(string input_name) {
	try {
		switch (mode) {
			case STDINP: 
				throw runtime_error("Provided file input name.");
				break;
			case STREAM: 
				file_in = new ifstream(input_name);
				if (!*file_in) {
					throw runtime_error("No file provided.");
				}
				break;
			case STRING:
				throw runtime_error("Provided file input name.");
				break;
		}
	} catch (exception &e) {
		cerr << "Caught exception: " << e.what() << '\n';
		mode = Parser :: STDINP;
		cerr << "Using " << get_mode() << " for reading." << '\n';
	}
}


void Parser :: build(vector<string> lines) {
	try {
		switch (mode) {
			case STDINP: 
				throw runtime_error("Trying to parse vector from cin.");
				break;
			case STREAM: 
				throw runtime_error("Trying to parse vector from stream.");
				break;
			case STRING:
				this -> lines = lines;
				this -> vector_cursor = 0;
				break;
		}
	} catch (exception &e) {
		cerr << "Caught exception: " << e.what() << '\n';
		mode = Parser :: STRING;
		cerr << "Using " << get_mode() << " for reading." << '\n';
		this -> build(lines);
	}
}

void Parser :: run() {
	cerr << "Parser running" << '\n';
	string *line = nullptr;
	switch (mode) {
		case STDINP:
			while (true) {
				line = read_line();
				parse(*line);	
			}
			break;
		case STREAM:
			while (true) {
				line = read_line();
				if (line == nullptr) {
					break;
				}
				parse(*line);
			} 			
			break;
		case STRING: 
			while (true) {
				line = read_line();
				if (line == nullptr) {
					break;
				}
				parse(*line);
			} 
			break;
	}
}

/****************** COMMANDS *********************

THE INITIAL VERSION WILL NOT ACCEPT SPECIAL WORDS SEPARATELY.
TO DO: 
	* MULTIPLE RAW READING.
	* CASE INSENSITIVE

Creation:
	CREATE DATABASE test;
	USE database;
	CREATE TABLE table_name
	(
	column_name1 data_type(size),
	column_name2 data_type(size),
	column_name3 data_type(size),
	....
	);

Update:
	INSERT INTO table_name VALUES (value1,value2,value3,...);
	UPDATE table_name SET column1=value1,column2=value2,... WHERE some_column=some_value;
	DELETE FROM table_name WHERE some_column=some_value;

Querys:
	SELECT column_name,column_name FROM table_name;
	SELECT DISTINCT column_name,column_name FROM table_name;
	SELECT column_name,column_name FROM table_name WHERE column_name operator value;
	SELECT * FROM Customers ORDER BY Country; 
	SELECT column_name(s) FROM table_name LIMIT number;
	SELECT column_name(s) FROM table_name WHERE column_name LIKE pattern;
	SELECT column_name(s) FROM table_name WHERE column_name IN (@column);

Query composition:
	(SELECT column_name(s) FROM table1) UNION (SELECT column_name(s) FROM table2);
	SELECT Orders.OrderID, Customers.CustomerName, Orders.OrderDate FROM Orders INNER JOIN Customers ON Orders.CustomerID=Customers.CustomerID; 
	SELECT Customers.CustomerName, Orders.OrderID INTO CustomersOrderBackup2013 FROM Customers LEFT JOIN Orders ON Customers.CustomerID=Orders.CustomerID;

**************************************************/

void Parser :: parse(string raw_data) {
	cerr << raw_data << '\n';
}

string* Parser :: read_line() {
	try {
		switch (mode) {
			case STDINP:        /////////////////// reads just a word
				cin >> line; 
				cout << line << '\n';
				break;
			case STREAM:
				if (!((*file_in) >> line)) {
					cerr << "Finished reading." << '\n';
					return nullptr;
				}
				break;
			case STRING: 	
				if (vector_cursor >= lines.size()) {
					cerr << "Finished reading." << '\n';
					return nullptr;
				} else {
					line = lines[vector_cursor];
					vector_cursor++;
				}
				break;
		} 
	} catch (exception &e) {
		cerr << "Caught exception @ read_line: " << e.what() <<'\n';
	}
	return &line;
}

void Tests :: test_name_not_provided() {
	cerr << "Test name not provided" << '\n';
	cerr << "----------------------" << '\n';
	Parser *parser = new Parser(Parser :: STREAM);
	parser -> build();
	cerr << '\n';
	delete parser;
}

void Tests :: test_file_not_provided() {
	cerr << "Test file not provided" << '\n';
	cerr << "----------------------" << '\n';
	Parser *parser = new Parser(Parser :: STREAM);
	cerr << '\n';
	delete parser;
}

void Tests :: run() {
	cerr << "Running string tests" << '\n';
	cerr << "====================" << '\n';
	for (int i = 0; i < TESTS; ++i) {
		cerr << "Test " << i << '\n';
		cerr << "------" << '\n';
		Parser *parser = new Parser(Parser :: STRING);

		parser -> build(TEST[i]);
		parser -> run();

		cerr << '\n';
		delete parser;
	}
	cerr << "\n";

	Tests :: test_name_not_provided();
	Tests :: test_file_not_provided();
}

int main() {
	//field_tests :: run();
	//storage_tests :: run();
	Tests :: run();
}

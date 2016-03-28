#ifndef STORAGE_H
#define STORAGE_H

#include <string>
#include <vector>
#include <map>
using namespace std;

#include "field.h"

class Head {
	private:
		map<string, string> assoc;
	public:
		Head(string raw_data);
		string type(string name);
};

class Column {
	private:
	public:
		map<string, void*> row;
		Column(string raw_data, Head h);
		void* get(string name);
};

class Storage {
	private:
		string name;
		Head *head;
	public:
		Storage(string raw_data);
		virtual void insert(string raw_data) = 0;
		string get_name();
		Head get_head();
};

class Vector : public Storage {
	private:
		vector<Column> v;
	public:
		Vector(string raw_data) : Storage(raw_data){}
		void insert(string raw_data);
		Column get(int idx); 
		int size();
};

class Database {
	private:
		string name;
		map<string, Storage*> tables;
	public:		
		Database(string name);
		void append_table(Storage* storage);
};

namespace storage_tests {
	void test_database_append();
	void run();
};

#endif 
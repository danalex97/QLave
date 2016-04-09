#include "storage.h"
#include "selectors.h"
using namespace charUtils;

Head :: Head(string raw_data) {
	char *str = allocString(raw_data);
	while (*str != 0) {
		char *line = allocString(splitAt(',', str));
		++str;

		string name = getName(line);
		string type_name = getName(line);

		if (!infer_type :: can_infer(type_name)) {
			throw invalid_argument("Not supported inferred type.");
		} else {
			assoc[name] = type_name;
		}
	}
}

string Head :: type(string name) {
	return assoc[name];
}

Head Storage :: get_head() {
	return *head;
}

Column :: Column(string raw_data, Head h) {
	char *str = allocString(raw_data);
	
	while (*str != 0) {
		char *aux = str;
		splitAt('=', str); ++str;
		string name = getName(aux); 

		aux = str;
		while (*aux != ',' && *aux != '"' && *aux != 0) {
			++aux;
		}
		if (*aux == '"') {
			string s2 = splitAt('"', str); ++str;
			string content = splitAt('"', str); ++str;
			string s4 = splitAt(',', str); ++str;

			void* data = infer_type :: infer_type(h.type(name), content);
			row[name] = data;
		} else {
			string content = getName(str); ++str;
		
			void* data = infer_type :: infer_type(h.type(name), content);
			row[name] = data;
		}
	}
}

void* Column :: get(string name) {
	return row[name];
}

void Vector :: insert(string raw_data) {
	v.push_back(*(new Column(raw_data, get_head())));
}

Column Vector :: get(int idx) {
	return v[idx];
}

int Vector :: size() {
	return v.size();
}

Storage :: Storage(string raw_data) {
	char *str = allocString(raw_data);
	
	name = splitAt('(', str);
	++str;
	raw_data = splitAt(')', str);

	head = new Head(raw_data);
}

string Storage :: get_name() {
	return name;
}

Database :: Database(string name) {
	this -> name = name;
	tables = {};
}

void Database :: append_table(Storage* storage) {
	if (tables.find(storage->get_name()) != tables.end()) {
		tables[storage->get_name()] = storage;
	} else {
		throw invalid_argument("Multiple tables with same name.");
	}
}

void storage_tests :: test_database_append() {
	Database *db = new Database("test");
	Vector *table = new Vector("table (nbr INT, str VARCHAR)");
	table->insert("str = \"string tata\", nbr = 5");
	if ( ((Type<int>*)(table->get(0)).get("nbr"))->getValue() != 5 ) {
		cerr << "Storage test 1 failed." << '\n';
	} else if ( ((Type<char>*)(table->get(0)).get("str"))->getValue() != "string tata" ) {
		cerr << "Storage test 2 failed." << '\n';
	} else {
		cerr << "Storage tests passed." << '\n';
	}
}

void storage_tests :: run() {
	test_database_append();
}

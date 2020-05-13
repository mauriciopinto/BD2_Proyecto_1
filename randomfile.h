//#ifndef BD2_PROYECTO_1_RANDOMFILE_H
//#define BD2_PROYECTO_1_RANDOMFILE_H

//#endif //BD2_PROYECTO_1_RANDOMFILE_H

#include <iostream>
#include <fstream>
#include <list>
#include "record.h"

using namespace std;

struct Pair {
        int key;
        int position;
};

void init_pair (Pair *, int, int);
record random_search_record (int, const char *, list<Pair>);
list<Pair> random_add_record (record *, const char *, list<Pair>);
void random_store_index (const char *, list<Pair>);

class random_file {
private:
	const char *data_filename;
	const char *index_filename;
	list<Pair> dictionary;
public:
	random_file (const char *data_filename, const char *index_filename) : data_filename (data_filename),
										 index_filename (index_filename) {
		ifstream index;
                index.open (index_filename, ios::binary);
                Pair *temp = new Pair;
                char buffer[sizeof (Pair)];
                if (index.good ()) {
                        while (!index.eof ()) {
                                index.read (buffer, sizeof (Pair));
                                temp = (Pair *) buffer;
                                dictionary.push_back (*temp);
                        }
                }
	}

	record search_record (int key) {
		return random_search_record (key, data_filename, dictionary);
	}

	void add_record (record *record) {
		dictionary = random_add_record (record, data_filename, dictionary);
	}

	void store_index () {
		random_store_index (index_filename, dictionary);
	}

	~random_file () {
		store_index ();
	}
};

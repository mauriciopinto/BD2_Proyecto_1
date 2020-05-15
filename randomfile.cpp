#include "randomfile.h"

list<Pair> sort_dictionary (list<Pair>);
record random_read_record (const char *, int);

void init_pair (Pair *p, int key, int position) {
	p->key = key;
	p->position = position;
}

record random_read_record (const char *data_filename, int position) {
	ifstream file;
	record *temp;
	char buffer[sizeof (record)];

	file.open (data_filename, ios::binary);
	file.seekg ((position));
	file.read (buffer, sizeof (record));

	file.close ();
	return *((record *) buffer);
}

list<Pair> sort_dictionary (list<Pair> dictionary) {
	if (dictionary.size () == 1)
                return dictionary;
        list<Pair> new_dict;
        list<Pair>::iterator index;
        Pair *temp = new Pair;
        int min;
        while (dictionary.size () > 0) {
                min = 10000;
                for (auto it = dictionary.begin (); it != dictionary.end (); it++) {
                        if (it->key < min) {
                                min = it->key;
                                index = it;
                                *temp = *it;
                        }
                }
                new_dict.push_back (*temp);
                dictionary.erase (index);
        }
        return new_dict;
}

record random_search_record (int key, const char *data_filename, list<Pair> dictionary) {
	list<Pair>::iterator it;
        int n = dictionary.size () - 1;
        if ((n+1) % 2 == 0 && n + 1 > 32) {
		n = (n+1)/2;
        	it = dictionary.begin ();
                advance (it, n);
                while (true) {
                	int prev_n = n;
			if (key == it->key)
                        	return random_read_record (data_filename, it->position);
                        if (key > it->key) {
                        	n += (n+1) / 2;
                                advance (it, n);
                        }
                        else {
                        	n -= (n+1) / 2;
                        	it = prev (it, n);
                        }
			if (prev_n == n || n > dictionary.size () - 1)
				break;
                }
	}
        else {
        	int i = 0;
                for (it = dictionary.begin (); it != dictionary.end (); it++) {
                	if (it->key == key)
                        	return random_read_record (data_filename, it->position);
                        i++;
                }
        }
	record *bad_record = new record;
	init_record (bad_record, -1, "bad record");
        return *bad_record;
}

list<Pair> random_add_record (record *r, const char *data_filename, list<Pair> dictionary) {
	ifstream i;
	i.open (data_filename, ios::ate);
	int pos = i.tellg ();
	
	ofstream file;
        file.open (data_filename, ios::binary | ios::app);
        
	file.write ((char *) r, sizeof (record));
       	file.flush ();
	file.close ();

	Pair *p1 = new Pair;
       	init_pair (p1, r->key, pos);
        
	dictionary.push_back (*p1);
       	dictionary = sort_dictionary (dictionary);
	return dictionary;
}

void random_store_index (const char *index_filename, list<Pair> dictionary) {
	ofstream index;
        index.open (index_filename, ios::binary);
	index.seekp (0);
	int dict_size = dictionary.size ();
	index.write ((char *) &dict_size, sizeof (int));
        for (auto it = dictionary.begin (); it != dictionary.end (); it++) {
        	index.write ((char *) &(*it), sizeof (Pair));
        }

	index.flush ();
	index.close ();
}

vector<record> random_get_all_records (const char *data_filename) {
        ifstream file;
        file.open (data_filename, ios::binary);
        char buffer[sizeof (record)];
        record *temp;
        vector<record> all_records;

        file.seekg (sizeof(int));
        file.read (buffer, sizeof (record));
        while (!file.eof ()) {
                temp = (record *) buffer;
                all_records.push_back (*temp);
                file.read (buffer, sizeof (record));
        }
        return all_records;
}

void print_dictionary (list<Pair> *dictionary) {
	list<Pair>::iterator it;
	for (it = dictionary->begin (); it != dictionary->end (); it++) 
		cout << it->key << " " << it->position << endl;
}

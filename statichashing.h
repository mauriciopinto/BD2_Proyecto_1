#ifndef BD2_PROYECTO_1_STATICHASHING_H
#define BD2_PROYECTO_1_STATICHASHING_H

#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "record.h"

using namespace std;

struct bucket {
        int position;
        int bucket_size;
        int count;
        bucket *overflow;
};

void print_hash_table (map<int, bucket *> *);

void hash_add_record (record *, map<int, bucket *> *, int, const char *);
record hash_search_record (int, map<int, bucket *> *, int, const char *);
void hash_store_index (const char *, map<int, bucket *> *);
void write_bucket (bucket *, const char *);
void init_bucket (bucket *, int, int, int);

class hash_file {
private:
	const char *data_filename;
	const char *hash_table_filename;
	map<int, bucket*> hash_table;
	int bucket_size;
	int n_buckets;
public:
	hash_file (const char *data_filename, const char *hash_table_filename, 
		   int bucket_size, int n_buckets) : data_filename (data_filename), 
						     hash_table_filename (hash_table_filename), 
						     bucket_size (bucket_size), n_buckets (n_buckets) {
		ifstream h_file;
		h_file.open (hash_table_filename, ios::binary);
		if (h_file.good ()) {
			for (int i = 0; i < n_buckets; i++) {
				char first_buffer[sizeof (int)];
				char second_buffer[sizeof (bucket)];
				
				h_file.read (first_buffer, sizeof (int));
				h_file.read (second_buffer, sizeof (bucket));
				int first = *((int *) first_buffer);
				bucket *second = (bucket *) second_buffer;
				bucket *n = new bucket;
				init_bucket (n, second->position, second->bucket_size, second->count);
				hash_table.insert (pair<int, bucket *> (first, n));
			}
		}
		else {
			for (int i = 0; i < n_buckets; i++) {
				bucket *b = new bucket;
				init_bucket (b, i * bucket_size, bucket_size, 0);
				write_bucket (b, data_filename);
				hash_table.insert (pair<int, bucket *> (i, b));
			}
		}
	};

	void add_record (record *record) {
		return hash_add_record (record, &hash_table, bucket_size, data_filename);
	}

	record search_record (int key) {
		return hash_search_record (key, &hash_table, bucket_size, data_filename);
	}

	void store_index () {
		hash_store_index (hash_table_filename, &hash_table);
	}

	~hash_file () {
		store_index ();
	}
};
#endif //BD2_PROYECTO_1_STATICHASHING_H

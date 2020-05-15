#ifndef BD2_PROYECTO_1_STATICHASHING_H
#define BD2_PROYECTO_1_STATICHASHING_H

#define BUCKET_SIZE 6


#include <iostream>
#include <map>
#include <vector>
#include <fstream>
#include "record.h"

using namespace std;

struct bucket {
	bool is_null;
        int position [BUCKET_SIZE];
        int bucket_size;
        int count;
        int overflow[1024];
	int overflow_count;
};

void print_hash_table (map<int, bucket> *);

void hash_add_record (record *, map<int, bucket> *, int, const char *);
record hash_search_record (int, map<int, bucket> *, int, const char *);
void hash_store_index (const char *, map<int, bucket> *);
void init_bucket (bucket *, int, int);
vector<record> hash_get_all_records (const char *);
vector<record> hash_range_search (int, int, const char *);

class hash_file {
private:
	const char *data_filename;
	const char *hash_table_filename;
	map<int, bucket> hash_table;
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
				/*char first_buffer[sizeof (int)];
				char second_buffer[sizeof (bucket)];
				
				h_file.read (first_buffer, sizeof (int));
				h_file.read (second_buffer, sizeof (bucket));
				int first = *((int *) first_buffer);
				bucket *second = (bucket *) second_buffer;
				if (second->is_null == true)
					second = nullptr;
					*/
				char buffer[sizeof (pair<int, bucket>)];
				h_file.read (buffer, sizeof (pair<int, bucket>));
				pair<int, bucket> p = *(pair<int, bucket> *) buffer;
				hash_table.insert (p);
			}
		}
		else {
			for (int i = 0; i < n_buckets; i++) {
				bucket b;
				b.is_null = true;
        			for (int i = 0; i < BUCKET_SIZE; i++)
                			b.position[i] = 0;
        			b.count = 0;
        			b.bucket_size = BUCKET_SIZE;
				hash_table.insert (pair<int, bucket> (i, b));
			}
		}
	};

	void add_record (record *record) {
		hash_add_record (record, &hash_table, bucket_size, data_filename);
	}

	record search_record (int key) {
		return hash_search_record (key, &hash_table, bucket_size, data_filename);
	}

	void store_index () {
		hash_store_index (hash_table_filename, &hash_table);
	}

	vector<record> get_all_records () {
		return hash_get_all_records (data_filename);
	}

	vector<record> range_search (int s, int e) {
		return hash_range_search (s, e, data_filename);
	}

	~hash_file () {
		store_index ();
	}
};
#endif //BD2_PROYECTO_1_STATICHASHING_H

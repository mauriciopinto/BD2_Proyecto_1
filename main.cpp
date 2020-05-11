#include <iostream>
#include "statichashing.h"

int main(){
	const char *filename = "hash_data.bin";
	const char *hash_filename = "hash_table.bin";
	hash_file h_file (filename, hash_filename, 6, 10);
	
	record *r1 = new record;
	init_record (r1, 1, "pepe");
	h_file.add_record (r1);
	record found = h_file.search_record (1);
	cout << found.key << " " << found.value << endl;
	return 0;
}

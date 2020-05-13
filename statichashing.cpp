#include "statichashing.h"

int hash_function (int, int);
bucket *find_bucket (int, map<int, bucket *> *);
record hash_find_record (int, bucket *, const char *);
record *hash_read_record (int, const char *);
int hash_write_record (record *, int, const char *);

void init_bucket (bucket *b, int position, int bucket_size, int count) {
	b->position = position;
	b->bucket_size = bucket_size;
	b->count = count;
}

void write_bucket (bucket *b, const char *filename) {
	record *temp = new record;
	for (int i = 0; i < b->bucket_size; i++) 
		hash_write_record (temp, b->position + i, filename);
}

record *hash_read_record (int position, const char *filename) {
	ifstream file;
	record *temp = new record;
	char buffer[sizeof (record)];
	
	file.open (filename, ios::binary);
	file.seekg ((position * sizeof(record)) + sizeof (int));
	file.read (buffer, sizeof (record));
	temp = (record *) buffer;

	file.close ();
        return temp;	
}

int hash_write_record (record *r, int position, const char *filename) {
	ofstream file;

	file.open (filename, ios::binary);
	file.seekp ((position * sizeof (record)) + sizeof (int));
	file.write ((char *) r, sizeof (record));

	int ret = file.tellp ();
	file.flush ();
	file.close ();
	return ret;
}

int hash_function (int key, int bucket_size) {
	return key % bucket_size;
}

bucket *find_bucket (int index, map<int, bucket *> *hash_table) {
	map<int, bucket *>::iterator it;
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
		if (index == it->first) {
			return it->second;
		}
	}
}

record hash_find_record (int key, bucket *b, const char *filename) {
	for (int i = 0; i < b->count; i++) {
		record *temp = hash_read_record (b->position + i, filename);	//complete
		if (key == temp->key)
			return *temp;
	}
	if (b->count >= b->bucket_size)
		hash_find_record (key, b->overflow, filename);
	else {
		record *bad_record = new record;
		init_record (bad_record, -1, "bad record");
		return *bad_record;
	}
}

/*Agrega un registro al bucket correspondiente. Si el bucket
 * se llena, crea un overflow bucket.*/
void hash_add_record (record *record, map<int, bucket *> *hash_table, int bucket_size, const char *filename) {
	int index = hash_function (record->key, bucket_size);
	bucket *b = find_bucket (index, hash_table);

	while (b->count >= b->bucket_size)
	       b = b->overflow;	
	int position = hash_write_record (record, b->position + b->count, filename); 		//complete
	b->count++;
	if (b->count >= b->bucket_size) {
		b->overflow = new bucket;
		init_bucket (b->overflow, position, b->bucket_size, 0);
		write_bucket (b->overflow, filename);
	}
	map<int, bucket *>::iterator it;
	it = hash_table->find (index);
	it->second = b;
}

/*Busca y retorna registros que tengan la clave KEY.
 * En caso no exista ninguno, retorna NULL*/
record hash_search_record (int key, map<int, bucket *> *hash_table, int bucket_size, const char *filename) {
	int index = hash_function (key, bucket_size);
	bucket *b = find_bucket (index, hash_table);
	return hash_find_record (key, b, filename);
}

void hash_store_index (const char *hash_table_filename, map<int, bucket *> *hash_table) {
	map<int, bucket *>::iterator it;
	ofstream file;
	file.open (hash_table_filename, ios::binary);
	file.seekp (0);
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
		int first = it->first;
		bucket *second = it->second;
		file.write ((char *) &first, sizeof (int));
		file.write ((char *) second, sizeof (bucket));
		file.flush ();
	}
	file.close ();
}

void print_hash_table (map<int, bucket *> *hash_table) {
	map<int, bucket *>::iterator it;
	for (it = hash_table->begin (); it != hash_table->end (); it++)
		cout << it->first << " " << it->second->position << " " << it->second->count << endl;
}

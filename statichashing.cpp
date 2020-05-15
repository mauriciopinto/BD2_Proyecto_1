#include "statichashing.h"

int hash_function (int, int);
bucket find_bucket (int, map<int, bucket> *);
record hash_find_record (int, bucket, const char *);
int hash_write_record (record *, int, const char *);

void init_bucket (bucket *b, int bucket_size, int count) {
	for (int i = 0; i < BUCKET_SIZE; i++)
		b->position[i] = -1;
	b->bucket_size = bucket_size;
	b->count = count;
	b->overflow = nullptr;
	b->is_null = false;
}

int hash_write_record (record *r, const char *filename) {
	ifstream i;
	i.open (filename, ios::ate);
	int ret = i.tellg ();
	i.close ();

	ofstream file;
	
	file.open (filename, ios::binary | ios::app);
	file.write ((char *) r, sizeof (record));

	file.flush ();
	file.close ();

	if (ret < 0)
		return 0;
	return ret;
}

int hash_function (int key, int bucket_size) {
	return key % bucket_size;
}

bucket find_bucket (int index, map<int, bucket> *hash_table) {
	map<int, bucket>::iterator it;
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
		if (index == it->first) {
			return it->second;
		}
	}
}

record hash_find_record (int key, bucket *b, const char *filename) {
	ifstream file;
	file.open (filename, ios::binary);
	char buffer[sizeof (record)];
	record *temp;
	for (int i = 0; i < b->count; i++) {
		file.seekg (b->position[i]);
		file.read (buffer, sizeof (record));
		temp = (record *) buffer;
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
void hash_add_record (record *record, map<int, bucket> *hash_table, int bucket_size, const char *filename) {
	int index = hash_function (record->key, bucket_size);
	bucket b = find_bucket (index, hash_table);
	if (!b.is_null) {
		while (b.count >= b.bucket_size)
	       		b = *(b.overflow);
	}
	int position = hash_write_record (record, filename); 		//complete
	if (b.is_null) {
		init_bucket (&b, BUCKET_SIZE, 0);
	}
	b.position[b.count] = position;
	b.count++;
	if (b.count >= b.bucket_size) {
		b.overflow = new bucket;
		init_bucket (b.overflow, b.bucket_size, 0);
	}
	map<int, bucket>::iterator it;
	it = hash_table->find (index);
	it->second = b;
}

/*Busca y retorna registros que tengan la clave KEY.
 * En caso no exista ninguno, retorna NULL*/
record hash_search_record (int key, map<int, bucket> *hash_table, int bucket_size, const char *filename) {
	int index = hash_function (key, bucket_size);
	bucket b = find_bucket (index, hash_table);
	return hash_find_record (key, &b, filename);
}

void hash_store_index (const char *hash_table_filename, map<int, bucket> *hash_table) {
	map<int, bucket>::iterator it;
	ofstream file;
	file.open (hash_table_filename, ios::binary);
	file.seekp (0);
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
		/*int first = it->first;
		bucket *second = it->second;
		if (!second) {
			second = new bucket;
			second->is_null = true;
		}
		file.write ((char *) &first, sizeof (int));
		file.write ((char *) second, sizeof (bucket));*/
		file.write ((char *) &(*it), sizeof (pair<int, bucket>));
		file.flush ();
	}
	file.close ();
}

void print_hash_table (map<int, bucket > *hash_table) {
	map<int, bucket>::iterator it;
	for (it = hash_table->begin (); it != hash_table->end (); it++)
		cout << it->first << " " << it->second.position[0] << " " << it->second.count << endl;
}

vector<record> hash_get_all_records (const char *data_filename) {
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

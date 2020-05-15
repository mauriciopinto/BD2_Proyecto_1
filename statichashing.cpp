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
	b->is_null = false;
}

/* Escribe un registro y retorna su posicion */
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

/*Funcion hash. Retorna el modulo de key entre bucket_size.*/
int hash_function (int key, int bucket_size) {
	return key % bucket_size;
}

/* Busca y retorna el bucket correspondiente a un indice */
bucket find_bucket (int index, map<int, bucket> *hash_table) {
	map<int, bucket>::iterator it;
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
		if (index == it->first) {
			return it->second;
		}
	}
}

/* Busca un registro dentro de un bucket. */
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
	if (b->overflow_count > 0) {
		for (int i = 0; i < b->overflow_count; i++) {
			file.seekg (b->overflow[i]);
			file.read (buffer, sizeof (record));
			temp = (record *) buffer;
			if (temp->key == key)
				return *temp;
		}	
	}
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

	int position = hash_write_record (record, filename);
	if (b.is_null) {
		init_bucket (&b, BUCKET_SIZE, 0);
	}
	if (b.count >= 6) {
		b.overflow[b.overflow_count] = position;
		b.overflow_count++;
	}
	else {
		b.position[b.count] = position;
		b.count++;
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

/* Escribe el indice en memoria. */
void hash_store_index (const char *hash_table_filename, map<int, bucket> *hash_table) {
	map<int, bucket>::iterator it;
	ofstream file;
	file.open (hash_table_filename, ios::binary);
	file.seekp (0);
	for (it = hash_table->begin (); it != hash_table->end (); it++) {
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

/* Retorna todos los registros del archivo de datos */
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

/* Realiza una busqueda por rango. Ya que la data no esta ordenada, se lee secuencialmente
 * los registros. */
vector<record> hash_range_search (int s, int e, const char *data_filename) {
	ifstream file;
        file.open (data_filename, ios::binary);
        char buffer[sizeof (record)];
        record *temp;
        vector<record> records;

        file.seekg (sizeof(int));
        file.read (buffer, sizeof (record));
        while (!file.eof ()) {
                temp = (record *) buffer;
		if (temp->key > s && temp->key < e)
                	records.push_back (*temp);
                file.read (buffer, sizeof (record));
        }
        return records;
}

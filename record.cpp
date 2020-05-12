#include "record.h"

void init_record (record *r, int key, string value) {
	r->key = key;
	strcpy (r->value, value.c_str ());	
}

#ifndef RECORD_H
#define RECORD_H

#include <string>
#include <cstring>

using namespace std;

struct record {
	int key;
	char value[12];
};

void init_record (record *, int, string);
#endif

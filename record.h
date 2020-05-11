#include <string>
#include <cstring>

using namespace std;

struct record {
	int key;
	char value[12];
};

void init_record (record *, int, string);

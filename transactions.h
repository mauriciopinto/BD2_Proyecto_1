#ifndef BD2_PROYECTO_1_TRANSACTIONS_H
#define BD2_PROYECTO_1_TRANSACTIONS_H
#include <iostream>
#include <pthread.h>
#include <vector>
#include <mutex>
#include "statichashing.h"
#include "randomfile.h"
#include <cstring>

using namespace std;

enum operation { R, W };

struct transaction {
	int t_id;
	int index;
	const char *data_filename;
	const char *index_filename;
	int n_buckets;
	int bucket_size;
	operation op;
	record data;
};

void init_transaction (transaction *, int, int, const char *, const char *, int, int, operation, record);
void *run_transaction (void *);
void setup_transactions (vector<transaction>, vector<transaction>);
void parse_transactions (const char *, const char *, int);
#endif //BD2_PROYECTO_1_TRANSACTIONS_H

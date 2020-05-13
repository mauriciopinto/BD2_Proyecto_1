//#ifndef BD2_PROYECTO_1_TRANSACTIONS_H
//#define BD2_PROYECTO_1_TRANSACTIONS_H

//#endif //BD2_PROYECTO_1_TRANSACTIONS_H
#include <iostream>
#include <pthread.h>
#include <vector>
#include <mutex>
#include "record.h"

using namespace std;

enum operation { R, W };

struct transaction {
	int t_id;
	record resource;
	operation op;
};

void init_transaction (transaction *, int, record, operation);
void *run_transaction (void *);
void setup_transactions (vector<transaction>, int, vector<record>);

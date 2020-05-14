#include "transactions.h"
#include "parser.h"

vector<vector<transaction>> split_transactions (vector<transaction>, int);

vector<vector<transaction>> split_transactions (vector<transaction> transactions, int n_transactions) {
	vector<vector<transaction>> split_transactions (n_transactions);
	for (int i = 0; i < transactions.size (); i++) 
		split_transactions[transactions[i].t_id].push_back (transactions[i]);
	return split_transactions;
}

void init_transaction (transaction *t, int t_id, record resource, operation op) {
	t->t_id = t_id;
	t->resource = resource;
	t->op = op;
}

void *run_transactions (void *arg) {
	vector<transaction> input;
	input = *((vector<transaction> *) arg);
}

void setup_transactions (vector<transaction> transactions, int n_transactions) {
	pthread_t thread[n_transactions];
	vector<vector<transaction>> s_transactions = split_transactions (transactions, n_transactions);

	for (int i = 0; i < n_transactions; i++)
		pthread_create (&thread[i], nullptr, run_transactions, (void *) &s_transactions[i]);
	for (int i = 0; i < n_transactions; i++)
		pthread_join (thread[i], nullptr);	
}

#include "transactions.h"
#include "parser.h"

void parse_transactions (const char *, const char *, int index);
vector<transaction> get_transactions (const char *, int index, int t_id);
void *run_transactions (void *);
void run_operation (transaction);

mutex resource;

vector<transaction> get_transactions (const char *filename, int index, int t_id) {
	ifstream file;
	file.open (filename);
	string str;
	vector<string> input;
	transaction temp;
	vector<transaction> trans;

	while (getline (file, str)) {
		string ext1 = ".txt";
		string ext2 = "_index.txt";
		input = read (str);
		if (input[0] == "INSERT") {
			temp.op = W;
			record r;
			init_record (&r, stoi (input[4]), input[6]);
			temp.data = r;
			temp.data_filename = (input[2] + ".txt").c_str ();
                	temp.index_filename = (input[2] + "_index.txt").c_str ();
		}
		else {
			temp.op = R;
			temp.data_filename = (input[3] + ".txt").c_str ();
			temp.index_filename = (input[3] + "_index.txt").c_str ();
			record r;
			init_record (&r, stoi (input[7]), "");
			temp.data = r;
		}
		temp.n_buckets = 6;
		temp.bucket_size = 6;
		trans.push_back (temp);
	}
}

void parse_transactions (const char *file1, const char *file2, int index) {
	/*vector<transaction> t1 = get_transactions (file1, index, 1);
	vector<transaction> t2 = get_transactions (file2, index, 2);*/
	ifstream f1, f2;;
        f1.open (file1);
	f2.open (file2);
        string str;
        vector<string> input;
        transaction temp;
        vector<transaction> t1;
	vector<transaction> t2;

        while (getline (f1, str)) {
                input = read (str);
                if (input[0] == "INSERT") {
                        temp.op = W;
                        record r;
                        init_record (&r, stoi (input[4]), input[6]);
                        temp.data = r;
                        temp.data_filename = (input[2] + ".bin").c_str ();
                        temp.index_filename = (input[2] + "_index.bin").c_str ();
                }
                else {
                        temp.op = R;
                        temp.data_filename = (input[3] + ".bin").c_str ();
                        temp.index_filename = (input[3] + "_index.bin").c_str ();
                        record r;
                        init_record (&r, stoi (input[7]), "");
                        temp.data = r;
                }
		temp.t_id = 1;
                temp.n_buckets = 6;
                temp.bucket_size = 6;
		temp.index = 0;
                t1.push_back (temp);
        }
	while (getline (f2, str)) {
                input = read (str);
                if (input[0] == "INSERT") {
                        temp.op = W;
                        record r;
                        init_record (&r, stoi (input[4]), input[6]);
                        temp.data = r;
                        temp.data_filename = (input[2] + ".bin").c_str ();
                        temp.index_filename = (input[2] + "_index.bin").c_str ();
                }
                else {
                        temp.op = R;
                        temp.data_filename = (input[3] + ".bin").c_str ();
                        temp.index_filename = (input[3] + "_index.bin").c_str ();
                        record r;
                        init_record (&r, stoi (input[7]), "");
                        temp.data = r;
                }
                temp.t_id = 2;
                temp.n_buckets = 6;
                temp.bucket_size = 6;
		temp.index = index;
                t1.push_back (temp);
        }

	const int n_transactions = 2;
        pthread_t thread[n_transactions];

        pthread_create (&thread[0], nullptr, run_transactions, (void *) &t1);
        pthread_create (&thread[1], nullptr, run_transactions, (void *) &t2);

        pthread_join (thread[0], NULL);
        pthread_join (thread[1], NULL);
}

void run_operation (transaction input) {
	cout << "running transaction " << input.t_id << endl;

    string temp="running transaction: " + to_string(input.t_id)+"."+"\n";
    ofstream filelog;
    filelog.open("logfile.txt", ios::app);
    filelog<<(temp);
    filelog.flush();
    filelog.close();

	if (input.index == 0) {
                hash_file h_file (input.data_filename, input.index_filename, input.bucket_size, input.n_buckets);
                if (input.op == R) {
			cout << "reading" << endl;

			string temp="Reading\n";
			ofstream filelog;
			filelog.open("logfile.txt", ios::app);
			filelog<<(temp);
			filelog.flush();
			filelog.close();

			h_file.search_record (input.data.key);

		}
                else {
			resource.lock ();
			cout << "writing" << endl;

			string temp="Writing\n";
			ofstream filelog;
			filelog.open("logfile.txt", ios::app);
			filelog<<(temp);
			filelog.flush();
			filelog.close();

			h_file.add_record (&input.data);
			resource.unlock ();
		}
        }
        else {
                random_file r_file (input.data_filename, input.index_filename);
                if (input.op == R)
			r_file.search_record (input.data.key);
		else {
			resource.lock ();
			r_file.add_record (&input.data);
			resource.unlock ();
		}
        }
}

void init_transaction (transaction *t, int t_id, int index, const char *data_filename, const char *index_filename, 
		       int n_buckets, int bucket_size, operation op, record data) {
	t->t_id = t_id;
	t->index = index;
	t->data_filename = data_filename;
	t->index_filename = index_filename;
	t->n_buckets = n_buckets;
	t->bucket_size = bucket_size;
	t->op = op;
	t->data = data;
}

void *run_transactions (void *arg) {
	vector<transaction> input;
	input = *((vector<transaction> *) arg);
	for (int i = 0; i < input.size (); i++)
		run_operation (input[i]);	
}

void setup_transactions (vector<transaction> transaction1, vector<transaction> transaction2) {
	const int n_transactions = 2;
	pthread_t thread[n_transactions];

	pthread_create (&thread[0], nullptr, run_transactions, (void *) &transaction1);
	pthread_create (&thread[1], nullptr, run_transactions, (void *) &transaction2);

	pthread_join (thread[0], NULL);
	pthread_join (thread[1], NULL);	
}

#include "transactions.h"
#include "parser.h"

void parse_transactions (const char *, const char *, int index);
vector<transaction> get_transactions (const char *, int index, int t_id);
void *run_transactions (void *);
void run_operation (transaction);

/*Elemento de exclusion para el recurso compartido*/
mutex resource;

/*Recibe dos archivos, los adapta a vectores de transacciones y ejecuta un hilo
 * para cada secuencia. Originalmente esta funcion estaba dividida en varias, pero por problemas
 * al momento de ejecutar nos vimos forzados a unirlas en una sola.*/
void parse_transactions (const char *file1, const char *file2, int index) {
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
		temp.index = 0;
                t1.push_back (temp);
        }

	const int n_transactions = 2;
        pthread_t thread[n_transactions];

        pthread_create (&thread[0], nullptr, run_transactions, (void *) &t1);
        pthread_create (&thread[1], nullptr, run_transactions, (void *) &t2);

        pthread_join (thread[0], NULL);
        pthread_join (thread[1], NULL);
}

/* Ejecuta una operacion en particular. Dependiendo de los atributos de la transaccion,
 * decide que funcion ejecutar. */
void run_operation (transaction input) {
	cout << "running transaction " << input.t_id << endl;
	if (input.index == 0) {
                hash_file h_file (input.data_filename, input.index_filename, input.bucket_size, input.n_buckets);
                if (input.op == R) {
			cout << "reading" << endl;
                        h_file.search_record (input.data.key);
		}
                else {
			resource.lock ();
			cout << "writing" << endl;
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

/* Constructor de la estructura transaction */
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

/* Funcion que corre cada thread y que ejecuta cada operacion de la secuencia */
void *run_transactions (void *arg) {
	vector<transaction> input;
	input = *((vector<transaction> *) arg);
	for (int i = 0; i < input.size (); i++)
		run_operation (input[i]);	
}

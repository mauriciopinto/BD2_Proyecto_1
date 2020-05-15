#include <iostream>
//#include "ui/mainwindow.h"
//#include "ui/input.h"
//#include <QApplication>
#include "transactions.h"
#include "parser.h"
#include <chrono>
using namespace std;


int main(int argc, char *argv[]){
    /*QApplication a(argc, argv);
    MainWindow w;
    input x;
    w.show();
    x.show();
    return a.exec();*/
    auto start = chrono::steady_clock::now ();
    string prueba="Select * from Hash where key = 37";
    //string prueba="Create Hash Index Hash";
    //string prueba="Insert Into Hash ( 37 , roxel )";
    vector<string> test=read(prueba);
    printvector(test);
    determinefunction(test);
    auto end = chrono::steady_clock::now ();

    cout << chrono::duration_cast<chrono::nanoseconds>(end - start).count () << "ns" << endl;
	//const char *filename1 = "transaction1.txt";
	//const char *filename2 = "transaction2.txt";
	
	/*transaction *t1, *t2, *t3, *t4, *t5;
	t1 = new transaction;
	t2 = new transaction;
	t3 = new transaction;
	t4 = new transaction;
	t5 = new transaction;*/
	/*record *r1, *r2, *r3, *r4, *r5;
	r1 = new record;
	r2 = new record;
	r3 = new record;
	r4 = new record;
	r5 = new record;
	init_record (r1, 1, "mauricio");
	init_record (r2, 2, "jonathan");
	init_record (r3, 1, "mauricio");
	init_record (r4, 3, "francesco");
	init_record (r5, 2, "jonathan");*/
	/*init_transaction (t1, 1, 0, "TEST.bin", "TEST_index.bin", 6, 6, W, *r1);
	init_transaction (t2, 2, 0, "TEST.bin", "TEST_index.bin", 6, 6, W, *r2);
	init_transaction (t3, 1, 0, "TEST.bin", "TEST_index.bin", 6, 6, R, *r3);
	init_transaction (t4, 2, 0, "TEST.bin", "TEST_index.bin", 6, 6, W, *r4);
	init_transaction (t5, 1, 0, "TEST.bin", "TEST_index.bin", 6, 6, R, *r5);*/

	/*vector<transaction> T1;
	vector<transaction> T2;
	T1.push_back (*t1);
	T2.push_back (*t2);
	T1.push_back (*t3);
	T2.push_back (*t4);
	T1.push_back (*t5);
	vector<vector<transaction>> all;
	all.push_back (T1);
	all.push_back (T2);*/
	//parse_transactions (filename1, filename2, 0);
	//hash_file h ("test.bin", "test_index.bin", 6, 6);
	/*h.add_record (r1);
	h.add_record (r2);
	record p = h.search_record (2);
	cout << p.key << " " << p.value << endl;*/
	//h.add_record ();
	return 0;
}

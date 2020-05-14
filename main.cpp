/*
#include <iostream>
#include "parser.h"
#include "randomfile.h"
#include "statichashing.h"

using namespace std;


int main(){
    //string prueba="Create Test2 Index hash";
    //string prueba="Insert Into Test2 ( 1 , Mauricio )";
    string prueba="Select * from TEST where key = 1";
    vector<string> test=read(prueba);
    printvector(test);
    determinefunction(test);
}

    */
#include "ui/mainwindow.h"
#include "input.h"
#include <QApplication>

    int main(int argc, char *argv[])
    {
        QApplication a(argc, argv);
        MainWindow w;
        input x;

        w.show();
        x.show();
        return a.exec();
    }


#include <iostream>
#include "parser.h"
#include "randomfile.h"
#include "statichashing.h"
#include "ui/mainwindow.h"
#include "ui/input.h"
#include <QApplication>

using namespace std;


int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    MainWindow w;
    input x;
    w.show();
    x.show();
    return a.exec();
}


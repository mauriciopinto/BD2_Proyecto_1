#include <iostream>
#include "ui/input.h"
#include <QApplication>

using namespace std;

int main(int argc, char *argv[]){
    QApplication a(argc, argv);
    input x;
    x.show();
    return a.exec();
}

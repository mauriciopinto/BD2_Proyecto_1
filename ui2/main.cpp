#include "mainwindow.h"
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

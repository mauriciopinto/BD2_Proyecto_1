#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QtDebug>

MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
{
    ui->setupUi(this);


}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::on_pushButton_clicked()
{
       QString data;
       QFile file( "/Users/jonathanprieto/Documents/GitHub/BD2_Proyecto_1/cmake-build-debug/outputcsv.csv");
       QStringList listA;
       int row = 0;

       if (file.open(QIODevice::ReadOnly)){
           ui->tableWidget->removeColumn(1);
           ui->tableWidget->removeColumn(0);
           qDebug()<<ui->tableWidget->rowCount();
           for (int i = 0; i <= ui->tableWidget->rowCount(); i++) {
               ui->tableWidget->removeRow(i);
           }

           while (!file.atEnd()){
           QString line = file.readLine();
           listA = line.split(",");
           ui->tableWidget->setColumnCount(listA.size());
           ui->tableWidget->insertRow(row);

           for (int x = 0; x < listA.size(); x++){
               qDebug()<<listA.at(x);
               QTableWidgetItem *test = new QTableWidgetItem(listA.at(x));
               ui->tableWidget->setItem(row, x, test);

        }
           row++;
       }

    }
       //para tener en la pantalla las operaciones
       ui->logg->insertHtml("load table");
       file.close();

}

void MainWindow::printmessage(string mensaje) {
    QString str=QString::fromStdString(mensaje);
    ui->logg->insertHtml(str);
}

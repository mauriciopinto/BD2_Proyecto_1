#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFile>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>

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
       QFile file( "C:\\Users\\Usuario\\Documents\\nuevointento\\test.csv");
       QStringList listA;
       int row = 0;
       if (file.open(QIODevice::ReadOnly)){
           while (!file.atEnd()){
           QString line = file.readLine();
           listA = line.split(";");
           ui->tableWidget->setColumnCount(listA.size());
           ui->tableWidget->insertRow(row);

           for (int x = 0; x < listA.size(); x++){

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

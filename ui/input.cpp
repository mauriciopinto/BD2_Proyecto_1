#include "input.h"
#include "ui_input.h"
#include "parser.h"

#include <QFile>
#include <QString>
#include <QStringList>
#include <QFileDialog>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QMessageBox>
#include <QtDebug>

input::input(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::input)
{
    ui->setupUi(this);
}

input::~input()
{
    delete ui;
}

void input::on_lineEdit_editingFinished()
{


}

void input::on_pushButton_clicked()
{
    QFile filelog( "/Users/jonathanprieto/Documents/GitHub/BD2_Proyecto_1/cmake-build-debug/logfile.txt");
    filelog.open(QIODevice::ReadOnly);
    QTextStream datalog(&filelog);

    QString str = ui->lineEdit->text();
    std::string utf8_text = str.toUtf8().constData();
    qDebug() << str;

    //string prueba="Create Test2 Index hash";
    //string prueba="Insert Into Test2 ( 2 , Jonathan )";
    //string prueba="Select * from TEST where key = 1";
    vector<string> test=read(str.toStdString());
    printvector(test);
    determinefunction(test);

    QString data;
    QFile file( "/Users/jonathanprieto/Documents/GitHub/BD2_Proyecto_1/cmake-build-debug/outputcsv.csv");
    QStringList listA;
    int row = 0;

    if (file.open(QIODevice::ReadOnly)){
        ui->tableWidget->removeColumn(1);
        ui->tableWidget->removeColumn(0);
        //qDebug()<<ui->tableWidget->rowCount();
        for (int i = 0; i <= ui->tableWidget->rowCount(); i++) {
            ui->tableWidget->removeRow(i);
        }

        while (!file.atEnd()){
            QString line = file.readLine();
            listA = line.split(",");
            ui->tableWidget->setColumnCount(listA.size());
            ui->tableWidget->insertRow(row);

            for (int x = 0; x < listA.size(); x++){
                //qDebug()<<listA.at(x);
                QTableWidgetItem *test = new QTableWidgetItem(listA.at(x));
                ui->tableWidget->setItem(row, x, test);

            }
            row++;
        }

    }
    file.close();

    ui->logg1->insertHtml(datalog.readAll());
    filelog.close();
}

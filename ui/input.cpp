#include "input.h"
#include "ui_input.h"
#include "parser.h"
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
    QString str = ui->lineEdit->text();
    std::string utf8_text = str.toUtf8().constData();
    qDebug() << str;

    //string prueba="Create Test2 Index hash";
    //string prueba="Insert Into Test2 ( 2 , Jonathan )";
    //string prueba="Select * from TEST where key = 1";
    vector<string> test=read(str.toStdString());
    printvector(test);
    determinefunction(test);
}

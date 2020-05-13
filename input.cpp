#include "input.h"
#include "ui_input.h"
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
    QString str = ui->lineEdit->text();
    std::string utf8_text = str.toUtf8().constData();
    qDebug() << str;


}

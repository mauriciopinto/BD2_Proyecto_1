#ifndef INPUT_H
#define INPUT_H

#include <QDialog>

namespace Ui {
class input;
}

class input : public QDialog
{
    Q_OBJECT

public:
    explicit input(QWidget *parent = nullptr);
    ~input();

public slots:
    void on_lineEdit_editingFinished();

    void on_pushButton_clicked();

private:
    Ui::input *ui;
};

#endif // INPUT_H

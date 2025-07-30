#ifndef LIEU_H
#define LIEU_H

#include <QDialog>

namespace Ui {
class lieu;
}

class lieu : public QDialog
{
    Q_OBJECT

public:
    explicit lieu(QWidget *parent = nullptr);
    ~lieu();

private:
    Ui::lieu *ui;
};

#endif // LIEU_H

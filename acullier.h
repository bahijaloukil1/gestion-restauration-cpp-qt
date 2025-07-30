#ifndef ACULLIER_H
#define ACULLIER_H

#include <QDialog>


namespace Ui {
class Acullier;
}

class Acullier : public QDialog

{
    Q_OBJECT

public:
    explicit Acullier(QWidget *parent = nullptr);
    ~Acullier();

private:
    Ui::Acullier *ui;
};

#endif // ACULLIER_H

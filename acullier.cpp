#include "acullier.h"
#include "ui_acullier.h"

Acullier::Acullier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Acullier)

{
    ui->setupUi(this);
}

Acullier::~Acullier()
{
    delete ui;
}

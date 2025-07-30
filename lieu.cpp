#include "lieu.h"
#include "ui_lieu.h"

lieu::lieu(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::lieu)
{
    ui->setupUi(this);
}

lieu::~lieu()
{
    delete ui;
}

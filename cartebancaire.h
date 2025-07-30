#ifndef CARTEBANCAIRE_H
#define CARTEBANCAIRE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QLineEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QMessageBox>

class carteBancaire : public QDialog
{
    Q_OBJECT

public:
    explicit carteBancaire(QWidget *parent = nullptr);
    ~carteBancaire();

private slots:
    void validerPaiement();
    void annulerPaiement();

private:
    QSqlDatabase m_db;

    QLineEdit *nomClientEdit;
    QLineEdit *numeroCarteEdit;
    QLineEdit *dateExpirationEdit;
    QLineEdit *cvvEdit;
    QLineEdit *montantEdit;

    QPushButton *validerButton;
    QPushButton *annulerButton;

    bool initDatabase();
};

#endif // CARTEBANCAIRE_H

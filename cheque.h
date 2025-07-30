// #ifndef CHEQUE_H
// #define CHEQUE_H

// #include <QDialog>

// namespace Ui {
// class cheque;
// }

// class cheque : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit cheque(QWidget *parent = nullptr);
//     ~cheque();

// private:
//     Ui::cheque *ui;
// };

// #endif // CHEQUE_H





// #ifndef CHEQUE_H
// #define CHEQUE_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>  // Ajoutez cette ligne
// #include <QMessageBox>
// #include <QDoubleValidator>
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QLabel>
// #include <QLineEdit>

// class cheque : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit cheque(int commandeId, QWidget *parent = nullptr);
//     ~cheque();

// private slots:
//     void validerPaiement();
//     void annulerPaiement();

// private:
//     QSqlDatabase m_db;
//     int m_commandeId;
//     double m_montantTotal;

//     // Widgets
//     QLabel *montantLabel;
//     QLabel *numeroChequeLabel;
//     QLineEdit *numeroChequeEdit;
//     QLabel *banqueLabel;
//     QLineEdit *banqueEdit;
//     QPushButton *validerButton;
//     QPushButton *annulerButton;
//     // Ajoutez cette déclaration
//     bool initDatabase();
//     void setupUI();
//     void chargerMontantCommande();
//     bool enregistrerPaiement();
// };

// #endif // CHEQUE_H






#ifndef CHEQUE_H
#define CHEQUE_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>
#include <QDoubleValidator>
#include <QPushButton>
#include <QVBoxLayout>
#include <QLabel>
#include <QLineEdit>

class cheque : public QDialog
{
    Q_OBJECT

public:
    explicit cheque(int commandeId, QWidget *parent = nullptr);
    ~cheque();

private slots:
    void validerPaiement();
    void annulerPaiement();

private:
    QSqlDatabase m_db;
    int m_commandeId;
    double m_montantTotal;

    // Widgets
    QLabel *montantLabel;
    QLabel *numeroChequeLabel;
    QLineEdit *numeroChequeEdit;
    QLabel *banqueLabel;
    QLineEdit *banqueEdit;
    QPushButton *validerButton;
    QPushButton *annulerButton;

    bool initDatabase();
    void setupUI();
    void chargerMontantCommande();
    bool enregistrerPaiement();
};

#endif // CHEQUE_H

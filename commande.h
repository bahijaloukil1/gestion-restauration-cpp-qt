// #ifndef COMMANDE_H
// #define COMMANDE_H

// #include <QDialog>
// #include <QPushButton>
// #include <QLabel>
// #include <QLineEdit>
// #include <QFormLayout>
// #include <QDialogButtonBox>
// #include <QVBoxLayout>
// #include <QMessageBox>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>
// #include <QGroupBox>
// #include <QHBoxLayout>
// #include <QFrame>
// #include <Qt>
// #include <QCoreApplication>
// #include <QIntValidator>    // Ajout pour les validateurs
// #include <QDoubleValidator> // Ajout pour les validateurs
// #include <QRegularExpressionValidator>

// class commande : public QDialog
// {
//     Q_OBJECT

// public:
//     commande(QWidget *parent = nullptr);
//     ~commande();

// private slots:
//     void ajouterCommande();
//     void afficherCommandes();

// private:
//     void setupUI();
//     void setupDatabase();
//     void createClientForm();
//     void createCommandeForm();

//     QVBoxLayout *mainLayout;
//     QFormLayout *clientFormLayout;
//     QFormLayout *commandeFormLayout;

//     // Champs client
//     QLineEdit *nomLineEdit;
//     QLineEdit *prenomLineEdit;
//     QLineEdit *adresseLineEdit;
//     QLineEdit *telephoneLineEdit;
//     QLineEdit *emailLineEdit;

//     // Champs commande
//     QLineEdit *produitLineEdit;
//     QLineEdit *quantiteLineEdit;
//     QLineEdit *prixLineEdit;

//     QPushButton *ajouterButton;
//     QPushButton *afficherButton;

//     QLabel *resultLabel;

//     QSqlDatabase db;
// };

// #endif // COMMANDE_H







#ifndef COMMANDE_H
#define COMMANDE_H

#include <QDialog>
#include <QIntValidator>
#include <QDoubleValidator>
#include <QPushButton>
#include <QLabel>
#include <QLineEdit>
#include <QFormLayout>
#include <QDialogButtonBox>
#include <QVBoxLayout>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QGroupBox>
#include <QHBoxLayout>
#include <QFrame>
#include <Qt>
#include <QCoreApplication>

class commande : public QDialog
{
    Q_OBJECT

public:
    commande(QWidget *parent = nullptr);
    ~commande();

private slots:
    void ajouterCommande();
    void afficherCommandes();

private:
    void setupUI();
    void setupDatabase();
    void createClientForm();
    void createCommandeForm();

    QVBoxLayout *mainLayout;
    QFormLayout *clientFormLayout;
    QFormLayout *commandeFormLayout;

    QLineEdit *nomLineEdit;
    QLineEdit *prenomLineEdit;
    QLineEdit *adresseLineEdit;
    QLineEdit *telephoneLineEdit;
    QLineEdit *emailLineEdit;

    QLineEdit *produitLineEdit;
    QLineEdit *quantiteLineEdit;
    QLineEdit *prixLineEdit;

    QPushButton *ajouterButton;
    QPushButton *afficherButton;

    QLabel *resultLabel;

    QSqlDatabase db;
};

#endif // COMMANDE_H

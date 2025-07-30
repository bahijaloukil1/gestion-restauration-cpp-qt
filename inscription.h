#ifndef INSCRIPTION_H
#define INSCRIPTION_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Connexion;
class Acculier;  // Ajout de la déclaration anticipée

namespace Ui {
class inscription;
}

class Inscription : public QDialog
{
    Q_OBJECT

public:
    explicit Inscription(QWidget *parent = nullptr);
    ~Inscription();

private slots:
    void validerInscription();

private:
    Ui::inscription *ui;
    Connexion *connexionWindow;
    Acculier *acculierWindow;  // Changement du nom de la variable
};

#endif // INSCRIPTION_H

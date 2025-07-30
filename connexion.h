#ifndef CONNEXION_H
#define CONNEXION_H

#include <QDialog>
#include <QMessageBox>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>

class Inscription;
class Acculier;  // Ajout de la déclaration anticipée

namespace Ui {
class connexion;
}

class Connexion : public QDialog
{
    Q_OBJECT

public:
    explicit Connexion(QWidget *parent = nullptr);
    ~Connexion();

private slots:
    void on_pushButton_4_clicked(); // Bouton Login
    void on_pushButton_6_clicked(); // Bouton Inscription

private:
    Ui::connexion *ui;
    Inscription *inscriptionWindow = nullptr;
    Acculier *acculierWindow = nullptr;  // Changement du nom de la variable
    QSqlDatabase db;

    bool initDatabase();
    bool validateUser(const QString &email, const QString &password);
};

#endif // CONNEXION_H

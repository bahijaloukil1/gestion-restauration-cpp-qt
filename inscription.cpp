#include "inscription.h"
#include "ui_inscription.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>

Inscription::Inscription(QWidget *parent) :
   QDialog(parent),
   ui(new Ui::Inscription)
{
   ui->setupUi(this);
    connect(ui->pushButtonInscription, &QPushButton::clicked, this, &Inscription::onInscriptionClicked);
}

Inscription::~Inscription()
{
   delete ui;
}

void Inscription::onInscriptionClicked()
{
    // Exemple de logique d'inscription
    QString email = ui->lineEdit_3->text();
    QString mot_de_passe = ui->lineEdit_4->text();

    if (email.isEmpty() || mot_de_passe.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs.");
        return;
    }

    QSqlQuery query;
    query.prepare("INSERT INTO utilisateur (email, mot_de_passe) VALUES (?, ?)");
    query.addBindValue(email);
    query.addBindValue(mot_de_passe);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "L'inscription a échoué : " + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Inscription réussie !");
        this->accept(); // Ferme la boîte de dialogue
    }
}


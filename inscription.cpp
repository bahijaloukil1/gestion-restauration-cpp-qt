#include "inscription.h"
#include "ui_inscription.h"
#include "connexion.h"
#include "acculier.h"
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include <QMessageBox>

Inscription::Inscription(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::inscription),
    connexionWindow(nullptr),
    acculierWindow(nullptr)
{
    ui->setupUi(this);
    setWindowTitle("Inscription");

    // Configuration des QLineEdit
    ui->lineEdit->setPlaceholderText("Entrez votre nom");
    ui->lineEdit->setFocus();
    ui->lineEdit_2->setPlaceholderText("Entrez votre prénom");
    ui->lineEdit_3->setPlaceholderText("email@exemple.com");
    ui->lineEdit_4->setPlaceholderText("Mot de passe");
    ui->lineEdit_4->setEchoMode(QLineEdit::Password);

    // Connexion des signaux returnPressed
    connect(ui->lineEdit, &QLineEdit::returnPressed, [this]() {
        ui->lineEdit_2->setFocus();
    });
    connect(ui->lineEdit_2, &QLineEdit::returnPressed, [this]() {
        ui->lineEdit_3->setFocus();
    });
    connect(ui->lineEdit_3, &QLineEdit::returnPressed, [this]() {
        ui->lineEdit_4->setFocus();
    });
    connect(ui->lineEdit_4, &QLineEdit::returnPressed, this, &Inscription::validerInscription);

    // Style des champs
    QString style = "QLineEdit { border: 2px solid rgba(253, 128, 253, 0.911); }"
                    "QLineEdit:focus { border: 2px solid rgb(222, 66, 159); }";
    ui->lineEdit->setStyleSheet(style);
    ui->lineEdit_2->setStyleSheet(style);
    ui->lineEdit_3->setStyleSheet(style);
    ui->lineEdit_4->setStyleSheet(style);

    // Connecter le label Sign Up
    connect(ui->label_9, &QLabel::linkActivated, this, &Inscription::validerInscription);
}

Inscription::~Inscription()
{
    delete ui;
    if (connexionWindow) {
        delete connexionWindow;
    }
    if (acculierWindow) {
        delete acculierWindow;
    }
}

void Inscription::validerInscription()
{
    QString nom = ui->lineEdit->text();
    QString prenom = ui->lineEdit_2->text();
    QString email = ui->lineEdit_3->text();
    QString password = ui->lineEdit_4->text();

    if (nom.isEmpty() || prenom.isEmpty() || email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    // Connexion à la base de données
    QSqlDatabase db = QSqlDatabase::database();
    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Base de données indisponible");
        return;
    }

    // Insertion dans la base de données
    QSqlQuery query;
    query.prepare("INSERT INTO users (email, password, firstname, lastname) "
                  "VALUES (:email, :password, :firstname, :lastname)");
    query.bindValue(":email", email);
    query.bindValue(":password", password);
    query.bindValue(":firstname", prenom);
    query.bindValue(":lastname", nom);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de l'inscription: " + query.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Inscription réussie !");
    this->hide();
    acculierWindow = new Acculier();
    acculierWindow->show();
}

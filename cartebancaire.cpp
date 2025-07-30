#include "cartebancaire.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QRegularExpression>
#include <QDebug>

carteBancaire::carteBancaire(QWidget *parent)
    : QDialog(parent)
{
    setWindowTitle("Paiement par Carte Bancaire");
    setMinimumSize(400, 300);

    // Création des champs
    nomClientEdit = new QLineEdit(this);
    numeroCarteEdit = new QLineEdit(this);
    dateExpirationEdit = new QLineEdit(this);
    cvvEdit = new QLineEdit(this);
    montantEdit = new QLineEdit(this);

    // Configuration des champs
    numeroCarteEdit->setPlaceholderText("1234 5678 9012 3456");
    numeroCarteEdit->setInputMask("9999 9999 9999 9999;_");
    dateExpirationEdit->setPlaceholderText("MM/AA");
    dateExpirationEdit->setInputMask("99/99;_");
    cvvEdit->setPlaceholderText("123");
    cvvEdit->setEchoMode(QLineEdit::Password);
    cvvEdit->setMaxLength(4);
    montantEdit->setPlaceholderText("Ex: 49.99");

    // Mise en page du formulaire
    QFormLayout *formLayout = new QFormLayout();
    formLayout->addRow("Nom du client:", nomClientEdit);
    formLayout->addRow("Numéro de carte:", numeroCarteEdit);
    formLayout->addRow("Date d'expiration (MM/AA):", dateExpirationEdit);
    formLayout->addRow("Code de sécurité (CVV):", cvvEdit);
    formLayout->addRow("Montant (€):", montantEdit);

    // Boutons
    validerButton = new QPushButton("Valider le paiement", this);
    annulerButton = new QPushButton("Annuler", this);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(validerButton);
    mainLayout->addWidget(annulerButton);

    setLayout(mainLayout);

    // Connexions
    connect(validerButton, &QPushButton::clicked, this, &carteBancaire::validerPaiement);
    connect(annulerButton, &QPushButton::clicked, this, &carteBancaire::annulerPaiement);

    // Initialisation de la base de données
    if (!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données.");
    }
}

carteBancaire::~carteBancaire()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

bool carteBancaire::initDatabase()
{
    if (QSqlDatabase::contains("qt_sql_default_connection")) {
        m_db = QSqlDatabase::database("qt_sql_default_connection");
    } else {
        m_db = QSqlDatabase::addDatabase("QSQLITE");
        m_db.setDatabaseName("gestion_restaurant.db");
    }

    if (!m_db.open()) {
        qDebug() << "Erreur de connexion à la base de données :" << m_db.lastError().text();
        return false;
    }

    // Vérifier si la table existe, sinon la créer
    QSqlQuery query;
    if (!query.exec("CREATE TABLE IF NOT EXISTS paiements_carte ("
                    "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                    "nom_client TEXT NOT NULL, "
                    "numero_carte TEXT NOT NULL, "
                    "date_expiration TEXT NOT NULL, "
                    "cvv TEXT NOT NULL, "
                    "montant REAL NOT NULL, "
                    "date_paiement TIMESTAMP DEFAULT CURRENT_TIMESTAMP)")) {
        qDebug() << "Erreur création table :" << query.lastError().text();
        return false;
    }

    return true;
}

void carteBancaire::validerPaiement()
{
    QString nom = nomClientEdit->text().trimmed();
    QString carte = numeroCarteEdit->text().trimmed().replace(" ", "");
    QString date = dateExpirationEdit->text().trimmed();
    QString cvv = cvvEdit->text().trimmed();
    QString montant = montantEdit->text().trimmed();

    // Validation des champs
    if (nom.isEmpty() || carte.isEmpty() || date.isEmpty() || cvv.isEmpty() || montant.isEmpty()) {
        QMessageBox::warning(this, "Champs manquants", "Veuillez remplir tous les champs.");
        return;
    }

    // Validation du numéro de carte (16 chiffres)
    QRegularExpression carteRegex("^\\d{16}$");
    if (!carteRegex.match(carte).hasMatch()) {
        QMessageBox::warning(this, "Numéro invalide", "Le numéro de carte doit contenir 16 chiffres.");
        return;
    }

    // Validation de la date (MM/AA)
    QRegularExpression dateRegex("^(0[1-9]|1[0-2])\\/(\\d{2})$");
    if (!dateRegex.match(date).hasMatch()) {
        QMessageBox::warning(this, "Date invalide", "Format de date invalide (MM/AA attendu).");
        return;
    }

    // Validation du CVV (3 ou 4 chiffres)
    QRegularExpression cvvRegex("^\\d{3,4}$");
    if (!cvvRegex.match(cvv).hasMatch()) {
        QMessageBox::warning(this, "CVV invalide", "Le code de sécurité doit contenir 3 ou 4 chiffres.");
        return;
    }

    // Validation du montant
    bool ok;
    double montantValue = montant.toDouble(&ok);
    if (!ok || montantValue <= 0) {
        QMessageBox::warning(this, "Montant invalide", "Veuillez saisir un montant valide.");
        return;
    }

    // Masquer les données sensibles pour l'insertion
    QString carteMasquee = carte.left(4) + QString("XXXXXXXX") + carte.right(4);
    QString cvvMasque = QString(cvv.length(), '*');

    QSqlQuery query;
    query.prepare("INSERT INTO paiements_carte (nom_client, numero_carte, date_expiration, cvv, montant) "
                  "VALUES (:nom, :carte, :date, :cvv, :montant)");
    query.bindValue(":nom", nom);
    query.bindValue(":carte", carteMasquee);
    query.bindValue(":date", date);
    query.bindValue(":cvv", cvvMasque);
    query.bindValue(":montant", montantValue);

    if (!query.exec()) {
        qDebug() << "Erreur SQL:" << query.lastError().text();
        qDebug() << "Requête:" << query.lastQuery();
        QMessageBox::critical(this, "Erreur", "Le paiement n'a pas pu être enregistré.\n" + query.lastError().text());
    } else {
        QMessageBox::information(this, "Succès", "Paiement effectué avec succès!");
        accept();
    }
}

void carteBancaire::annulerPaiement()
{
    reject();
}

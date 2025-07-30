#include "connexion.h"
#include "ui_connexion.h"
#include "inscription.h"
#include "acculier.h"

#include <QPixmap>
#include <QDebug>
#include <QDir>
#include <QMessageBox>

Connexion::Connexion(QWidget *parent)
    : QDialog(parent),
    ui(new Ui::connexion),
    inscriptionWindow(nullptr),
    acculierWindow(nullptr),
    db(QSqlDatabase::addDatabase("QSQLITE"))
{
    ui->setupUi(this);
    setWindowTitle("Connexion");

    // Appliquer le style avec l'image de fond
    this->setStyleSheet(
        "QDialog {"
        "   background-image: url(:/images/background.png);"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   background-size: cover;"
        "}"
        "QFrame {"
        "   background-color: rgba(255, 255, 255, 0.85);"
        "   border-radius: 12px;"
        "   border: 1px solid rgb(18, 19, 56);"
        "}"
        );

    if (!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'initialiser la base de données");
    }

    // Chargement du logo
    QPixmap logo(":image/image5.jpg");
    if (!logo.isNull() && ui->frame_2) {
        ui->label->setVisible(false);
        ui->label_2->setVisible(false);

        QLabel *imgLabel = new QLabel(ui->frame_2);
        imgLabel->setObjectName("imgLogo");

        int margin = 20;
        imgLabel->setGeometry(
            margin,
            margin,
            ui->frame_2->width() - 2 * margin,
            ui->frame_2->height() - 2 * margin
            );

        imgLabel->setStyleSheet(
            "QLabel {"
            "   background: transparent;"
            "   border: none;"
            "}"
            );
        imgLabel->setAlignment(Qt::AlignCenter);

        logo = logo.scaled(
            imgLabel->width(),
            imgLabel->height(),
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            );

        imgLabel->setPixmap(logo);
        imgLabel->raise();
    } else {
        qDebug() << "Erreur: Impossible de charger l'image depuis les ressources Qt";
        ui->label->setVisible(true);
        ui->label_2->setVisible(true);
    }
}

Connexion::~Connexion()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;

    if (inscriptionWindow) {
        delete inscriptionWindow;
    }

    if (acculierWindow) {
        delete acculierWindow;
    }
}

bool Connexion::initDatabase()
{
    QString dbPath = QDir::currentPath() + "/restaurant.db";
    db.setDatabaseName(dbPath);

    if (!db.open()) {
        qDebug() << "Erreur DB:" << db.lastError().text();
        return false;
    }

    QSqlQuery query;
    QString createTable = "CREATE TABLE IF NOT EXISTS users ("
                          "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                          "email TEXT UNIQUE NOT NULL, "
                          "password TEXT NOT NULL, "
                          "firstname TEXT, "
                          "lastname TEXT)";

    if (!query.exec(createTable)) {
        qDebug() << "Erreur création table:" << query.lastError().text();
        return false;
    }

    return true;
}

bool Connexion::validateUser(const QString &email, const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT * FROM users WHERE email = :email AND password = :password");
    query.bindValue(":email", email);
    query.bindValue(":password", password);

    if (!query.exec()) {
        qDebug() << "Erreur requête:" << query.lastError().text();
        return false;
    }

    return query.next();
}

void Connexion::on_pushButton_4_clicked() // Bouton Login
{
    QString email = ui->lineEdit->text();
    QString password = ui->lineEdit_2->text();

    if (email.isEmpty() || password.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    if (!db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Base de données indisponible");
        return;
    }

    if (validateUser(email, password)) {
        QMessageBox::information(this, "Succès", "Connexion réussie !");
        this->hide();
        acculierWindow = new Acculier();
        acculierWindow->show();
    } else {
        QMessageBox::warning(this, "Erreur", "Email ou mot de passe incorrect");
    }
}

void Connexion::on_pushButton_6_clicked() // Bouton Inscription
{
    this->hide();
    inscriptionWindow = new Inscription();
    inscriptionWindow->show();
}

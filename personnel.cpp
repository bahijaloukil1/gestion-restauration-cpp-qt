// #include "personnel.h"
// #include <QSqlQuery>
// #include <QMessageBox>
// #include <QGroupBox>
// #include <QSqlError>
// #include <QHBoxLayout>
// #include <QDebug>
// #include <QRegularExpression>

// personnel::personnel(int userId, QWidget *parent) :
//     QDialog(parent),
//     m_userId(userId),
//     m_originalEmail("")
// {
//     setWindowTitle("Mon Espace Personnel");
//     resize(600, 400);

//     // Initialisation des widgets
//     emailEdit = new QLineEdit(this);
//     prenomEdit = new QLineEdit(this);
//     nomEdit = new QLineEdit(this);
//     currentPassEdit = new QLineEdit(this);
//     newPassEdit = new QLineEdit(this);
//     confirmPassEdit = new QLineEdit(this);

//     currentPassEdit->setEchoMode(QLineEdit::Password);
//     newPassEdit->setEchoMode(QLineEdit::Password);
//     confirmPassEdit->setEchoMode(QLineEdit::Password);

//     // Configuration de l'interface
//     setupUI();

//     // Connexion à la base de données
//     if (!connecterBaseDeDonnees()) {
//         QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
//         return;
//     }

//     // Chargement du profil
//     chargerProfil();
//     toggleEditMode(false);
// }

// personnel::~personnel()
// {
//     if (m_db.isOpen()) {
//         m_db.close();
//     }
// }

// void personnel::setupUI()
// {
//     QVBoxLayout *mainLayout = new QVBoxLayout(this);

//     // Groupe informations personnelles
//     QGroupBox *infoGroup = new QGroupBox("Mes informations", this);
//     QFormLayout *formLayout = new QFormLayout(infoGroup);

//     formLayout->addRow("Email:", emailEdit);
//     formLayout->addRow("Prénom:", prenomEdit);
//     formLayout->addRow("Nom:", nomEdit);

//     // Groupe mot de passe
//     QGroupBox *passGroup = new QGroupBox("Changement de mot de passe", this);
//     QFormLayout *passLayout = new QFormLayout(passGroup);

//     passLayout->addRow("Mot de passe actuel:", currentPassEdit);
//     passLayout->addRow("Nouveau mot de passe:", newPassEdit);
//     passLayout->addRow("Confirmer mot de passe:", confirmPassEdit);

//     // Ajout des groupes au layout principal
//     mainLayout->addWidget(infoGroup);
//     mainLayout->addWidget(passGroup);
//     mainLayout->addLayout(creerBoutons());

//     setLayout(mainLayout);
//     // Charger et appliquer l'image de fond
//     QPixmap background(":/background/img30.jpg"); // Chemin vers votre image dans les ressources
//     background = background.scaled(this->size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

//     QPalette palette;
//     palette.setBrush(QPalette::Window, background);
//     this->setPalette(palette);
// }

// QHBoxLayout* personnel::creerBoutons()
// {
//     QHBoxLayout *boutonsLayout = new QHBoxLayout();

//     modifierBtn = new QPushButton("Modifier mon profil", this);
//     sauvegarderBtn = new QPushButton("Sauvegarder", this);
//     annulerBtn = new QPushButton("Annuler", this);
//     changerPassBtn = new QPushButton("Changer mot de passe", this);

//     boutonsLayout->addWidget(modifierBtn);
//     boutonsLayout->addWidget(sauvegarderBtn);
//     boutonsLayout->addWidget(annulerBtn);
//     boutonsLayout->addWidget(changerPassBtn);

//     connect(modifierBtn, &QPushButton::clicked, this, &personnel::on_modifierProfil_clicked);
//     connect(sauvegarderBtn, &QPushButton::clicked, this, &personnel::on_sauvegarderProfil_clicked);
//     connect(annulerBtn, &QPushButton::clicked, this, &personnel::on_annulerModifications_clicked);
//     connect(changerPassBtn, &QPushButton::clicked, this, &personnel::on_changerMotDePasse_clicked);

//     return boutonsLayout;
// }

// bool personnel::connecterBaseDeDonnees()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE");
//     m_db.setDatabaseName("restaurant.db");

//     if (!m_db.open()) {
//         qDebug() << "Erreur DB:" << m_db.lastError().text();
//         return false;
//     }

//     qDebug() << "Base de données ouverte avec succès";
//     return true;
// }

// void personnel::chargerProfil()
// {
//     QSqlDatabase db = QSqlDatabase::database();
//     if (!db.isOpen()) {
//         QMessageBox::critical(this, "Erreur", "Base de données non connectée");
//         return;
//     }

//     QSqlQuery query;
//     if (!query.prepare("SELECT email, firstname, lastname FROM users WHERE id = :id")) {
//         QMessageBox::critical(this, "Erreur", "Erreur de préparation: " + query.lastError().text());
//         return;
//     }

//     query.bindValue(":id", m_userId);

//     if (!query.exec()) {
//         QMessageBox::critical(this, "Erreur", "Erreur de lecture: " + query.lastError().text());
//         return;
//     }

//     if (query.next()) {
//         m_originalEmail = query.value("email").toString();
//         emailEdit->setText(m_originalEmail);
//         prenomEdit->setText(query.value("firstname").toString());
//         nomEdit->setText(query.value("lastname").toString());
//     } else {
//         QMessageBox::warning(this, "Erreur", "Utilisateur non trouvé");
//     }
// }

// void personnel::toggleEditMode(bool editable)
// {
//     emailEdit->setReadOnly(!editable);
//     prenomEdit->setReadOnly(!editable);
//     nomEdit->setReadOnly(!editable);

//     sauvegarderBtn->setEnabled(editable);
//     annulerBtn->setEnabled(editable);
//     modifierBtn->setEnabled(!editable);
// }

// void personnel::on_modifierProfil_clicked()
// {
//     toggleEditMode(true);
// }

// void personnel::on_sauvegarderProfil_clicked()
// {
//     QString newEmail = emailEdit->text().trimmed();
//     QString prenom = prenomEdit->text().trimmed();
//     QString nom = nomEdit->text().trimmed();

//     // Validation des champs
//     if (newEmail.isEmpty() || prenom.isEmpty() || nom.isEmpty()) {
//         QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
//         return;
//     }

//     // Vérification format email avec expression régulière
//     QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
//     if (!emailRegex.match(newEmail).hasMatch()) {
//         QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse email valide");
//         return;
//     }

//     QSqlDatabase db = QSqlDatabase::database();
//     if (!db.isOpen()) {
//         QMessageBox::critical(this, "Erreur", "Base de données non connectée");
//         return;
//     }

//     // Vérifier si l'email a changé
//     if (newEmail != m_originalEmail) {
//         QSqlQuery checkQuery;
//         checkQuery.prepare("SELECT COUNT(*) FROM users WHERE email = :email AND id != :id");
//         checkQuery.bindValue(":email", newEmail);
//         checkQuery.bindValue(":id", m_userId);

//         if (!checkQuery.exec()) {
//             QMessageBox::critical(this, "Erreur", "Erreur de vérification email: " + checkQuery.lastError().text());
//             return;
//         }

//         if (checkQuery.next() && checkQuery.value(0).toInt() > 0) {
//             QMessageBox::warning(this, "Erreur", "Cet email est déjà utilisé par un autre compte");
//             return;
//         }
//     }

//     // Mise à jour du profil
//     QSqlQuery updateQuery;
//     if (!updateQuery.prepare("UPDATE users SET email = :email, firstname = :firstname, lastname = :lastname WHERE id = :id")) {
//         QMessageBox::critical(this, "Erreur", "Erreur de préparation: " + updateQuery.lastError().text());
//         return;
//     }

//     updateQuery.bindValue(":email", newEmail);
//     updateQuery.bindValue(":firstname", prenom);
//     updateQuery.bindValue(":lastname", nom);
//     updateQuery.bindValue(":id", m_userId);

//     if (!updateQuery.exec()) {
//         QMessageBox::critical(this, "Erreur", "Échec mise à jour: " + updateQuery.lastError().text());
//         return;
//     }

//     QMessageBox::information(this, "Succès", "Profil mis à jour avec succès");
//     m_originalEmail = newEmail;
//     toggleEditMode(false);
// }

// void personnel::on_changerMotDePasse_clicked()
// {
//     QString currentPass = currentPassEdit->text();
//     QString newPass = newPassEdit->text();
//     QString confirmPass = confirmPassEdit->text();

//     if (newPass.isEmpty() || confirmPass.isEmpty()) {
//         QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
//         return;
//     }

//     if (newPass != confirmPass) {
//         QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas");
//         return;
//     }

//     if (!verifierMotDePasse(currentPass)) {
//         QMessageBox::warning(this, "Erreur", "Mot de passe actuel incorrect");
//         return;
//     }

//     QSqlQuery query(m_db);
//     query.prepare("UPDATE users SET password = :password WHERE id = :id");
//     query.bindValue(":password", newPass);
//     query.bindValue(":id", m_userId);

//     if (query.exec()) {
//         QMessageBox::information(this, "Succès", "Mot de passe changé avec succès");
//         currentPassEdit->clear();
//         newPassEdit->clear();
//         confirmPassEdit->clear();
//     } else {
//         QMessageBox::critical(this, "Erreur", "Échec du changement: " + query.lastError().text());
//     }
// }

// void personnel::on_annulerModifications_clicked()
// {
//     chargerProfil();
//     toggleEditMode(false);
// }

// bool personnel::verifierMotDePasse(const QString &password)
// {
//     QSqlQuery query(m_db);
//     query.prepare("SELECT password FROM users WHERE id = :id");
//     query.bindValue(":id", m_userId);

//     if (query.exec() && query.next()) {
//         return (query.value(0).toString() == password);
//     }
//     return false;
// }


#include "personnel.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QGroupBox>
#include <QSqlError>
#include <QHBoxLayout>
#include <QDebug>
#include <QRegularExpression>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QLabel>

personnel::personnel(int userId, QWidget *parent) :
    QDialog(parent),
    m_userId(userId),
    m_originalEmail("")
{
    setWindowTitle("Mon Espace Personnel");
    resize(800, 600);

    // Initialisation des widgets
    emailEdit = new QLineEdit(this);
    prenomEdit = new QLineEdit(this);
    nomEdit = new QLineEdit(this);
    currentPassEdit = new QLineEdit(this);
    newPassEdit = new QLineEdit(this);
    confirmPassEdit = new QLineEdit(this);

    // Configuration des champs
    currentPassEdit->setEchoMode(QLineEdit::Password);
    newPassEdit->setEchoMode(QLineEdit::Password);
    confirmPassEdit->setEchoMode(QLineEdit::Password);

    // Configuration de l'interface
    setupUI();

    // Connexion à la base de données
    if (!connecterBaseDeDonnees()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
        return;
    }

    // Chargement du profil
    chargerProfil();
    toggleEditMode(false);
}

void personnel::setupUI()
{
    // Style global
    this->setStyleSheet(
        "QDialog {"
        "   background-color: #f5f5f5;"
        "   font-family: 'Segoe UI', Arial;"
        "}"

        "QGroupBox {"
        "   background-color: white;"
        "   border: 1px solid #ddd;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding: 15px;"
        "   font-size: 14px;"
        "}"

        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 5px;"
        "   font-weight: bold;"
        "}"

        "QLineEdit {"
        "   padding: 8px;"
        "   border: 1px solid #ddd;"
        "   border-radius: 4px;"
        "   min-width: 250px;"
        "}"

        "QLineEdit:read-only {"
        "   background-color: #f9f9f9;"
        "}"

        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   min-width: 120px;"
        "   font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"

        "QPushButton:disabled {"
        "   background-color: #95a5a6;"
        "}"

        "QPushButton#changerPassBtn {"
        "   background-color: #2ecc71;"
        "}"

        "QPushButton#changerPassBtn:hover {"
        "   background-color: #27ae60;"
        "}"
        );

    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Titre
    QLabel *titleLabel = new QLabel("Mon Espace Personnel", this);
    titleLabel->setStyleSheet(
        "QLabel {"
        "   font-size: 20px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   padding-bottom: 10px;"
        "   border-bottom: 2px solid #3498db;"
        "}"
        );
    mainLayout->addWidget(titleLabel);

    // Groupe informations personnelles
    QGroupBox *infoGroup = new QGroupBox("Informations personnelles", this);
    QFormLayout *formLayout = new QFormLayout(infoGroup);
    formLayout->setSpacing(10);
    formLayout->setContentsMargins(10, 15, 10, 15);

    formLayout->addRow("Email:", emailEdit);
    formLayout->addRow("Prénom:", prenomEdit);
    formLayout->addRow("Nom:", nomEdit);

    // Groupe mot de passe
    QGroupBox *passGroup = new QGroupBox("Changement de mot de passe", this);
    QFormLayout *passLayout = new QFormLayout(passGroup);
    passLayout->setSpacing(10);
    passLayout->setContentsMargins(10, 15, 10, 15);

    passLayout->addRow("Mot de passe actuel:", currentPassEdit);
    passLayout->addRow("Nouveau mot de passe:", newPassEdit);
    passLayout->addRow("Confirmer mot de passe:", confirmPassEdit);

    // Ajout des groupes au layout principal
    mainLayout->addWidget(infoGroup);
    mainLayout->addWidget(passGroup);
    mainLayout->addLayout(creerBoutons());

    setLayout(mainLayout);
}

QHBoxLayout* personnel::creerBoutons()
{
    QHBoxLayout *boutonsLayout = new QHBoxLayout();
    boutonsLayout->setSpacing(10);

    modifierBtn = new QPushButton("Modifier", this);
    sauvegarderBtn = new QPushButton("Sauvegarder", this);
    annulerBtn = new QPushButton("Annuler", this);
    changerPassBtn = new QPushButton("Changer mot de passe", this);
    changerPassBtn->setObjectName("changerPassBtn");

    boutonsLayout->addStretch();
    boutonsLayout->addWidget(modifierBtn);
    boutonsLayout->addWidget(sauvegarderBtn);
    boutonsLayout->addWidget(annulerBtn);
    boutonsLayout->addWidget(changerPassBtn);
    boutonsLayout->addStretch();

    connect(modifierBtn, &QPushButton::clicked, this, &personnel::on_modifierProfil_clicked);
    connect(sauvegarderBtn, &QPushButton::clicked, this, &personnel::on_sauvegarderProfil_clicked);
    connect(annulerBtn, &QPushButton::clicked, this, &personnel::on_annulerModifications_clicked);
    connect(changerPassBtn, &QPushButton::clicked, this, &personnel::on_changerMotDePasse_clicked);

    return boutonsLayout;
}

bool personnel::connecterBaseDeDonnees()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("restaurant.db");

    if (!m_db.open()) {
        qDebug() << "Erreur DB:" << m_db.lastError().text();
        return false;
    }
    return true;
}

void personnel::chargerProfil()
{
    QSqlQuery query;
    query.prepare("SELECT email, firstname, lastname FROM users WHERE id = :id");
    query.bindValue(":id", m_userId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur de lecture: " + query.lastError().text());
        return;
    }

    if (query.next()) {
        m_originalEmail = query.value("email").toString();
        emailEdit->setText(m_originalEmail);
        prenomEdit->setText(query.value("firstname").toString());
        nomEdit->setText(query.value("lastname").toString());
    }
}

void personnel::toggleEditMode(bool editable)
{
    emailEdit->setReadOnly(!editable);
    prenomEdit->setReadOnly(!editable);
    nomEdit->setReadOnly(!editable);

    sauvegarderBtn->setEnabled(editable);
    annulerBtn->setEnabled(editable);
    modifierBtn->setEnabled(!editable);
}

void personnel::on_modifierProfil_clicked()
{
    toggleEditMode(true);
}




void personnel::setBackground()
{
    // Style pour le fond
    this->setStyleSheet(
        "reservation {"
        "   background-image: url(:/background/img28.jpg);"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   background-size: cover;"
        "}"

        "QGroupBox, QFrame, QScrollArea, QWidget#formulaireWidget {"
        "   background-color: rgba(255, 255, 255, 0.85);"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "}"

        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"

        "QLineEdit, QSpinBox {"
        "   padding: 6px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   background: white;"
        "}"
        );
}


void personnel::on_sauvegarderProfil_clicked()
{
    QString newEmail = emailEdit->text().trimmed();
    QString prenom = prenomEdit->text().trimmed();
    QString nom = nomEdit->text().trimmed();

    // Validation des champs
    if (newEmail.isEmpty() || prenom.isEmpty() || nom.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    // Validation email
    QRegularExpression emailRegex(R"(^[a-zA-Z0-9._%+-]+@[a-zA-Z0-9.-]+\.[a-zA-Z]{2,}$)");
    if (!emailRegex.match(newEmail).hasMatch()) {
        QMessageBox::warning(this, "Erreur", "Veuillez entrer une adresse email valide");
        return;
    }

    // Vérification email unique
    if (newEmail != m_originalEmail) {
        QSqlQuery checkQuery;
        checkQuery.prepare("SELECT COUNT(*) FROM users WHERE email = :email AND id != :id");
        checkQuery.bindValue(":email", newEmail);
        checkQuery.bindValue(":id", m_userId);

        if (!checkQuery.exec() || (checkQuery.next() && checkQuery.value(0).toInt() > 0)) {
            QMessageBox::warning(this, "Erreur", "Cet email est déjà utilisé");
            return;
        }
    }

    // Mise à jour
    QSqlQuery updateQuery;
    updateQuery.prepare("UPDATE users SET email = :email, firstname = :firstname, lastname = :lastname WHERE id = :id");
    updateQuery.bindValue(":email", newEmail);
    updateQuery.bindValue(":firstname", prenom);
    updateQuery.bindValue(":lastname", nom);
    updateQuery.bindValue(":id", m_userId);

    if (!updateQuery.exec()) {
        QMessageBox::critical(this, "Erreur", "Échec mise à jour: " + updateQuery.lastError().text());
        return;
    }

    QMessageBox::information(this, "Succès", "Profil mis à jour");
    m_originalEmail = newEmail;
    toggleEditMode(false);
}

void personnel::on_changerMotDePasse_clicked()
{
    QString currentPass = currentPassEdit->text();
    QString newPass = newPassEdit->text();
    QString confirmPass = confirmPassEdit->text();

    // Validation
    if (currentPass.isEmpty() || newPass.isEmpty() || confirmPass.isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
        return;
    }

    if (newPass != confirmPass) {
        QMessageBox::warning(this, "Erreur", "Les mots de passe ne correspondent pas");
        return;
    }

    if (!verifierMotDePasse(currentPass)) {
        QMessageBox::warning(this, "Erreur", "Mot de passe actuel incorrect");
        return;
    }

    // Mise à jour
    QSqlQuery query;
    query.prepare("UPDATE users SET password = :password WHERE id = :id");
    query.bindValue(":password", newPass);
    query.bindValue(":id", m_userId);

    if (query.exec()) {
        QMessageBox::information(this, "Succès", "Mot de passe changé");
        currentPassEdit->clear();
        newPassEdit->clear();
        confirmPassEdit->clear();
    } else {
        QMessageBox::critical(this, "Erreur", "Échec du changement: " + query.lastError().text());
    }
}

void personnel::on_annulerModifications_clicked()
{
    chargerProfil();
    toggleEditMode(false);
}

bool personnel::verifierMotDePasse(const QString &password)
{
    QSqlQuery query;
    query.prepare("SELECT password FROM users WHERE id = :id");
    query.bindValue(":id", m_userId);

    return (query.exec() && query.next() && query.value(0).toString() == password);
}

personnel::~personnel()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

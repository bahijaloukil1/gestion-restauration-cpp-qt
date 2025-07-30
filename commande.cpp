// #include "commande.h"

// commande::commande(QWidget *parent) : QDialog(parent)
// {
//     setupDatabase();
//     setupUI();
// }

// commande::~commande()
// {
//     if (db.isOpen()) {
//         db.close();
//     }
// }

// void commande::setupUI()
// {
//     setWindowTitle("Commande en ligne");
//     resize(1574, 826);

//     mainLayout = new QVBoxLayout(this);

//     // Titre
//     QPushButton *titre = new QPushButton("🛒 Commande en ligne", this);
//     titre->setStyleSheet("QPushButton{font-family: 'Playfair Display', serif; font-size:47px; background-color: #f9f5f0; color: #333; line-height: 1.6; margin: 0; padding: 0;}");
//     titre->setFixedHeight(61);
//     mainLayout->addWidget(titre);

//     // Frame pour les formulaires
//     QFrame *frame = new QFrame(this);
//     frame->setFrameShape(QFrame::StyledPanel);
//     frame->setFrameShadow(QFrame::Raised);

//     QHBoxLayout *formLayout = new QHBoxLayout(frame);

//     // Formulaire client
//     QGroupBox *clientGroup = new QGroupBox("Informations Client");
//     clientFormLayout = new QFormLayout(clientGroup);
//     createClientForm();
//     formLayout->addWidget(clientGroup);

//     // Formulaire commande
//     QGroupBox *commandeGroup = new QGroupBox("Détails de la Commande");
//     commandeFormLayout = new QFormLayout(commandeGroup);
//     createCommandeForm();
//     formLayout->addWidget(commandeGroup);

//     mainLayout->addWidget(frame);

//     // Boutons
//     QHBoxLayout *buttonLayout = new QHBoxLayout();
//     ajouterButton = new QPushButton("AJOUTER", this);
//     afficherButton = new QPushButton("AFFICHER COMMANDES", this);

//     buttonLayout->addWidget(ajouterButton);
//     buttonLayout->addWidget(afficherButton);
//     mainLayout->addLayout(buttonLayout);

//     // Label pour les résultats
//     resultLabel = new QLabel(this);
//     resultLabel->setAlignment(Qt::AlignCenter);
//     mainLayout->addWidget(resultLabel);

//     // Connexions
//     connect(ajouterButton, &QPushButton::clicked, this, &commande::ajouterCommande);
//     connect(afficherButton, &QPushButton::clicked, this, &commande::afficherCommandes);

//     setLayout(mainLayout);
// }

// void commande::createClientForm()
// {
//     nomLineEdit = new QLineEdit(this);
//     prenomLineEdit = new QLineEdit(this);
//     adresseLineEdit = new QLineEdit(this);
//     telephoneLineEdit = new QLineEdit(this);
//     emailLineEdit = new QLineEdit(this);

//     clientFormLayout->addRow("Nom:", nomLineEdit);
//     clientFormLayout->addRow("Prénom:", prenomLineEdit);
//     clientFormLayout->addRow("Adresse:", adresseLineEdit);
//     clientFormLayout->addRow("Téléphone:", telephoneLineEdit);
//     clientFormLayout->addRow("Email:", emailLineEdit);
// }

// void commande::createCommandeForm()
// {
//     produitLineEdit = new QLineEdit(this);
//     quantiteLineEdit = new QLineEdit(this);
//     prixLineEdit = new QLineEdit(this);

//     commandeFormLayout->addRow("Produit:", produitLineEdit);
//     commandeFormLayout->addRow("Quantité:", quantiteLineEdit);
//     commandeFormLayout->addRow("Prix unitaire:", prixLineEdit);
// }

// void commande::setupDatabase()
// {
//     db = QSqlDatabase::addDatabase("QSQLITE");
//     db.setDatabaseName(QCoreApplication::applicationDirPath() + "/commandes.db");

//     if (!db.open()) {
//         QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la base de données: " + db.lastError().text());
//         return;
//     }

//     // Vérifie si les tables existent déjà
//     QStringList tables = db.tables();
//     if (!tables.contains("clients") || !tables.contains("commandes")) {
//         QSqlQuery query;

//         if (!query.exec("CREATE TABLE IF NOT EXISTS clients ("
//                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                         "nom TEXT NOT NULL, "
//                         "prenom TEXT NOT NULL, "
//                         "adresse TEXT, "
//                         "telephone TEXT, "
//                         "email TEXT)")) {
//             QMessageBox::critical(this, "Erreur", "Erreur création table clients: " + query.lastError().text());
//         }

//         if (!query.exec("CREATE TABLE IF NOT EXISTS commandes ("
//                         "id INTEGER PRIMARY KEY AUTOINCREMENT, "
//                         "client_id INTEGER NOT NULL, "
//                         "produit TEXT NOT NULL, "
//                         "quantite INTEGER NOT NULL, "
//                         "prix REAL NOT NULL, "
//                         "FOREIGN KEY(client_id) REFERENCES clients(id) ON DELETE CASCADE)")) {
//             QMessageBox::critical(this, "Erreur", "Erreur création table commandes: " + query.lastError().text());
//         }
//     }
// }

// void commande::ajouterCommande()
// {
//     // Validation des champs
//     if (nomLineEdit->text().isEmpty() || prenomLineEdit->text().isEmpty() ||
//         produitLineEdit->text().isEmpty() || quantiteLineEdit->text().isEmpty() ||
//         prixLineEdit->text().isEmpty()) {
//         QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs obligatoires");
//         return;
//     }

//     // Validation numérique
//     bool ok;
//     quantiteLineEdit->text().toInt(&ok);
//     if (!ok) {
//         QMessageBox::warning(this, "Attention", "La quantité doit être un nombre entier");
//         return;
//     }

//     prixLineEdit->text().toDouble(&ok);
//     if (!ok) {
//         QMessageBox::warning(this, "Attention", "Le prix doit être un nombre");
//         return;
//     }

//     db.transaction();

//     // Insertion client
//     QSqlQuery query;
//     query.prepare("INSERT INTO clients (nom, prenom, adresse, telephone, email) "
//                   "VALUES (:nom, :prenom, :adresse, :telephone, :email)");
//     query.bindValue(":nom", nomLineEdit->text());
//     query.bindValue(":prenom", prenomLineEdit->text());
//     query.bindValue(":adresse", adresseLineEdit->text());
//     query.bindValue(":telephone", telephoneLineEdit->text());
//     query.bindValue(":email", emailLineEdit->text());

//     if (!query.exec()) {
//         db.rollback();
//         QMessageBox::critical(this, "Erreur", "Erreur insertion client: " + query.lastError().text());
//         return;
//     }

//     int clientId = query.lastInsertId().toInt();

//     // Insertion commande
//     query.prepare("INSERT INTO commandes (client_id, produit, quantite, prix) "
//                   "VALUES (:client_id, :produit, :quantite, :prix)");
//     query.bindValue(":client_id", clientId);
//     query.bindValue(":produit", produitLineEdit->text());
//     query.bindValue(":quantite", quantiteLineEdit->text().toInt());
//     query.bindValue(":prix", prixLineEdit->text().toDouble());

//     if (!query.exec()) {
//         db.rollback();
//         QMessageBox::critical(this, "Erreur", "Erreur insertion commande: " + query.lastError().text());
//         return;
//     }

//     db.commit();
//     resultLabel->setText("Commande ajoutée avec succès!");

//     // Réinitialisation des champs
//     nomLineEdit->clear();
//     prenomLineEdit->clear();
//     adresseLineEdit->clear();
//     telephoneLineEdit->clear();
//     emailLineEdit->clear();
//     produitLineEdit->clear();
//     quantiteLineEdit->clear();
//     prixLineEdit->clear();
// }

// void commande::afficherCommandes()
// {
//     QSqlQuery query("SELECT c.nom, c.prenom, cmd.produit, cmd.quantite, cmd.prix "
//                     "FROM commandes cmd "
//                     "JOIN clients c ON cmd.client_id = c.id");

//     if (!query.exec()) {
//         QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des commandes: " + query.lastError().text());
//         return;
//     }

//     QString result = "<h2>Liste des Commandes</h2><table border='1'><tr>"
//                      "<th>Nom</th><th>Prénom</th><th>Produit</th>"
//                      "<th>Quantité</th><th>Prix unitaire</th></tr>";

//     while (query.next()) {
//         result += QString("<tr><td>%1</td><td>%2</td><td>%3</td><td>%4</td><td>%5</td></tr>")
//         .arg(query.value(0).toString())
//             .arg(query.value(1).toString())
//             .arg(query.value(2).toString())
//             .arg(query.value(3).toString())
//             .arg(QString::number(query.value(4).toDouble(), 'f', 2));
//     }

//     result += "</table>";
//     resultLabel->setText(result);
// }


#include "commande.h"
#include <QMessageBox>
#include <QSqlQuery>
#include <QSqlError>
#include <QCoreApplication>

commande::commande(QWidget *parent) : QDialog(parent)
{
    setupDatabase();
    setupUI();
}

commande::~commande()
{
    if (db.isOpen()) {
        db.close();
    }
}

void commande::setupUI()
{
    // Style global
    this->setStyleSheet(
        "QWidget {"
        "   font-family: 'Segoe UI', Arial;"
        "   background-color: #f5f5f5;"
        "}"
        "QPushButton {"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"
        "QLineEdit {"
        "   padding: 8px;"
        "   border: 1px solid #ddd;"
        "   border-radius: 4px;"
        "   min-width: 250px;"
        "}"
        "QLineEdit:focus {"
        "   border: 1px solid #4CAF50;"
        "}"
        "QGroupBox {"
        "   border: 1px solid #3498db;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "   padding-top: 15px;"
        "}"
        "QGroupBox::title {"
        "   subcontrol-origin: margin;"
        "   left: 10px;"
        "   padding: 0 5px;"
        "}"
        );

    setWindowTitle("Commande en ligne");
    resize(1200, 800);

    mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(20);
    mainLayout->setContentsMargins(30, 20, 30, 20);

    // Titre
    QLabel *titre = new QLabel("🛒 COMMANDE EN LIGNE", this);
    titre->setStyleSheet(
        "QLabel {"
        "   font-size: 28px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "   padding: 15px 0;"
        "   border-bottom: 2px solid #3498db;"
        "}"
        );
    titre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titre);

    // Frame pour les formulaires
    QFrame *frame = new QFrame(this);
    frame->setFrameShape(QFrame::StyledPanel);
    frame->setStyleSheet(
        "QFrame {"
        "   background-color: white;"
        "   border-radius: 8px;"
        "   padding: 20px;"
        "}"
        );

    QHBoxLayout *formLayout = new QHBoxLayout(frame);
    formLayout->setSpacing(30);

    // Formulaire client
    QGroupBox *clientGroup = new QGroupBox("Informations Client");
    clientGroup->setStyleSheet(
        "QGroupBox {"
        "   font-size: 16px;"
        "   font-weight: bold;"
        "   color: #2c3e50;"
        "}"
        );
    clientFormLayout = new QFormLayout(clientGroup);
    clientFormLayout->setSpacing(15);
    clientFormLayout->setContentsMargins(15, 25, 15, 15);
    createClientForm();
    formLayout->addWidget(clientGroup);

    // Formulaire commande
    QGroupBox *commandeGroup = new QGroupBox("Détails de la Commande");
    commandeGroup->setStyleSheet(clientGroup->styleSheet());
    commandeFormLayout = new QFormLayout(commandeGroup);
    commandeFormLayout->setSpacing(15);
    commandeFormLayout->setContentsMargins(15, 25, 15, 15);
    createCommandeForm();
    formLayout->addWidget(commandeGroup);

    mainLayout->addWidget(frame);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(20);
    buttonLayout->setContentsMargins(0, 10, 0, 10);

    ajouterButton = new QPushButton("AJOUTER", this);
    afficherButton = new QPushButton("AFFICHER COMMANDES", this);

    // Style des boutons
    QString buttonStyle =
        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 10px 20px;"
        "   font-size: 14px;"
        "}"
        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"
        "QPushButton:pressed {"
        "   background-color: #1a6ca1;"
        "}";

    ajouterButton->setStyleSheet(buttonStyle);
    afficherButton->setStyleSheet(buttonStyle);

    buttonLayout->addWidget(ajouterButton, 0, Qt::AlignCenter);
    buttonLayout->addWidget(afficherButton, 0, Qt::AlignCenter);
    mainLayout->addLayout(buttonLayout);

    // Label pour les résultats
    resultLabel = new QLabel(this);
    resultLabel->setStyleSheet(
        "QLabel {"
        "   padding: 15px;"
        "   background-color: #f8f9fa;"
        "   border: 1px solid #ddd;"
        "   border-radius: 5px;"
        "   margin-top: 10px;"
        "}"
        "QLabel h2 {"
        "   color: #2c3e50;"
        "}"
        "QLabel table {"
        "   border-collapse: collapse;"
        "   width: 100%;"
        "   margin-top: 10px;"
        "}"
        "QLabel th {"
        "   background-color: #3498db;"
        "   color: white;"
        "   padding: 8px;"
        "   text-align: left;"
        "}"
        "QLabel td {"
        "   padding: 8px;"
        "   border-bottom: 1px solid #ddd;"
        "}"
        "QLabel tr:nth-child(even) {"
        "   background-color: #f2f2f2;"
        "}"
        );
    resultLabel->setAlignment(Qt::AlignCenter);
    resultLabel->setWordWrap(true);
    mainLayout->addWidget(resultLabel);

    // Connexions
    connect(ajouterButton, &QPushButton::clicked, this, &commande::ajouterCommande);
    connect(afficherButton, &QPushButton::clicked, this, &commande::afficherCommandes);

    setLayout(mainLayout);
}

void commande::createClientForm()
{
    nomLineEdit = new QLineEdit(this);
    prenomLineEdit = new QLineEdit(this);
    adresseLineEdit = new QLineEdit(this);
    telephoneLineEdit = new QLineEdit(this);
    emailLineEdit = new QLineEdit(this);

    // Style pour champs obligatoires
    QString requiredStyle = "QLineEdit { border: 1px solid #e74c3c; }";
    nomLineEdit->setStyleSheet(requiredStyle);
    prenomLineEdit->setStyleSheet(requiredStyle);

    clientFormLayout->addRow("Nom*:", nomLineEdit);
    clientFormLayout->addRow("Prénom*:", prenomLineEdit);
    clientFormLayout->addRow("Adresse:", adresseLineEdit);
    clientFormLayout->addRow("Téléphone:", telephoneLineEdit);
    clientFormLayout->addRow("Email:", emailLineEdit);
}

void commande::createCommandeForm()
{
    produitLineEdit = new QLineEdit(this);
    quantiteLineEdit = new QLineEdit(this);
    prixLineEdit = new QLineEdit(this);

    // Style pour champs obligatoires
    QString requiredStyle = "QLineEdit { border: 1px solid #e74c3c; }";
    produitLineEdit->setStyleSheet(requiredStyle);
    quantiteLineEdit->setStyleSheet(requiredStyle);
    prixLineEdit->setStyleSheet(requiredStyle);

    commandeFormLayout->addRow("Produit*:", produitLineEdit);
    commandeFormLayout->addRow("Quantité*:", quantiteLineEdit);
    commandeFormLayout->addRow("Prix unitaire*:", prixLineEdit);
}

void commande::setupDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName(QCoreApplication::applicationDirPath() + "/commandes.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Impossible d'ouvrir la base de données: " + db.lastError().text());
        return;
    }

    // Vérifie si les tables existent déjà
    QStringList tables = db.tables();
    if (!tables.contains("clients") || !tables.contains("commandes")) {
        QSqlQuery query;

        if (!query.exec("CREATE TABLE IF NOT EXISTS clients ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "nom TEXT NOT NULL, "
                        "prenom TEXT NOT NULL, "
                        "adresse TEXT, "
                        "telephone TEXT, "
                        "email TEXT)")) {
            QMessageBox::critical(this, "Erreur", "Erreur création table clients: " + query.lastError().text());
        }

        if (!query.exec("CREATE TABLE IF NOT EXISTS commandes ("
                        "id INTEGER PRIMARY KEY AUTOINCREMENT, "
                        "client_id INTEGER NOT NULL, "
                        "produit TEXT NOT NULL, "
                        "quantite INTEGER NOT NULL, "
                        "prix REAL NOT NULL, "
                        "FOREIGN KEY(client_id) REFERENCES clients(id) ON DELETE CASCADE)")) {
            QMessageBox::critical(this, "Erreur", "Erreur création table commandes: " + query.lastError().text());
        }
    }
}

void commande::ajouterCommande()
{
    // Validation des champs
    if (nomLineEdit->text().isEmpty() || prenomLineEdit->text().isEmpty() ||
        produitLineEdit->text().isEmpty() || quantiteLineEdit->text().isEmpty() ||
        prixLineEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Attention", "Veuillez remplir tous les champs obligatoires (*)");
        return;
    }

    // Validation numérique
    bool ok;
    int quantite = quantiteLineEdit->text().toInt(&ok);
    if (!ok || quantite < 1) {
        QMessageBox::warning(this, "Attention", "La quantité doit être un nombre entier positif");
        return;
    }

    double prix = prixLineEdit->text().toDouble(&ok);
    if (!ok || prix <= 0) {
        QMessageBox::warning(this, "Attention", "Le prix doit être un nombre positif");
        return;
    }

    db.transaction();

    // Insertion client
    QSqlQuery query;
    query.prepare("INSERT INTO clients (nom, prenom, adresse, telephone, email) "
                  "VALUES (:nom, :prenom, :adresse, :telephone, :email)");
    query.bindValue(":nom", nomLineEdit->text());
    query.bindValue(":prenom", prenomLineEdit->text());
    query.bindValue(":adresse", adresseLineEdit->text());
    query.bindValue(":telephone", telephoneLineEdit->text());
    query.bindValue(":email", emailLineEdit->text());

    if (!query.exec()) {
        db.rollback();
        QMessageBox::critical(this, "Erreur", "Erreur insertion client: " + query.lastError().text());
        return;
    }

    int clientId = query.lastInsertId().toInt();

    // Insertion commande
    query.prepare("INSERT INTO commandes (client_id, produit, quantite, prix) "
                  "VALUES (:client_id, :produit, :quantite, :prix)");
    query.bindValue(":client_id", clientId);
    query.bindValue(":produit", produitLineEdit->text());
    query.bindValue(":quantite", quantite);
    query.bindValue(":prix", prix);

    if (!query.exec()) {
        db.rollback();
        QMessageBox::critical(this, "Erreur", "Erreur insertion commande: " + query.lastError().text());
        return;
    }

    db.commit();
    resultLabel->setText("<span style='color:#27ae60; font-weight:bold;'>Commande ajoutée avec succès!</span>");

    // Réinitialisation des champs
    nomLineEdit->clear();
    prenomLineEdit->clear();
    adresseLineEdit->clear();
    telephoneLineEdit->clear();
    emailLineEdit->clear();
    produitLineEdit->clear();
    quantiteLineEdit->clear();
    prixLineEdit->clear();
}

void commande::afficherCommandes()
{
    QSqlQuery query("SELECT c.nom, c.prenom, cmd.produit, cmd.quantite, cmd.prix "
                    "FROM commandes cmd "
                    "JOIN clients c ON cmd.client_id = c.id");

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur", "Erreur lors de la récupération des commandes: " + query.lastError().text());
        return;
    }

    QString result = "<h2>Liste des Commandes</h2>"
                     "<table>"
                     "<tr>"
                     "<th>Nom</th>"
                     "<th>Prénom</th>"
                     "<th>Produit</th>"
                     "<th>Quantité</th>"
                     "<th>Prix unitaire</th>"
                     "</tr>";

    while (query.next()) {
        result += QString("<tr>"
                          "<td>%1</td>"
                          "<td>%2</td>"
                          "<td>%3</td>"
                          "<td align='center'>%4</td>"
                          "<td align='right'>%5 €</td>"
                          "</tr>")
                      .arg(query.value(0).toString())
                      .arg(query.value(1).toString())
                      .arg(query.value(2).toString())
                      .arg(query.value(3).toString())
                      .arg(QString::number(query.value(4).toDouble(), 'f', 2));
    }

    result += "</table>";

    if (query.size() == 0) {
        result += "<p style='color:#7f8c8d; font-style:italic;'>Aucune commande trouvée</p>";
    }

    resultLabel->setText(result);
}

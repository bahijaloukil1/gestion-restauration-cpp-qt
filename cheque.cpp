// #include "cheque.h"
// #include "ui_cheque.h"

// cheque::cheque(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::cheque)
// {
//     ui->setupUi(this);
// }

// cheque::~cheque()
// {
//     delete ui;
// }




// #include "cheque.h"
// #include <QSqlError>  // Ajoutez cette ligne si elle n'existe pas
// #include <QMessageBox>
// #include <QSqlQuery>
// cheque::cheque(int commandeId, QWidget *parent)
//     : QDialog(parent), m_commandeId(commandeId), m_montantTotal(0.0)
// {
//     setWindowTitle("Paiement par Chèque");
//     setMinimumSize(400, 300);

//     // Initialisation de la base de données
//     m_db = QSqlDatabase::addDatabase("QSQLITE", "cheque_connection");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
//         return;
//     }

//     setupUI();
//     chargerMontantCommande();
// }

// cheque::~cheque()
// {
//     if (m_db.isOpen()) {
//         m_db.close();
//     }
// }

// void cheque::setupUI()
// {
//     QVBoxLayout *mainLayout = new QVBoxLayout(this);
//     mainLayout->setSpacing(15);
//     mainLayout->setContentsMargins(20, 20, 20, 20);

//     // Titre
//     QLabel *titre = new QLabel("Paiement par Chèque");
//     titre->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50;");
//     mainLayout->addWidget(titre, 0, Qt::AlignCenter);

//     // Montant de la commande
//     montantLabel = new QLabel("Montant total: Chargement...");
//     montantLabel->setStyleSheet("font-size: 16px;");
//     mainLayout->addWidget(montantLabel);

//     // Numéro de chèque
//     numeroChequeLabel = new QLabel("Numéro du chèque:");
//     numeroChequeEdit = new QLineEdit();
//     numeroChequeEdit->setPlaceholderText("Entrez le numéro du chèque");
//     mainLayout->addWidget(numeroChequeLabel);
//     mainLayout->addWidget(numeroChequeEdit);

//     // Banque
//     banqueLabel = new QLabel("Banque émettrice:");
//     banqueEdit = new QLineEdit();
//     banqueEdit->setPlaceholderText("Nom de la banque");
//     mainLayout->addWidget(banqueLabel);
//     mainLayout->addWidget(banqueEdit);

//     // Boutons
//     QHBoxLayout *buttonLayout = new QHBoxLayout();

//     validerButton = new QPushButton("Valider");
//     validerButton->setStyleSheet(
//         "QPushButton {"
//         "   background-color: #27ae60;"
//         "   color: white;"
//         "   padding: 8px 16px;"
//         "   border: none;"
//         "   border-radius: 4px;"
//         "}"
//         "QPushButton:hover { background-color: #219653; }"
//         );
//     connect(validerButton, &QPushButton::clicked, this, &cheque::validerPaiement);

//     annulerButton = new QPushButton("Annuler");
//     annulerButton->setStyleSheet(
//         "QPushButton {"
//         "   background-color: #e74c3c;"
//         "   color: white;"
//         "   padding: 8px 16px;"
//         "   border: none;"
//         "   border-radius: 4px;"
//         "}"
//         "QPushButton:hover { background-color: #c0392b; }"
//         );
//     connect(annulerButton, &QPushButton::clicked, this, &cheque::annulerPaiement);

//     buttonLayout->addWidget(validerButton);
//     buttonLayout->addWidget(annulerButton);
//     mainLayout->addLayout(buttonLayout);

//     setLayout(mainLayout);
// }

// void cheque::chargerMontantCommande()
// {
//     QSqlQuery query(m_db);
//     query.prepare("SELECT total FROM commandes WHERE id = :id");
//     query.bindValue(":id", m_commandeId);

//     if (query.exec() && query.next()) {
//         m_montantTotal = query.value(0).toDouble();
//         montantLabel->setText(QString("Montant total: %1 €").arg(m_montantTotal, 0, 'f', 2));
//     } else {
//         QMessageBox::critical(this, "Erreur", "Impossible de charger le montant de la commande");
//         montantLabel->setText("Erreur de chargement");
//     }
// }
// bool  cheque::initDatabase()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE", "cheque_connection");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
//         return false;
//     }

//     // Création de la table si elle n'existe pas
//     QSqlQuery query(m_db);
//     bool success = query.exec(
//         "CREATE TABLE IF NOT EXISTS paiements_cheque ("
//         "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
//         "   commande_id INTEGER NOT NULL,"
//         "   numero_cheque TEXT NOT NULL,"
//         "   banque TEXT NOT NULL,"
//         "   montant REAL NOT NULL,"
//         "   date_paiement TEXT DEFAULT CURRENT_TIMESTAMP,"
//         "   FOREIGN KEY (commande_id) REFERENCES commandes(id)"
//         ")"
//         );

//     if (!success) {
//         QMessageBox::critical(this, "Erreur",
//                               "Échec de création de la table paiements_cheque:\n" +
//                                   query.lastError().text());
//         return false;
//     }

//     return true;
// }
// bool cheque::enregistrerPaiement()
// {
//     QSqlQuery query(m_db);
//     query.prepare("UPDATE commandes SET statut = 'payé', mode_paiement = 'chèque' WHERE id = :id");
//     query.bindValue(":id", m_commandeId);

//     if (!query.exec()) {
//         return false;
//     }

//     query.prepare("INSERT INTO paiements_cheque (commande_id, numero_cheque, banque, montant, date) "
//                   "VALUES (:commande_id, :numero, :banque, :montant, datetime('now'))");
//     query.bindValue(":commande_id", m_commandeId);
//     query.bindValue(":numero", numeroChequeEdit->text());
//     query.bindValue(":banque", banqueEdit->text());
//     query.bindValue(":montant", m_montantTotal);

//     return query.exec();
// }

// void cheque::validerPaiement()
// {
//     if (numeroChequeEdit->text().isEmpty() || banqueEdit->text().isEmpty()) {
//         QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs");
//         return;
//     }

//     if (enregistrerPaiement()) {
//         QMessageBox::information(this, "Succès", "Paiement par chèque enregistré avec succès");
//         accept();
//     } else {
//         QMessageBox::critical(this, "Erreur", "Échec de l'enregistrement du paiement");
//     }
// }

// void cheque::annulerPaiement()
// {
//     reject();
// }




#include "cheque.h"
#include <QSqlError>
#include <QMessageBox>
#include <QSqlQuery>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QLineEdit>
#include <QPushButton>

cheque::cheque(int commandeId, QWidget *parent)
    : QDialog(parent), m_commandeId(commandeId), m_montantTotal(0.0)
{
    setWindowTitle("Paiement par Chèque");
    setMinimumSize(400, 300);

    if (!initDatabase()) {
        return;
    }

    setupUI();
    chargerMontantCommande();
}

cheque::~cheque()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

void cheque::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setSpacing(15);
    mainLayout->setContentsMargins(20, 20, 20, 20);

    // Titre
    QLabel *titre = new QLabel("Paiement par Chèque");
    titre->setStyleSheet("font-size: 18px; font-weight: bold; color: #2c3e50;");
    mainLayout->addWidget(titre, 0, Qt::AlignCenter);

    // Montant de la commande
    montantLabel = new QLabel("Montant total: Chargement...");
    montantLabel->setStyleSheet("font-size: 16px;");
    mainLayout->addWidget(montantLabel);

    // Numéro de chèque
    numeroChequeLabel = new QLabel("Numéro du chèque:");
    numeroChequeEdit = new QLineEdit();
    numeroChequeEdit->setPlaceholderText("Entrez le numéro du chèque");
   //numeroChequeEdit->setValidator(new QRegularExpressionValidator(QRegularExpression("[0-9]{6,}"), this)); // Validation 6 chiffres minimum
    mainLayout->addWidget(numeroChequeLabel);
    mainLayout->addWidget(numeroChequeEdit);

    // Banque
    banqueLabel = new QLabel("Banque émettrice:");
    banqueEdit = new QLineEdit();
    banqueEdit->setPlaceholderText("Nom de la banque");
    mainLayout->addWidget(banqueLabel);
    mainLayout->addWidget(banqueEdit);

    // Boutons
    QHBoxLayout *buttonLayout = new QHBoxLayout();
    buttonLayout->setSpacing(10);

    validerButton = new QPushButton("Valider");
    validerButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #27ae60;"
        "   color: white;"
        "   padding: 10px 20px;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #219653; }"
        "QPushButton:disabled { background-color: #95a5a6; }"
    );

    annulerButton = new QPushButton("Annuler");
    annulerButton->setStyleSheet(
        "QPushButton {"
        "   background-color: #e74c3c;"
        "   color: white;"
        "   padding: 10px 20px;"
        "   border: none;"
        "   border-radius: 5px;"
        "   font-weight: bold;"
        "}"
        "QPushButton:hover { background-color: #c0392b; }"
    );

    buttonLayout->addWidget(annulerButton);
    buttonLayout->addWidget(validerButton);
    mainLayout->addLayout(buttonLayout);

    // Connexions
    connect(validerButton, &QPushButton::clicked, this, &cheque::validerPaiement);
    connect(annulerButton, &QPushButton::clicked, this, &cheque::annulerPaiement);

    setLayout(mainLayout);
}

// void cheque::chargerMontantCommande()
// {
//     QSqlQuery query(m_db);
//     query.prepare("SELECT total FROM commandes WHERE id = :id");
//     query.bindValue(":id", m_commandeId);

//     if (query.exec() && query.next()) {
//         m_montantTotal = query.value(0).toDouble();
//         montantLabel->setText(QString("Montant total: %1 €").arg(m_montantTotal, 0, 'f', 2));
//     } else {
//         QMessageBox::critical(this, "Erreur",
//             QString("Impossible de charger le montant:\n%1").arg(query.lastError().text()));
//         montantLabel->setText("Erreur de chargement");
//         validerButton->setEnabled(false);
//     }
// }

// bool cheque::initDatabase()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE", "cheque_connection");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QMessageBox::critical(this, "Erreur",
//             QString("Connexion DB échouée:\n%1").arg(m_db.lastError().text()));
//         return false;
//     }

//     // Activer les clés étrangères
//     m_db.exec("PRAGMA foreign_keys = ON");

//     // Vérifier existence table commandes
//     QSqlQuery query(m_db);
//     if (!query.exec("SELECT 1 FROM sqlite_master WHERE type='table' AND name='commandes'") || !query.next()) {
//         QMessageBox::critical(this, "Erreur", "La table 'commandes' n'existe pas");
//         return false;
//     }

//     // Créer table paiements_cheque si inexistante
//     if (!query.exec(
//         "CREATE TABLE IF NOT EXISTS paiements_cheque ("
//         "   id INTEGER PRIMARY KEY AUTOINCREMENT,"
//         "   commande_id INTEGER NOT NULL,"
//         "   numero_cheque TEXT NOT NULL,"
//         "   banque TEXT NOT NULL,"
//         "   montant REAL NOT NULL,"
//         "   date_paiement TEXT DEFAULT CURRENT_TIMESTAMP,"
//         "   FOREIGN KEY (commande_id) REFERENCES commandes(id) ON DELETE CASCADE"
//         ")"))
//     {
//         QMessageBox::critical(this, "Erreur DB",
//             QString("Échec création table:\n%1").arg(query.lastError().text()));
//         return false;
//     }

//     return true;
// }





void cheque::chargerMontantCommande()
{
    if (!m_db.isOpen()) {
        QMessageBox::critical(this, "Erreur", "Base de données non connectée");
        return;
    }

    QSqlQuery query(m_db);
    query.prepare("SELECT total FROM commandes WHERE id = :commande_id");
    query.bindValue(":commande_id", m_commandeId);

    qDebug() << "Exécution requête pour commande ID:" << m_commandeId;
    qDebug() << "Requête SQL:" << query.lastQuery();

    if (!query.exec()) {
        QString errorDetails = "Erreur SQL: " + query.lastError().text() + "\n"
                               + "Requête: " + query.lastQuery() + "\n"
                               + "Paramètres: [commande_id=" + QString::number(m_commandeId) + "]";
        QMessageBox::critical(this, "Erreur DB", errorDetails);
        return;
    }

    if (query.next()) {
        m_montantTotal = query.value(0).toDouble();
        montantLabel->setText(QString("Montant: %1 €").arg(m_montantTotal, 0, 'f', 2));
        qDebug() << "Montant chargé:" << m_montantTotal;
    } else {
        QMessageBox::warning(this, "Avertissement",
                             QString("Aucune commande trouvée avec l'ID %1").arg(m_commandeId));
    }
}

bool cheque::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE", "cheque_connection_" + QString::number(m_commandeId));
    m_db.setDatabaseName("gestion_restaurant.db");

    // Configuration UTF-8 pour éviter les problèmes de caractères
    m_db.setConnectOptions("QSQLITE_ENCODING=UTF-8");

    if (!m_db.open()) {
        QString erreur = "Échec connexion DB:\n";
        erreur += "Fichier: " + m_db.databaseName() + "\n";
        erreur += "Erreur: " + m_db.lastError().text();
        QMessageBox::critical(this, "Erreur DB", erreur);
        return false;
    }

    // Vérification des tables
    QSqlQuery checkQuery(m_db);
    if (!checkQuery.exec("PRAGMA table_info(commandes)")) {
        QMessageBox::critical(this, "Erreur DB",
                              "La table 'commandes' n'existe pas ou est corrompue");
        return false;
    }

    return true;
}

bool cheque::enregistrerPaiement()
{
    QSqlDatabase::database().transaction();

    QSqlQuery query(m_db);
    query.prepare("UPDATE commandes SET statut = 'payé', mode_paiement = 'chèque' WHERE id = :id");
    query.bindValue(":id", m_commandeId);

    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    query.prepare(
        "INSERT INTO paiements_cheque (commande_id, numero_cheque, banque, montant) "
        "VALUES (:commande_id, :numero, :banque, :montant)"
    );
    query.bindValue(":commande_id", m_commandeId);
    query.bindValue(":numero", numeroChequeEdit->text());
    query.bindValue(":banque", banqueEdit->text());
    query.bindValue(":montant", m_montantTotal);

    if (!query.exec()) {
        QSqlDatabase::database().rollback();
        return false;
    }

    return QSqlDatabase::database().commit();
}

void cheque::validerPaiement()
{
    // Validation des champs
    if (numeroChequeEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le numéro de chèque");
        return;
    }

    if (banqueEdit->text().isEmpty()) {
        QMessageBox::warning(this, "Erreur", "Veuillez saisir le nom de la banque");
        return;
    }

    if (enregistrerPaiement()) {
        QMessageBox::information(this, "Succès", "Paiement enregistré avec succès!");
        accept();
    } else {
        QMessageBox::critical(this, "Erreur",
            QString("Échec de l'enregistrement:\n%1").arg(m_db.lastError().text()));
    }
}

void cheque::annulerPaiement()
{
    reject();
}

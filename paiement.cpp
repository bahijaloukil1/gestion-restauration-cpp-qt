// #include "paiement.h"
// #include "ui_paiement.h"
// #include "cartebancaire.h" // Ajoutez cette inclusion
// #include <QPushButton>
// #include <QMessageBox>
// #include <QSqlQuery>
// #include <QDebug>

// paiement::paiement(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::paiement),
//     mainLayout(new QVBoxLayout(this)) // Initialisation dans la liste d'initialisation
// {
//     ui->setupUi(this);
//     setWindowTitle("Paiement");

//     // Configuration du layout principal
//     this->setLayout(mainLayout);

//     if(!initDatabase()) {
//         QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
//         return;
//     }

//     setupPaymentButtons();

//     // Ajout du buttonBox au layout
//     mainLayout->addWidget(ui->buttonBox);

//     // Connexions
//     connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &paiement::onButtonBoxAccepted);
//     connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &paiement::reject);
// }

// paiement::~paiement()
// {
//     if(m_db.isOpen()) {
//         m_db.close();
//     }
//     delete ui;
// }

// bool paiement::initDatabase()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QSqlError err = m_db.lastError();
//         qDebug() << "Erreur DB paiement:" << err.text();
//         return false;
//     }
//     return true;
// }

// void paiement::setupPaymentButtons()
// {
//     // Layout pour les boutons de paiement
//     QVBoxLayout *paymentLayout = new QVBoxLayout();

//     QStringList paymentMethods = {
//         "Carte Bancaire",
//         "Espèces",
//         "Chèque",
//         "Ticket Restaurant"
//     };

//     foreach (const QString &method, paymentMethods) {
//         QPushButton *button = new QPushButton(method, this);
//         button->setStyleSheet(
//             "QPushButton {"
//             "   padding: 10px;"
//             "   font-size: 14px;"
//             "   margin: 5px;"
//             "}"
//             );
//         paymentLayout->addWidget(button);
//     }

//     // Ajout au layout principal
//     mainLayout->insertLayout(0, paymentLayout);
// }

// void paiement::onButtonBoxAccepted()
// {
//     QMessageBox::information(this, "Paiement", "Paiement effectué avec succès");
//     accept();
// }

// #include "paiement.h"
// #include "ui_paiement.h"
// #include "cartebancaire.h"
// #include "especes.h"
// #include <QPushButton>
// #include <QMessageBox>
// #include <QSqlQuery>
// #include <QDebug>

// paiement::paiement(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::paiement),
//     mainLayout(new QVBoxLayout(this))
// {
//     ui->setupUi(this);
//     setWindowTitle("Paiement");

//     this->setLayout(mainLayout);

//     if(!initDatabase()) {
//         QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
//         return;
//     }

//     setupPaymentButtons();

//     mainLayout->addWidget(ui->buttonBox);

//     connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &paiement::onButtonBoxAccepted);
//     connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &paiement::reject);
// }

// paiement::~paiement()
// {
//     if(m_db.isOpen()) {
//         m_db.close();
//     }
//     delete ui;
// }

// bool paiement::initDatabase()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QSqlError err = m_db.lastError();
//         qDebug() << "Erreur DB paiement:" << err.text();
//         return false;
//     }
//     return true;
// }

// void paiement::setupPaymentButtons()
// {
//     QVBoxLayout *paymentLayout = new QVBoxLayout();

//     QStringList paymentMethods = {
//         "Carte Bancaire",
//         "Espèces",
//         "Chèque",
//         "Ticket Restaurant"
//     };

//     foreach (const QString &method, paymentMethods) {
//         QPushButton *button = new QPushButton(method, this);
//         button->setStyleSheet(
//             "QPushButton {"
//             "   padding: 10px;"
//             "   font-size: 14px;"
//             "   margin: 5px;"
//             "}"
//             );
//         paymentLayout->addWidget(button);

//         if (method == "Carte Bancaire") {
//             connect(button, &QPushButton::clicked, this, &paiement::openCarteBancairePage);
//         }
//     }

//     mainLayout->insertLayout(0, paymentLayout);
// }

// void paiement::onButtonBoxAccepted()
// {
//     QMessageBox::information(this, "Paiement", "Paiement effectué avec succès");
//     accept();
// }

// void paiement::openCarteBancairePage()
// {
//     carteBancaire *cb = new carteBancaire(this);
//     cb->exec();
//     delete cb; // Nettoyage mémoire
// }

// // ... (le reste du code reste inchangé)

// void paiement::setupPaymentButtons()
// {
//     QVBoxLayout *paymentLayout = new QVBoxLayout();

//     QStringList paymentMethods = {
//         "Carte Bancaire",
//         "Espèces",
//         "Chèque",
//         "Ticket Restaurant"
//     };

//     foreach (const QString &method, paymentMethods) {
//         QPushButton *button = new QPushButton(method, this);
//         button->setStyleSheet(
//             "QPushButton {"
//             "   padding: 10px;"
//             "   font-size: 14px;"
//             "   margin: 5px;"
//             "}"
//             );
//         paymentLayout->addWidget(button);

//         if (method == "Carte Bancaire") {
//             connect(button, &QPushButton::clicked, this, &paiement::openCarteBancairePage);
//         }
//         else if (method == "Espèces") {
//             connect(button, &QPushButton::clicked, this, &paiement::openEspecesPage);
//         }
//     }

//     mainLayout->insertLayout(0, paymentLayout);
// }

// // ... (le reste du code reste inchangé)

// void paiement::openEspecesPage()
// {
//     especes *esp = new especes(this);
//     esp->exec();
//     delete esp; // Nettoyage mémoire
// }


#include "paiement.h"
#include "ui_paiement.h"
#include "cartebancaire.h"
#include "especes.h"
#include "cheque.h"  // Ajoutez cette inclusion
#include <QPushButton>
#include <QMessageBox>
#include <QSqlQuery>
#include <QDebug>

paiement::paiement(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::paiement),
    mainLayout(new QVBoxLayout(this))
{
    ui->setupUi(this);
    setWindowTitle("Paiement");

    this->setLayout(mainLayout);

    if(!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
        return;
    }

    setupPaymentButtons();

    mainLayout->addWidget(ui->buttonBox);

    connect(ui->buttonBox, &QDialogButtonBox::accepted, this, &paiement::onButtonBoxAccepted);
    connect(ui->buttonBox, &QDialogButtonBox::rejected, this, &paiement::reject);
}

paiement::~paiement()
{
    if(m_db.isOpen()) {
        m_db.close();
    }
    delete ui;
}

bool paiement::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("gestion_restaurant.db");

    if (!m_db.open()) {
        QSqlError err = m_db.lastError();
        qDebug() << "Erreur DB paiement:" << err.text();
        return false;
    }
    return true;
}

void paiement::setupPaymentButtons()
{
    QVBoxLayout *paymentLayout = new QVBoxLayout();

    QStringList paymentMethods = {
        "Carte Bancaire",
        "Espèces",
        "Chèque",
        "Ticket Restaurant"
    };

    foreach (const QString &method, paymentMethods) {
        QPushButton *button = new QPushButton(method, this);
        button->setStyleSheet(
            "QPushButton {"
            "   padding: 10px;"
            "   font-size: 14px;"
            "   margin: 5px;"
            "   background-color: #D4A76A;"
            "   color: white;"
            "   border: none;"
            "   border-radius: 4px;"
            "}"
            "QPushButton:hover {"
            "   background-color: #45a049;"
            "}"
            );
        paymentLayout->addWidget(button);

        if (method == "Carte Bancaire") {
            connect(button, &QPushButton::clicked, this, &paiement::openCarteBancairePage);
        }
        else if (method == "Espèces") {
            connect(button, &QPushButton::clicked, this, &paiement::openEspecesPage);
        }
        // Vous pouvez ajouter d'autres méthodes de paiement ici
        else if (method == "Chèque") {  // Ajoutez cette condition
            connect(button, &QPushButton::clicked, this, &paiement::openChequePage);
        }
        // Dans setupPaymentButtons(), ajoutez cette condition :
        else if (method == "Ticket Restaurant") {
            connect(button, &QPushButton::clicked, this, &paiement::openTicketPage);
        }
    }

    mainLayout->insertLayout(0, paymentLayout);
}

void paiement::onButtonBoxAccepted()
{
    QMessageBox::information(this, "Paiement", "Paiement effectué avec succès");
    accept();
}

void paiement::openCarteBancairePage()
{
    carteBancaire *cb = new carteBancaire(this);
    cb->exec();
    delete cb;
}

// void paiement::openEspecesPage()
// {
//     especes *esp = new especes(this);
//     esp->exec();
//     delete esp;
// }




// void paiement::openEspecesPage()
// {
//     // Obtenez l'ID de commande actuelle
//     int idCommande = obtenirIdCommandeCourante();

//     if (idCommande <= 0) {
//         QMessageBox::warning(this, "Erreur", "Aucune commande sélectionnée");
//         return;
//     }

//     especes *esp = new especes(idCommande, this);  // Passer l'ID de commande, pas this
//     esp->exec();
//     delete esp;
// }

int paiement::obtenirIdCommandeCourante()
{
    QSqlQuery query;
    query.exec("SELECT id FROM commandes WHERE payee = 0 ORDER BY id DESC LIMIT 1");
    return query.next() ? query.value(0).toInt() : -1;
}



// [Tout le code existant reste inchangé avant le constructeur]

// paiement::paiement(QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::paiement),
//     mainLayout(new QVBoxLayout(this))
// {
//     ui->setupUi(this);
//     setWindowTitle("Paiement");

//     // Appliquer le fond
//     setBackground();

//     // [Tout le reste du code constructeur existant reste inchangé]
// }

// // [Toutes les méthodes existantes restent inchangées]

// // Ajoutez ces nouvelles méthodes à la fin du fichier
void paiement::setBackground()
{
    // Style pour le fond
    this->setStyleSheet(
        "QDialog {"
        "   background-image: url(:/images/background.jpg);"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   background-size: cover;"
        "}"

        "QWidget {"
        "   background-color: rgba(255, 255, 255, 0.7);"  // Fond semi-transparent pour les widgets
        "}"
        );
}

void paiement::resizeEvent(QResizeEvent *event)
{
    // Pour que l'image s'adapte au redimensionnement
    QPixmap bkgnd(":/background/img23.jpg");
    bkgnd = bkgnd.scaled(size(), Qt::IgnoreAspectRatio, Qt::SmoothTransformation);

    QPalette palette;
    palette.setBrush(QPalette::Window, bkgnd);
    this->setPalette(palette);

    QDialog::resizeEvent(event);
}


// void paiement::openChequePage()
// {
//     cheque *chq = new cheque(this);  // Crée une instance de la page chèque
//     chq->exec();                     // Affiche la page en mode modal
//     delete chq;                      // Nettoie la mémoire après fermeture
// }


void paiement::openChequePage()
{
    // Vous devez passer l'ID de la commande actuelle
    // Remplacez 123 par l'ID réel de la commande
    cheque *chq = new cheque(123, this);
    chq->exec();
    delete chq;
}
// Ajoutez cette nouvelle méthode :
// void paiement::openTicketPage()
// {
//     ticket *tkt = new ticket(this);
//     tkt->exec();
//     delete tkt;
// }


void paiement::openTicketPage()
{
    // Utilisez un ID client de test (remplacez 1 par un ID existant)
    int idClientTest = 1;

    ticket *tkt = new ticket(idClientTest, this);
    tkt->exec();
    delete tkt;
}
// Ajoutez l'implémentation manquante
void paiement::openEspecesPage()
{
    // Implémentation de la méthode
    qDebug() << "Page espèces ouverte";

    // Exemple d'implémentation :
    QDialog *especesDialog = new QDialog(this);
    especesDialog->setWindowTitle("Paiement en espèces");

    QVBoxLayout *layout = new QVBoxLayout(especesDialog);
    layout->addWidget(new QLabel("Montant à payer en espèces:"));
    // ... ajoutez d'autres widgets au besoin ...

    especesDialog->exec();
}

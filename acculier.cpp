#include "acculier.h"
#include "ui_acculier.h"

#include <QDebug>
#include<QLabel>
#include <QMessageBox>
#include <QRegularExpression>
#include "connexion.h"  // Ajoutez cette ligne en haut du fichier

Acculier::Acculier(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Dialog),  // Utiliser Dialog comme dans le fichier UI
    menuWindow(nullptr),
    commandeWindow(nullptr),
    reservationWindow(nullptr)  ,// Initialisez le pointeur
    localisationWindow(nullptr),
    personnelWindow(nullptr) , // Initialisez le nouveau pointeur
    historiqueWindow(nullptr)  // Ajoutez cette initialisatio
{
    ui->setupUi(this);
    setWindowTitle("Tableau de bord");

    if(!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Impossible de se connecter à la base de données");
    }
    loadImageToFrame();
    // Configuration initiale
    ui->label->setText("<a href='#' style='color: #fff; text-decoration: none;'>🏠 Dashbord</a>");
    ui->label->setTextFormat(Qt::RichText);
    ui->label->setOpenExternalLinks(false);



    // Configuration du label_14 pour la gestion des réservations
    ui->label_14->setText("<a href='reservation_management' style='color: #fff; text-decoration: none;'>📅 Gestion des Réservations</a>");
    ui->label_14->setTextFormat(Qt::RichText);
    ui->label_14->setOpenExternalLinks(false);

    // Configuration du label_17 pour le personnel
    ui->label_17->setText("<a href='personnel' style='color: #fff; text-decoration: none;'>👥 Personnel</a>");
    ui->label_17->setTextFormat(Qt::RichText);
    ui->label_17->setOpenExternalLinks(false);
    ui->label_15->setText("<a href='historique' style='color: #fff; text-decoration: none;'>📊 Historique des visites</a>");
    ui->label_15->setTextFormat(Qt::RichText);
    ui->label_15->setOpenExternalLinks(false);


    // Connexions des signaux
    connect(ui->label, &QLabel::linkActivated, this, &Acculier::onDashboardClicked);
    connect(ui->pushButton, &QPushButton::clicked, this, &Acculier::onSearchClicked);
    connect(ui->lineEdit, &QLineEdit::textChanged, this, &Acculier::updateSearchResults);
    connect(ui->label_14, &QLabel::linkActivated, this, &Acculier::onReservationManagementClicked);  // Ajoutez cette ligne
    // Chargement initial
    connect(ui->label_17, &QLabel::linkActivated, this, &Acculier::onPersonnelClicked);
    connect(ui->label_15, &QLabel::linkActivated, this, &Acculier::onHistoriqueClicked);

    loadDashboardData();

    // Configuration des labels cliquables
    ui->label_2->setText("<a href='menu' style='color: #fff; text-decoration: none;'>🍽 Consultation du menu</a>");
    ui->label_3->setText("<a href='order' style='color: #fff; text-decoration: none;'>🛒 Commande en ligne</a>");
    ui->label_9->setText("<a href='reservation' style='color: #fff; text-decoration: none;'>📅 Réservation</a>");
    ui->label_4->setText("<a href='payment' style='color: #fff; text-decoration: none;'>💳 Paiement</a>");
    ui->label_5->setText("<a href='orderslist' style='color: #fff; text-decoration: none;'>🧾 Localisation</a>");

    // Formatage
    ui->label_2->setTextFormat(Qt::RichText);
    ui->label_3->setTextFormat(Qt::RichText);
    ui->label_9->setTextFormat(Qt::RichText);
    ui->label_4->setTextFormat(Qt::RichText);
    ui->label_5->setTextFormat(Qt::RichText);

    ui->label_6->setText("<a href='feedback' style='color: #fff; text-decoration: none;'>📝 Feedback</a>");
    ui->label_6->setTextFormat(Qt::RichText);
    ui->label_6->setOpenExternalLinks(false);




    // Connexions
    connect(ui->label_2, &QLabel::linkActivated, this, &Acculier::onMenuClicked);
    connect(ui->label_3, &QLabel::linkActivated, this, &Acculier::onOrderClicked);
    connect(ui->label_9, &QLabel::linkActivated, this, &Acculier::onReservationClicked);
    connect(ui->label_4, &QLabel::linkActivated, this, &Acculier::onPaymentClicked);
    // connect(ui->label_5, &QLabel::linkActivated, this, &Acculier::onOrdersListClicked);
    connect(ui->label_5, &QLabel::linkActivated, this, &Acculier::onLocalisationClicked);  // Modifiez cette ligne
    connect(ui->label_6, &QLabel::linkActivated, this, &Acculier::onFeedbackClicked);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &Acculier::onLoginButtonClicked);
}

Acculier::~Acculier()
{
    if(db.isOpen()) {
        db.close();
    }
    delete ui;
}

bool Acculier::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("gestion_restaurant.db");

    if (!db.open()) {
        qDebug() << "Erreur DB:" << db.lastError().text();
        return false;
    }

    return true;
}

// void Acculier::onDashboardClicked()
// {
//     loadDashboardData();
//     showAllSections(true);
// }

void Acculier::onSearchClicked()
{
    QString searchText = ui->lineEdit->text().trimmed();

    if(searchText.isEmpty()) {
        loadDashboardData();
        showAllSections(true);
        return;
    }

    searchInDatabase(searchText);
}

void Acculier::updateSearchResults(const QString &searchText)
{
    if(searchText.length() >= 3) {
        onSearchClicked();
    }
}

void Acculier::loadDashboardData()
{
    // Commandes du jour
    QSqlQuery query;
    if(query.exec("SELECT COUNT(*) FROM commandes WHERE date = DATE('now')") && query.next()) {
        ui->label_12->setText("✅ Nombre total de ");
        ui->label_13->setText(query.value(0).toString() + " commandes du jour");
    }

    // Plats populaires
    if(query.exec("SELECT nom FROM plats ORDER BY commandes DESC LIMIT 3")) {
        QStringList plats;
        while(query.next()) {
            plats << query.value(0).toString();
        }
        // ui->label_14->setText("🍱 " + plats.join(", "));
    }

    // Commandes urgentes
    if(query.exec("SELECT COUNT(*) FROM commandes WHERE statut = 'urgent'")) {
        if(query.next()) {
            //  ui->label_15->setText("⚠ " + query.value(0).toString() + " commandes urgentes");
        }
    }

    // Nouvelles inscriptions
    if(query.exec("SELECT COUNT(*) FROM clients WHERE date >= DATE('now', '-7 days')")) {
        if(query.next()) {
            //  ui->label_16->setText("🔔 " + query.value(0).toString() + " nouveaux clients (7j)");
        }
    }
}

void Acculier::searchInDatabase(const QString &term)
{
    QString searchTerm = term.toLower().trimmed();

    // Masquer toutes les sections d'abord
    showAllSections(false);

    // Dictionnaire des termes de recherche et des sections correspondantes
    QHash<QString, QString> keywordMap = {
        {"commande", "commandes"},
        {"total", "commandes"},
        {"jour", "commandes"},
        {"plat", "plats"},
        {"populaire", "plats"},
        {"menu", "plats"},
        {"urgent", "urgentes"},
        {"urgence", "urgentes"},
        {"client", "clients"},
        {"inscription", "clients"},
        {"nouveau", "clients"}
    };

    // Trouver la section correspondante
    QString foundSection;
    for (auto it = keywordMap.begin(); it != keywordMap.end(); ++it) {
        if (searchTerm.contains(it.key())) {
            foundSection = it.value();
            break;
        }
    }

    // Afficher la section correspondante
    if (!foundSection.isEmpty()) {
        showSection(foundSection, true);

        // Mettre à jour les données si nécessaire
        if (foundSection == "commandes") {
            QSqlQuery query;
            if(query.exec("SELECT client, plat FROM commandes WHERE date = DATE('now') LIMIT 5")) {
                QStringList details;
                while(query.next()) {
                    details << QString("- %1: %2").arg(query.value(0).toString(), query.value(1).toString());
                }
                ui->label_13->setText(ui->label_13->text() + "\n\nDétails:\n" + details.join("\n"));
            }
        }
    } else {
        ui->label_13->setText("🔍 Aucune section trouvée pour: " + term);
        ui->frame_3->show(); // Montrer au moins un cadre pour le message
    }
}

void Acculier::showAllSections(bool show)
{
    ui->frame_3->setVisible(show);    // Commandes
    ui->frame_4->setVisible(show);    // Urgentes
    /*ui->frame_6->setVisible(show); */   // Plats
    // ui->frame_7->setVisible(show);    // Clients
}

void Acculier::showSection(const QString &sectionName, bool show)
{
    if (sectionName == "commandes") {
        ui->frame_3->setVisible(show);
        ui->label_12->setVisible(show);
        ui->label_13->setVisible(show);
    }
    else if (sectionName == "plats") {
        //ui->frame_6->setVisible(show);
        //  ui->label_14->setVisible(show);
    }
    else if (sectionName == "urgentes") {
        ui->frame_4->setVisible(show);
        // ui->label_15->setVisible(show);
    }
    else if (sectionName == "clients") {
        //ui->frame_7->setVisible(show);
        // ui->label_16->setVisible(show);
    }
}

void Acculier::onMenuClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (menuWindow) {
        menuWindow->close();
        delete menuWindow;
    }

    // Créer et afficher la nouvelle fenêtre Menu
    menuWindow = new Menu(this);
    menuWindow->setWindowTitle("Menu du Restaurant");

    // Configuration de la fenêtre
    menuWindow->setWindowModality(Qt::ApplicationModal); // Rend modale
    menuWindow->setAttribute(Qt::WA_DeleteOnClose); // Auto-destruction

    // Connection pour la fermeture
    connect(menuWindow, &Menu::destroyed, this, [this]() {
        menuWindow = nullptr;
    });

    menuWindow->show();

    // Masquer l'accueil (optionnel)
    // this->hide();
}

void Acculier::onOrderClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (commandeWindow) {
        commandeWindow->close();
        delete commandeWindow;
    }

    // Créer et afficher la nouvelle fenêtre Commande
    commandeWindow = new commande(this);
    commandeWindow->setWindowTitle("Commande en ligne");

    // Configuration de la fenêtre
    commandeWindow->setWindowModality(Qt::ApplicationModal);
    commandeWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Connection pour la fermeture
    connect(commandeWindow, &commande::destroyed, this, [this]() {
        commandeWindow = nullptr;
    });

    commandeWindow->show();
}

void Acculier::onReservationClicked()
{
    // Même logique que pour la commande
    if (commandeWindow) {
        commandeWindow->close();
        delete commandeWindow;
    }

    commandeWindow = new commande(this);
    commandeWindow->setWindowTitle("Réservation et Commande");

    commandeWindow->setWindowModality(Qt::ApplicationModal);
    commandeWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(commandeWindow, &commande::destroyed, this, [this]() {
        commandeWindow = nullptr;
    });

    commandeWindow->show();
}

// void Acculier::onPaymentClicked()
// {
//     QMessageBox::information(this, "Paiement", "Paiement sélectionné");
//     // Logique pour le paiement
// }

void Acculier::onPaymentClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (paymentWindow) {
        paymentWindow->close();
        delete paymentWindow;
    }

    // Créer et afficher la nouvelle fenêtre de paiement
    paymentWindow = new paiement(this);
    paymentWindow->setWindowTitle("Paiement");

    // Configuration de la fenêtre
    paymentWindow->setWindowModality(Qt::ApplicationModal);
    paymentWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Connection pour la fermeture
    connect(paymentWindow, &paiement::destroyed, this, [this]() {
        paymentWindow = nullptr;
    });

    paymentWindow->show();
}

void Acculier::onOrdersListClicked()
{
    QMessageBox::information(this, "Commandes", "Liste des commandes sélectionnée");
    // Afficher la liste des commandes
}
void Acculier::loadImageToFrame()
{
    // ============ PREMIER FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel5 = new QLabel(ui->frame_5);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap5(":/background/img9.jpg");

    if(pixmap5.isNull()) {
        qDebug() << "Erreur: Impossible de charger img1.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel5->setPixmap(pixmap5.scaled(
            ui->frame_5->width() - 10,  // -10 pour la marge
            ui->frame_5->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel5->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel5->setGeometry(0, 0, ui->frame_5->width(), ui->frame_5->height());
    }

    // 6. Styler le premier frame
    ui->frame_5->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );






    // ============ FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel3 = new QLabel(ui->frame_3);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap3(":/background/img10.jpg");

    if(pixmap3.isNull()) {
        qDebug() << "Erreur: Impossible de charger img10.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel3->setPixmap(pixmap3.scaled(
            ui->frame_3->width() - 10,  // -10 pour la marge
            ui->frame_3->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel3->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel3->setGeometry(0, 0, ui->frame_3->width(), ui->frame_3->height());
    }

    // 6. Styler le premier frame
    ui->frame_3->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );






    // ============ FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel4 = new QLabel(ui->frame_4);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap4(":/background/img11.jpg");

    if(pixmap4.isNull()) {
        qDebug() << "Erreur: Impossible de charger img11.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel4->setPixmap(pixmap4.scaled(
            ui->frame_4->width() - 10,  // -10 pour la marge
            ui->frame_4->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel4->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel4->setGeometry(0, 0, ui->frame_4->width(), ui->frame_4->height());
    }

    // 6. Styler le premier frame
    ui->frame_4->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );





    // ============ FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel6 = new QLabel(ui->frame_6);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap6(":/background/Dessert.jpg");

    if(pixmap6.isNull()) {
        qDebug() << "Erreur: Impossible de charger img11.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel6->setPixmap(pixmap6.scaled(
            ui->frame_6->width() - 10,  // -10 pour la marge
            ui->frame_6->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel6->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel6->setGeometry(0, 0, ui->frame_6->width(), ui->frame_6->height());
    }

    // 6. Styler le premier frame
    ui->frame_6->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );



    // ============ FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel7 = new QLabel(ui->frame_7);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap7(":/background/img12.jpg");

    if(pixmap7.isNull()) {
        qDebug() << "Erreur: Impossible de charger img12.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel7->setPixmap(pixmap7.scaled(
            ui->frame_7->width() - 10,  // -10 pour la marge
            ui->frame_7->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel7->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel7->setGeometry(0, 0, ui->frame_7->width(), ui->frame_7->height());
    }

    // 6. Styler le premier frame
    ui->frame_7->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );



}


void Acculier::onReservationManagementClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (reservationWindow) {
        reservationWindow->close();
        delete reservationWindow;
    }

    // Créer et afficher la nouvelle fenêtre Reservation
    reservationWindow = new reservation(this);
    reservationWindow->setWindowTitle("Gestion des Réservations");

    // Configuration de la fenêtre
    reservationWindow->setWindowModality(Qt::ApplicationModal);
    reservationWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Connection pour la fermeture
    connect(reservationWindow, &reservation::destroyed, this, [this]() {
        reservationWindow = nullptr;
    });

    reservationWindow->show();
}

void Acculier::onLocalisationClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (localisationWindow) {
        localisationWindow->close();
        delete localisationWindow;
    }

    // Créer et afficher la nouvelle fenêtre Localisation
    localisationWindow = new localisation(this);
    localisationWindow->setWindowTitle("Localisation");

    // Configuration de la fenêtre
    localisationWindow->setWindowModality(Qt::ApplicationModal);
    localisationWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Connection pour la fermeture
    connect(localisationWindow, &localisation::destroyed, this, [this]() {
        localisationWindow = nullptr;
    });

    localisationWindow->show();
}

// void Acculier::onPersonnelClicked()
// {
//     // Fermer la fenêtre précédente si elle existe
//     if (personnelWindow) {
//         personnelWindow->close();
//         delete personnelWindow;
//     }

//     // Créer et afficher la nouvelle fenêtre Personnel
//     personnelWindow = new personnel(this);
//     personnelWindow->setWindowTitle("Gestion du Personnel");

//     // Configuration de la fenêtre
//     personnelWindow->setWindowModality(Qt::ApplicationModal);
//     personnelWindow->setAttribute(Qt::WA_DeleteOnClose);

//     // Connection pour la fermeture
//     connect(personnelWindow, &personnel::destroyed, this, [this]() {
//         personnelWindow = nullptr;
//     });

//     personnelWindow->show();
// }





void Acculier::onPersonnelClicked()
{
    if (personnelWindow) {
        personnelWindow->close();
        delete personnelWindow;
    }

    // Passez un ID utilisateur valide ici (par exemple, l'ID de l'utilisateur connecté)
    int currentUserId = 1; // Remplacez par l'ID réel
    personnelWindow = new personnel(currentUserId, this);
    personnelWindow->setWindowTitle("Gestion du Personnel");
    personnelWindow->setWindowModality(Qt::ApplicationModal);
    personnelWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(personnelWindow, &personnel::destroyed, this, [this]() {
        personnelWindow = nullptr;
    });

    personnelWindow->show();
}


// void Acculier::onFeedbackClicked()
// {
//     // Fermer la fenêtre précédente si elle existe
//     if (feedbackWindow) {
//         feedbackWindow->close();
//         delete feedbackWindow;
//     }

//     // Créer et afficher la nouvelle fenêtre Feedback
//     feedbackWindow = new feedback(this);
//     feedbackWindow->setWindowTitle("Feedback Clients");

//     // Configuration de la fenêtre
//     feedbackWindow->setWindowModality(Qt::ApplicationModal);
//     feedbackWindow->setAttribute(Qt::WA_DeleteOnClose);

//     // Connection pour la fermeture
//     connect(feedbackWindow, &feedback::destroyed, this, [this]() {
//         feedbackWindow = nullptr;
//     });

//     feedbackWindow->show();
// }



void Acculier::onFeedbackClicked()
{
    if (feedbackWindow) {
        feedbackWindow->close();
        delete feedbackWindow;
    }

    feedbackWindow = new feedback(this);
    feedbackWindow->setWindowModality(Qt::ApplicationModal);
    feedbackWindow->setAttribute(Qt::WA_DeleteOnClose);

    connect(feedbackWindow, &feedback::destroyed, this, [this]() {
        feedbackWindow = nullptr;
    });

    feedbackWindow->show();
}


void Acculier::onHistoriqueClicked()
{
    // Fermer la fenêtre précédente si elle existe
    if (historiqueWindow) {
        historiqueWindow->close();
        delete historiqueWindow;
    }

    // Créer et afficher la nouvelle fenêtre Historique
    historiqueWindow = new historique(this);
    historiqueWindow->setWindowTitle("Historique des Visites");

    // Configuration de la fenêtre
    historiqueWindow->setWindowModality(Qt::ApplicationModal);
    historiqueWindow->setAttribute(Qt::WA_DeleteOnClose);

    // Connection pour la fermeture
    connect(historiqueWindow, &historique::destroyed, this, [this]() {
        historiqueWindow = nullptr;
    });

    historiqueWindow->show();
}



void Acculier::onDashboardClicked()
{
    if (historiqueWindow) {
        historiqueWindow->ajouterVisite(QDateTime::currentDateTime());
    }

    loadDashboardData();
    showAllSections(true);
}


void Acculier::onLoginButtonClicked() {
    this->close();  // Ferme la fenêtre actuelle

    // Utilisez la classe Connexion (avec majuscule si c'est le nom de la classe)
    Connexion *connexionWindow = new Connexion();  // Notez la majuscule si c'est le nom de la classe
    connexionWindow->setWindowTitle("Page de Connexion");
    connexionWindow->show();
}

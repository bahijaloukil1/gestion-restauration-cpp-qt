// #include "ticket.h"
// #include "ui_ticket.h"

// ticket::ticket(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::ticket)
// {
//     ui->setupUi(this);
// }

// ticket::~ticket()
// {
//     delete ui;
// }





// #include "ticket.h"
// #include <QSqlQuery>
// #include <QMessageBox>
// #include <QDebug>
// #include <QStyle>
// #include <QSqlError>
// #include <QDateTime>
// #include <QLayoutItem>

// ticket::ticket(int idClient, QWidget *parent) :
//     QDialog(parent),
//     clientId(idClient),
//     selectedCommandId(-1) // Initialisation à -1 (aucune sélection)
// {
//     setupUI();
//     setWindowTitle("Tickets Restaurant");
//     resize(600, 500);

//     setupUI();

//     if(!initDatabase()) {
//         QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
//         return;
//     }

//     chargerCommandesClient();
// }

// ticket::~ticket()
// {
//     if(m_db.isOpen()) {
//         m_db.close();
//     }
// }

// void ticket::setupUI()
// {
//     // Configuration du layout principal
//     mainLayout = new QVBoxLayout(this);

//     // Zone de défilement pour les boutons de commande
//     scrollArea = new QScrollArea(this);
//     scrollWidget = new QWidget();
//     buttonsLayout = new QVBoxLayout(scrollWidget);
//     buttonsLayout->setAlignment(Qt::AlignTop);

//     scrollArea->setWidget(scrollWidget);
//     scrollArea->setWidgetResizable(true);

//     // Label pour afficher les détails
//     labelDetails = new QLabel("Sélectionnez une commande", this);
//     labelDetails->setWordWrap(true);
//     labelDetails->setAlignment(Qt::AlignLeft | Qt::AlignTop);
//     labelDetails->setStyleSheet("font-size: 14px; padding: 10px;");
//     labelDetails->setMinimumHeight(150);

//     // Layout pour les boutons d'action
//     actionsLayout = new QHBoxLayout();
//     actionsLayout->setSpacing(10);

//     // Organisation des widgets
//     mainLayout->addWidget(scrollArea);
//     mainLayout->addWidget(labelDetails);
//     mainLayout->addLayout(actionsLayout);

//     // Style général
//     setStyleSheet(
//         "QDialog { background-color: #f5f5f5; }"
//         "QPushButton {"
//         "   padding: 10px;"
//         "   background-color: #4CAF50;"
//         "   color: white;"
//         "   border: none;"
//         "   border-radius: 4px;"
//         "   min-width: 200px;"
//         "}"
//         "QPushButton:hover { background-color: #45a049; }"
//         "QLabel { background-color: white; border-radius: 5px; }"
//         );
// }

// bool ticket::initDatabase()
// {
//     m_db = QSqlDatabase::addDatabase("QSQLITE", "ticket_connection");
//     m_db.setDatabaseName("gestion_restaurant.db");

//     if (!m_db.open()) {
//         QSqlError err = m_db.lastError();
//         qDebug() << "Erreur DB:" << err.text();
//         return false;
//     }
//     return true;
// }

// // void ticket::chargerCommandesClient()
// // {
// //     QSqlQuery query(m_db);
// //     query.prepare("SELECT id, date_creation, total FROM commandes WHERE client_id = ? AND statut = 'payé'");
// //     query.addBindValue(clientId);

// //     if(!query.exec()) {
// //         QSqlError err = query.lastError();
// //         QMessageBox::warning(this, "Erreur", "Impossible de charger les commandes: " + err.text());
// //         return;
// //     }

// //     if(!query.size()) {
// //         QLabel *emptyLabel = new QLabel("Aucune commande trouvée", scrollWidget);
// //         emptyLabel->setAlignment(Qt::AlignCenter);
// //         buttonsLayout->addWidget(emptyLabel);
// //         return;
// //     }

// //     while(query.next()) {
// //         int idCommande = query.value(0).toInt();
// //         QDateTime date = query.value(1).toDateTime();
// //         QString dateStr = date.toString("dd/MM/yyyy HH:mm");
// //         double total = query.value(2).toDouble();

// //         QPushButton *btn = new QPushButton(
// //             QString("Commande #%1 - %2 - %3 €").arg(idCommande).arg(dateStr).arg(total, 0, 'f', 2),
// //             scrollWidget
// //             );

// //         btn->setProperty("commandeId", idCommande);
// //         btn->setCursor(Qt::PointingHandCursor);
// //         connect(btn, &QPushButton::clicked, this, &ticket::onCommandeClicked);

// //         buttonsLayout->addWidget(btn);
// //     }
// // }

// // void ticket::chargerCommandesClient()
// // {
// //     // Nettoyer les anciens boutons s'ils existent
// //     QLayoutItem* item;
// //     while ((item = buttonsLayout->takeAt(0)) != nullptr) {
// //         if (item->widget()) {
// //             delete item->widget();
// //         }
// //         delete item;
// //     }

// //     QSqlQuery query(m_db);

// //     // Debug important
// //     qDebug() << "Connexion DB ouverte ?" << m_db.isOpen();
// //     qDebug() << "Tentative de chargement des commandes pour client ID:" << clientId;

// //     // Version avec statut 'payé'
// //     query.prepare("SELECT id, date_creation, total FROM commandes WHERE client_id = ? AND statut = 'payé'");
// //     query.addBindValue(clientId);

// //     if(!query.exec()) {
// //         QSqlError err = query.lastError();
// //         qDebug() << "Erreur requête (avec statut):" << err.text();

// //         // Fallback - version sans statut
// //         query.prepare("SELECT id, date_creation, total FROM commandes WHERE client_id = ?");
// //         query.addBindValue(clientId);

// //         if(!query.exec()) {
// //             QSqlError fallbackErr = query.lastError();
// //             qDebug() << "Erreur requête (sans statut):" << fallbackErr.text();

// //             QLabel *errorLabel = new QLabel(
// //                 "Erreur de chargement:\n" + fallbackErr.text(),
// //                 scrollWidget
// //                 );
// //             errorLabel->setAlignment(Qt::AlignCenter);
// //             errorLabel->setStyleSheet("color: red;");
// //             buttonsLayout->addWidget(errorLabel);

// //             return;
// //         }
// //     }

// //     // Vérifier si des résultats existent
// //     if(!query.size()) {
// //         QLabel *emptyLabel = new QLabel(
// //             "Aucune commande trouvée pour ce client",
// //             scrollWidget
// //             );
// //         emptyLabel->setAlignment(Qt::AlignCenter);
// //         emptyLabel->setStyleSheet("font-style: italic;");
// //         buttonsLayout->addWidget(emptyLabel);
// //         return;
// //     }

// //     // Parcourir les résultats
// //     while(query.next()) {
// //         int idCommande = query.value(0).toInt();
// //         QDateTime date = query.value(1).toDateTime();
// //         QString dateStr = date.toString("dd/MM/yyyy HH:mm");
// //         double total = query.value(2).toDouble();

// //         QPushButton *btn = new QPushButton(
// //             QString("Commande #%1 - %2 - %3 €")
// //                 .arg(idCommande)
// //                 .arg(dateStr)
// //                 .arg(total, 0, 'f', 2),
// //             scrollWidget
// //             );

// //         // Style du bouton
// //         btn->setStyleSheet(
// //             "QPushButton {"
// //             "   text-align: left;"
// //             "   padding: 8px;"
// //             "   margin: 2px;"
// //             "   background-color: #f8f8f8;"
// //             "   border: 1px solid #ddd;"
// //             "}"
// //             "QPushButton:hover {"
// //             "   background-color: #e8e8e8;"
// //             "}"
// //             );

// //         btn->setProperty("commandeId", idCommande);
// //         btn->setCursor(Qt::PointingHandCursor);
// //         connect(btn, &QPushButton::clicked, this, &ticket::onCommandeClicked);

// //         buttonsLayout->addWidget(btn);
// //     }

// //     // Ajouter un stretch pour pousser les boutons vers le haut
// //     buttonsLayout->addStretch();
// // }





// void ticket::chargerCommandesClient()
// {


//         QPushButton *btn = new QPushButton(/*...*/, scrollWidget);
//         btn->setProperty("commandeId", idCommande); // ESSENTIEL !

//         // Style de base
//         btn->setStyleSheet(
//             "QPushButton {"
//             "   text-align: left;"
//             "   padding: 8px;"
//             "   margin: 2px;"
//             "   background-color: #f8f8f8;"
//             "   border: 1px solid #ddd;"
//             "}"
//             "QPushButton:hover {"
//             "   background-color: #e8e8e8;"
//             "}"
//             );

//         // Connexion VERIFIEE
//         connect(btn, &QPushButton::clicked, this, &ticket::onCommandeClicked);

//         buttonsLayout->addWidget(btn);
//     }
// }



// // void ticket::onCommandeClicked()
// // {
// //     QPushButton *btn = qobject_cast<QPushButton*>(sender());
// //     if(btn) {
// //         afficherDetailsCommande(btn->property("commandeId").toInt());
// //     }
// // }




// // void ticket::onCommandeClicked()
// // {
// //     QPushButton *btn = qobject_cast<QPushButton*>(sender());
// //     if (btn) {
// //         selectedCommandId = btn->property("commandeId").toInt();
// //         qDebug() << "Commande sélectionnée :" << selectedCommandId; // Debug utile
// //         afficherDetailsCommande(selectedCommandId);
// //     }
// // }


// void ticket::onCommandeClicked()
// {
//     QPushButton *clickedButton = qobject_cast<QPushButton*>(sender());
//     if (!clickedButton) {
//         qDebug() << "Erreur: L'émetteur n'est pas un QPushButton";
//         return;
//     }

//     // Désélectionner le précédent bouton
//     if (lastSelectedButton) {
//         lastSelectedButton->setStyleSheet(""); // Réinitialiser le style
//     }

//     // Mettre à jour la sélection
//     selectedCommandId = clickedButton->property("commandeId").toInt();
//     lastSelectedButton = clickedButton;

//     // Style visuel pour la sélection
//     clickedButton->setStyleSheet(
//         "background-color: #4CAF50;"
//         "color: white;"
//         "border: 1px solid #45a049;"
//         );

//     qDebug() << "Commande sélectionnée ID:" << selectedCommandId;
//     afficherDetailsCommande(selectedCommandId);
// }
// void ticket::afficherDetailsCommande(int idCommande)
// {


//     qDebug() << "Tentative d'affichage pour commande ID:" << idCommande;

//     if (idCommande <= 0) {
//         qDebug() << "ID de commande invalide !";
//         return;
//     }
//     QSqlQuery query(m_db);
//     query.prepare(
//         "SELECT p.nom, lc.quantite, p.prix, (lc.quantite * p.prix) as total_ligne "
//         "FROM ligne_commande lc "
//         "JOIN produits p ON lc.produit_id = p.id "
//         "WHERE lc.commande_id = ?"
//         );
//     query.addBindValue(idCommande);

//     if(!query.exec()) {
//         QMessageBox::warning(this, "Erreur", "Impossible de charger les détails");
//         return;
//     }

//     QString details = QString("<h3>Ticket Restaurant - Commande #%1</h3>").arg(idCommande);
//     double total = 0;

//     details += "<table style='width:100%; border-collapse:collapse;'>";
//     details += "<tr><th style='text-align:left; padding:5px;'>Produit</th>"
//                "<th style='text-align:right; padding:5px;'>Qté</th>"
//                "<th style='text-align:right; padding:5px;'>Prix U.</th>"
//                "<th style='text-align:right; padding:5px;'>Total</th></tr>";

//     while(query.next()) {
//         QString nom = query.value(0).toString();
//         int quantite = query.value(1).toInt();
//         double prix = query.value(2).toDouble();
//         double totalLigne = query.value(3).toDouble();

//         details += QString("<tr>"
//                            "<td style='padding:5px;'>%1</td>"
//                            "<td style='text-align:right; padding:5px;'>%2</td>"
//                            "<td style='text-align:right; padding:5px;'>%3 €</td>"
//                            "<td style='text-align:right; padding:5px;'>%4 €</td>"
//                            "</tr>")
//                        .arg(nom)
//                        .arg(quantite)
//                        .arg(prix, 0, 'f', 2)
//                        .arg(totalLigne, 0, 'f', 2);

//         total += totalLigne;
//     }

//     details += QString("<tr><td colspan='3' style='text-align:right; padding:5px; border-top:1px solid #ddd;'><strong>Total</strong></td>"
//                        "<td style='text-align:right; padding:5px; border-top:1px solid #ddd;'><strong>%1 €</strong></td></tr>")
//                    .arg(total, 0, 'f', 2);
//     details += "</table>";

//     labelDetails->setText(details);
//     creerBoutonsActions();
// }

// void ticket::creerBoutonsActions()
// {
//     // Nettoyer les anciens boutons
//     QLayoutItem* item;
//     while ((item = actionsLayout->takeAt(0)) != nullptr) {
//         if (item->widget()) {
//             delete item->widget();
//         }
//         delete item;
//     }

//     // Créer les boutons d'action
//     QPushButton *btnImprimer = new QPushButton("Imprimer", this);
//     QPushButton *btnEmail = new QPushButton("Envoyer par email", this);
//     QPushButton *btnQR = new QPushButton("Générer QR Code", this);

//     // Style spécifique pour les boutons d'action
//     QString actionStyle = "QPushButton { padding: 8px 15px; min-width: 120px; }";
//     btnImprimer->setStyleSheet(actionStyle + "background-color: #2196F3;");
//     btnEmail->setStyleSheet(actionStyle + "background-color: #FF9800;");
//     btnQR->setStyleSheet(actionStyle + "background-color: #9C27B0;");

//     // Connexions
//     connect(btnImprimer, &QPushButton::clicked, this, &ticket::imprimerTicket);
//     connect(btnEmail, &QPushButton::clicked, this, &ticket::envoyerParEmail);
//     connect(btnQR, &QPushButton::clicked, this, &ticket::genererQRCode);

//     // Ajout au layout
//     actionsLayout->addWidget(btnImprimer);
//     actionsLayout->addWidget(btnEmail);
//     actionsLayout->addWidget(btnQR);
//     actionsLayout->addStretch();
// }

// void ticket::imprimerTicket()
// {
//     QMessageBox::information(this, "Impression", "Le ticket a été envoyé à l'imprimante");
//     // Implémentation réelle de l'impression ici
// }

// void ticket::envoyerParEmail()
// {
//     QMessageBox::information(this, "Email", "Le ticket a été envoyé par email");
//     // Implémentation réelle de l'envoi email ici
// }

// void ticket::genererQRCode()
// {
//     QMessageBox::information(this, "QR Code", "QR Code généré pour ce ticket");
//     // Implémentation réelle du QR Code ici
// }






// #include "ticket.h"
// #include <QSqlQuery>
// #include <QMessageBox>
// #include <QDebug>
// #include <QDateTime>
// #include <QLayoutItem>
// #include <QSqlError>
// #include <QDir>
// #include <QPalette>

// ticket::ticket(int idClient, QWidget *parent) :
//     QDialog(parent),
//     clientId(idClient),
//     selectedCommandId(-1),
//     lastSelectedButton(nullptr),
//     scrollArea(nullptr),
//     scrollWidget(nullptr),
//     mainLayout(nullptr),
//     buttonsLayout(nullptr),
//     actionsLayout(nullptr),
//     labelDetails(nullptr)
// {
//     setWindowTitle("Tickets Restaurant");
//     resize(600, 500);

//     // Initialisation de l'interface
//     setupUI();

//     // Connexion à la base de données
//     if(!initDatabase()) {
//         QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
//         return;
//     }

//     // Chargement des commandes
//     chargerCommandesClient();
// }

// ticket::~ticket()
// {
//     if(m_db.isOpen()) {
//         m_db.close();
//     }
// }

// void ticket::setupUI()
// {
//     // Layout principal
//     mainLayout = new QVBoxLayout(this);
//     mainLayout->setContentsMargins(10, 10, 10, 10);
//     mainLayout->setSpacing(10);

//     // Zone de défilement pour les commandes
//     scrollArea = new QScrollArea(this);
//     scrollArea->setWidgetResizable(true);
//     scrollArea->setFrameShape(QFrame::NoFrame);

//     scrollWidget = new QWidget();
//     buttonsLayout = new QVBoxLayout(scrollWidget);
//     buttonsLayout->setAlignment(Qt::AlignTop);
//     buttonsLayout->setSpacing(5);

//     scrollArea->setWidget(scrollWidget);

//     // Zone d'affichage des détails
//     labelDetails = new QLabel("Sélectionnez une commande", this);
//     labelDetails->setWordWrap(true);
//     labelDetails->setAlignment(Qt::AlignLeft | Qt::AlignTop);
//     labelDetails->setMinimumHeight(150);
//     labelDetails->setSizePolicy(QSizePolicy::Expanding, QSizePolicy::MinimumExpanding);

//     // Layout pour les boutons d'action
//     actionsLayout = new QHBoxLayout();
//     actionsLayout->setSpacing(10);

//     // Organisation de l'interface
//     mainLayout->addWidget(scrollArea);
//     mainLayout->addWidget(labelDetails);
//     mainLayout->addLayout(actionsLayout);

//     // Style CSS
//     setStyleSheet(R"(
//         QDialog {
//             background-color: #f5f5f5;
//             font-family: Arial;
//         }
//         QScrollArea {
//             background: transparent;
//             border: 1px solid #ddd;
//             border-radius: 5px;
//         }
//         QPushButton {
//             padding: 8px;
//             margin: 2px;
//             text-align: left;
//             background-color: #f8f8f8;
//             border: 1px solid #ddd;
//             border-radius: 4px;
//         }
//         QPushButton:hover {
//             background-color: #e8e8e8;
//         }
//         QLabel {
//             background-color: white;
//             border-radius: 5px;
//             padding: 10px;
//             border: 1px solid #ddd;
//         }
//     )");
// }

// bool ticket::initDatabase()
// {
//     // Vérification du chemin de la base de données
//     QString dbPath = QDir::currentPath() + "/gestion_restaurant.db";
//     qDebug() << "Chemin de la base de données:" << dbPath;

//     m_db = QSqlDatabase::addDatabase("QSQLITE", "ticket_connection");
//     m_db.setDatabaseName(dbPath);

//     if (!m_db.open()) {
//         QSqlError err = m_db.lastError();
//         qDebug() << "Erreur de connexion à la base de données:" << err.text();
//         return false;
//     }

//     return true;
// }

// void ticket::chargerCommandesClient()
// {
//     // Nettoyage des anciens boutons
//     QLayoutItem* item;
//     while ((item = buttonsLayout->takeAt(0)) != nullptr) {
//         if (item->widget()) {
//             delete item->widget();
//         }
//         delete item;
//     }

//     // Vérification de la connexion
//     if (!m_db.isOpen()) {
//         QLabel *errorLabel = new QLabel("Erreur: Base de données non connectée", scrollWidget);
//         errorLabel->setStyleSheet("color: red;");
//         buttonsLayout->addWidget(errorLabel);
//         return;
//     }

//     // Requête SQL
//     QSqlQuery query(m_db);
//     query.prepare("SELECT id, date_creation, total FROM commandes WHERE client_id = ?");
//     query.addBindValue(clientId);

//     if (!query.exec()) {
//         QLabel *errorLabel = new QLabel(
//             "Erreur de chargement:\n" + query.lastError().text(),
//             scrollWidget
//             );
//         errorLabel->setStyleSheet("color: red;");
//         buttonsLayout->addWidget(errorLabel);
//         return;
//     }

//     if (query.size() == 0) {
//         QLabel *emptyLabel = new QLabel("Aucune commande disponible", scrollWidget);
//         emptyLabel->setStyleSheet("font-style: italic; color: #666;");
//         buttonsLayout->addWidget(emptyLabel);
//         return;
//     }

//     // Création des boutons pour chaque commande
//     while (query.next()) {
//         int idCommande = query.value(0).toInt();
//         QDateTime date = query.value(1).toDateTime();
//         double total = query.value(2).toDouble();

//         QPushButton *btn = new QPushButton(
//             QString("Commande #%1 - %2 - %3 €")
//                 .arg(idCommande)
//                 .arg(date.toString("dd/MM/yyyy HH:mm"))
//                 .arg(total, 0, 'f', 2),
//             scrollWidget
//             );

//         // Configuration du bouton
//         btn->setProperty("commandeId", idCommande);
//         btn->setCursor(Qt::PointingHandCursor);
//         connect(btn, &QPushButton::clicked, this, &ticket::onCommandeClicked);

//         buttonsLayout->addWidget(btn);
//     }

//     // Ajout d'un espace flexible
//     buttonsLayout->addStretch();
// }

// void ticket::onCommandeClicked()
// {
//     QPushButton *btn = qobject_cast<QPushButton*>(sender());
//     if (!btn) {
//         qDebug() << "Erreur: Impossible de caster le sender en QPushButton";
//         return;
//     }

//     // Désélection de l'ancien bouton
//     if (lastSelectedButton) {
//         lastSelectedButton->setStyleSheet("");
//     }

//     // Mise à jour de la sélection
//     selectedCommandId = btn->property("commandeId").toInt();
//     lastSelectedButton = btn;

//     // Style du bouton sélectionné
//     btn->setStyleSheet(R"(
//         background-color: #4CAF50;
//         color: white;
//         border: 1px solid #45a049;
//     )");

//     // Affichage des détails
//     afficherDetailsCommande(selectedCommandId);
// }

// void ticket::afficherDetailsCommande(int idCommande)
// {
//     if (idCommande <= 0) {
//         labelDetails->setText("ID de commande invalide");
//         return;
//     }

//     QSqlQuery query(m_db);
//     query.prepare(R"(
//         SELECT p.nom, lc.quantite, p.prix, (lc.quantite * p.prix) as total_ligne
//         FROM ligne_commande lc
//         JOIN produits p ON lc.produit_id = p.id
//         WHERE lc.commande_id = ?
//     )");
//     query.addBindValue(idCommande);

//     if (!query.exec()) {
//         labelDetails->setText("Erreur de chargement des détails");
//         qDebug() << "Erreur requête détails:" << query.lastError().text();
//         return;
//     }

//     // Construction du HTML pour l'affichage
//     QString html = QString("<h3>Détails de la commande #%1</h3>").arg(idCommande);
//     html += "<table style='width:100%; border-collapse:collapse; margin-top:10px;'>";
//     html += "<tr style='background-color:#f2f2f2;'>"
//             "<th style='padding:8px; text-align:left;'>Produit</th>"
//             "<th style='padding:8px; text-align:right;'>Quantité</th>"
//             "<th style='padding:8px; text-align:right;'>Prix unitaire</th>"
//             "<th style='padding:8px; text-align:right;'>Total</th>"
//             "</tr>";

//     double totalGeneral = 0;
//     while (query.next()) {
//         QString nom = query.value(0).toString();
//         int quantite = query.value(1).toInt();
//         double prix = query.value(2).toDouble();
//         double totalLigne = query.value(3).toDouble();
//         totalGeneral += totalLigne;

//         html += QString("<tr>"
//                         "<td style='padding:6px; border-bottom:1px solid #eee;'>%1</td>"
//                         "<td style='padding:6px; border-bottom:1px solid #eee; text-align:right;'>%2</td>"
//                         "<td style='padding:6px; border-bottom:1px solid #eee; text-align:right;'>%3 €</td>"
//                         "<td style='padding:6px; border-bottom:1px solid #eee; text-align:right;'>%4 €</td>"
//                         "</tr>")
//                     .arg(nom)
//                     .arg(quantite)
//                     .arg(prix, 0, 'f', 2)
//                     .arg(totalLigne, 0, 'f', 2);
//     }

//     // Ligne du total général
//     html += QString("<tr style='background-color:#f9f9f9;'>"
//                     "<td colspan='3' style='padding:8px; text-align:right; font-weight:bold;'>Total</td>"
//                     "<td style='padding:8px; text-align:right; font-weight:bold;'>%1 €</td>"
//                     "</tr>")
//                 .arg(totalGeneral, 0, 'f', 2);

//     html += "</table>";
//     labelDetails->setText(html);

//     // Création des boutons d'action
//     creerBoutonsActions();
// }

// void ticket::creerBoutonsActions()
// {
//     // Nettoyage des anciens boutons
//     QLayoutItem* item;
//     while ((item = actionsLayout->takeAt(0)) != nullptr) {
//         if (item->widget()) {
//             delete item->widget();
//         }
//         delete item;
//     }

//     // Création des boutons
//     QPushButton *btnImprimer = new QPushButton("Imprimer", this);
//     QPushButton *btnEmail = new QPushButton("Envoyer par email", this);
//     QPushButton *btnQR = new QPushButton("Générer QR Code", this);

//     // Style des boutons
//     QString buttonStyle = R"(
//         QPushButton {
//             padding: 8px 15px;
//             min-width: 120px;
//             color: white;
//             border: none;
//             border-radius: 4px;
//         }
//     )";

//     btnImprimer->setStyleSheet(buttonStyle + "background-color: #2196F3;");
//     btnEmail->setStyleSheet(buttonStyle + "background-color: #FF9800;");
//     btnQR->setStyleSheet(buttonStyle + "background-color: #9C27B0;");

//     // Connexions des signaux
//     connect(btnImprimer, &QPushButton::clicked, this, &ticket::imprimerTicket);
//     connect(btnEmail, &QPushButton::clicked, this, &ticket::envoyerParEmail);
//     connect(btnQR, &QPushButton::clicked, this, &ticket::genererQRCode);

//     // Ajout au layout
//     actionsLayout->addWidget(btnImprimer);
//     actionsLayout->addWidget(btnEmail);
//     actionsLayout->addWidget(btnQR);
//     actionsLayout->addStretch();
// }

// void ticket::imprimerTicket()
// {
//     if (selectedCommandId <= 0) {
//         QMessageBox::warning(this, "Impression", "Aucune commande sélectionnée");
//         return;
//     }
//     QMessageBox::information(this, "Impression",
//                              QString("Impression de la commande #%1").arg(selectedCommandId));
// }

// void ticket::envoyerParEmail()
// {
//     if (selectedCommandId <= 0) {
//         QMessageBox::warning(this, "Email", "Aucune commande sélectionnée");
//         return;
//     }
//     QMessageBox::information(this, "Email",
//                              QString("Envoi par email de la commande #%1").arg(selectedCommandId));
// }

// void ticket::genererQRCode()
// {
//     if (selectedCommandId <= 0) {
//         QMessageBox::warning(this, "QR Code", "Aucune commande sélectionnée");
//         return;
//     }
//     QMessageBox::information(this, "QR Code",
//                              QString("Génération du QR Code pour la commande #%1").arg(selectedCommandId));
// }




// #include "ticket.h"
// #include "ui_ticket.h"

// #include <QSqlQuery>
// #include <QMessageBox>
// #include <QDebug>
// #include <QDateTime>
// #include <QPushButton>
// #include <QTextDocument>
// #include <QPrinter>
// #include <QPrintDialog>
// #include <QDir>

// ticket::ticket(int idClient, QWidget *parent) :
//     QDialog(parent),
//     ui(new Ui::ticket),
//     clientId(idClient),
//     selectedCommandId(-1),
//     ticketDetails(nullptr),
//     commandesContainer(nullptr),
//     commandesLayout(nullptr),
//     scrollArea(nullptr)
// {
//     ui->setupUi(this);
//     setWindowTitle("Gestion des Tickets Restaurant");
//     resize(900, 700);

//     setupUI();

//     if(!initDatabase()) {
//         QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
//         return;
//     }

//     chargerCommandesClient();
// }

// void ticket::setupUI()
// {
//     // Layout principal
//     QVBoxLayout *mainLayout = new QVBoxLayout(this);
//     mainLayout->setContentsMargins(20, 20, 20, 20);
//     mainLayout->setSpacing(15);

//     // Header
//     QLabel *header = new QLabel("Mes Tickets Restaurant", this);
//     header->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50;");
//     mainLayout->addWidget(header, 0, Qt::AlignCenter);

//     // Section commandes
//     QGroupBox *commandesGroup = new QGroupBox("Commandes disponibles", this);
//     QVBoxLayout *commandesGroupLayout = new QVBoxLayout(commandesGroup);

//     scrollArea = new QScrollArea(this);
//     scrollArea->setWidgetResizable(true);
//     commandesContainer = new QWidget();
//     commandesLayout = new QVBoxLayout(commandesContainer);
//     commandesLayout->setAlignment(Qt::AlignTop);
//     commandesLayout->setSpacing(10);
//     scrollArea->setWidget(commandesContainer);
//     commandesGroupLayout->addWidget(scrollArea);

//     // Détails commande
//     QGroupBox *detailsGroup = new QGroupBox("Détails du ticket", this);
//     QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);
//     ticketDetails = new QTextEdit(this);
//     ticketDetails->setReadOnly(true);
//     detailsLayout->addWidget(ticketDetails);

//     // Boutons d'action
//     QHBoxLayout *btnLayout = new QHBoxLayout();
//     QPushButton *btnPrint = new QPushButton("Imprimer", this);
//     QPushButton *btnEmail = new QPushButton("Envoyer par email", this);
//     QPushButton *btnClose = new QPushButton("Fermer", this);

//     // Style des boutons
//     QString buttonStyle = "QPushButton { padding: 10px; font-size: 12px; border-radius: 5px; }";
//     btnPrint->setStyleSheet(buttonStyle + "background-color: #3498db; color: white;");
//     btnEmail->setStyleSheet(buttonStyle + "background-color: #e67e22; color: white;");
//     btnClose->setStyleSheet(buttonStyle + "background-color: #95a5a6; color: white;");

//     btnLayout->addWidget(btnPrint);
//     btnLayout->addWidget(btnEmail);
//     btnLayout->addStretch();
//     btnLayout->addWidget(btnClose);

//     // Organisation
//     mainLayout->addWidget(commandesGroup);
//     mainLayout->addWidget(detailsGroup);
//     mainLayout->addLayout(btnLayout);

//     // Connexions
//     connect(btnPrint, &QPushButton::clicked, this, &ticket::printTicket);
//     connect(btnEmail, &QPushButton::clicked, this, &ticket::sendEmail);
//     connect(btnClose, &QPushButton::clicked, this, &QDialog::reject);
// }

// bool ticket::initDatabase()
// {
//     db = QSqlDatabase::addDatabase("QSQLITE");
//     QString dbPath = QDir::currentPath() + "/gestion_restaurant.db";
//     db.setDatabaseName(dbPath);

//     qDebug() << "Chemin de la base de données:" << dbPath;

//     if (!db.open()) {
//         QMessageBox::critical(this, "Erreur",
//                               QString("Impossible d'ouvrir la base de données:\n%1\nChemin: %2")
//                                   .arg(db.lastError().text())
//                                   .arg(dbPath));
//         return false;
//     }
//     return true;
// }

// void ticket::chargerCommandesClient()
// {
//     // Nettoyage avant nouveau chargement
//     QLayoutItem* child;
//     while ((child = commandesLayout->takeAt(0)) != nullptr) {
//         delete child->widget();
//         delete child;
//     }

//     QSqlQuery query(db);
//     query.prepare("SELECT id, date, total FROM commandes WHERE client_id = ? AND statut = 'payé' ORDER BY date DESC");
//     query.bindValue(0, clientId);

//     if (!query.exec()) {
//         QMessageBox::warning(this, "Erreur",
//                              QString("Impossible de charger les commandes:\n%1").arg(query.lastError().text()));
//         return;
//     }

//     if (query.size() == 0) {
//         QLabel *emptyLabel = new QLabel("Aucune commande disponible", commandesContainer);
//         emptyLabel->setStyleSheet("color: #7f8c8d; font-style: italic;");
//         emptyLabel->setAlignment(Qt::AlignCenter);
//         commandesLayout->addWidget(emptyLabel);
//         return;
//     }

//     while (query.next()) {
//         int commandeId = query.value(0).toInt();
//         QString date = query.value(1).toDateTime().toString("dd/MM/yyyy HH:mm");
//         double total = query.value(2).toDouble();

//         QPushButton *btn = new QPushButton(
//             QString("Commande #%1 - %2 - %3€").arg(commandeId).arg(date).arg(total, 0, 'f', 2),
//             commandesContainer
//             );

//         // Style du bouton
//         btn->setStyleSheet(R"(
//             QPushButton {
//                 text-align: left;
//                 padding: 12px;
//                 background-color: white;
//                 border: 1px solid #bdc3c7;
//                 border-radius: 5px;
//             }
//             QPushButton:hover {
//                 background-color: #f5f5f5;
//             }
//         )");

//         btn->setProperty("commandeId", commandeId);
//         connect(btn, &QPushButton::clicked, this, &ticket::loadTicketDetails);
//         commandesLayout->addWidget(btn);
//     }
//     commandesLayout->addStretch();
// }

// void ticket::loadTicketDetails()
// {
//     QPushButton *btn = qobject_cast<QPushButton*>(sender());
//     if (!btn) return;

//     selectedCommandId = btn->property("commandeId").toInt();

//     QSqlQuery query(db);
//     query.prepare(
//         "SELECT p.nom, lc.quantite, p.prix "
//         "FROM ligne_commande lc "
//         "JOIN produits p ON lc.produit_id = p.id "
//         "WHERE lc.commande_id = ?"
//         );
//     query.bindValue(0, selectedCommandId);

//     if (!query.exec()) {
//         QMessageBox::warning(this, "Erreur",
//                              QString("Impossible de charger les détails:\n%1").arg(query.lastError().text()));
//         return;
//     }

//     // Génération du contenu HTML
//     QString html;
//     html += "<html><body style='font-family:Arial;'>";
//     html += QString("<h1 style='color:#2c3e50;'>Ticket Restaurant #%1</h1>").arg(selectedCommandId);
//     html += "<table width='100%' border='1' cellspacing='0' cellpadding='5' style='border-collapse:collapse;'>";
//     html += "<tr style='background-color:#3498db; color:white;'>"
//             "<th>Produit</th><th>Quantité</th><th>Prix</th><th>Total</th></tr>";

//     double total = 0;
//     while (query.next()) {
//         QString nom = query.value(0).toString();
//         int qte = query.value(1).toInt();
//         double prix = query.value(2).toDouble();
//         double totalLigne = qte * prix;
//         total += totalLigne;

//         html += QString("<tr style='border-bottom:1px solid #eee;'>"
//                         "<td>%1</td>"
//                         "<td align='right'>%2</td>"
//                         "<td align='right'>%3€</td>"
//                         "<td align='right'>%4€</td>"
//                         "</tr>")
//                     .arg(nom)
//                     .arg(qte)
//                     .arg(prix, 0, 'f', 2)
//                     .arg(totalLigne, 0, 'f', 2);
//     }

//     html += QString("<tr style='background-color:#f8f9fa; font-weight:bold;'>"
//                     "<td colspan='3' align='right'>Total</td>"
//                     "<td align='right'>%1€</td>"
//                     "</tr>")
//                 .arg(total, 0, 'f', 2);

//     html += "</table></body></html>";

//     ticketDetails->setHtml(html);
// }

// void ticket::printTicket()
// {
//     if (selectedCommandId == -1) {
//         QMessageBox::warning(this, "Erreur", "Aucun ticket sélectionné");
//         return;
//     }

//     QPrinter printer;
//     QPrintDialog dialog(&printer, this);
//     if (dialog.exec() == QDialog::Accepted) {
//         QTextDocument doc;
//         doc.setHtml(ticketDetails->toHtml());
//         doc.print(&printer);
//     }
// }

// void ticket::sendEmail()
// {
//     if (selectedCommandId == -1) {
//         QMessageBox::warning(this, "Erreur", "Aucun ticket sélectionné");
//         return;
//     }

//     QSqlQuery query(db);
//     query.prepare("SELECT email FROM clients WHERE id = ?");
//     query.bindValue(0, clientId);

//     if (!query.exec() || !query.next()) {
//         QMessageBox::warning(this, "Erreur",
//                              QString("Email du client introuvable:\n%1").arg(query.lastError().text()));
//         return;
//     }

//     QString clientEmail = query.value(0).toString();
//     QMessageBox::information(this, "Email",
//                              QString("Ticket #%1 prêt à être envoyé à %2").arg(selectedCommandId).arg(clientEmail));
// }

// ticket::~ticket()
// {
//     delete ui;
//     if (db.isOpen()) {
//         db.close();
//     }
// }





#include "ticket.h"
#include "ui_ticket.h"

#include <QSqlQuery>
#include <QMessageBox>
#include <QDebug>
#include <QDateTime>
#include <QPushButton>
#include <QTextDocument>
#include <QPrinter>
#include <QPrintDialog>
#include <QDir>
#include <QCoreApplication>

ticket::ticket(int idClient, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::ticket),
    clientId(idClient),
    selectedCommandId(-1)
{
    ui->setupUi(this);
    setWindowTitle("Gestion des Tickets Restaurant");
    resize(900, 700);

    setupUI();

    if(!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    chargerCommandesClient();
}

void ticket::setupUI()
{
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(20, 20, 20, 20);
    mainLayout->setSpacing(15);

    // Header
    QLabel *header = new QLabel("Mes Tickets Restaurant", this);
    header->setStyleSheet("font-size: 24px; font-weight: bold; color: #2c3e50;");
    mainLayout->addWidget(header, 0, Qt::AlignCenter);

    // Section commandes
    QGroupBox *commandesGroup = new QGroupBox("Commandes disponibles", this);
    QVBoxLayout *commandesGroupLayout = new QVBoxLayout(commandesGroup);

    scrollArea = new QScrollArea(this);
    scrollArea->setWidgetResizable(true);
    commandesContainer = new QWidget();
    commandesLayout = new QVBoxLayout(commandesContainer);
    commandesLayout->setAlignment(Qt::AlignTop);
    commandesLayout->setSpacing(10);
    scrollArea->setWidget(commandesContainer);
    commandesGroupLayout->addWidget(scrollArea);

    // Détails commande
    QGroupBox *detailsGroup = new QGroupBox("Détails du ticket", this);
    QVBoxLayout *detailsLayout = new QVBoxLayout(detailsGroup);
    ticketDetails = new QTextEdit(this);
    ticketDetails->setReadOnly(true);
    detailsLayout->addWidget(ticketDetails);

    // Boutons d'action
    QHBoxLayout *btnLayout = new QHBoxLayout();
    QPushButton *btnPrint = new QPushButton("Imprimer", this);
    QPushButton *btnEmail = new QPushButton("Envoyer par email", this);
    QPushButton *btnClose = new QPushButton("Fermer", this);

    QString buttonStyle = "QPushButton { padding: 10px; font-size: 12px; border-radius: 5px; }";
    btnPrint->setStyleSheet(buttonStyle + "background-color: #3498db; color: white;");
    btnEmail->setStyleSheet(buttonStyle + "background-color: #e67e22; color: white;");
    btnClose->setStyleSheet(buttonStyle + "background-color: #95a5a6; color: white;");

    btnLayout->addWidget(btnPrint);
    btnLayout->addWidget(btnEmail);
    btnLayout->addStretch();
    btnLayout->addWidget(btnClose);

    mainLayout->addWidget(commandesGroup);
    mainLayout->addWidget(detailsGroup);
    mainLayout->addLayout(btnLayout);

    connect(btnPrint, &QPushButton::clicked, this, &ticket::printTicket);
    connect(btnEmail, &QPushButton::clicked, this, &ticket::sendEmail);
    connect(btnClose, &QPushButton::clicked, this, &QDialog::reject);
}

bool ticket::initDatabase()
{
    db = QSqlDatabase::addDatabase("QSQLITE");
    QString dbPath = QCoreApplication::applicationDirPath() + "/commandes.db";
    db.setDatabaseName(dbPath);

    qDebug() << "Chemin de la base de données:" << dbPath;

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur",
                              QString("Impossible d'ouvrir la base de données:\n%1\nChemin: %2")
                                  .arg(db.lastError().text())
                                  .arg(dbPath));
        return false;
    }
    return true;
}

void ticket::chargerCommandesClient()
{
    QLayoutItem* child;
    while ((child = commandesLayout->takeAt(0)) != nullptr) {
        delete child->widget();
        delete child;
    }

    QSqlQuery query(db);
    query.prepare("SELECT id, produit, quantite, prix FROM commandes WHERE client_id = ?");
    query.bindValue(0, clientId);

    if (!query.exec()) {
        QMessageBox::warning(this, "Erreur",
                             QString("Impossible de charger les commandes:\n%1").arg(query.lastError().text()));
        return;
    }

    if (query.size() == 0) {
        QLabel *emptyLabel = new QLabel("Aucune commande disponible", commandesContainer);
        emptyLabel->setStyleSheet("color: #7f8c8d; font-style: italic;");
        emptyLabel->setAlignment(Qt::AlignCenter);
        commandesLayout->addWidget(emptyLabel);
        return;
    }

    while (query.next()) {
        int commandeId = query.value(0).toInt();
        QString produit = query.value(1).toString();
        int quantite = query.value(2).toInt();
        double prix = query.value(3).toDouble();
        double total = quantite * prix;

        QPushButton *btn = new QPushButton(
            QString("Commande #%1 - %2 x %3 - %4€")
                .arg(commandeId)
                .arg(produit)
                .arg(quantite)
                .arg(total, 0, 'f', 2),
            commandesContainer
            );

        btn->setStyleSheet(R"(
            QPushButton {
                text-align: left;
                padding: 12px;
                background-color: white;
                border: 1px solid #bdc3c7;
                border-radius: 5px;
            }
            QPushButton:hover {
                background-color: #f5f5f5;
            }
        )");

        btn->setProperty("commandeId", commandeId);
        connect(btn, &QPushButton::clicked, this, &ticket::loadTicketDetails);
        commandesLayout->addWidget(btn);
    }
    commandesLayout->addStretch();
}

void ticket::loadTicketDetails()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    selectedCommandId = btn->property("commandeId").toInt();

    QSqlQuery query(db);
    query.prepare("SELECT c.nom, c.prenom, cmd.produit, cmd.quantite, cmd.prix "
                  "FROM commandes cmd "
                  "JOIN clients c ON cmd.client_id = c.id "
                  "WHERE cmd.id = ?");
    query.bindValue(0, selectedCommandId);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur",
                             QString("Impossible de charger les détails:\n%1").arg(query.lastError().text()));
        return;
    }

    QString nomClient = query.value(0).toString();
    QString prenomClient = query.value(1).toString();
    QString produit = query.value(2).toString();
    int quantite = query.value(3).toInt();
    double prix = query.value(4).toDouble();
    double total = quantite * prix;

    QString html;
    html += "<html><body style='font-family:Arial;'>";
    html += QString("<h1 style='color:#2c3e50;'>Ticket Restaurant #%1</h1>").arg(selectedCommandId);
    html += QString("<p>Client: %1 %2</p>").arg(prenomClient).arg(nomClient);
    html += "<table width='100%' border='1' cellspacing='0' cellpadding='5' style='border-collapse:collapse;'>";
    html += "<tr style='background-color:#3498db; color:white;'>"
            "<th>Produit</th><th>Quantité</th><th>Prix unitaire</th><th>Total</th></tr>";

    html += QString("<tr style='border-bottom:1px solid #eee;'>"
                    "<td>%1</td>"
                    "<td align='right'>%2</td>"
                    "<td align='right'>%3€</td>"
                    "<td align='right'>%4€</td>"
                    "</tr>")
                .arg(produit)
                .arg(quantite)
                .arg(prix, 0, 'f', 2)
                .arg(total, 0, 'f', 2);

    html += QString("<tr style='background-color:#f8f9fa; font-weight:bold;'>"
                    "<td colspan='3' align='right'>Total</td>"
                    "<td align='right'>%1€</td>"
                    "</tr>")
                .arg(total, 0, 'f', 2);

    html += "</table></body></html>";

    ticketDetails->setHtml(html);
}

void ticket::printTicket()
{
    if (selectedCommandId == -1) {
        QMessageBox::warning(this, "Erreur", "Aucun ticket sélectionné");
        return;
    }

    QPrinter printer;
    QPrintDialog dialog(&printer, this);
    if (dialog.exec() == QDialog::Accepted) {
        QTextDocument doc;
        doc.setHtml(ticketDetails->toHtml());
        doc.print(&printer);
    }
}

void ticket::sendEmail()
{
    if (selectedCommandId == -1) {
        QMessageBox::warning(this, "Erreur", "Aucun ticket sélectionné");
        return;
    }

    QSqlQuery query(db);
    query.prepare("SELECT email FROM clients WHERE id = ?");
    query.bindValue(0, clientId);

    if (!query.exec() || !query.next()) {
        QMessageBox::warning(this, "Erreur",
                             QString("Email du client introuvable:\n%1").arg(query.lastError().text()));
        return;
    }

    QString clientEmail = query.value(0).toString();
    QMessageBox::information(this, "Email",
                             QString("Ticket #%1 prêt à être envoyé à %2").arg(selectedCommandId).arg(clientEmail));
}

ticket::~ticket()
{
    delete ui;
    if (db.isOpen()) {
        db.close();
    }
}

// #ifndef ACCULIER_H
// #define ACCULIER_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>
// #include<QPixmap>
// #include <Menu.h>
// #include "commande.h"
// #include "reservation.h"  // Ajoutez cette ligne
// #include "paiement.h"  // Ajoutez cette ligne
// #include "localisation.h"  // Ajoutez cette inclusion

// namespace Ui {
// class Dialog;
// }

// class Acculier : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit Acculier(QWidget *parent = nullptr);
//     ~Acculier() override;

// private slots:
//     void onDashboardClicked();
//     void onSearchClicked();
//     void updateSearchResults(const QString &searchText);

//     void onMenuClicked();       // Pour "Consultation du menu"
//     void onOrderClicked();      // Pour "Commande en ligne"
//     void onReservationClicked();// Pour "Réservation"
//     void onPaymentClicked();    // Pour "Paiement"
//     void onOrdersListClicked(); // Pour "Listes des commandes"

//     void onReservationManagementClicked();
//     void onLocalisationClicked();  // Ajoutez cette ligne pour le slot de localisation
//      void onAdvancedSearchClicked(); // Ajoutez cette ligne
// private:
//     Ui::Dialog *ui;
//     QSqlDatabase db;
//     Menu *menuWindow;  // Pointeur vers la fenêtre Menu
//     commande *commandeWindow;  // Pointeur vers la fenêtre Commande
//      reservation *reservationWindow;  // Ajoutez cette ligne pour la fenêtre de réservation
//     paiement *paymentWindow;  // Ajoutez cette ligne
//    localisation *localisationWindow;  // Ajoutez cette ligne pour le pointeur vers Localisation



//     bool initDatabase();
//     void loadDashboardData();
//     void searchInDatabase(const QString &term);
//     void showAllSections(bool show);
//     void showSection(const QString &sectionName, bool show);
//     void loadImageToFrame();
// };
// #endif // ACCULIER_H



#ifndef ACCULIER_H
#define ACCULIER_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery>
#include <QSqlError>
#include<QPixmap>
#include <Menu.h>
#include "commande.h"
#include "reservation.h"  // Ajoutez cette ligne
#include "paiement.h"  // Ajoutez cette ligne
#include "localisation.h"  // Ajoutez cette inclusion
#include "personnel.h"  // Ajoutez cette inclusion
#include "feedback.h"  // Ajoutez cette ligne
#include "historique.h"

namespace Ui {
class Dialog;
}

class Acculier : public QDialog
{
    Q_OBJECT

public:
    explicit Acculier(QWidget *parent = nullptr);
    ~Acculier() override;

private slots:
    void onDashboardClicked();
    void onSearchClicked();
    void updateSearchResults(const QString &searchText);

    void onMenuClicked();       // Pour "Consultation du menu"
    void onOrderClicked();      // Pour "Commande en ligne"
    void onReservationClicked();// Pour "Réservation"
    void onPaymentClicked();    // Pour "Paiement"
    void onOrdersListClicked(); // Pour "Listes des commandes"

    void onReservationManagementClicked();
    void onLocalisationClicked();  // Ajoutez cette ligne pour le slot de localisation
    void onPersonnelClicked();  // Ajoutez cette ligne pour le nouveau slot
    void onFeedbackClicked();  // Ajoutez cette ligne
    void onHistoriqueClicked();  // Ajoutez cette déclaration
    void onLoginButtonClicked();  // Ajoutez cette ligne dans vos slots privés
private:
    Ui::Dialog *ui;
    QSqlDatabase db;
    Menu *menuWindow;  // Pointeur vers la fenêtre Menu
    commande *commandeWindow;  // Pointeur vers la fenêtre Commande
    reservation *reservationWindow;  // Ajoutez cette ligne pour la fenêtre de réservation
    paiement *paymentWindow;  // Ajoutez cette ligne
    localisation *localisationWindow;  // Ajoutez cette ligne pour le pointeur vers Localisation
    personnel *personnelWindow;  // Ajoutez cette ligne pour le pointeur vers Personnel
    feedback *feedbackWindow;  // Ajoutez cette ligne
      historique *historiqueWindow;
    bool initDatabase();
    void loadDashboardData();
    void searchInDatabase(const QString &term);
    void showAllSections(bool show);
    void showSection(const QString &sectionName, bool show);
    void loadImageToFrame();
};
#endif // ACCULIER_H

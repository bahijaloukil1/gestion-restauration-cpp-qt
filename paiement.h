#ifndef PAIEMENT_H
#define PAIEMENT_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>
#include <QVBoxLayout>
#include "cartebancaire.h"  // Ajoutez cette inclusion
#include "especes.h"  // Ajoutez cette inclusion
#include "cheque.h"  // Ajoutez cette inclusion
#include "ticket.h"

namespace Ui {
class paiement;
}

class paiement : public QDialog
{
    Q_OBJECT

public:
    explicit paiement(QWidget *parent = nullptr);
    ~paiement();

protected:
    void resizeEvent(QResizeEvent *event) override;
private slots:
    void onButtonBoxAccepted();
    void openCarteBancairePage();  // Ajoutez cette déclaration
    void openEspecesPage();  // Ajoutez cette déclaration
    void openChequePage();  // Ajoutez cette déclaration
    void openTicketPage();  // Nouvelle déclaration
    // Déclaration existante
private:
    Ui::paiement *ui;
    QSqlDatabase m_db;
    QVBoxLayout *mainLayout;
    int m_commandeId; // Ajoutez cette ligne


    bool initDatabase();
    void setupPaymentButtons();
    void setBackground();  // Nouvelle méthode pour le fond
    int obtenirIdCommandeCourante();
};

#endif // PAIEMENT_H

#ifndef RESERVATION_H
#define RESERVATION_H

#include <QDialog>
#include <QDateTime>
#include <QFormLayout>
#include <QLineEdit>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QLabel>
#include <QScrollArea>
#include <QMessageBox>
#include <QPixmap>

namespace Ui {
class reservation;
}

struct Reservation {
    int id;
    QString nomClient;
    QString telephone;
    int nbPersonnes;
    QString dateHeure;  // Changé de QDateTime à QString
    QString statut;
    QString commentaires;
};

class reservation : public QDialog
{
    Q_OBJECT

public:
    explicit reservation(QWidget *parent = nullptr);
    ~reservation();

private slots:
    void reserverTable();
    void annulerReservation();
    void modifierReservation();
    void afficherFormulaireReservation(bool show = true);
    void loadImageToFrame();

private:
    Ui::reservation *ui;
       QFrame *frame;
    QList<Reservation> reservations;
    QScrollArea *scrollArea;
    QWidget *widgetContenu;
    QVBoxLayout *layoutCommandes;

    QWidget *formulaireWidget;
    QLineEdit *nomClientEdit;
    QLineEdit *telephoneEdit;
    QSpinBox *nbPersonnesSpin;
    QLineEdit *dateHeureEdit;  // Changé de QDateTimeEdit à QLineEdit
    QLineEdit *commentairesEdit;

    int currentClientId;
    void setBackground();  // Ajoutez cette ligne
    void chargerReservationsClient(int clientId);
    void afficherReservations();
    QWidget* creerWidgetReservation(const Reservation &res);
    void clearFormulaire();
};

#endif // RESERVATION_H

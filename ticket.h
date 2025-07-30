// #ifndef TICKET_H
// #define TICKET_H

// #include <QDialog>

// namespace Ui {
// class ticket;
// }

// class ticket : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit ticket(QWidget *parent = nullptr);
//     ~ticket();

// private:
//     Ui::ticket *ui;
// };

// #endif // TICKET_H




// #ifndef TICKET_H
// #define TICKET_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlError>  // Ajouté
// #include <QDateTime>  // Ajouté
// #include <QPushButton>
// #include <QVBoxLayout>
// #include <QScrollArea>
// #include <QLabel>

// class ticket : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit ticket(int idClient, QWidget *parent = nullptr);  // Changé pour prendre int
//     ~ticket();

// private slots:
//     void onCommandeClicked();
//     void imprimerTicket();
//     void envoyerParEmail();
//     void genererQRCode();

// private:
//     QSqlDatabase m_db;
//     int clientId;

//     // Widgets
//     int selectedCommandId = -1;
//     QPushButton* lastSelectedButton = nullptr;
//     QScrollArea *scrollArea;
//     QWidget *scrollWidget;
//     QVBoxLayout *mainLayout;
//     QVBoxLayout *buttonsLayout;
//     QHBoxLayout *actionsLayout;
//     QLabel *labelDetails;
//     int selectedCommandId;
//     void setupUI();
//     bool initDatabase();
//     void chargerCommandesClient();
//     void afficherDetailsCommande(int idCommande);
//     void creerBoutonsActions();
// };

// #endif // TICKET_H





// #ifndef TICKET_H
// #define TICKET_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlError> // AJOUTEZ CETTE INCLUSION
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QScrollArea>
// #include <QLabel>
// #include <QPushButton>

// class ticket : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit ticket(int idClient, QWidget *parent = nullptr);
//     ~ticket();

// private slots:
//     void onCommandeClicked();
//     void imprimerTicket();
//     void envoyerParEmail();
//     void genererQRCode();

// private:
//     QSqlDatabase m_db;
//     int clientId;
//     int selectedCommandId;
//     QPushButton* lastSelectedButton;

//     // Widgets
//     QScrollArea *scrollArea;
//     QWidget *scrollWidget;
//     QVBoxLayout *mainLayout;
//     QVBoxLayout *buttonsLayout;
//     QHBoxLayout *actionsLayout;
//     QLabel *labelDetails;

//     void setupUI();
//     bool initDatabase();
//     void chargerCommandesClient();
//     void afficherDetailsCommande(int idCommande);
//     void creerBoutonsActions();
// };

// #endif // TICKET_H



// #ifndef TICKET_H
// #define TICKET_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlError>
// #include <QTextEdit>
// #include <QVBoxLayout>
// #include <QLabel>
// #include <QGroupBox>
// #include <QScrollArea>

// namespace Ui {
// class ticket;
// }

// class ticket : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit ticket(int idClient, QWidget *parent = nullptr);
//     ~ticket();

// private slots:
//     void chargerCommandesClient();
//     void loadTicketDetails();
//     void printTicket();
//     void sendEmail();

// private:
//     Ui::ticket *ui;
//     QSqlDatabase db;
//     int clientId;
//     int selectedCommandId;

//     // Widgets
//     QTextEdit *ticketDetails;
//     QWidget *commandesContainer;
//     QVBoxLayout *commandesLayout;
//     QScrollArea *scrollArea;

//     void setupUI();
//     bool initDatabase();
// };

// #endif // TICKET_H




#ifndef TICKET_H
#define TICKET_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError>  // Ajouté
#include <QTextEdit>
#include <QVBoxLayout>
#include <QLabel>     // Ajouté
#include <QGroupBox>
#include <QScrollArea>

namespace Ui {
class ticket;
}

class ticket : public QDialog
{
    Q_OBJECT

public:
    explicit ticket(int idClient, QWidget *parent = nullptr);
    ~ticket();

private slots:
    void chargerCommandesClient();
    void loadTicketDetails();
    void printTicket();
    void sendEmail();

private:
    Ui::ticket *ui;
    QSqlDatabase db;
    int clientId;
    int selectedCommandId;

    // Widgets
    QTextEdit *ticketDetails;
    QWidget *commandesContainer;
    QVBoxLayout *commandesLayout;
    QScrollArea *scrollArea;

    void setupUI();
    bool initDatabase();
};

#endif // TICKET_H

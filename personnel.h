// #ifndef PERSONNEL_H
// #define PERSONNEL_H

// #include <QDialog>

// namespace Ui {
// class personnel;
// }

// class personnel : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit personnel(QWidget *parent = nullptr);
//     ~personnel();

// private:
//     Ui::personnel *ui;
// };

// #endif // PERSONNEL_H



// #ifndef PERSONNEL_H
// #define PERSONNEL_H

// #include <QDialog>
// #include <QSqlDatabase>
// #include <QSqlQuery>
// #include <QSqlError>
// #include <QMessageBox>
// #include <QStandardItemModel>
// #include <QVBoxLayout>
// #include <QHBoxLayout>
// #include <QFormLayout>
// #include <QTableView>
// #include <QLineEdit>
// #include <QComboBox>
// #include <QPushButton>
// #include <QLabel>

// class personnel : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit personnel(QWidget *parent = nullptr);
//     ~personnel();

// private slots:
//     void on_ajouterButton_clicked();
//     void on_modifierButton_clicked();
//     void on_supprimerButton_clicked();
//     void on_tableView_clicked(const QModelIndex &index);
//     void actualiserTableau();

// private:
//     QSqlDatabase db;
//     int currentUserId = -1;
//     QStandardItemModel *model;

//     // Widgets
//     QTableView *tableView;
//     QLineEdit *emailEdit;
//     QLineEdit *prenomEdit;
//     QLineEdit *nomEdit;
//     QComboBox *roleComboBox;
//     QPushButton *ajouterButton;
//     QPushButton *modifierButton;
//     QPushButton *supprimerButton;

//     bool initDatabase();
// };

// #endif // PERSONNEL_H



// #ifndef PERSONNEL_H
// #define PERSONNEL_H

// #include <QDialog>

// namespace Ui {
// class personnel;
// }

// class personnel : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit personnel(QWidget *parent = nullptr);
//     ~personnel();

// private:
//     Ui::personnel *ui;
// };

// #endif // PERSONNEL_H


#ifndef PERSONNEL_H
#define PERSONNEL_H

#include <QDialog>
#include <QPixmap>
#include <QPalette>
#include <QSqlDatabase>
#include <QSqlError> // Ajouté
#include <QLineEdit>
#include <QPushButton>
#include <QGroupBox>
#include <QVBoxLayout>
#include <QFormLayout>
#include <QMessageBox>

class personnel : public QDialog
{
    Q_OBJECT

public:
    explicit personnel(int userId, QWidget *parent = nullptr);
    ~personnel();

private slots:
    void on_modifierProfil_clicked();
    void on_sauvegarderProfil_clicked();
    void on_changerMotDePasse_clicked();
    void on_annulerModifications_clicked();

private:
    int m_userId;
     QString m_originalEmail;  // Ajout de cette déclaration
    QSqlDatabase m_db;

    // Widgets
    QLineEdit *emailEdit;
    QLineEdit *prenomEdit;
    QLineEdit *nomEdit;
    QLineEdit *telephoneEdit;
    QLineEdit *currentPassEdit;
    QLineEdit *newPassEdit;
    QLineEdit *confirmPassEdit;
    QPushButton *modifierBtn;
    QPushButton *sauvegarderBtn;
    QPushButton *annulerBtn;
    QPushButton *changerPassBtn;

    void chargerProfil();
    void setupUI();
    void toggleEditMode(bool editable);
    bool verifierMotDePasse(const QString &password);
    bool connecterBaseDeDonnees();
    QHBoxLayout* creerBoutons(); // Changé le type de retour
      void setBackground();  // Ajoutez cette ligne
};
#endif // PERSONNEL_H



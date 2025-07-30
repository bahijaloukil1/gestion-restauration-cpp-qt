// #ifndef FEEDBACK_H
// #define FEEDBACK_H

// #include <QDialog>

// namespace Ui {
// class feedback;
// }

// class feedback : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit feedback(QWidget *parent = nullptr);
//     ~feedback();

// private:
//     Ui::feedback *ui;
// };

// #endif // FEEDBACK_H




#ifndef FEEDBACK_H
#define FEEDBACK_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlError> // Ajout crucial
#include <QButtonGroup>
#include <QTextEdit>
#include <QPushButton>
#include <QFormLayout>
#include <QScrollArea>
#include <QLabel> // Ajout important

class feedback : public QDialog
{
    Q_OBJECT

public:
    explicit feedback(QWidget *parent = nullptr);
    ~feedback();

private slots:
    void onEnvoyerClicked();
    void onNoteClicked(int note);

private:
    QSqlDatabase m_db;
    QButtonGroup *m_noteButtons;
    int m_noteSelectionnee;

    // Widgets
    QTextEdit *textEditCommentaire;
    QPushButton *pushButtonEnvoyer;
    QFormLayout *formLayout;
    QScrollArea *scrollAreaCategories;

    void setupUI();
    void creerBoutonsNotes();
    bool connecterBaseDeDonnees();
    void chargerCategories();
};

#endif // FEEDBACK_H

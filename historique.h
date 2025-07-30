// #ifndef HISTORIQUE_H
// #define HISTORIQUE_H

// #include <QDialog>
// #include <QDateTime>
// #include <QVector>

// QT_BEGIN_NAMESPACE
// class QChartView;
// class QChart;
// class QBarSeries;
// class QBarSet;
// class QValueAxis;
// class QBarCategoryAxis;
// QT_END_NAMESPACE

// class historique : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit historique(QWidget *parent = nullptr);
//     ~historique();

//     void ajouterVisite(const QDateTime &date);

// private:
//     void chargerHistorique();
//     void sauvegarderHistorique();
//     void creerGraphique();

//     QVector<QDateTime> m_visites;
//     QChartView *m_chartView;
// };

// #endif // HISTORIQUE_H



// #ifndef HISTORIQUE_H
// #define HISTORIQUE_H

// #include <QDialog>
// #include <QDateTime>
// #include <QVector>
// #include <QtCharts>

// QT_BEGIN_NAMESPACE
// namespace Ui { class historique; }
// QT_END_NAMESPACE

// class historique : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit historique(QWidget *parent = nullptr);
//     ~historique();

//     void ajouterVisite(const QDateTime &date);
//     void genererStatistiques();

// private:
//     Ui::historique *ui;
//     QVector<QDateTime> m_visites;
//     QChartView *m_chartView;

//     void chargerHistorique();
//     void sauvegarderHistorique();
//     void creerGraphiqueBarres();
//     void creerGraphiqueCourbe();
//     void creerGraphiqueSecteurs();
//     void creerGraphiqueCombined();
// };




// #ifndef HISTORIQUE_H
// #define HISTORIQUE_H

// #include <QDialog>
// #include <QVector>
// #include <QDate>
// #include <QVBoxLayout>
// #include <QChartView>
// #include <QRadioButton>
// #include <QTextEdit>
// #include <QDateTime>

// struct Visite {
//     QDate date;
//     QString type;
// };

// class historique : public QDialog
// {
//     Q_OBJECT

// public:
//     explicit historique(QWidget *parent = nullptr);
//     ~historique();

//     // Méthode pour ajouter une visite
//     void ajouterVisite(const QDateTime &dateTime);

// private slots:
//     void onTypeGraphiqueChanged();

// private:
//     void chargerHistorique();
//     void creerGraphiqueBarres();
//     void creerGraphiqueCourbe();
//     void creerGraphiqueSecteurs();
//     void mettreAJourStatistiques();

//     QVBoxLayout *mainLayout;
//     QChartView *m_chartView;
//     QRadioButton *radioBarres;
//     QRadioButton *radioCourbe;
//     QRadioButton *radioSecteurs;
//     QTextEdit *textStats;
//     QVector<Visite> m_visites;
// };

// #endif // HISTORIQUE_H




#ifndef HISTORIQUE_H
#define HISTORIQUE_H

#include <QDialog>
#include <QVBoxLayout>
#include <QLabel>
#include <QChartView>
#include <QChart>
#include <QPieSeries>
#include <QBarSeries>
#include <QBarSet>
#include <QBarCategoryAxis>
#include <QValueAxis>
#include <QDateTime>

class historique : public QDialog
{
    Q_OBJECT

public:
    explicit historique(QWidget *parent = nullptr);
    void ajouterVisite(const QDateTime &dateTime); // Ajout de la méthode manquante

private:
    void creerGraphiqueInvestissements();
    void creerGraphiqueCroissance();

    QVBoxLayout *mainLayout;
    QChartView *chartViewInvest;
    QChartView *chartViewCroissance;
    QVector<QDateTime> m_visites; // Ajout pour stocker les visites
};

#endif // HISTORIQUE_H

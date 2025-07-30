// // #include "historique.h"
// // #include <QFile>
// // #include <QTextStream>
// // #include <QVBoxLayout>
// // #include <QChartView>
// // #include <QBarSeries>
// // #include <QBarSet>
// // #include <QBarCategoryAxis>
// // #include <QValueAxis>

// // historique::historique(QWidget *parent) : QDialog(parent)
// // {
// //     setWindowTitle("Historique des Visites");
// //     resize(800, 600);

// //     m_chartView = new QChartView(this);
// //     m_chartView->setRenderHint(QPainter::Antialiasing);

// //     QVBoxLayout *layout = new QVBoxLayout(this);
// //     layout->addWidget(m_chartView);
// //     setLayout(layout);

// //     chargerHistorique();
// //     creerGraphique();
// // }

// // historique::~historique()
// // {
// //     // Destructeur
// // }

// // void historique::ajouterVisite(const QDateTime &date)
// // {
// //     m_visites.append(date);
// //     sauvegarderHistorique();
// //     creerGraphique();
// // }

// // void historique::creerGraphique()
// // {
// //     // Compter les visites par jour
// //     QMap<QDate, int> visitesParJour;
// //     for (const QDateTime &visite : m_visites) {
// //         QDate date = visite.date();
// //         visitesParJour[date]++;
// //     }

// //     // Créer les séries de données
// //     QBarSeries *series = new QBarSeries();
// //     QBarSet *barSet = new QBarSet("Visites");

// //     QStringList categories;
// //     QList<QDate> dates = visitesParJour.keys();
// //     std::sort(dates.begin(), dates.end());

// //     for (const QDate &date : dates) {
// //         *barSet << visitesParJour[date];
// //         categories << date.toString("dd/MM");
// //     }

// //     series->append(barSet);

// //     // Créer le graphique
// //     QChart *chart = new QChart();
// //     chart->addSeries(series);
// //     chart->setTitle("Historique des visites");
// //     chart->setAnimationOptions(QChart::SeriesAnimations);

// //     // Configurer les axes
// //     QBarCategoryAxis *axisX = new QBarCategoryAxis();
// //     axisX->append(categories);
// //     chart->addAxis(axisX, Qt::AlignBottom);
// //     series->attachAxis(axisX);

// //     QValueAxis *axisY = new QValueAxis();
// //     axisY->setLabelFormat("%d");
// //     axisY->setTitleText("Nombre de visites");
// //     chart->addAxis(axisY, Qt::AlignLeft);
// //     series->attachAxis(axisY);

// //     // Configurer la légende
// //     chart->legend()->setVisible(true);
// //     chart->legend()->setAlignment(Qt::AlignBottom);

// //     m_chartView->setChart(chart);
// // }

// // void historique::chargerHistorique()
// // {
// //     QFile file("historique_visites.txt");
// //     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
// //         return;

// //     QTextStream in(&file);
// //     while (!in.atEnd()) {
// //         QString line = in.readLine();
// //         QDateTime date = QDateTime::fromString(line, Qt::ISODate);
// //         if (date.isValid()) {
// //             m_visites.append(date);
// //         }
// //     }
// //     file.close();
// // }

// // void historique::sauvegarderHistorique()
// // {
// //     QFile file("historique_visites.txt");
// //     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
// //         return;

// //     QTextStream out(&file);
// //     for (const QDateTime &date : m_visites) {
// //         out << date.toString(Qt::ISODate) << "\n";
// //     }
// //     file.close();
// // }


// #include "historique.h"
// #include <QFile>
// #include <QTextStream>
// #include <QVBoxLayout>
// #include <QBarSeries>
// #include <QBarSet>
// #include <QBarCategoryAxis>
// #include <QValueAxis>
// #include <QChartView>

// historique::historique(QWidget *parent) :
//     QDialog(parent),
//     m_chartView(new QChartView(this))
// {
//     setWindowTitle("Historique des Visites");
//     resize(800, 600);

//     m_chartView->setRenderHint(QPainter::Antialiasing);

//     QVBoxLayout *layout = new QVBoxLayout(this);
//     layout->addWidget(m_chartView);
//     setLayout(layout);

//     chargerHistorique();
//     creerGraphique();
// }

// historique::~historique()
// {
//     // Le QChartView sera supprimé automatiquement grâce au parentage
// }

// void historique::ajouterVisite(const QDateTime &date)
// {
//     m_visites.append(date);
//     sauvegarderHistorique();
//     creerGraphique();
// }

// void historique::creerGraphique()
// {
//     // Compter les visites par jour
//     QMap<QDate, int> visitesParJour;
//     for (const QDateTime &visite : m_visites) {
//         QDate date = visite.date();
//         visitesParJour[date]++;
//     }

//     // Créer les séries de données
//     QBarSeries *series = new QBarSeries();
//     QBarSet *barSet = new QBarSet("Visites");

//     QStringList categories;
//     QList<QDate> dates = visitesParJour.keys();
//     std::sort(dates.begin(), dates.end());

//     for (const QDate &date : dates) {
//         *barSet << visitesParJour[date];
//         categories << date.toString("dd/MM/yyyy");
//     }

//     series->append(barSet);

//     // Créer le graphique
//     QChart *chart = new QChart();
//     chart->addSeries(series);
//     chart->setTitle("Historique des visites");
//     chart->setAnimationOptions(QChart::SeriesAnimations);

//     // Configurer les axes
//     QBarCategoryAxis *axisX = new QBarCategoryAxis();
//     axisX->append(categories);
//     chart->addAxis(axisX, Qt::AlignBottom);
//     series->attachAxis(axisX);

//     QValueAxis *axisY = new QValueAxis();
//     axisY->setLabelFormat("%d");
//     axisY->setTitleText("Nombre de visites");
//     chart->addAxis(axisY, Qt::AlignLeft);
//     series->attachAxis(axisY);

//     // Configurer la légende
//     chart->legend()->setVisible(true);
//     chart->legend()->setAlignment(Qt::AlignBottom);

//     m_chartView->setChart(chart);
// }

// void historique::chargerHistorique()
// {
//     QFile file("historique_visites.txt");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//         return;

//     QTextStream in(&file);
//     while (!in.atEnd()) {
//         QString line = in.readLine();
//         QDateTime date = QDateTime::fromString(line, Qt::ISODate);
//         if (date.isValid()) {
//             m_visites.append(date);
//         }
//     }
//     file.close();
// }

// void historique::sauvegarderHistorique()
// {
//     QFile file("historique_visites.txt");
//     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//         return;

//     QTextStream out(&file);
//     for (const QDateTime &date : m_visites) {
//         out << date.toString(Qt::ISODate) << "\n";
//     }
//     file.close();
// }




// #include "historique.h"
// #include <QFile>
// #include <QTextStream>
// #include <QVBoxLayout>
// #include <QChartView>
// #include <QBarSeries>
// #include <QBarSet>
// #include <QBarCategoryAxis>
// #include <QValueAxis>
// #include <QPainter>

// historique::historique(QWidget *parent) :
//     QDialog(parent),
//     m_chartView(new QChartView(this))
// {
//     setWindowTitle("Statistiques des Visites");
//     resize(1000, 600);

//     // Configuration du graphique
//     m_chartView->setRenderHint(QPainter::Antialiasing);

//     QVBoxLayout *layout = new QVBoxLayout(this);
//     layout->addWidget(m_chartView);
//     setLayout(layout);

//     // Style de la fenêtre
//     setStyleSheet("background-color: #f5f5f5;");

//     chargerHistorique();
//     creerGraphique();
// }

// historique::~historique()
// {
//     // La destruction est gérée automatiquement par le parentage Qt
// }

// void historique::ajouterVisite(const QDateTime &date)
// {
//     m_visites.append(date);
//     sauvegarderHistorique();
//     creerGraphique(); // Mise à jour du graphique
// }

// void historique::creerGraphique()
// {
//     // 1. Compter les visites par jour
//     QMap<QDate, int> visitesParJour;
//     for (const QDateTime &visite : m_visites) {
//         QDate date = visite.date();
//         visitesParJour[date]++;
//     }

//     // 2. Préparer les données pour le graphique
//     QBarSeries *series = new QBarSeries();
//     QBarSet *barSet = new QBarSet("Visites");
//     barSet->setColor(QColor(75, 123, 186)); // Couleur des barres

//     QStringList categories;
//     QList<QDate> dates = visitesParJour.keys();
//     std::sort(dates.begin(), dates.end());

//     // 3. Remplir les données
//     for (const QDate &date : dates) {
//         *barSet << visitesParJour[date];
//         categories << date.toString("ddd d MMM"); // Format: "Lun 12 Jan"
//     }
//     series->append(barSet);

//     // 4. Création du graphique
//     QChart *chart = new QChart();
//     chart->addSeries(series);
//     chart->setTitle("Fréquentation du Restaurant");
//     chart->setAnimationOptions(QChart::SeriesAnimations);
//     chart->setTheme(QChart::ChartThemeLight);
//     chart->setBackgroundBrush(QBrush(QColor(245, 245, 245)));

//     // 5. Configuration des axes
//     // Axe X (dates)
//     QBarCategoryAxis *axisX = new QBarCategoryAxis();
//     axisX->append(categories);
//     axisX->setTitleText("Dates");
//     chart->addAxis(axisX, Qt::AlignBottom);
//     series->attachAxis(axisX);

//     // Axe Y (nombre de visites)
//     QValueAxis *axisY = new QValueAxis();
//     axisY->setLabelFormat("%d");
//     axisY->setTitleText("Nombre de visites");
//     axisY->setMin(0);
//     // Ajoute une marge de 10% au maximum pour une meilleure visibilité
//     if (!visitesParJour.isEmpty()) {
//         int max = *std::max_element(visitesParJour.begin(), visitesParJour.end());
//         axisY->setMax(max + (max * 0.1));
//     }
//     chart->addAxis(axisY, Qt::AlignLeft);
//     series->attachAxis(axisY);

//     // 6. Légende
//     chart->legend()->setVisible(true);
//     chart->legend()->setAlignment(Qt::AlignBottom);

//     // 7. Appliquer le graphique
//     m_chartView->setChart(chart);
// }

// void historique::chargerHistorique()
// {
//     QFile file("historique_visites.txt");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//         return;

//     QTextStream in(&file);
//     while (!in.atEnd()) {
//         QString line = in.readLine().trimmed();
//         if (!line.isEmpty()) {
//             QDateTime date = QDateTime::fromString(line, Qt::ISODate);
//             if (date.isValid()) {
//                 m_visites.append(date);
//             }
//         }
//     }
//     file.close();
// }

// void historique::sauvegarderHistorique()
// {
//     QFile file("historique_visites.txt");
//     if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
//         return;

//     QTextStream out(&file);
//     for (const QDateTime &date : m_visites) {
//         out << date.toString(Qt::ISODate) << "\n";
//     }
//     file.close();
// }





// #include "historique.h"
// #include <QFile>
// #include <QMessageBox>
// #include <QHBoxLayout>
// #include <QButtonGroup>
// #include <QtCharts/QBarSeries>
// #include <QtCharts/QBarSet>
// #include <QtCharts/QLineSeries>
// #include <QtCharts/QPieSeries>
// #include <QtCharts/QBarCategoryAxis>
// #include <QtCharts/QValueAxis>
// #include <QtCharts/QDateTimeAxis>

// historique::historique(QWidget *parent) :
//     QDialog(parent),
//     m_chartView(new QChartView(this))
// {
//     setWindowTitle("Statistiques des Visites");
//     resize(1000, 600);

//     // Création des widgets
//     mainLayout = new QVBoxLayout(this);

//     // Création des boutons radio
//     QHBoxLayout *radioLayout = new QHBoxLayout();
//     radioBarres = new QRadioButton("Barres", this);
//     radioCourbe = new QRadioButton("Courbe", this);
//     radioSecteurs = new QRadioButton("Secteurs", this);

//     radioBarres->setChecked(true);

//     radioLayout->addWidget(radioBarres);
//     radioLayout->addWidget(radioCourbe);
//     radioLayout->addWidget(radioSecteurs);

//     // Zone de texte pour les stats
//     textStats = new QTextEdit(this);
//     textStats->setReadOnly(true);

//     // Ajout au layout principal
//     mainLayout->addLayout(radioLayout);
//     mainLayout->addWidget(m_chartView);
//     mainLayout->addWidget(textStats);

//     // Connexion des signaux
//     QButtonGroup *group = new QButtonGroup(this);
//     group->addButton(radioBarres, 0);
//     group->addButton(radioCourbe, 1);
//     group->addButton(radioSecteurs, 2);
//     connect(group, &QButtonGroup::buttonClicked, this, &historique::onTypeGraphiqueChanged);

//     chargerHistorique();
//     onTypeGraphiqueChanged();
// }

// historique::~historique()
// {
//     // La destruction des widgets est gérée par le système de parenté Qt
// }

// void historique::ajouterVisite(const QDateTime &dateTime)
// {
//     Visite visite;
//     visite.date = dateTime.date();
//     visite.type = "Visite"; // Type par défaut

//     // Ajouter à la liste en mémoire
//     m_visites.append(visite);

//     // Sauvegarder dans le fichier
//     QFile file("historique.txt");
//     if (file.open(QIODevice::Append | QIODevice::Text)) {
//         QTextStream out(&file);
//         out << visite.date.toString("yyyy-MM-dd") << " " << visite.type << "\n";
//         file.close();
//     }

//     // Mettre à jour l'affichage
//     mettreAJourStatistiques();
//     onTypeGraphiqueChanged();
// }

// void historique::chargerHistorique()
// {
//     m_visites.clear();

//     QFile file("historique.txt");
//     if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
//     {
//         QMessageBox::warning(this, "Erreur", "Impossible d'ouvrir le fichier historique");
//         return;
//     }

//     QTextStream in(&file);
//     while (!in.atEnd())
//     {
//         QString line = in.readLine();
//         QStringList parts = line.split(" ");
//         if (parts.size() >= 2)
//         {
//             Visite visite;
//             visite.date = QDate::fromString(parts[0], "yyyy-MM-dd");
//             visite.type = parts[1];
//             m_visites.append(visite);
//         }
//     }

//     file.close();
//     mettreAJourStatistiques();
// }

// void historique::onTypeGraphiqueChanged()
// {
//     if (radioBarres->isChecked())
//         creerGraphiqueBarres();
//     else if (radioCourbe->isChecked())
//         creerGraphiqueCourbe();
//     else if (radioSecteurs->isChecked())
//         creerGraphiqueSecteurs();
// }

// void historique::creerGraphiqueBarres()
// {
//     if (m_visites.empty()) return;

//     QChart *chart = new QChart();
//     chart->setTitle("Statistiques des visites (Barres)");

//     QBarSeries *series = new QBarSeries();

//     // Compter les visites par date
//     QMap<QDate, int> counts;
//     for (const Visite &visite : m_visites)
//     {
//         counts[visite.date]++;
//     }

//     QBarSet *set = new QBarSet("Visites");
//     QStringList categories;

//     for (auto it = counts.begin(); it != counts.end(); ++it)
//     {
//         *set << it.value();
//         categories << it.key().toString("dd/MM");
//     }

//     series->append(set);
//     chart->addSeries(series);

//     QBarCategoryAxis *axisX = new QBarCategoryAxis();
//     axisX->append(categories);
//     chart->addAxis(axisX, Qt::AlignBottom);
//     series->attachAxis(axisX);

//     QValueAxis *axisY = new QValueAxis();
//     axisY->setLabelFormat("%d");
//     chart->addAxis(axisY, Qt::AlignLeft);
//     series->attachAxis(axisY);

//     m_chartView->setChart(chart);
// }

// void historique::creerGraphiqueCourbe()
// {
//     if (m_visites.empty()) return;

//     QChart *chart = new QChart();
//     chart->setTitle("Statistiques des visites (Courbe)");

//     QLineSeries *series = new QLineSeries();
//     series->setName("Visites");

//     // Compter les visites par date
//     QMap<QDate, int> counts;
//     for (const Visite &visite : m_visites)
//     {
//         counts[visite.date]++;
//     }

//     for (auto it = counts.begin(); it != counts.end(); ++it)
//     {
//         series->append(it.key().toJulianDay(), it.value());
//     }

//     chart->addSeries(series);

//     QDateTimeAxis *axisX = new QDateTimeAxis();
//     axisX->setFormat("dd/MM");
//     axisX->setTitleText("Date");
//     chart->addAxis(axisX, Qt::AlignBottom);
//     series->attachAxis(axisX);

//     QValueAxis *axisY = new QValueAxis();
//     axisY->setLabelFormat("%d");
//     axisY->setTitleText("Nombre de visites");
//     chart->addAxis(axisY, Qt::AlignLeft);
//     series->attachAxis(axisY);

//     m_chartView->setChart(chart);
// }

// void historique::creerGraphiqueSecteurs()
// {
//     if (m_visites.empty()) return;

//     QChart *chart = new QChart();
//     chart->setTitle("Répartition des types de visites");

//     QPieSeries *series = new QPieSeries();

//     // Compter les visites par type
//     QMap<QString, int> counts;
//     for (const Visite &visite : m_visites)
//     {
//         counts[visite.type]++;
//     }

//     for (auto it = counts.begin(); it != counts.end(); ++it)
//     {
//         series->append(it.key(), it.value());
//     }

//     series->setLabelsVisible();
//     chart->addSeries(series);

//     m_chartView->setChart(chart);
// }

// void historique::mettreAJourStatistiques()
// {
//     if (m_visites.empty()) {
//         textStats->setPlainText("Aucune donnée disponible");
//         return;
//     }

//     QDate firstDate = m_visites.first().date;
//     QDate lastDate = m_visites.last().date;
//     int total = m_visites.size();
//     int days = firstDate.daysTo(lastDate) + 1;
//     double avg = days > 0 ? static_cast<double>(total) / days : 0;

//     QString stats = QString(
//                         "Statistiques:\n"
//                         "Total visites: %1\n"
//                         "Période: %2 - %3\n"
//                         "Moyenne/jour: %4"
//                         ).arg(total)
//                         .arg(firstDate.toString("dd/MM/yyyy"))
//                         .arg(lastDate.toString("dd/MM/yyyy"))
//                         .arg(avg, 0, 'f', 1);

//     textStats->setPlainText(stats);
// }






#include "historique.h"
#include <QPainter>

historique::historique(QWidget *parent) : QDialog(parent)
{
    setWindowTitle("Nos Statistiques");
    resize(800, 800);

    mainLayout = new QVBoxLayout(this);

    // Titre principal
    QLabel *titre = new QLabel("NOS CHIFFRES");
    titre->setStyleSheet("font-size: 24px; font-weight: bold; margin-bottom: 20px;");
    titre->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(titre);

    // Graphique des investissements
    creerGraphiqueInvestissements();

    // Graphique de croissance
    creerGraphiqueCroissance();
}

void historique::ajouterVisite(const QDateTime &dateTime)
{
    // Stocker la visite
    m_visites.append(dateTime);

    // Mettre à jour les graphiques si nécessaire
    // (Dans cette version, les graphiques sont statiques donc pas de mise à jour)
}

void historique::creerGraphiqueInvestissements()
{
    // Sous-titre
    QLabel *sousTitre = new QLabel("Nos investissements");
    sousTitre->setStyleSheet("font-size: 18px; margin-top: 10px;");
    mainLayout->addWidget(sousTitre);

    // Création du graphique
    QPieSeries *series = new QPieSeries();
    series->append("Personnel 13.3%", 13.3);
    series->append("consultation de menu 18.3%", 18.3);
    series->append("Réservation Table 60%", 60);
    series->append("commande en ligne 30%", 30);
    series->append("Feedback 15.3%", 15.3);

    // Configuration des tranches
    for (QPieSlice *slice : series->slices()) {
        slice->setLabelVisible();
        slice->setLabelColor(Qt::black);
        slice->setBorderWidth(2);
    }

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->legend()->setVisible(true);
    chart->legend()->setAlignment(Qt::AlignRight);
    chart->setBackgroundVisible(false);

    chartViewInvest = new QChartView(chart);
    chartViewInvest->setRenderHint(QPainter::Antialiasing);
    chartViewInvest->setMinimumHeight(300);
    mainLayout->addWidget(chartViewInvest);
}

void historique::creerGraphiqueCroissance()
{
    // Sous-titre
    QLabel *sousTitre = new QLabel("Notre croissance");
    sousTitre->setStyleSheet("font-size: 18px; margin-top: 30px;");
    mainLayout->addWidget(sousTitre);

    // Création du graphique
    QBarSet *set = new QBarSet("Croissance (%)");
    *set << 75 << 50 << 25 << 0;
    set->setColor(QColor(52, 152, 219)); // Couleur bleue

    QBarSeries *series = new QBarSeries();
    series->append(set);

    QChart *chart = new QChart();
    chart->addSeries(series);
    chart->setBackgroundVisible(false);

    QStringList categories;
    categories << "2021" << "2022" << "2023" << "2024";

    QBarCategoryAxis *axisX = new QBarCategoryAxis();
    axisX->append(categories);
    chart->addAxis(axisX, Qt::AlignBottom);
    series->attachAxis(axisX);

    QValueAxis *axisY = new QValueAxis();
    axisY->setRange(0, 100);
    axisY->setTitleText("Pourcentage");
    chart->addAxis(axisY, Qt::AlignLeft);
    series->attachAxis(axisY);

    chartViewCroissance = new QChartView(chart);
    chartViewCroissance->setRenderHint(QPainter::Antialiasing);
    chartViewCroissance->setMinimumHeight(300);
    mainLayout->addWidget(chartViewCroissance);
}

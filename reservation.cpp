#include "reservation.h"
#include "ui_reservation.h"
#include <QFormLayout>
#include <QLabel>
#include <QSpinBox>
#include <QPushButton>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QPixmap>
#include <QScrollArea>
#include <QMessageBox>

reservation::reservation(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::reservation)
{
    ui->setupUi(this);

    setWindowTitle("Réservation de Table");
    resize(800, 600);
 setBackground();
    currentClientId = 1;

    // Boutons principaux
    QPushButton *btnReserver = new QPushButton("Réserver une table", this);
    QPushButton *btnAnnuler = new QPushButton("Annuler réservation", this);
    QPushButton *btnRafraichir = new QPushButton("Actualiser", this);

    QHBoxLayout *layoutBoutons = new QHBoxLayout();
    layoutBoutons->addWidget(btnReserver);
    layoutBoutons->addWidget(btnAnnuler);
    layoutBoutons->addWidget(btnRafraichir);

    // Zone de défilement
    scrollArea = new QScrollArea(this);
    widgetContenu = new QWidget();
    layoutCommandes = new QVBoxLayout(widgetContenu);
    scrollArea->setWidgetResizable(true);
    scrollArea->setWidget(widgetContenu);

    // Formulaire
    formulaireWidget = new QWidget(this);
    QFormLayout *formLayout = new QFormLayout(formulaireWidget);

    nomClientEdit = new QLineEdit();
    telephoneEdit = new QLineEdit();
    telephoneEdit->setInputMask("99 99 99 99 99;_");

    nbPersonnesSpin = new QSpinBox();
    nbPersonnesSpin->setRange(1, 20);

    dateHeureEdit = new QLineEdit();
    dateHeureEdit->setInputMask("99/99/9999 99:99;_");
    dateHeureEdit->setPlaceholderText("JJ/MM/AAAA HH:MM");

    commentairesEdit = new QLineEdit();

    formLayout->addRow("Nom:", nomClientEdit);
    formLayout->addRow("Téléphone:", telephoneEdit);
    formLayout->addRow("Nombre de personnes:", nbPersonnesSpin);
    formLayout->addRow("Date et heure:", dateHeureEdit);
    formLayout->addRow("Commentaires:", commentairesEdit);

    QPushButton *btnConfirmer = new QPushButton("Confirmer");
    QPushButton *btnAnnulerForm = new QPushButton("Annuler");
    QHBoxLayout *formButtonsLayout = new QHBoxLayout();
    formButtonsLayout->addWidget(btnConfirmer);
    formButtonsLayout->addWidget(btnAnnulerForm);
    formLayout->addRow(formButtonsLayout);

    formulaireWidget->setLayout(formLayout);
    formulaireWidget->hide();

    // Layout principal
    QVBoxLayout *layoutPrincipal = new QVBoxLayout(this);
    layoutPrincipal->addLayout(layoutBoutons);
    layoutPrincipal->addWidget(formulaireWidget);
    layoutPrincipal->addWidget(scrollArea);
    setLayout(layoutPrincipal);

    // Connexions
    connect(btnReserver, &QPushButton::clicked, this, [this]() {
        afficherFormulaireReservation();
    });
    connect(btnAnnuler, &QPushButton::clicked, this, &reservation::annulerReservation);
    connect(btnRafraichir, &QPushButton::clicked, this, [this]() {
        afficherReservations();
    });
    connect(btnConfirmer, &QPushButton::clicked, this, &reservation::reserverTable);
    connect(btnAnnulerForm, &QPushButton::clicked, this, [this]() {
        afficherFormulaireReservation(false);
    });

    chargerReservationsClient(currentClientId);
    afficherReservations();
}

reservation::~reservation()
{
    delete ui;
}

void reservation::chargerReservationsClient(int clientId)
{
    reservations.clear();

    Reservation res1{
        1,
        "Jean Dupont",
        "06 12 34 56 78",
        4,
        QDateTime::currentDateTime().addDays(1).toString("dd/MM/yyyy HH:mm"),
        "Confirmée",
        "Table près de la fenêtre"
    };

    Reservation res2{
        2,
        "Jean Dupont",
        "06 12 34 56 78",
        2,
        QDateTime::currentDateTime().addDays(3).toString("dd/MM/yyyy HH:mm"),
        "Confirmée",
        "Anniversaire"
    };

    if (clientId == 1) {
        reservations << res1 << res2;
    }
}

void reservation::afficherReservations()
{
    QLayout *layout = widgetContenu->layout();
    while (QLayoutItem* item = layout->takeAt(0)) {
        delete item->widget();
        delete item;
    }

    for (const Reservation &res : std::as_const(reservations)) {
        if (res.statut != "Annulée") {
            QWidget *widgetRes = creerWidgetReservation(res);
            layout->addWidget(widgetRes);
        }
    }

    static_cast<QVBoxLayout*>(layout)->addStretch();
}

QWidget* reservation::creerWidgetReservation(const Reservation &res)
{
    QWidget *widget = new QWidget();
    QHBoxLayout *layout = new QHBoxLayout(widget);

    QLabel *lblInfo = new QLabel(
        QString("Réservation #%1\n%2 personnes - %3\nLe %4\n%5")
            .arg(res.id)
            .arg(res.nbPersonnes)
            .arg(res.nomClient)
            .arg(res.dateHeure)
            .arg(res.commentaires)
        );

    QLabel *lblStatut = new QLabel(res.statut);
    QPushButton *btnModifier = new QPushButton("Modifier", widget);
    btnModifier->setProperty("reservationId", res.id);
    connect(btnModifier, &QPushButton::clicked, this, &reservation::modifierReservation);

    QPushButton *btnAnnuler = new QPushButton("Annuler", widget);
    btnAnnuler->setProperty("reservationId", res.id);
    connect(btnAnnuler, &QPushButton::clicked, this, &reservation::annulerReservation);

    QString style;
    if (res.statut == "Confirmée") {
        style = "background-color: #D4EDDA;";
    } else if (res.statut == "Annulée") {
        style = "background-color: #F8D7DA;";
    } else {
        style = "background-color: #FFF3CD;";
    }

    widget->setStyleSheet(style + "border: 1px solid #DDD; border-radius: 5px; padding: 10px;");

    layout->addWidget(lblInfo, 1);
    layout->addWidget(lblStatut);
    layout->addWidget(btnModifier);
    layout->addWidget(btnAnnuler);

    return widget;
}

void reservation::reserverTable()
{
    if (nomClientEdit->text().isEmpty() || telephoneEdit->text().contains('_') || dateHeureEdit->text().contains('_')) {
        QMessageBox::warning(this, "Erreur", "Veuillez remplir tous les champs obligatoires");
        return;
    }

    int nouveauId = reservations.isEmpty() ? 1 : reservations.last().id + 1;
    Reservation nouvelleRes{
        nouveauId,
        nomClientEdit->text(),
        telephoneEdit->text(),
        nbPersonnesSpin->value(),
        dateHeureEdit->text(),
        "Confirmée",
        commentairesEdit->text()
    };

    reservations.append(nouvelleRes);
    clearFormulaire();
    afficherFormulaireReservation(false);
    afficherReservations();

    QMessageBox::information(this, "Succès", "Votre réservation a été enregistrée!");
}

void reservation::annulerReservation()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int id = btn->property("reservationId").toInt();

    for (Reservation &res : reservations) {
        if (res.id == id) {
            if (res.statut == "Annulée") {
                QMessageBox::information(this, "Information", "Cette réservation est déjà annulée");
                return;
            }

            if (QMessageBox::question(this, "Confirmation",
                                      "Êtes-vous sûr de vouloir annuler cette réservation?",
                                      QMessageBox::Yes | QMessageBox::No) == QMessageBox::Yes) {
                res.statut = "Annulée";
                afficherReservations();
                QMessageBox::information(this, "Succès", QString("Réservation #%1 annulée").arg(id));
            }
            return;
        }
    }

    QMessageBox::warning(this, "Erreur", "Réservation introuvable!");
}

void reservation::modifierReservation()
{
    QPushButton *btn = qobject_cast<QPushButton*>(sender());
    if (!btn) return;

    int id = btn->property("reservationId").toInt();

    for (int i = 0; i < reservations.size(); ++i) {
        if (reservations[i].id == id) {
            if (reservations[i].statut == "Annulée") {
                QMessageBox::warning(this, "Erreur", "Impossible de modifier une réservation annulée");
                return;
            }

            nomClientEdit->setText(reservations[i].nomClient);
            telephoneEdit->setText(reservations[i].telephone);
            nbPersonnesSpin->setValue(reservations[i].nbPersonnes);
            dateHeureEdit->setText(reservations[i].dateHeure);
            commentairesEdit->setText(reservations[i].commentaires);

            reservations.removeAt(i);
            afficherFormulaireReservation();
            return;
        }
    }

    QMessageBox::warning(this, "Erreur", "Réservation introuvable!");
}

void reservation::afficherFormulaireReservation(bool show)
{
    formulaireWidget->setVisible(show);
    scrollArea->setVisible(!show);

    if (!show) {
        clearFormulaire();
    }
}

void reservation::clearFormulaire()
{
    nomClientEdit->clear();
    telephoneEdit->clear();
    nbPersonnesSpin->setValue(2);
    dateHeureEdit->clear();
    commentairesEdit->clear();
}



void reservation::loadImageToFrame()
{
    // // Vérifier que le frame existe
    // if (!ui->frame) {
    //     qDebug() << "Erreur: Le frame n'existe pas";
    //     return;
    // }

    // // Créer un QLabel pour l'image
    // QLabel *imageLabel1 = new QLabel(ui->frame);
    // imageLabel1->setObjectName("backgroundImageLabel");

    // // Charger l'image depuis les ressources
    // QPixmap pixmap1(":/background/img20.jpg");

    // if(pixmap1.isNull()) {
    //     qDebug() << "Erreur: Impossible de charger img20.jpg depuis les ressources";
    //     return;
    // }

    // // Redimensionner et positionner l'image
    // imageLabel1->setPixmap(pixmap1.scaled(
    //     ui->frame->width(),
    //     ui->frame->height(),
    //     Qt::KeepAspectRatioByExpanding,
    //     Qt::SmoothTransformation
    //     ));

    // imageLabel1->setAlignment(Qt::AlignCenter);
    // imageLabel1->setGeometry(0, 0, ui->frame->width(), ui->frame->height());
    // imageLabel1->setScaledContents(true);

    // // Styler le frame
    // ui->frame->setStyleSheet(
    //     "QFrame {"
    //     "   border: 2px solid #8B4513;"
    //     "   border-radius: 8px;"
    //     "   background-color: white;"
    //     "}"
    //     );
}


void reservation::setBackground()
{
    // Style pour le fond
    this->setStyleSheet(
        "reservation {"
        "   background-image: url(:/background/img20.jpg);"
        "   background-position: center;"
        "   background-repeat: no-repeat;"
        "   background-size: cover;"
        "}"

        "QGroupBox, QFrame, QScrollArea, QWidget#formulaireWidget {"
        "   background-color: rgba(255, 255, 255, 0.85);"
        "   border-radius: 5px;"
        "   padding: 10px;"
        "}"

        "QPushButton {"
        "   background-color: #3498db;"
        "   color: white;"
        "   border: none;"
        "   padding: 8px 16px;"
        "   border-radius: 4px;"
        "   font-weight: bold;"
        "}"

        "QPushButton:hover {"
        "   background-color: #2980b9;"
        "}"

        "QLineEdit, QSpinBox {"
        "   padding: 6px;"
        "   border: 1px solid #ccc;"
        "   border-radius: 4px;"
        "   background: white;"
        "}"
        );
}

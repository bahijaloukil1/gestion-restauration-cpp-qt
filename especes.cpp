#include "especes.h"
#include "ui_especes.h"

especes::especes(int commandeId, QWidget *parent) :
    QDialog(parent),
    ui(new Ui::especes),
    montantTotal(0.0),
    m_commandeId(commandeId)
{
    ui->setupUi(this);
    setupUI();
    applyStyles();

    if (!initDatabase()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
        return;
    }

    if (!verifierCommandeExiste()) {
        QMessageBox::critical(this, "Erreur", "Commande invalide ou inexistante");
        this->close();
        return;
    }

    calculerMontantTotal();
}

especes::~especes()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
    delete ui;
}

void especes::setupUI()
{
    // Configuration de base
    setWindowTitle("Paiement en espèces");
    setMinimumSize(400, 300);

    // Layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);
    mainLayout->setContentsMargins(10, 10, 10, 10);
    mainLayout->setSpacing(10);

    // Zone de montant total
    QFrame *frameTotal = new QFrame();
    QHBoxLayout *layoutTotal = new QHBoxLayout(frameTotal);
    QLabel *labelTotalText = new QLabel("Montant total:");
    montantTotalLabel = new QLabel("0.00 €");
    layoutTotal->addWidget(labelTotalText);
    layoutTotal->addWidget(montantTotalLabel);
    mainLayout->addWidget(frameTotal);

    // Zone de saisie
    QFrame *frameSaisie = new QFrame();
    QVBoxLayout *layoutSaisie = new QVBoxLayout(frameSaisie);
    QLabel *labelMontant = new QLabel("Montant donné:");
    montantEdit = new QLineEdit();
  //  montantEdit->setValidator(new QDoubleValidator(0, 10000, 2, this));
    layoutSaisie->addWidget(labelMontant);
    layoutSaisie->addWidget(montantEdit);
    mainLayout->addWidget(frameSaisie);

    // Zone de montant restant
    montantRestantLabel = new QLabel();
    montantRestantLabel->setAlignment(Qt::AlignCenter);
    mainLayout->addWidget(montantRestantLabel);

    // Boutons
    QFrame *frameBoutons = new QFrame();
    QHBoxLayout *layoutBoutons = new QHBoxLayout(frameBoutons);
    btnValider = new QPushButton("Valider");
    btnAnnuler = new QPushButton("Annuler");
    layoutBoutons->addWidget(btnValider);
    layoutBoutons->addWidget(btnAnnuler);
    mainLayout->addWidget(frameBoutons);

    // Connexions
    connect(btnValider, &QPushButton::clicked, this, &especes::validerPaiement);
    connect(btnAnnuler, &QPushButton::clicked, this, &especes::annulerPaiement);
    connect(montantEdit, &QLineEdit::textChanged, this, &especes::onMontantEditChanged);
}

void especes::applyStyles()
{
    // Styles CSS pour l'interface
    setStyleSheet(R"(
        QDialog { background-color: #f5f5f5; }
        QLabel { color: #333; }
        QLineEdit { padding: 5px; border: 1px solid #ccc; }
        QPushButton { padding: 8px; min-width: 80px; }
        #btnValider { background-color: #4CAF50; color: white; }
        #btnAnnuler { background-color: #f44336; color: white; }
    )");
}

bool especes::initDatabase()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("gestion_restaurant.db");

    if (!m_db.open()) {
        qDebug() << "Erreur DB:" << m_db.lastError().text();
        return false;
    }
    return true;
}

bool especes::verifierCommandeExiste()
{
    if (m_commandeId <= 0) return false;

    QSqlQuery query;
    query.prepare("SELECT COUNT(*) FROM commandes WHERE id = ?");
    query.addBindValue(m_commandeId);

    if (!query.exec()) {
        qDebug() << "Erreur vérification commande:" << query.lastError().text();
        return false;
    }

    return query.next() && query.value(0).toInt() > 0;
}

void especes::calculerMontantTotal()
{
    QSqlQuery query;
    query.prepare("SELECT SUM(quantite * prix) FROM commandes WHERE id = ?");
    query.addBindValue(m_commandeId);

    if (!query.exec()) {
        QMessageBox::critical(this, "Erreur",
                              QString("Calcul impossible: %1").arg(query.lastError().text()));
        return;
    }

    if (query.next()) {
        montantTotal = query.value(0).toDouble();
        montantTotalLabel->setText(montantTotal > 0 ?
                                       QString::number(montantTotal, 'f', 2) + " €" :
                                       "Aucune commande valide");
        btnValider->setEnabled(montantTotal > 0);
    }
}

void especes::onMontantEditChanged(const QString &text)
{
    bool ok;
    double montant = text.toDouble(&ok);

    if (ok && montantTotal > 0) {
        double reste = montantTotal - montant;
        if (reste > 0) {
            montantRestantLabel->setText(QString("Reste: %1 €").arg(reste, 0, 'f', 2));
        } else {
            montantRestantLabel->setText("Montant suffisant");
        }
    } else {
        montantRestantLabel->clear();
    }
}

void especes::validerPaiement()
{
    if (montantTotal <= 0) {
        QMessageBox::warning(this, "Erreur", "Aucune commande à payer");
        return;
    }

    bool ok;
    double montant = montantEdit->text().toDouble(&ok);

    if (!ok || montant < montantTotal) {
        QMessageBox::warning(this, "Erreur", "Montant insuffisant");
        return;
    }

    m_db.transaction();
    QSqlQuery query;

    // Enregistrement du paiement
    query.prepare("INSERT INTO paiements (commande_id, montant, methode) "
                  "VALUES (?, ?, 'Espèces')");
    query.addBindValue(m_commandeId);
    query.addBindValue(montantTotal);

    if (!query.exec()) {
        m_db.rollback();
        QMessageBox::critical(this, "Erreur",
                              QString("Échec d'enregistrement: %1").arg(query.lastError().text()));
        return;
    }

    // Marquer la commande comme payée
    query.prepare("UPDATE commandes SET statut = 'Payée' WHERE id = ?");
    query.addBindValue(m_commandeId);

    if (!query.exec()) {
        m_db.rollback();
        QMessageBox::critical(this, "Erreur",
                              QString("Échec de mise à jour: %1").arg(query.lastError().text()));
        return;
    }

    m_db.commit();

    double monnaie = montant - montantTotal;
    QMessageBox::information(this, "Succès",
                             QString("Paiement accepté!\nMonnaie à rendre: %1 €").arg(monnaie, 0, 'f', 2));
    accept();
}

void especes::annulerPaiement()
{
    reject();
}

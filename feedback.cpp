// #include "feedback.h"
// #include "ui_feedback.h"

// feedback::feedback(QWidget *parent)
//     : QDialog(parent)
//     , ui(new Ui::feedback)
// {
//     ui->setupUi(this);
// }

// feedback::~feedback()
// {
//     delete ui;
// }




#include "feedback.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QVBoxLayout>
#include <QLabel>
#include <QCheckBox>
#include <QDebug>
#include <stdexcept> // Pour std::runtime_error

feedback::feedback(QWidget *parent) :
    QDialog(parent),
    m_noteSelectionnee(0)
{
    setWindowTitle("Feedback Client");
    resize(600, 500);

    if (!connecterBaseDeDonnees()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
    }

    setupUI();
    creerBoutonsNotes();
    chargerCategories();
}

feedback::~feedback()
{
    if (m_db.isOpen()) {
        m_db.close();
    }
}

void feedback::setupUI()
{
    // Création des widgets
    textEditCommentaire = new QTextEdit(this);
    pushButtonEnvoyer = new QPushButton("Envoyer le feedback", this);
    formLayout = new QFormLayout();
    scrollAreaCategories = new QScrollArea(this);

    // Configuration du layout principal
    QVBoxLayout *mainLayout = new QVBoxLayout(this);

    // Ajout des widgets au layout
    mainLayout->addLayout(formLayout);
    mainLayout->addWidget(new QLabel("Commentaire:", this));
    mainLayout->addWidget(textEditCommentaire);
    mainLayout->addWidget(scrollAreaCategories);
    mainLayout->addWidget(pushButtonEnvoyer);

    // Style
    this->setStyleSheet("QDialog { background-color: #f8f9fa; }");
    textEditCommentaire->setPlaceholderText("Votre avis nous intéresse...");

    QString buttonStyle = "QPushButton {"
                          "  background-color: #4CAF50;"
                          "  color: white;"
                          "  border: none;"
                          "  padding: 8px 16px;"
                          "  border-radius: 4px;"
                          "}";
    pushButtonEnvoyer->setStyleSheet(buttonStyle);

    connect(pushButtonEnvoyer, &QPushButton::clicked, this, &feedback::onEnvoyerClicked);
}

void feedback::creerBoutonsNotes()
{
    QWidget *notesWidget = new QWidget();
    QHBoxLayout *notesLayout = new QHBoxLayout(notesWidget);
    notesLayout->setSpacing(5);

    m_noteButtons = new QButtonGroup(this);

    for (int i = 1; i <= 5; ++i) {
        QPushButton *btn = new QPushButton(QString::number(i), notesWidget);
        btn->setFixedSize(40, 40);
        btn->setCheckable(true);
        btn->setStyleSheet(
            "QPushButton {"
            "  border: 1px solid #ddd;"
            "  border-radius: 20px;"
            "  background-color: white;"
            "}"
            "QPushButton:checked {"
            "  background-color: #FFD700;"
            "  font-weight: bold;"
            "}"
            );
        m_noteButtons->addButton(btn, i);
        notesLayout->addWidget(btn);
    }

    formLayout->addRow("Note (1-5):", notesWidget);
    connect(m_noteButtons, &QButtonGroup::idClicked, this, &feedback::onNoteClicked);
}

void feedback::chargerCategories()
{
    QWidget *categoriesContainer = new QWidget();
    QVBoxLayout *categoriesLayout = new QVBoxLayout(categoriesContainer);

    QSqlQuery query("SELECT id, nom FROM categories_feedback ORDER BY nom", m_db);
    if (!query.exec()) {
        qDebug() << "Erreur chargement catégories:" << query.lastError().text();
        return;
    }

    while (query.next()) {
        QCheckBox *checkbox = new QCheckBox(query.value(1).toString(), categoriesContainer);
        checkbox->setProperty("categoryId", query.value(0));
        categoriesLayout->addWidget(checkbox);
    }

    scrollAreaCategories->setWidget(categoriesContainer);
    scrollAreaCategories->setWidgetResizable(true);
}

bool feedback::connecterBaseDeDonnees()
{
    m_db = QSqlDatabase::addDatabase("QSQLITE");
    m_db.setDatabaseName("gestion_restaurant.db");

    if (!m_db.open()) {
        qDebug() << "Erreur DB:" << m_db.lastError().text();
        return false;
    }

    QSqlQuery query(m_db);
    QStringList tables = {
        "CREATE TABLE IF NOT EXISTS feedbacks ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "client_id INTEGER,"
        "note INTEGER NOT NULL,"
        "commentaire TEXT,"
        "date TIMESTAMP DEFAULT CURRENT_TIMESTAMP)",

        "CREATE TABLE IF NOT EXISTS categories_feedback ("
        "id INTEGER PRIMARY KEY AUTOINCREMENT,"
        "nom TEXT NOT NULL UNIQUE)",

        "CREATE TABLE IF NOT EXISTS feedback_categories ("
        "feedback_id INTEGER,"
        "category_id INTEGER,"
        "PRIMARY KEY(feedback_id, category_id))",

        "INSERT OR IGNORE INTO categories_feedback (nom) VALUES "
        "('Qualité de la nourriture'), ('Service'), ('Ambiance'), "
        "('Propreté'), ('Rapport qualité-prix')"
    };

    for (const QString &sql : tables) {
        if (!query.exec(sql)) {
            qDebug() << "Erreur création table:" << query.lastError().text();
            return false;
        }
    }

    return true;
}

void feedback::onNoteClicked(int note)
{
    m_noteSelectionnee = note;
}

void feedback::onEnvoyerClicked()
{
    if (m_noteSelectionnee == 0) {
        QMessageBox::warning(this, "Attention", "Veuillez sélectionner une note");
        return;
    }

    QString commentaire = textEditCommentaire->toPlainText().trimmed();
    int clientId = 1; // À remplacer par l'ID du client connecté

    m_db.transaction();

    try {
        QSqlQuery query(m_db);
        query.prepare("INSERT INTO feedbacks (client_id, note, commentaire) "
                      "VALUES (:client_id, :note, :commentaire)");
        query.bindValue(":client_id", clientId);
        query.bindValue(":note", m_noteSelectionnee);
        query.bindValue(":commentaire", commentaire.isEmpty() ? QVariant() : commentaire);

        if (!query.exec()) {
            throw std::runtime_error(query.lastError().text().toStdString());
        }

        int feedbackId = query.lastInsertId().toInt();
        QWidget *categoriesWidget = scrollAreaCategories->widget();
        QList<QCheckBox*> checkboxes = categoriesWidget->findChildren<QCheckBox*>();

        for (QCheckBox *checkbox : checkboxes) {
            if (checkbox->isChecked()) {
                int categoryId = checkbox->property("categoryId").toInt();
                query.prepare("INSERT INTO feedback_categories (feedback_id, category_id) "
                              "VALUES (:feedback_id, :category_id)");
                query.bindValue(":feedback_id", feedbackId);
                query.bindValue(":category_id", categoryId);

                if (!query.exec()) {
                    throw std::runtime_error(query.lastError().text().toStdString());
                }
            }
        }

        m_db.commit();
        QMessageBox::information(this, "Merci", "Votre feedback a été enregistré !");
        this->close();

    } catch (const std::exception &e) {
        m_db.rollback();
        QMessageBox::critical(this, "Erreur", e.what());
    }
}

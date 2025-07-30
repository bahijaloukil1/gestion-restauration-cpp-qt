#include "menu.h"
#include "ui_menu.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>

Menu::Menu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::Menu)
{
    ui->setupUi(this);

    // Initialisation BDD
    db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("menu_database.db");

    if (!db.open()) {
        QMessageBox::critical(this, "Erreur", "Connexion à la base de données échouée");
    }
    // Rendre label_29 cliquable
    ui->label_29->setCursor(Qt::PointingHandCursor);  // Change le curseur en main
    ui->label_29->installEventFilter(this);
    loadImageToFrame();  // Charger les images après l'initialisation UI
}

void Menu::loadImageToFrame()
{
    // ============ PREMIER FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel1 = new QLabel(ui->frame);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap1(":/background/img1.jpg");

    if(pixmap1.isNull()) {
        qDebug() << "Erreur: Impossible de charger img1.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel1->setPixmap(pixmap1.scaled(
            ui->frame->width() - 10,  // -10 pour la marge
            ui->frame->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel1->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel1->setGeometry(0, 0, ui->frame->width(), ui->frame->height());
    }

    // 6. Styler le premier frame
    ui->frame->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );

    // ============ DEUXIÈME FRAME (frame_2) ============
    // 1. Créer un QLabel pour contenir la deuxième image
    QLabel *imageLabel2 = new QLabel(ui->frame_2);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap2(":/background/img2.jpg"); // Assurez-vous d'avoir ajouté img2.jpg à vos ressources

    if(pixmap2.isNull()) {
        qDebug() << "Erreur: Impossible de charger img2.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel2->setPixmap(pixmap2.scaled(
            ui->frame_2->width() - 10,  // -10 pour la marge
            ui->frame_2->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel2->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel2->setGeometry(0, 0, ui->frame_2->width(), ui->frame_2->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_2->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );


    // ============ 3 FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel3 = new QLabel(ui->frame_3);

    // 2. Charger la 3 image depuis les ressources
    QPixmap pixmap3(":/background/img3.jpg");

    if(pixmap3.isNull()) {
        qDebug() << "Erreur: Impossible de charger img3.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel3->setPixmap(pixmap3.scaled(
            ui->frame_3->width() - 10,  // -10 pour la marge
            ui->frame_3->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel3->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel3->setGeometry(0, 0, ui->frame_3->width(), ui->frame_3->height());
    }

    // 6. Styler le 3 frame
    ui->frame_3->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );







    // ============ 4FRAME (frame_4) ============
    // 1. Créer un QLabel pour contenir la deuxième image
    QLabel *imageLabel4 = new QLabel(ui->frame_4);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap4(":/background/img4.jpg"); // Assurez-vous d'avoir ajouté img4.jpg à vos ressources

    if(pixmap4.isNull()) {
        qDebug() << "Erreur: Impossible de charger img4.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel4->setPixmap(pixmap4.scaled(
            ui->frame_4->width() - 10,  // -10 pour la marge
            ui->frame_4->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel4->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel4->setGeometry(0, 0, ui->frame_4->width(), ui->frame_4->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_4->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );




    // ============ 5FRAME (frame_5) ============
    // 1. Créer un QLabel pour contenir la 5 image
    QLabel *imageLabel5 = new QLabel(ui->frame_5);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap5(":/background/img5.jpg"); // Assurez-vous d'avoir ajouté img4.jpg à vos ressources

    if(pixmap5.isNull()) {
        qDebug() << "Erreur: Impossible de charger img5.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel5->setPixmap(pixmap5.scaled(
            ui->frame_5->width() - 10,  // -10 pour la marge
            ui->frame_5->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel5->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel5->setGeometry(0, 0, ui->frame_5->width(), ui->frame_5->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_5->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );




    // ============ 6 FRAME (frame_6) ============
    // 1. Créer un QLabel pour contenir la 5 image
    QLabel *imageLabel6 = new QLabel(ui->frame_6);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap6(":/background/img6.jpg"); // Assurez-vous d'avoir ajouté img4.jpg à vos ressources

    if(pixmap6.isNull()) {
        qDebug() << "Erreur: Impossible de charger img6.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel6->setPixmap(pixmap6.scaled(
            ui->frame_6->width() - 10,  // -10 pour la marge
            ui->frame_6->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel6->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel6->setGeometry(0, 0, ui->frame_6->width(), ui->frame_6->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_6->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );




    // ============ 7 FRAME (frame_7) ============
    // 1. Créer un QLabel pour contenir la 5 image
    QLabel *imageLabel7 = new QLabel(ui->frame_7);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap7(":/background/img7.jpg"); // Assurez-vous d'avoir ajouté img4.jpg à vos ressources

    if(pixmap7.isNull()) {
        qDebug() << "Erreur: Impossible de charger img7.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel7->setPixmap(pixmap7.scaled(
            ui->frame_7->width() - 10,  // -10 pour la marge
            ui->frame_7->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel7->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel7->setGeometry(0, 0, ui->frame_7->width(), ui->frame_7->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_7->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );



    // ============ 8 FRAME (frame_8) ============
    // 1. Créer un QLabel pour contenir la 8 image
    QLabel *imageLabel8 = new QLabel(ui->frame_8);

    // 2. Charger la deuxième image depuis les ressources
    QPixmap pixmap8(":/background/img8.jpg"); // Assurez-vous d'avoir ajouté img4.jpg à vos ressources

    if(pixmap8.isNull()) {
        qDebug() << "Erreur: Impossible de charger img8.jpg depuis les ressources";
    } else {
        // 3. Redimensionner l'image pour s'adapter au frame
        imageLabel8->setPixmap(pixmap8.scaled(
            ui->frame_8->width() - 10,  // -10 pour la marge
            ui->frame_8->height() - 10,
            Qt::KeepAspectRatio,
            Qt::SmoothTransformation
            ));

        // 4. Centrer l'image dans le label
        imageLabel8->setAlignment(Qt::AlignCenter);

        // 5. Ajuster la taille du label pour remplir le frame
        imageLabel8->setGeometry(0, 0, ui->frame_8->width(), ui->frame_8->height());
    }

    // 6. Styler le deuxième frame (identique au premier)
    ui->frame_8->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );

    ui->label_29->setStyleSheet(
        "QLabel {"
        "   padding: 5px;"
        "   background-color: #8B4513;"
        "   color: white;"
        "   border-radius: 4px;"
        "}"
        "QLabel:hover {"
        "   background-color: #A0522D;"
        "}"
        );


}
bool Menu::eventFilter(QObject *obj, QEvent *event)
{
    if (obj == ui->label_29 && event->type() == QEvent::MouseButtonPress) {
        onLabel29Clicked();
        return true;
    }
    return QDialog::eventFilter(obj, event);
}
void Menu::onLabel29Clicked()
{
    qDebug() << "Label 29 cliqué!";
    // Ajoutez ici le code à exécuter lors du clic
    // Par exemple :
    // QMessageBox::information(this, "Info", "Label 29 a été cliqué!");
}
Menu::~Menu()
{
    if (db.isOpen()) {
        db.close();
    }
    delete ui;
}

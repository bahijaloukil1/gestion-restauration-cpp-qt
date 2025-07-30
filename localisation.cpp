#include "localisation.h"
#include "ui_localisation.h"
#include <QSqlQuery>
#include <QMessageBox>
#include <QLabel>
#include <QDebug>
#include <QPixmap>

localisation::localisation(QWidget *parent)
    : QDialog(parent)
    , ui(new Ui::localisation)
{
    ui->setupUi(this);
     loadImageToFrame(); // Appel au chargement de l'image
    setMinimumSize(500, 100); // Taille minimale recommandée
     setBackgroundImage();  // D'abord le fond

}


void localisation::setBackgroundImage()
{
    // 1. Charger l'image de fond
    QPixmap background(":/background/img28.jpg");

    if(background.isNull()) {
        qDebug() << "Erreur: Impossible de charger l'image de fond";
        return;
    }

    // 2. Redimensionner l'image
    background = background.scaled(this->size(), Qt::KeepAspectRatioByExpanding, Qt::SmoothTransformation);

    // 3. Appliquer comme fond
    QPalette palette;
    palette.setBrush(QPalette::Window, background);
    this->setPalette(palette);

    // 4. Style pour les frames (transparence)
    this->setStyleSheet(
        "QFrame {"
        "   background-color: rgba(255, 255, 255, 200);"  // Blanc semi-transparent
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "}"
        );
}

localisation::~localisation()
{
    delete ui;
}
void  localisation::loadImageToFrame()
{
    // // ============ PREMIER FRAME (frame) ============
    // // 1. Créer un QLabel pour contenir l'image
    // QLabel *imageLabel1 = new QLabel(ui->frame);

    // // 2. Charger la première image depuis les ressources
    // QPixmap pixmap(":/background/img28.jpg");

    // if(pixmap.isNull()) {
    //     qDebug() << "Erreur: Impossible de charger img28.jpg depuis les ressources";
    // } else {
    //     // 3. Redimensionner l'image pour s'adapter au frame
    //     imageLabel1->setPixmap(pixmap.scaled(
    //         ui->frame->width() - 10,  // -10 pour la marge
    //         ui->frame->height() - 10,
    //         Qt::KeepAspectRatio,
    //         Qt::SmoothTransformation
    //         ));

    //     // 4. Centrer l'image dans le label
    //     imageLabel1->setAlignment(Qt::AlignCenter);

    //     // 5. Ajuster la taille du label pour remplir le frame
    //     imageLabel1->setGeometry(0, 0, ui->frame->width(), ui->frame->height());
    // }

    // // 6. Styler le premier frame
    // ui->frame->setStyleSheet(
    //     "QFrame {"
    //     "   border: 2px solid #8B4513;"
    //     "   border-radius: 8px;"
    //     "   background-color: white;"
    //     "}"
        // );



    // ============ PREMIER FRAME (frame) ============
    // 1. Créer un QLabel pour contenir l'image
    QLabel *imageLabel2 = new QLabel(ui->frame_2);

    // 2. Charger la première image depuis les ressources
    QPixmap pixmap2(":/background/img27.jpeg");

    if(pixmap2.isNull()) {
        qDebug() << "Erreur: Impossible de charger img27.jpeg depuis les ressources";
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

    // 6. Styler le premier frame
    ui->frame_2->setStyleSheet(
        "QFrame {"
        "   border: 2px solid #8B4513;"
        "   border-radius: 8px;"
        "   background-color: white;"
        "}"
        );


}



void localisation::resizeEvent(QResizeEvent *event)
{
    QDialog::resizeEvent(event);
    setBackgroundImage();  // Réajuste l'image lors du redimensionnement
}

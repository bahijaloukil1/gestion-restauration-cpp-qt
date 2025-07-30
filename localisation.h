#ifndef LOCALISATION_H
#define LOCALISATION_H

#include <QDialog>

namespace Ui {
class localisation;
}

class localisation : public QDialog
{
    Q_OBJECT

public:
    explicit localisation(QWidget *parent = nullptr);
    ~localisation();
    void loadImageToFrame(); // Déplacé en public si besoin d'appel externe
private:
    Ui::localisation *ui;
    void setBackgroundImage();  // Nouvelle méthode
protected:
    void resizeEvent(QResizeEvent *event) override;
};

#endif // LOCALISATION_H


#ifndef MENU_H
#define MENU_H

#include <QDialog>
#include <QSqlDatabase>
#include <QPixmap>

namespace Ui {
class Menu;
}

class Menu : public QDialog
{
    Q_OBJECT

public:
    explicit Menu(QWidget *parent = nullptr);
    ~Menu();

protected:
    bool eventFilter(QObject *obj, QEvent *event) override;  // Ajoutez cette ligne

private:
    Ui::Menu *ui;
    QSqlDatabase db;
    void loadImageToFrame();

private slots:
    void onLabel29Clicked();  // Déclaration du slot
};

#endif // MENU_H

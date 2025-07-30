#include "connexion.h"
#include "acculier.h"
#include "Menu.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    Connexion w;
    w.show();
    return a.exec();
}

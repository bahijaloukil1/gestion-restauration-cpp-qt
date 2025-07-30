#include "connexion.h"
#include "acullier.h"
#include <QApplication>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    connexion loginDialog;  // <<-- nom de la classe corrigé ici

    if (loginDialog.exec() == QDialog::Accepted) {
        Acullier acceuil;
        acceuil.show();
        return a.exec();
    }

    return 0;
}

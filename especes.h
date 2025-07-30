#ifndef ESPECES_H
#define ESPECES_H

#include <QDialog>
#include <QSqlDatabase>
#include <QSqlQuery> // Ajouté
#include <QSqlError> // Ajouté
#include <QMessageBox> // Ajouté
#include <QLabel>
#include <QLineEdit>
#include <QVBoxLayout>
#include <QHBoxLayout>
#include <QFrame>
#include <QPushButton>
#include <QDebug> // Ajouté

namespace Ui {
class especes;
}

class especes : public QDialog
{
    Q_OBJECT

public:
    explicit especes(int commandeId, QWidget *parent = nullptr); // Modifié
    ~especes();

private slots:
    void validerPaiement();
    void annulerPaiement();
    void onMontantEditChanged(const QString &text); // Ajouté

private:
    Ui::especes *ui;
    QSqlDatabase m_db;
    double montantTotal;
    int m_commandeId; // Ajouté

    // Widgets
    QLabel *montantTotalLabel;
    QLineEdit *montantEdit;
    QLabel *montantRestantLabel;
    QPushButton *btnValider;
    QPushButton *btnAnnuler;

    void setupUI(); // Ajouté
    void applyStyles(); // Ajouté
    bool initDatabase();
    bool verifierCommandeExiste(); // Ajouté
    void calculerMontantTotal();
};

#endif // ESPECES_H

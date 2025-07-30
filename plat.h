#ifndef PLAT_H
#define PLAT_H

#include <QString>
#include <QObject>

class Commande; // Forward declaration au lieu d'inclusion

class Plat : public QObject {
    Q_OBJECT
public:
    Plat(int id, QString nom, double prix, QObject* parent = nullptr);

    int getId() const;
    QString getNom() const;
    double getPrix() const;

private:
    int m_id;
    QString m_nom;
    double m_prix;
};

#endif // PLAT_H

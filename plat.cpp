#include "plat.h"
#include "commande.h" // Maintenant safe car pas d'inclusion circulaire

Plat::Plat(int id, QString nom, double prix, QObject* parent)
    : QObject(parent), m_id(id), m_nom(nom), m_prix(prix) {}

int Plat::getId() const { return m_id; }
QString Plat::getNom() const { return m_nom; }
double Plat::getPrix() const { return m_prix; }

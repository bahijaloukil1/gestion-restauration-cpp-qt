QT += core gui widgets sql printsupport
# Ajoutez cette ligne
QT += widgets
QT += core gui sql charts widgets
TARGET = restaurant
TEMPLATE = app

SOURCES += \
   acculier.cpp \
    cartebancaire.cpp \
    cheque.cpp \
    commande.cpp \
    especes.cpp \
    feedback.cpp \
    historique.cpp \
    lieu.cpp \
    localisation.cpp \
    main.cpp \
    connexion.cpp \
    inscription.cpp \
    menu.cpp \
    paiement.cpp \
    personnel.cpp \
    plat.cpp \
    reservation.cpp \
    ticket.cpp

HEADERS += \
   acculier.h \
    cartebancaire.h \
    cheque.h \
    commande.h \
    connexion.h \
    especes.h \
    feedback.h \
    historique.h \
    inscription.h \
    lieu.h \
    localisation.h \
    menu.h \
    paiement.h \
    personnel.h \
    plat.h \
    reservation.h \
    ticket.h

FORMS += \
    acculier.ui \
    cartebancaire.ui \
    cheque.ui \
    commande.ui \
    connexion.ui \
    especes.ui \
    feedback.ui \
    historique.ui \
    inscription.ui \
    lieu.ui \
    localisation.ui \
    menu.ui \
    paiement.ui \
    personnel.ui \
    plat.ui \
    reservation.ui \
    ticket.ui

RESOURCES += \
    image.qrc

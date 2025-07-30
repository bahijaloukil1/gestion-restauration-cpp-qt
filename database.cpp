#include "database.h"

bool Database::connectDB() {
    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("restaurant.db");

    if (!db.open()) {
      //  qDebug() << "Erreur de connexion à la base de données:" << db.lastError().text();
        return false;
    }
    return true;
}

void Database::initDB() {
    QSqlQuery query;
    query.exec("CREATE TABLE IF NOT EXISTS users ("
               "id INTEGER PRIMARY KEY AUTOINCREMENT,"
               "nom_prenom TEXT NOT NULL,"
               "email TEXT UNIQUE NOT NULL,"
               "password TEXT NOT NULL)");
}

bool Database::userExists(const QString &email) {
    QSqlQuery query;
    query.prepare("SELECT email FROM users WHERE email = :email");
    query.bindValue(":email", email);
    return query.exec() && query.next();
}

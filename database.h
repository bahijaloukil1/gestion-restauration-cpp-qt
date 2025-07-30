#ifndef DATABASE_H
#define DATABASE_H

#include <QSqlDatabase>
#include <QSqlQuery>
#include <QDebug>

class Database {
public:
    static bool connectDB();
    static void initDB();
    static bool userExists(const QString &email);
};

#endif // DATABASE_H

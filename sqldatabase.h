#ifndef SQLDATABASE_H
#define SQLDATABASE_H

#include <QHash>
#include <QMutex>
#include <QFuture>
#include <QSqlQuery>

//#include "qzcommon.h"

class  SqlDatabase : public QObject
{
    Q_OBJECT

public:
    explicit SqlDatabase(QObject* parent = 0);
    ~SqlDatabase();

    // Returns database connection for current thread
    QSqlDatabase database();

    // Sets database to be created for other threads
    void setDatabase(const QSqlDatabase &database);

    static SqlDatabase* instance();

private:
    QString m_databaseName;
    QString m_connectOptions;
};

#endif // SQLDATABASE_H

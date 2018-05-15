#include "sqldatabase.h"

#include <QApplication>
#include <QThreadStorage>

#include <QtConcurrent/QtConcurrentRun>
QThreadStorage<QSqlDatabase> s_databases;
Q_GLOBAL_STATIC(SqlDatabase, qz_sql_database)

SqlDatabase::SqlDatabase(QObject* parent)
    : QObject(parent)
{
}

SqlDatabase::~SqlDatabase()
{
}

QSqlDatabase SqlDatabase::database()
{
    if (QThread::currentThread() == qApp->thread()) {
        return QSqlDatabase::database();
    }

    if (!s_databases.hasLocalData()) {
        const QString threadStr = QString::number((quintptr) QThread::currentThread());
        //QSqlDatabase db = QSqlDatabase::addDatabase(QSL("QSQLITE"), threadStr);
        QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE", threadStr);
        db.setDatabaseName("C:\\database.db3");
        //db.setDatabaseName(m_databaseName);
        //db.setConnectOptions(m_connectOptions);
        db.open();
        s_databases.setLocalData(db);
    }

    //return db;
    return s_databases.localData();
}

void SqlDatabase::setDatabase(const QSqlDatabase &database)
{
    m_databaseName = database.databaseName();
    m_connectOptions = database.connectOptions();
}

// instance
SqlDatabase* SqlDatabase::instance()
{
    return qz_sql_database();
}

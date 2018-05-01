#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>
#include "sqldatabase.h"
#include <QFile>

int main(int argc, char **argv)
{


    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    Browser browser;
    //const QString dbFile = DataPaths::currentProfilePath() + QLatin1String("/browsedata.db");

    // Reconnect
    /*if (m_databaseConnected) {
        QSqlDatabase::removeDatabase(QSqlDatabase::database().connectionName());
    }*/

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\browsedata.db");

    /*if (!QFile::exists(dbFile)) {
        qWarning("Cannot find SQLite database file! Copying and using the defaults!");

        QFile(":data/browsedata.db").copy(dbFile);
        QFile(dbFile).setPermissions(QFile::ReadUser | QFile::WriteUser);
        db.setDatabaseName(dbFile);
    }

    if (mApp->isPrivate()) {
        db.setConnectOptions("QSQLITE_OPEN_READONLY");
    }*/

    if (!db.open()) {
        qWarning("Cannot open SQLite database! Continuing without database....");
    }

    SqlDatabase::instance()->setDatabase(db);

    BrowserWindow *window = browser.createWindow();
    //BrowserWindow *window2 = browser.createWindow();
    //window->currentTab()->setUrl(url);
    return app.exec();
}

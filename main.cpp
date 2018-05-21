#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>
#include "sqldatabase.h"
#include <QFile>
#include <QSettings>
#include <QStandardPaths>
int main(int argc, char **argv)
{

    QCoreApplication::setOrganizationName("StuckInTheCode");
    //QCoreApplication::setOrganizationDomain("https://github.com/StuckInTheCode/KODBYDOT");
    QCoreApplication::setApplicationName("KODBYDOT");
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    ///////////////////////////////////////////////////Load main icon
    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral(":/data/KODBYDOT.png")));
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QSettings::setDefaultFormat(QSettings::IniFormat);
    QCoreApplication::setApplicationVersion("0.0.1");
    Browser browser;

    /////////////////////////////////////////////////Load the database
    const QString directory = QStandardPaths::writableLocation(QStandardPaths::AppLocalDataLocation);
    QDir dir;
    dir.mkpath(directory);                  //makes directory for application, if it doesn't exist
    const QString directoryPath =directory + QLatin1String("/browsedata.db");
    QSqlDatabase db = QSqlDatabase::addDatabase(QLatin1String("QSQLITE"));

    if (!QFile::exists(directoryPath)) {
        qWarning("Cannot find database file! Upload default");
        QFile(":data/browsedata.db").copy(directory);
        QFile(directory).setPermissions(QFile::ReadUser | QFile::WriteUser);
    }
        db.setDatabaseName(directoryPath);
    if (!db.open()) {
        qWarning("Cannot open SQLite database! Continue without database....");
    }
    ///////////////////////////////////////////////
    SqlDatabase::instance()->setDatabase(db);

    BrowserWindow *window = browser.createWindow();
    return app.exec();
}

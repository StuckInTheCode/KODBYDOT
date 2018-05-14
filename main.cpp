#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>
#include "sqldatabase.h"
#include <QFile>
#include <QSettings>
int main(int argc, char **argv)
{

    QCoreApplication::setOrganizationName("StuckInTheCode");
    //QCoreApplication::setOrganizationDomain("https://github.com/StuckInTheCode/KODBYDOT");
    QCoreApplication::setApplicationName("KODBYDOT");

    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);
    app.setWindowIcon(QIcon(QStringLiteral("C:\\KODBYDOT.png")));
    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    QSettings::setDefaultFormat(QSettings::IniFormat);

    Browser browser;
    const QString dbFile = QApplication::applicationDirPath() + QLatin1String("/browsedata.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\browsedata.db");
    //db.setDatabaseName(":/data/browsedata.db");
    if (!db.open()) {
        qWarning("Cannot open SQLite database! Continuing without database....");
    }

    SqlDatabase::instance()->setDatabase(db);


    BrowserWindow *window = browser.createWindow();
    return app.exec();
}

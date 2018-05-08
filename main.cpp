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
    //QSettings s_settings;
    QSettings::setDefaultFormat(QSettings::IniFormat);
    //const QString s = "C:\\Programming\\Qt\\browser\\settings.ini";
    //QFile * f = new QFile(s);
    //s_settings = new QSettings(QApplication::applicationDirPath() + QLatin1String("/settings.ini"), QSettings::IniFormat);
    //s_settings =  new QSettings(s, QSettings::IniFormat);
    //s_settings->sync();
    Browser browser;
    const QString dbFile = QApplication::applicationDirPath() + QLatin1String("/browsedata.db");

    QSqlDatabase db = QSqlDatabase::addDatabase("QSQLITE");
    db.setDatabaseName("C:\\browsedata.db");
    //db.setDatabaseName("C:\\Programming\\Qt\\browser\\build-KODBYDOT-Desktop_Qt_5_10_1_MSVC2015_32bit-Release\\debug\\browsedata.db");
    //const QString dFile = QDir::current().absolutePath()+ QLatin1String("/browsedata.db");
    //db.setDatabaseName(dFile);

    if (!db.open()) {
        qWarning("Cannot open SQLite database! Continuing without database....");
    }

    SqlDatabase::instance()->setDatabase(db);


    BrowserWindow *window = browser.createWindow();
    //BrowserWindow *window2 = browser.createWindow();
    //window->currentTab()->setUrl(url);
    return app.exec();
}

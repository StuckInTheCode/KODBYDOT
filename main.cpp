#include "browser.h"
#include "browserwindow.h"
#include "webview.h"
#include <QApplication>
#include <QWebEngineSettings>


int main(int argc, char **argv)
{
    QCoreApplication::setAttribute(Qt::AA_EnableHighDpiScaling);
    QCoreApplication::setAttribute(Qt::AA_UseHighDpiPixmaps);

    QApplication app(argc, argv);

    QWebEngineSettings::defaultSettings()->setAttribute(QWebEngineSettings::PluginsEnabled, true);
    app.exec();
    app.exit();
    Browser browser;
    return 0;
}

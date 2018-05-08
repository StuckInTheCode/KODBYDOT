#include "browser.h"
#include "browserwindow.h"
#include <QWebEngineProfile>
#include <QSettings>
#include "history.h"

Browser::Browser():
     m_history(new History(0))
    ,profile(QWebEngineProfile::defaultProfile())
    ,m_urlInterceptor(new NetworkUrlInterceptor())
   , m_homePage(new QUrl())
{
    QSettings settings;
    settings.beginGroup("Home-Page");
    m_homePage = new QUrl(settings.value("url", QString()).toString());
    settings.endGroup();
    profile->setRequestInterceptor(m_urlInterceptor);
    QObject::connect(
        profile, &QWebEngineProfile::downloadRequested,
        &m_downloadManagerWidget, &DownloadManagerWidget::downloadRequested);

    // QObject::connect(this,&QWebEngineCertificateError::Error,certificateError(const QWebEngineCertificateError &error)
}

BrowserWindow *Browser::createWindow()
{
   // m_urlInterceptor = new NetworkUrlInterceptor();

    auto mainWindow = new BrowserWindow(this, profile);
    //QSettings::setDefaultFormat(QSettings::IniFormat);

    mWindows.push_back(mainWindow);
    //mainWindow->resize();
    mWindows.append(mainWindow);
    mainWindow->show();
    return mainWindow;
}
void Browser::setHomePage(QUrl *url)
{
    m_homePage = url;
}
QUrl* Browser::getHomePage()
{
    return m_homePage;
}
Browser::~Browser()
{
    //QSettings settings;
    //settings.beginGroup("Home-Page");
    //settings.setValue(QLatin1String("url"), m_homePage->toDisplayString());
    //settings.endGroup();

}

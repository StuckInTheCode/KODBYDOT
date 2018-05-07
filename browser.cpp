#include "browser.h"
#include "browserwindow.h"
#include <QWebEngineProfile>
#include "history.h"

Browser::Browser():
     m_history(new History(0))
    ,profile(QWebEngineProfile::defaultProfile())
    ,m_urlInterceptor(new NetworkUrlInterceptor())
{
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

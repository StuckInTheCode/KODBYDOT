#include "browser.h"
#include "browserwindow.h"
#include <QWebEngineProfile>
Browser::Browser():
     m_history(0)
{
    QObject::connect(
        QWebEngineProfile::defaultProfile(), &QWebEngineProfile::downloadRequested,
        &m_downloadManagerWidget, &DownloadManagerWidget::downloadRequested);
}

BrowserWindow *Browser::createWindow()
{   auto mainWindow = new BrowserWindow(this, QWebEngineProfile::defaultProfile());
    mWindows.push_back(mainWindow);
    //mainWindow->resize();
    mWindows.append(mainWindow);
    mainWindow->show();
    return mainWindow;
}

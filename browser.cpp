#include "browser.h"
#include "browserwindow.h"
#include <QWebEngineProfile>

Browser::Browser()
{
}

BrowserWindow *Browser::createWindow()
{   auto mainWindow = new BrowserWindow(this, QWebEngineProfile::defaultProfile());
    mWindows.push_back(mainWindow);
    //mainWindow->resize();
    mWindows.append(mainWindow);
    mainWindow->show();
    return mainWindow;
}

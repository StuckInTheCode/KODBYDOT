#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>
#include <QLinkedList>
#include <QPushButton>
#include <QLineEdit>
class WebPage;
class WebView;
class Browser;
class TabWidget;
class CookieJar;
class CookieManager;
class History;
class ToolbarSearch;
class QAction;
QT_END_NAMESPACE
class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(Browser *browser, QWebEngineProfile *profile);
    TabWidget *tabWidget() const;
    WebView *currentTab() const;
    Browser *browser(){ return m_browser; }
    History *history() const;
    QWebEngineProfile *profile() { return m_profile;}
private:
    QMenu *createFileMenu(TabWidget *tabWidget);
    QMenu *createViewMenu();
    QMenu *createOptionsMenu();
public slots:
    void load();
    void loadURL(QUrl url);
    void addToBookmarks();
    void urlChanged(const QUrl &url);
    void titleChanged(const QString &title);
private:
    Browser *m_browser;
    CookieJar *m_cookiejar;
    CookieManager * m_cookiemanager;
    QWebEngineProfile *m_profile;
    ToolbarSearch * m_search;
    TabWidget *m_tabWidget;
    QPushButton *m_button;
    QPushButton *m_bookmark;
    QLineEdit *m_urlLineEdit;
};

#endif // BROWSERWINDOW_H

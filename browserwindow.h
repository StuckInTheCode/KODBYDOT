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
    QMenu *createEditMenu();
    QMenu *createViewMenu(); //QToolBar *toolBar
    QMenu *createWindowMenu(TabWidget *tabWidget);
    QMenu *createOptionsMenu();
    QMenu *createHelpMenu();
    QToolBar *createToolBar();
//public signals:

public slots:
    void load();
    void loadURL(QUrl url);
    void addToBookmarks();
    void urlChanged(const QUrl &url);
private:
    QAction *m_stopAction;
    QAction *m_reloadAction;
    Browser *m_browser;
    CookieJar *m_cookiejar;
    CookieManager * m_cookiemanager;
    //QLineEdit *m_urlLineEdit;
    QWebEngineProfile *m_profile;
    //QLinkedList<WebPage*> m_pages;
    //Ui::window *ui;
    ToolbarSearch * m_search;
    TabWidget *m_tabWidget;
    QPushButton *m_button;
    QPushButton *m_bookmark;
    QLineEdit *m_urlLineEdit;
};

#endif // BROWSERWINDOW_H

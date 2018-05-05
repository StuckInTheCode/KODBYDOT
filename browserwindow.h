#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>
#include <QLinkedList>
#include <QPushButton>
#include <QLineEdit>
class WebPage;
class Browser;
class TabWidget;
class CookieJar;
class CookieManager;
class History;
class ToolbarSearch;
QT_END_NAMESPACE
class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(Browser *browser, QWebEngineProfile *profile);
    //WebView *currentTab() const;
    Browser *browser() { return m_browser; }
    History *history();
    QWebEngineProfile *profile() { return m_profile;}
private:
    QMenu *createFileMenu(TabWidget *tabWidget);
    QMenu *createEditMenu();
    QMenu *createViewMenu(QToolBar *toolBar);
    QMenu *createWindowMenu(TabWidget *tabWidget);
    QMenu *createHelpMenu();
    QToolBar *createToolBar();
//public signals:

public slots:
    void load();
    void loadURL(QUrl url);
    void on_pushButton_clicked();
    void urlChanged(const QUrl &url);
private:
    Browser *m_browser;
    CookieJar *m_cookiejar;
    CookieManager * m_cookiemanager;
    //QLineEdit *m_urlLineEdit;
    QWebEngineProfile *m_profile;
    QLinkedList<WebPage*> m_pages;
    //Ui::window *ui;
    ToolbarSearch * m_search;
    TabWidget *m_tabWidget;
    QPushButton *m_button;
    QLineEdit *m_urlLineEdit;
};

#endif // BROWSERWINDOW_H

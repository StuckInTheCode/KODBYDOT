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
QT_END_NAMESPACE
class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(Browser *browser, QWebEngineProfile *profile);
    //WebView *currentTab() const;
    Browser *browser() { return m_browser; }
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
    void on_pushButton_clicked();
private:
    CookieJar *m_cookiejar;
    CookieManager * m_cookiemanager;
    Browser *m_browser;
    //QLineEdit *m_urlLineEdit;
    QWebEngineProfile *m_profile;
    QLinkedList<WebPage*> m_pages;
    //Ui::window *ui;
    TabWidget *m_tabWidget;
    QPushButton *m_button;
    QLineEdit *m_urlLineEdit;
};

#endif // BROWSERWINDOW_H

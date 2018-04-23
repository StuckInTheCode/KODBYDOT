#ifndef BROWSERWINDOW_H
#define BROWSERWINDOW_H

#include <QMainWindow>
#include <QWebEnginePage>
#include <QLinkedList>
class WebPage;
class Browser;
class TabWidget;

QT_END_NAMESPACE
class BrowserWindow : public QMainWindow
{
    Q_OBJECT

public:
    BrowserWindow(Browser *browser, QWebEngineProfile *profile);
    //WebView *currentTab() const;
    Browser *browser() { return m_browser; }
private:
    QMenu *createFileMenu(TabWidget *tabWidget);
    QMenu *createEditMenu();
    QMenu *createViewMenu(QToolBar *toolBar);
    QMenu *createWindowMenu(TabWidget *tabWidget);
    QMenu *createHelpMenu();
    QToolBar *createToolBar();
//public signals:

private slots:
    void on_pushButton_clicked();
private:
    Browser *m_browser;
    //QLineEdit *m_urlLineEdit;

    QWebEngineProfile *m_profile;
    QLinkedList<WebPage*> m_pages;
    //Ui::window *ui;
    TabWidget *m_tabWidget;
};

#endif // BROWSERWINDOW_H

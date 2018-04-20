#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QWebEnginePage>
#include <QLineEdit>
#include <QTabBar>
#include "webview.h"

class QUrl;
//class QTabBar;
class WebView;

class TabWidget : public QTabWidget
{
    Q_OBJECT

public:
    TabWidget(QWebEngineProfile *profile, QWidget *parent = nullptr): QTabWidget(parent), m_profile(profile)
    {
            setAttribute(Qt::WA_DeleteOnClose, true);
            QTabBar *tabBar = this->tabBar();
            tabBar->setTabsClosable(true);
            tabBar->setSelectionBehaviorOnRemove(QTabBar::SelectPreviousTab);
            tabBar->setMovable(true);
            tabBar->setContextMenuPolicy(Qt::CustomContextMenu);
            //connect(tabBar, &QTabBar::customContextMenuRequested, this, &TabWidget::handleContextMenuRequested);
            connect(tabBar, &QTabBar::tabCloseRequested, this, &TabWidget::closeTab);
            connect(tabBar, &QTabBar::tabBarDoubleClicked, [this](int index) {
                if (index == -1)
                    createTab();
            });

            setDocumentMode(true);
            setElideMode(Qt::ElideRight);

            //connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);
    }

    WebView* createTab()
    {
        WebView *webView = createBackgroundTab();
        setCurrentWidget(webView);
        return webView;
    }
    WebView* createBackgroundTab()
    {
        WebView *webView = new WebView(nullptr);
        //WebPage *webPage = new WebPage(m_profile, webView);
        //webView->setPage(webPage);
        setupView(webView);
        //int index = addTab(webView, tr("(Untitled)"));
        //setTabIcon(index, webView->favIcon());
        //Workaround for QTBUG-61770
        //webView->resize(currentWidget()->size()); //вызывает исключение
        webView->show();
        return webView;
    }

signals:

public slots:
    void closeTab(int index)
    {
        if (WebView *view = webView(index)) {
               //bool hasFocus = view->hasFocus();
               removeTab(index);
               //if (hasFocus && count() > 0)
               //    currentWebView()->setFocus();
               if (count() == 0)
                   createTab();
               view->deleteLater();
           }

    }
    /*WebView *currentWebView() const;
    void setUrl(const QUrl &url);
    WebView *createTab();
    WebView *createBackgroundTab();

    void nextTab();
    void previousTab();
    void cloneTab(int index);
    void closeOtherTabs(int index);
    void reloadAllTabs();
    void reloadTab(int index);*/


private:

    QUrl *m_url;
    QLineEdit *UrlPath;
    WebView *webView(int index) const
    {
        return qobject_cast<WebView*>(widget(index));
    }
    void setupView(WebView *webView)
    {    QWebEnginePage *webPage = webView->page();}
    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H

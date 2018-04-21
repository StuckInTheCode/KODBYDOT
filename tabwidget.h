#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QWebEnginePage>
#include <QLineEdit>
#include <QTabBar>
#include "ui_window.h"
#include "webview.h"

class QUrl;
//class QTabBar;
QT_BEGIN_NAMESPACE
namespace Ui {
class window;
}
class WebView;

class TabWidget : public QTabWidget, public Ui::window
{
    Q_OBJECT

public:
    TabWidget(QWebEngineProfile *profile, QWidget *parent = nullptr): QTabWidget(parent), m_profile(profile)//,ui(new Ui::window)
    {
        setupUi(this);
        preview->load(QUrl("http://harrix.org/"));

        //ui->tab();
        setAttribute(Qt::WA_DeleteOnClose, true);
        QTabBar *tabBar = this->tabBar();
        tabBar->resize(125,20);
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
            connect(GO,&QPushButton::clicked, this, &TabWidget::load);
            connect(pushButton, &QPushButton::clicked, this, &TabWidget::createTab);
            setDocumentMode(true);
            setElideMode(Qt::ElideRight);
            createTab();
            //connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged); !важно
    }

    void load()
    {
       this->preview->load(QUrl(this->lineEdit->text()));
    }

    WebView* createTab()
    {
        WebView *webView = createBackgroundTab();
        setCurrentWidget(webView);
        return webView;
    }
    WebView* createBackgroundTab()
    {
        WebView *webView2 = new WebView(nullptr);
        QWebEngineView * webView= new QWebEngineView(nullptr);
        //this->preview->
        //WebPage *webPage = new WebPage(m_profile, webView);
        //webView->setPage(webPage);
        //setupView(webView);
        //ui->tabWidget->addTab(webView, tr("(Untitled)"));
        int index = addTab(webView, tr("(Untitled)"));
        this->preview=webView;
        //preview=webView;
        //setTabIcon(index, webView->favIcon());
        //Workaround for QTBUG-61770
        webView->resize(currentWidget()->size()); //вызывает исключение
        webView->show();
        return webView2;
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
    //WebView *currentWebView() const;
    void setUrl(const QUrl &url){}
    //WebView *createTab();
    //WebView *createBackgroundTab();

    void nextTab(){}
    void previousTab(){}
    void cloneTab(int index){}
    void closeOtherTabs(int index){}
    void reloadAllTabs(){}
    void reloadTab(int index){}


private:
    //Ui::window *ui;
    //QUrl *m_url;
    //QLineEdit *UrlPath;
    WebView *webView(int index) const
    {
        return qobject_cast<WebView*>(QTabWidget::widget(index));
    }
    void setupView(WebView *webView)
    {    QWebEnginePage *webPage = webView->page();}
    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H

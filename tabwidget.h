#ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QWebEnginePage>
#include <QLineEdit>
#include <QTabBar>
#include "ui_window.h"
#include "webview.h"

class QUrl;

QT_BEGIN_NAMESPACE
namespace Ui {
class window;
}
class WebView;
/*Need to use the QWebEnginePage class instead the WebPage class*/

class TabWidget : public QTabWidget//, public Ui::window
{
    Q_OBJECT

public:
    TabWidget(QWebEngineProfile *profile, QWidget *parent = nullptr): QTabWidget(parent), m_profile(profile),ui(new Ui::window)
    {
        //QWidget *m_window = new QWidget(nullptr);
        ui->setupUi(this);
        //this->setCurrentWidget(m_window);
        //preview->load(QUrl("http://harrix.org/"));
        //ui->tab();
        setAttribute(Qt::WA_DeleteOnClose, true);
        QTabBar *tabBar = this->tabBar();
        //tabBar->resize(125,20);
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
            connect(ui->GO,&QPushButton::clicked, this, &TabWidget::load);
            //QPushButton * newtab = ui->pushButton;
            connect(this->ui->pushButton, &QPushButton::clicked, this, &TabWidget::createTab);
            setDocumentMode(true);
            setElideMode(Qt::ElideRight);
            createTab();
           // connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);// !важно
    }

    void handleCurrentChanged()
    {

        //int index = this->currentIndex();
        //if(index<count())
        //setCurrentIndex(index+1);
        //this->preview->setPage(webView(index)->page());
        //this->preview->se
        //setCurrentWidget(webView(index));
        //setupView(webView(index));
        //this->preview = webView(index);
    }
    void load()
    {
        QWebEngineView *view = webView(currentIndex());
        view->load(QUrl(ui->lineEdit->text()));
       //QWebEngineView * webView = this->currentWidget()->children();
       // webView->load(QUrl(ui->lineEdit->text()));
       //this->preview->close();
       //ui->preview->load(QUrl(ui->lineEdit->text()));
    }

    QWebEngineView* createTab()
    {
        QWebEngineView *webView = createBackgroundTab();
        setCurrentWidget(webView);
        return webView;
    }
    QWebEngineView* createBackgroundTab()
    {
        //WebView *webView2 = new WebView(nullptr);
        QWebEngineView * webView= new QWebEngineView(nullptr);

        //this->preview->
        //WebPage *webPage = new WebPage(m_profile, webView);
        //webView->setPage(webPage);
        setupView(webView);
        //ui->tabWidget->addTab(webView, tr("(Untitled)"));
        int index = addTab(webView, tr("(Untitled)"));
        //preview=webView;
        //setTabIcon(index, webView->favIcon());
        //Workaround for QTBUG-61770
        //webView->resize(currentWidget()->size()); //вызывает исключение
        webView->show();
        webView->load(QUrl("http://harrix.org/"));
        //webView->load(QUrl(ui->lineEdit->text()));
        return webView;
    }

signals:

public slots:
    void closeTab(int index)
    {
        if (QWebEngineView *view = webView(index)) {
               //bool hasFocus = view->hasFocus();
               removeTab(index);
               //if (hasFocus && count() > 0)
               //    currentWebView()->setFocus();
               if (count() == 0)
                   createTab();
               view->deleteLater();
           }

    }
    QWebEngineView *currentWebView() const
    {
        return webView(currentIndex());
    }
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
    Ui::window *ui;
    //QUrl *m_url;
    //QLineEdit *UrlPath;
    QWebEngineView *webView(int index) const
    {
        return qobject_cast<QWebEngineView*>(QTabWidget::widget(index));
    }
    void setupView(QWebEngineView *webView)
    {
       // QWebEnginePage *webPage = webView->page();

        //ui->preview->setPage(webPage);
    }
    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H

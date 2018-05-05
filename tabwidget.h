 #ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QHBoxLayout>
#include <QWebEnginePage>
#include <QToolButton>
#include <QLineEdit>
#include <QTabBar>
#include "tabbar.h"
#include "ui_window.h"
#include "webview.h"
#include "webpage.h"
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
        //ui->setupUi(this);
        //this->setCurrentWidget(m_window);
        //preview->load(QUrl("http://harrix.org/"));
        //ui->tab();
        setAttribute(Qt::WA_DeleteOnClose, true);


        QTabBar *tabBar = this->tabBar();
        //this->setSizeIncrement(1,5);
        //this->show();

        //TabBar * tabBar = new TabBar(this->tabBar());
        //this->setTabBar(tabBar);
        //this->setTabBar();
        //tabBar->resize(125,20);
        QToolButton * button = new QToolButton(this);
        button->setText("+");
        //this->setTabOrder();
        this->setCornerWidget(button);
        //QHBoxLayout * lay= new QHBoxLayout();
        //tabBar->setLayout(lay);
        //lay->addWidget(button);
        //tabBar->setTabButton(0,QTabBar::ButtonPosition::LeftSide ,button);
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

            connect(this, &QTabWidget::currentChanged, this, &TabWidget::handleCurrentChanged);
            //connect(ui->GO,&QPushButton::clicked, this, &TabWidget::load);
            //QPushButton * newtab = ui->pushButton;

            setDocumentMode(true);
            setElideMode(Qt::ElideRight);
            //tabBar->set
            createTab();
           // connect(this, &QTabWidget::currentChanged, this, &TabWidget::currentChanged);// !важно
    }

    void TabWidget::handleCurrentChanged(int index)
    {
        if (index != -1) {
            QWebEngineView *view = webView(index);
            if (!view->url().isEmpty())
                view->setFocus();
            emit titleChanged(view->title());
            //emit loadProgress(view->loadProgress());
            emit urlChanged(view->url());
            //emit IconChanged(view->favIcon());
            /*emit webActionEnabledChanged(QWebEnginePage::Back, view->isWebActionEnabled(QWebEnginePage::Back));
            emit webActionEnabledChanged(QWebEnginePage::Forward, view->isWebActionEnabled(QWebEnginePage::Forward));
            emit webActionEnabledChanged(QWebEnginePage::Stop, view->isWebActionEnabled(QWebEnginePage::Stop));
            emit webActionEnabledChanged(QWebEnginePage::Reload,view->isWebActionEnabled(QWebEnginePage::Reload));
        */} else {
            emit titleChanged(QString());
            //emit loadProgress(0);
            emit urlChanged(QUrl());
            //emit IconChanged(QIcon());
            /*emit webActionEnabledChanged(QWebEnginePage::Back, false);
            emit webActionEnabledChanged(QWebEnginePage::Forward, false);
            emit webActionEnabledChanged(QWebEnginePage::Stop, false);
            emit webActionEnabledChanged(QWebEnginePage::Reload, true);
        */}
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
    bool loadURL(QUrl url)
    {
        QWebEngineView *view = webView(currentIndex());
        //view->load(url);
        view->setUrl(url);
        //bool correctRequest = 1?view->page()->
        /*if(!correctRequest)
        {
            return true;
        }*/
        return false;
    }

    QWebEngineView* createTab()
    {
        QWebEngineView *webView = createBackgroundTab();
        connect(webView, &QWebEngineView::titleChanged, [this, webView](const QString &title) {
            int index = indexOf(webView);
            if (index != -1) {
                setTabText(index, title);
                setTabToolTip(index, title);
            }
            if (currentIndex() == index)
                emit titleChanged(title);
        });
        connect(webView, &QWebEngineView::urlChanged, [this, webView](const QUrl &url) {
            int index = indexOf(webView);
            if (index != -1)
                tabBar()->setTabData(index, url);
            if (currentIndex() == index)
                emit urlChanged(url);
        });
        /*connect(webView, &WebView::favIconChanged, [this, webView](const QIcon &icon) {
            int index = indexOf(webView);
            if (index != -1)
                setTabIcon(index, icon);
            if (currentIndex() == index)
                emit favIconChanged(icon);
        });
        connect(this, &QWebEngineView::iconChanged, [this](const QIcon &) {
            emit favIconChanged(favIcon());
        });*/
        connect(webView, &QWebEngineView::iconChanged, [this, webView](const QIcon &icon) {
                    int index = indexOf(webView);
                    //if (index != -1)
                        setTabIcon(index, icon);
                    //if (currentIndex() == index)
                    //    emit favIconChanged(icon);
                });
        setCurrentWidget(webView);
        return webView;
    }
    QWebEngineView* createBackgroundTab()
    {
        //WebView *webView2 = new WebView(nullptr);
        QWebEngineView * webView= new QWebEngineView(nullptr);

        //this->preview->
        WebPage *webPage = new WebPage(m_profile, webView);
        webView->setPage(webPage);
        //setupView(webView);
        //ui->tabWidget->addTab(webView, tr("(Untitled)"));

        int index = addTab(webView, tr("    "));

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
void titleChanged(const QString &title);
void urlChanged(const QUrl &url);
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
    /*void setupView(QWebEngineView *webView)
    {
       // QWebEnginePage *webPage = webView->page();

        //ui->preview->setPage(webPage);
    }*/
    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H

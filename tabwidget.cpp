#include "tabwidget.h"

TabWidget::TabWidget(QWebEngineProfile *profile, QWidget *parent, QUrl * homePage): QTabWidget(parent), m_profile(profile),ui(new Ui::window),m_homePage(homePage)
{
    setAttribute(Qt::WA_DeleteOnClose, true);

    QTabBar *tabBar = this->tabBar();

    QToolButton * button = new QToolButton(this);
    button->setText("+");
    this->setCornerWidget(button);
    connect(button,&QToolButton::clicked,this,&TabWidget::createTab);
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

        setDocumentMode(true);
        setElideMode(Qt::ElideRight);
        createTab();
}

void TabWidget::handleCurrentChanged(int index)
{
    if (index != -1) {
        WebView *view = webView(index);
        if (!view->url().isEmpty())
            view->setFocus();
        emit titleChanged(view->title());
        //emit loadProgress(view->loadProgress(0));
        emit urlChanged(view->url());
        //emit IconChanged(view->favIcon());
        /*emit webActionEnabledChanged(QWebEnginePage::Back, view->isWebActionEnabled(QWebEnginePage::Back));
        emit webActionEnabledChanged(QWebEnginePage::Forward, view->isWebActionEnabled(QWebEnginePage::Forward));
        emit webActionEnabledChanged(QWebEnginePage::Stop, view->isWebActionEnabled(QWebEnginePage::Stop));
        emit webActionEnabledChanged(QWebEnginePage::Reload,view->isWebActionEnabled(QWebEnginePage::Reload));
    */} else {
        emit titleChanged(QString());
        emit loadProgress(0);
        emit urlChanged(QUrl());
        //emit IconChanged(QIcon());
        /*emit webActionEnabledChanged(QWebEnginePage::Back, false);
        emit webActionEnabledChanged(QWebEnginePage::Forward, false);
        emit webActionEnabledChanged(QWebEnginePage::Stop, false);
        emit webActionEnabledChanged(QWebEnginePage::Reload, true);
    */}
}

void TabWidget::load()
{
    WebView *view = webView(currentIndex());
    view->load(QUrl(ui->lineEdit->text()));
}
bool TabWidget::loadURL(QUrl url)
{
    WebView *view = webView(currentIndex());
    view->setUrl(url);
    return false;
}

WebView* TabWidget::createTab()
{
    WebView * webView = createBackgroundTab();
    if(webView)
    setCurrentWidget(webView);
    return webView;
}
WebView* TabWidget::createIncognitoTab()
{
    if(this->count()>31)
    {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                             tr("Please close any tab before create new"), QMessageBox::Ok);
            return nullptr;
    }
    WebView *webView = new WebView(nullptr);
    WebPage *webPage = new WebPage(m_profile, webView);
    webView->setPage(webPage);
    connect(webPage, &QWebEnginePage::linkHovered, [this, webView](const QString &url) {
        if (currentIndex() == indexOf(webView))
            emit linkHovered(url);
    });
    connect(webView, &QWebEngineView::urlChanged, [this, webView](const QUrl &url) {
        int index = indexOf(webView);
        if (index != -1)
            tabBar()->setTabData(index, url);
        if (currentIndex() == index)
            emit urlChanged(url);
    });
    connect(webView, &QWebEngineView::loadProgress, [this, webView](int progress) {
        if (currentIndex() == indexOf(webView))
            emit loadProgress(progress);
    });
    int index = addTab(webView, tr("    "));

    webView->show();
    webView->load(*m_homePage);
    webView->isIncognito=true;
    setCurrentWidget(webView);
    setTabText(index,"Incognito");
    setTabWhatsThis(index,"Incognito tab");
    return webView;
}

WebView* TabWidget::createBackgroundTab()
{
    if(this->count()>31)
    {
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                             tr("Please close any tab before create new"), QMessageBox::Ok);
            return nullptr;
    }
    WebView *webView = new WebView(nullptr);
    WebPage *webPage = new WebPage(m_profile, webView);
    webView->setPage(webPage);
    connect(webPage, &QWebEnginePage::linkHovered, [this, webView](const QString &url) {
        if (currentIndex() == indexOf(webView))
            emit linkHovered(url);
    });
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
    connect(webView, &QWebEngineView::loadProgress, [this, webView](int progress) {
        if (currentIndex() == indexOf(webView))
            emit loadProgress(progress);
    });

    connect(webView, &QWebEngineView::iconChanged, [this, webView](const QIcon &icon) {
                int index = indexOf(webView);
                    setTabIcon(index, icon);
            });


    int index = addTab(webView, tr("    "));
    setTabIcon(index, webView->icon());
    webView->resize(currentWidget()->size());
    webView->show();
    webView->load(*m_homePage);
    return webView;
}

void TabWidget::closeTab(int index)
{
    if (WebView *view = webView(index)) {
           bool hasFocus = view->hasFocus();
           removeTab(index);
           if (hasFocus && count() > 0)
            currentWebView()->setFocus();
           if (count() == 0)
               createTab();
           view->deleteLater();
       }

}
WebView *TabWidget::currentWebView() const
{
    return webView(currentIndex());
}
WebView *TabWidget::webView(int index) const
{
     return qobject_cast<WebView*>(QTabWidget::widget(index));
}

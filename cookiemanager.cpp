#include "cookiemanager.h"
#include "cookiejar.h"
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>

CookieManager::CookieManager(QWidget *parent):
    QWidget(parent)
   ,m_layout(new QVBoxLayout(this))
{
    setupUi(this);
/*
    m_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);

    mainWidget->setLayout(m_layout);
    //m_scrollArea->setLayout(m_layout);
    m_scrollArea->setWidget(mainWidget);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);*/

    m_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);
    //m_layout->update();
    QWidget *w = new QWidget();
    //QPalette p = w->palette();
    //p.setColor(widget->backgroundRole(), Qt::white);
    //w->setPalette(p);
    w->setVisible(true);
    w->setLayout(m_layout);
    //w->show();
    //scrollAreaWidgetContents->setLayout(m_layout);
    m_scrollArea->setWidget(w);
    m_scrollArea->setWidgetResizable(true);
    //m_scrollArea->setLayout(m_layout);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);

    //connect(m_deleteAllButton, &QPushButton::clicked, this, &MainWindow::handleDeleteAllClicked);
    //connect(m_newButton, &QPushButton::clicked, this, &MainWindow::handleNewClicked);

    //m_store = m_webview->page()->profile()->cookieStore();
    //m_store->loadAllCookies();
}
void CookieManager::LoadCookies(CookieJar * jar)
{
    //CookieWidget *widget;
    //widget = new CookieWidget(jar->getAllCookies()[0]);

    //widget->setHighlighted(m_cookies.count() % 2);
    //m_cookies.append(cookie);
    //m_layout->addWidget(widget);
    //m_layout->insertWidget(0,widget);
    int colvo = jar->getAllCookies().count();
    int i = 0;
    while(i<colvo)
    {
        QNetworkCookie cookie = jar->getAllCookies()[i];
        //CookieDialog dialog(cookie);
        //dialog.exec();
        CookieWidget *widget = new CookieWidget(cookie,this);
        //widget->setFixedHeight(100);
        //widget->setVisible(true);
        //widget->show();
        //widget->setHighlighted(m_cookies.count() % 2);
        //m_cookies.append(cookie);
        m_layout->insertWidget(0,widget);

        connect(widget, &CookieWidget::viewClicked, [cookie]() {
            CookieDialog dialog(cookie);
            dialog.exec();
        });
        connect(widget, &CookieWidget::deleteClicked, [this]() {
            m_layout->removeWidget(this);
        });
        i++;
    }
    //if (containsCookie(cookie))
    //    return;



   /* connect(widget, &CookieWidget::deleteClicked, [this, cookie, widget]() {
        m_store->deleteCookie(cookie);
        delete widget;
        m_cookies.removeOne(cookie);
        for (int i = 0; i < m_layout->count() - 1; i++) {
            // fix background colors
            auto widget = qobject_cast<CookieWidget*>(m_layout->itemAt(i)->widget());
            widget->setHighlighted(i % 2);
        }
    });*/

}

void CookieManager::addCookie(const QNetworkCookie &cookie)
{
    /*CookieWidget *widget = new CookieWidget(cookie,this);
    //m_scrollArea->setWidget(widget);
    //m_scrollArea->widget()->layout()->addWidget(widget);
    //m_layout->addWidget(widget);
   // m_scrollArea->setWidget(widget);
    //m_scrollArea->layout()->addWidget(widget);
    //m_scrollArea->setLayout(m_layout);
    m_layout->insertWidget(0,widget);

    //CookieDialog dialog(cookie);
    //dialog.exec();

    connect(widget, &CookieWidget::viewClicked, [cookie]() {
        CookieDialog dialog(cookie);
        dialog.exec();
    });
    */
    //if (containsCookie(cookie))
    //    return;

    CookieWidget *widget = new CookieWidget(cookie,this);
    widget->setFocus();
    //widget->setVisible(true);
    //widget->setHighlighted(m_cookies.count() % 2);
    //m_cookies.append(cookie);
    //m_scrollArea->setWidget(widget);
    m_layout->insertWidget(0,widget);
    /*connect(widget, &CookieWidget::deleteClicked, [this, cookie, widget]() {
        m_store->deleteCookie(cookie);
        delete widget;
        m_cookies.removeOne(cookie);
        for (int i = 0; i < m_layout->count() - 1; i++) {
            // fix background colors
            auto widget = qobject_cast<CookieWidget*>(m_layout->itemAt(i)->widget());
            widget->setHighlighted(i % 2);
        }
    });*/

    connect(widget, &CookieWidget::viewClicked, [cookie]() {
        CookieDialog dialog(cookie);
        dialog.exec();
    });
    connect(widget, &CookieWidget::deleteClicked, [this]() {
        m_layout->removeWidget(this);
    });
}
/*CookieManager *CookieManager::createWindow()
{   auto mainWindow = new CookieManager(this, QWebEngineProfile::defaultProfile());
    mWindows.push_back(mainWindow);
    //mainWindow->resize();
    mWindows.append(mainWindow);
    mainWindow->show();
    return mainWindow;
}*/

CookieDialog::CookieDialog(const QNetworkCookie &cookie, QWidget *parent): QDialog(parent)
{
    setupUi(this);
    m_nameLineEdit->setText(cookie.name());
    m_domainLineEdit->setText(cookie.domain());
    m_valueLineEdit->setText(cookie.value());
    m_pathLineEdit->setText(cookie.path());
    m_dateEdit->setDate(cookie.expirationDate().date());
    m_isSecureComboBox->addItem(cookie.isSecure() ? tr("yes") : tr("no"));
    m_isHttpOnlyComboBox->addItem(cookie.isHttpOnly() ? tr("yes") : tr("no"));
    m_addButton_4->setVisible(false);
    m_cancelButton_4->setText(tr("Close"));
}

CookieDialog::CookieDialog(QWidget *parent): QDialog(parent)
{
    setupUi(this);
    m_nameLineEdit->setReadOnly(false);
    m_domainLineEdit->setReadOnly(false);
    m_valueLineEdit->setReadOnly(false);
    m_pathLineEdit->setReadOnly(false);
    m_dateEdit->setReadOnly(false);
    m_dateEdit->setDate(QDateTime::currentDateTime().addYears(1).date());
    m_isSecureComboBox->addItem(tr("no"));
    m_isSecureComboBox->addItem(tr("yes"));
    m_isHttpOnlyComboBox->addItem(tr("no"));
    m_isHttpOnlyComboBox->addItem(tr("yes"));
}

QNetworkCookie CookieDialog::cookie()
{
    QNetworkCookie cookie;
    cookie.setDomain(m_domainLineEdit->text());
    cookie.setName(m_nameLineEdit->text().toLatin1());
    cookie.setValue(m_valueLineEdit->text().toLatin1());
    cookie.setExpirationDate(QDateTime(m_dateEdit->date()));
    cookie.setPath(m_pathLineEdit->text());
    cookie.setSecure(m_isSecureComboBox->currentText() == tr("yes"));
    cookie.setHttpOnly(m_isHttpOnlyComboBox->currentText() == tr("yes"));
    return cookie;
}

CookieWidget::CookieWidget(const QNetworkCookie &cookie, QWidget *parent): QWidget(parent)
{
    setupUi(this);
    //setAutoFillBackground(true);
    m_nameLabel->setText(cookie.name());
    m_domainLabel->setText(cookie.domain());
    connect(m_viewButton, &QPushButton::clicked, this, &CookieWidget::viewClicked);
    connect(m_deleteButton, &QPushButton::clicked, this, &CookieWidget::deleteClicked);
}

void CookieWidget::setHighlighted(bool enabled)
{
    QPalette p = palette();
    p.setColor(backgroundRole(), enabled ? QColor(0xF0, 0xF8, 0xFF) : Qt::white);
    setPalette(p);
}


#include "cookiemanager.h"
#include "cookiejar.h"
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>
#include <QMessageBox>

CookieManager::CookieManager(QWidget *parent):
    QWidget(parent)
   ,m_layout(new QVBoxLayout(this))
{
    setupUi(this);
    m_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);

    QWidget *w = new QWidget();
    w->setVisible(true);
    w->setLayout(m_layout);
    m_scrollArea->setWidget(w);
    m_scrollArea->setWidgetResizable(true);
    m_scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    m_scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
}
void CookieManager::LoadCookies(CookieJar * jar)
{
    int colvo = jar->getAllCookies().count();
    int i = 0;
    while(i<colvo)
    {
        QNetworkCookie cookie = jar->getAllCookies()[i];
        CookieWidget *widget = new CookieWidget(cookie,this);

        m_layout->insertWidget(0,widget);

        connect(widget, &CookieWidget::viewClicked, [cookie]() {
            CookieDialog dialog(cookie);
            dialog.exec();
        });
        connect(widget, &CookieWidget::deleteClicked, [this,jar,cookie]() {
            jar->deleteCookie(cookie);
            m_layout->removeWidget(this);
        });
        i++;
    }
    connect(this->m_deleteAllButton_2,&QPushButton::clicked,[this,jar](){
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                             tr("Are you sure to delete ALL cookies?"), QMessageBox::Yes | QMessageBox::No);
        if (button != QMessageBox::Yes) {
            return;
        }
        jar->deleteAllCookies();
        for (int i = m_layout->count() - 1; i >= 0; i--)
            delete m_layout->itemAt(i)->widget();
    });

}

void CookieManager::addCookie(const QNetworkCookie &cookie)
{
    CookieWidget *widget = new CookieWidget(cookie,this);
    widget->setFocus();
    m_layout->insertWidget(0,widget);
    connect(widget, &CookieWidget::viewClicked, [cookie]() {
        CookieDialog dialog(cookie);
        dialog.exec();
    });
    connect(widget, &CookieWidget::deleteClicked, [this,cookie,widget]() {
        emit deleteCookie(cookie);
        delete widget;
    });
}
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
    setAutoFillBackground(true);
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


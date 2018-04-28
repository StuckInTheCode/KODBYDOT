#include "cookiemanager.h"

CookieManager::CookieManager()
{

}
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>

CookieDialog::CookieDialog(const QNetworkCookie &cookie, QWidget *parent): QDialog(parent)
{
}

CookieDialog::CookieDialog(QWidget *parent): QDialog(parent)
{
}

CookieWidget::CookieWidget(const QNetworkCookie &cookie, QWidget *parent): QWidget(parent)
{
 
}

void CookieWidget::setHighlighted(bool enabled)
{

}

QNetworkCookie CookieDialog::cookie()
{

}


#include "cookiejar.h"
#include <QSettings>
#include "ui_cookiedialog.h"
#include "browserwindow.h"
#include <QNetworkCookie>
#include <QWebEngineProfile>
#include <QWebEngineSettings>
#include <QDateTime>
#include "cookiemanager.h"

CookieJar::CookieJar(QObject* parent,QWebEngineProfile *profile)
    : QObject(parent)
    , m_client(profile->cookieStore())
    //, m_client(mApp->webProfile()->cookieStore())
{
    loadSettings();
    m_client->loadAllCookies();
    if(m_allowCookies)
    {
        connect(m_client, &QWebEngineCookieStore::cookieAdded, this, &CookieJar::slotCookieAdded);
        connect(m_client, &QWebEngineCookieStore::cookieRemoved, this, &CookieJar::slotCookieRemoved);
    }
}

void CookieJar::loadSettings()
{
    QSettings settings;
    settings.beginGroup("Cookie-Settings");
    m_allowCookies = settings.value("allowCookies", true).toBool();
    m_filterThirdParty = settings.value("filterThirdPartyCookies", false).toBool();
    m_filterTrackingCookie = settings.value("filterTrackingCookie", false).toBool();
    m_whitelist = settings.value("whitelist", QStringList()).toStringList();
    m_blacklist = settings.value("blacklist", QStringList()).toStringList();
    settings.endGroup();
}

void CookieJar::setAllowCookies(bool allow)
{
    m_allowCookies = allow;
}

void CookieJar::deleteCookie(const QNetworkCookie &cookie)
{
    m_client->deleteCookie(cookie);
}

QVector<QNetworkCookie> CookieJar::getAllCookies() const
{
    return m_cookies;
}

void CookieJar::deleteAllCookies()
{
    m_client->deleteAllCookies();
}

bool CookieJar::matchDomain(QString cookieDomain, QString siteDomain) const
{
    // According to RFC 6265

    // Remove leading dot
    if (cookieDomain.startsWith(QLatin1Char('.'))) {
        cookieDomain = cookieDomain.mid(1);
    }

    if (siteDomain.startsWith(QLatin1Char('.'))) {
        siteDomain = siteDomain.mid(1);
    }
    if (cookieDomain == siteDomain) {
            return true;
    }

    if (!siteDomain.endsWith(cookieDomain)) {
          return false;
    }

    int index = siteDomain.indexOf(cookieDomain);

    return index > 0 && siteDomain[index - 1] == QLatin1Char('.');
    //return QString::compare(cookieDomain,siteDomain);
    //return QzTools::matchDomain(cookieDomain, siteDomain);
}

bool CookieJar::listMatchesDomain(const QStringList &list, const QString &cookieDomain) const
{
    foreach (const QString &d, list) {
        if (matchDomain(d, cookieDomain)) {
            return true;
        }
    }

    return false;
}

void CookieJar::slotCookieAdded(const QNetworkCookie &cookie)
{
    if (rejectCookie(QString(), cookie, cookie.domain())) {
        m_client->deleteCookie(cookie);
        return;
    }

    m_cookies.append(cookie);
    emit cookieAdded(cookie);
   //CookieDialog dialog(cookie);
   // dialog.exec();
}

void CookieJar::slotCookieRemoved(const QNetworkCookie &cookie)
{
    if (m_cookies.removeOne(cookie))
        emit cookieRemoved(cookie);
}

bool CookieJar::rejectCookie(const QString &domain, const QNetworkCookie &cookie, const QString &cookieDomain) const
{
    Q_UNUSED(domain)

    if (!m_allowCookies) {
        bool result = listMatchesDomain(m_whitelist, cookieDomain);
        if (!result) {
#ifdef COOKIE_DEBUG
            qDebug() << "not in whitelist" << cookie;
#endif
            return true;
        }
    }

    if (m_allowCookies) {
        bool result = listMatchesDomain(m_blacklist, cookieDomain);
        if (result) {
#ifdef COOKIE_DEBUG
            qDebug() << "found in blacklist" << cookie;
#endif
            return true;
        }
    }

    if (m_filterTrackingCookie && cookie.name().startsWith("__utm")) {
#ifdef COOKIE_DEBUG
        qDebug() << "purged as tracking " << cookie;
#endif
        return true;
    }

    return false;
}

#include "cookiejar.h"
#include "browserwindow.h"
#include <QNetworkCookie>
#include <QWebEngineProfile>
#include <QWebEngineSettings>


CookieJar::CookieJar(QObject* parent,QWebEngineProfile *profile)
    : QObject(parent)
    , m_client(profile->cookieStore())

{
    m_client->loadAllCookies();
}

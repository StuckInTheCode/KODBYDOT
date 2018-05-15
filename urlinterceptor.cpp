#include "urlinterceptor.h"
#include <QMutexLocker>
#include <QSettings>
#include <QWebEngineProfile>
NetworkUrlInterceptor::NetworkUrlInterceptor(QObject *parent)
    : QWebEngineUrlRequestInterceptor(parent)
    , m_sendDNT(false)
{
    QSettings settings;
    settings.beginGroup("Web-Browser-Settings");
    m_globalUserAgent = settings.value("UserAgent", QString()).toString();
    settings.endGroup();

    settings.beginGroup("User-Agent-Settings");
    m_usePerDomainUserAgent = settings.value("UsePerDomainUA", false).toBool();
    QStringList domainList = settings.value("DomainList", QStringList()).toStringList();
    QStringList userAgentsList = settings.value("UserAgentsList", QStringList()).toStringList();
    settings.endGroup();

    m_usePerDomainUserAgent = (m_usePerDomainUserAgent && domainList.count() == userAgentsList.count());

    if (m_usePerDomainUserAgent) {
        for (int i = 0; i < domainList.count(); ++i) {
            m_userAgentsList[domainList.at(i)] = userAgentsList.at(i);
        }
    }

    const QString  userAgent = m_globalUserAgent.isEmpty() ? m_defaultUserAgent : m_globalUserAgent;
    QWebEngineProfile::defaultProfile()->setHttpUserAgent(userAgent);

    loadSettings();
}

void NetworkUrlInterceptor::interceptRequest(QWebEngineUrlRequestInfo &info)
{
    QMutexLocker lock(&m_mutex);

    if (m_sendDNT) {
        info.setHttpHeader(QByteArrayLiteral("DNT"), QByteArrayLiteral("1"));
    }

    const QString host = info.firstPartyUrl().host();

    if (m_usePerDomainUserAgent) {
        QString userAgent;
        if (m_userAgentsList.contains(host)) {
            userAgent = m_userAgentsList.value(host);
        } else {
            QHashIterator<QString, QString> i(m_userAgentsList);
            while (i.hasNext()) {
                i.next();
                if (host.endsWith(i.key())) {
                    userAgent = i.value();
                    break;
                }
            }
        }
        if (!userAgent.isEmpty()) {
            info.setHttpHeader(QByteArrayLiteral("User-Agent"), userAgent.toUtf8());
        }
    }

    foreach (UrlInterceptor *interceptor, m_interceptors) {
        interceptor->interceptRequest(info);
    }
}

void NetworkUrlInterceptor::installUrlInterceptor(UrlInterceptor *interceptor)
{
    QMutexLocker lock(&m_mutex);

    if (!m_interceptors.contains(interceptor)) {
        m_interceptors.append(interceptor);
    }
}

void NetworkUrlInterceptor::removeUrlInterceptor(UrlInterceptor *interceptor)
{
    QMutexLocker lock(&m_mutex);

    m_interceptors.removeOne(interceptor);
}

void NetworkUrlInterceptor::loadSettings()
{
    QMutexLocker lock(&m_mutex);

    QSettings settings;
    settings.beginGroup("Web-Browser-Settings");
    m_sendDNT = settings.value("DoNotTrack", false).toBool();
    settings.endGroup();
}

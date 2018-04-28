#ifndef COOKIEJAR_H
#define COOKIEJAR_H

#include <QVector>
#include <QStringList>
#include <QWebEngineCookieStore>
#include <QWebEngineProfile>



class  CookieJar : public QObject
{
    Q_OBJECT

public:

    explicit CookieJar(QObject* parent = 0, QWebEngineProfile *m_cookies = 0);

private:

    QWebEngineCookieStore *m_client;
    QVector<QNetworkCookie> m_cookies;
};

#endif // COOKIEJAR_H

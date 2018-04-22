#ifndef WEBPAGE_H
#define WEBPAGE_H

#include <QWebEnginePage>

class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    WebPage(QWebEngineProfile *profile, QObject *parent = nullptr);
    void clearCookie();
    void saveCookie();
    void addToFavorite();
};

#endif // WEBPAGE_H

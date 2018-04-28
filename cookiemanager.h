#ifndef COOKIEMANAGER_H
#define COOKIEMANAGER_H
#include "ui_cookiejar.h"
//#include "ui_cookiemanager.h"
#include "ui_cookiedialog.h"
#include <QNetworkCookie>
#include <QMainWindow>

QT_BEGIN_NAMESPACE
class QWebEngineCookieStore;
QT_END_NAMESPACE

class CookieManager
{
public:
    CookieManager();
};

class CookieDialog : public QDialog, public Ui_CookieDialog
{
    Q_OBJECT
public:
    CookieDialog(const QNetworkCookie &cookie, QWidget *parent = nullptr);
    CookieDialog(QWidget *parent = 0);
    QNetworkCookie cookie();
};

class CookieWidget : public QWidget,  public Ui_CookieJar
{
    Q_OBJECT
public:
    CookieWidget(const QNetworkCookie &cookie, QWidget *parent = nullptr);
    void setHighlighted(bool enabled);
signals:
    void deleteClicked();
    void viewClicked();
};

#endif // COOKIEMANAGER_H

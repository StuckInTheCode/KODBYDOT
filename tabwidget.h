 #ifndef TABWIDGET_H
#define TABWIDGET_H

#include <QTabWidget>
#include <QHBoxLayout>
#include <QWebEnginePage>
#include <QToolButton>
#include <QLineEdit>
#include <QTabBar>
#include "ui_window.h"
#include "webview.h"
#include "webpage.h"
class QUrl;

QT_BEGIN_NAMESPACE
namespace Ui {
class window;
}
class WebView;

class TabWidget : public QTabWidget
{
    Q_OBJECT
public:
    TabWidget(QWebEngineProfile *profile, QWidget *parent = nullptr, QUrl * homePage = nullptr);
    void TabWidget::handleCurrentChanged(int index);
    void load();
    bool loadURL(QUrl url);
    WebView* createTab();
    WebView* createIncognitoTab();
    WebView* createBackgroundTab();

signals:
void linkHovered(const QString &link);
void loadProgress(int progress);
void titleChanged(const QString &title);
void urlChanged(const QUrl &url);

public slots:
    void closeTab(int index);
    WebView *currentWebView() const;
    void setUrl(const QUrl &url){}

private:
    Ui::window *ui;
    WebView *webView(int index) const;
    QUrl * m_homePage;
    QWebEngineProfile *m_profile;
};

#endif // TABWIDGET_H

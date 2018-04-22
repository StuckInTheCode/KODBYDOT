#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QIcon>
#include <QWebEngineView>
#include <QWidget>

class WebPage;

class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = nullptr);
    void setPage(WebPage *page);
};

#endif

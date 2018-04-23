#ifndef WEBVIEW_H
#define WEBVIEW_H

#include <QIcon>
#include <QWebEngineView>
#include <QWidget>
#include <QWebEnginePage>

class WebPage;

class WebView : public QWebEngineView
{
    Q_OBJECT
public:
    WebView(QWidget *parent = nullptr);
    void setPage(WebPage *page);
    QWebEngineView *createWindow(QWebEnginePage::WebWindowType type) override; //изменяет виртуальную функцию, вызываемую внутри класса, таким образом создавая разные вариаты окон
};

#endif

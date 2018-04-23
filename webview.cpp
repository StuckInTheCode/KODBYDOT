#include "browser.h"
#include "browserwindow.h"
#include "tabwidget.h"
#include "webpage.h"
#include "webpopupwindow.h"
#include "webview.h"
#include <QContextMenuEvent>
#include <QDebug>
#include <QMenu>
#include <QMessageBox>
#include <QTimer>

WebView::WebView(QWidget *parent): QWebEngineView(parent)
{
}
void WebView::setPage(WebPage *page)
{
    QWebEngineView::setPage(page);
}


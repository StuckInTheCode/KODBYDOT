/****************************************************************************
**
** Copyright (C) 2016 The Qt Company Ltd.
** Contact: https://www.qt.io/licensing/
**
** This file is part of the examples of the Qt Toolkit.
**
** $QT_BEGIN_LICENSE:BSD$
** Commercial License Usage
** Licensees holding valid commercial Qt licenses may use this file in
** accordance with the commercial license agreement provided with the
** Software or, alternatively, in accordance with the terms contained in
** a written agreement between you and The Qt Company. For licensing terms
** and conditions see https://www.qt.io/terms-conditions. For further
** information use the contact form at https://www.qt.io/contact-us.
**
** BSD License Usage
** Alternatively, you may use this file under the terms of the BSD license
** as follows:
**
** "Redistribution and use in source and binary forms, with or without
** modification, are permitted provided that the following conditions are
** met:
**   * Redistributions of source code must retain the above copyright
**     notice, this list of conditions and the following disclaimer.
**   * Redistributions in binary form must reproduce the above copyright
**     notice, this list of conditions and the following disclaimer in
**     the documentation and/or other materials provided with the
**     distribution.
**   * Neither the name of The Qt Company Ltd nor the names of its
**     contributors may be used to endorse or promote products derived
**     from this software without specific prior written permission.
**
**
** THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS
** "AS IS" AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT
** LIMITED TO, THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR
** A PARTICULAR PURPOSE ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT
** OWNER OR CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL,
** SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT
** LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
** DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
** THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
** (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
** OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE."
**
** $QT_END_LICENSE$
**
****************************************************************************/

#include "browser.h"
#include "browserwindow.h"
#include "downloadmanagerwidget.h"
#include "tabwidget.h"
#include "webview.h"
#include "cookiejar.h"
#include "cookiemanager.h"
#include "history.h"
#include "historymanager.h"
#include "toolbarsearch.h"
#include "savepagedialog.h"
#include "webview.h"
#include "settings.h"
#include "bookmarkdialog.h"

#include <QApplication>
#include <QCloseEvent>
#include <QAction>
#include <QDesktopWidget>
#include <QEvent>
#include <QFileDialog>
#include <QInputDialog>
#include <QMenuBar>
#include <QMessageBox>
#include <QProgressBar>
#include <QStatusBar>
#include <QToolBar>
#include <QVBoxLayout>
#include <QWebEngineProfile>
#include <QHBoxLayout>
#include <QPushButton>
BrowserWindow::BrowserWindow(Browser *browser, QWebEngineProfile *profile)
    : m_browser(browser)
    , m_profile(profile)
    , m_tabWidget(new TabWidget(profile, this, browser->getHomePage()))
    , m_cookiejar ( new CookieJar(this, profile))
    , m_cookiemanager( new CookieManager())
    , m_button( new QPushButton(this) )
    , m_bookmark( new QPushButton(this) )
    , m_urlLineEdit( new QLineEdit(this))
    , m_search( new ToolbarSearch(this))
{
    m_cookiemanager->LoadCookies(m_cookiejar);
    connect(m_cookiejar, &CookieJar::cookieAdded, m_cookiemanager, &CookieManager::addCookie);
    //QPushButton *m_button =  new QPushButton(this);
    //QLineEdit *m_urlLineEdit = new QLineEdit(this);
    //m_urlLineEdit->setAlignment(Qt::AlignLeft);
    m_button->setText("GO");
    QHBoxLayout *m_layout = new QHBoxLayout(this);
    menuBar()->addMenu(createFileMenu(m_tabWidget));
    menuBar()->addMenu(createViewMenu());
    menuBar()->addMenu(createOptionsMenu());

    //m_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    //m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(10);
    m_search->setFixedWidth(300);
    m_bookmark->setText("B");
    m_bookmark->setFixedWidth(25);
    //m_bookmark->setIcon(new QIcon());
    QWidget *w = new QWidget();
    //QPalette p = w->palette();
    //w->setPalette(p);
    w->setLayout(m_layout);
    m_layout->addWidget(m_urlLineEdit);
    m_layout->addWidget(m_button);
    m_layout->addWidget(m_search);
    m_layout->addWidget(m_bookmark);

    //ui->setupUi(this);
    //ui->preview->load(QUrl("http://harrix.org/"));
    //ui->preview->load(this->browser()->getHomePage());
    setAttribute(Qt::WA_DeleteOnClose, true);
    setFocusPolicy(Qt::ClickFocus);

    QWidget *mainWidget = new QWidget(this);
    QToolBar toolbar("KODBYDOT",mainWidget);
    addToolBar(&toolbar);
    QVBoxLayout *layout = new QVBoxLayout;
    layout->setSpacing(0);
    layout->setMargin(0);
    layout->addWidget(w);
    layout->addWidget(m_tabWidget);
    //QPushButton *button = new QPushButton(mainWidget);
    //layout->addWidget(button);
    //mainWidget->setLayout(m_tabWidget);
    addToolBarBreak();
    //connect(m_tabWidget, &TabWidget::urlChanged, [this](const QUrl &url) {
    //    m_urlLineEdit->setText(url.toDisplayString());
   // });
    //connect(button,&QPushButton::clicked, this, &BrowserWindow::on_pushButton_clicked);
    connect(m_button,&QPushButton::clicked, this, &BrowserWindow::load);
    connect(m_urlLineEdit, &QLineEdit::returnPressed,this, &BrowserWindow::load);
    connect(m_bookmark,&QPushButton::clicked, this, &BrowserWindow::addToBookmarks);
    connect(m_search, SIGNAL(search(QUrl)), SLOT(loadURL(QUrl)));
    connect(m_tabWidget,&TabWidget::urlChanged,this,&BrowserWindow::urlChanged);
    connect(m_tabWidget, &TabWidget::linkHovered, [this](const QString& url) {
        statusBar()->showMessage(url);
    });
    //connect(m_tabWidget, &TabWidget::loadProgress, this, &BrowserWindow::loadProgress);
    //connect(m_search,&ToolbarSearch::search(QUrl),this,(QUrl)->{m_tabWidget->loadURL(QUrl))};
    mainWidget->setLayout(layout);
    setCentralWidget(mainWidget);
    //m_tabWidget->createTab();

}
void BrowserWindow::urlChanged(const QUrl &url)
{
    m_urlLineEdit->setText(url.toDisplayString());
    history()->addHistoryEntry(m_tabWidget->currentWebView());
}

void BrowserWindow::addToBookmarks()
{
    BookmarkDialog * dialog = new BookmarkDialog(this);
    dialog->exec();
}
void BrowserWindow::load()
{
    m_tabWidget->loadURL(QUrl::fromUserInput(m_urlLineEdit->text()));
    m_urlLineEdit->setText(m_tabWidget->currentWebView()->url().toDisplayString());
    //history()->addHistoryEntry(m_tabWidget->currentWebView());
}

void BrowserWindow::loadURL(QUrl url)
{
    if (!url.isValid())
        return;
    m_urlLineEdit->setText(url.toDisplayString());
    m_tabWidget->loadURL(url);
}

QMenu *BrowserWindow::createFileMenu(TabWidget *tabWidget)
{
    QMenu *fileMenu = new QMenu(tr("&File"));
    //fileMenu->addAction(tr("&New Window"), this, &BrowserWindow::handleNewWindowTriggered, QKeySequence::New);
    //fileMenu->addAction(tr("New &Incognito Window"), this, &BrowserWindow::handleNewIncognitoWindowTriggered);

    QAction *newTabAction = new QAction(tr("New &Tab"), this);
    newTabAction->setShortcuts(QKeySequence::AddTab);
    connect(newTabAction, &QAction::triggered, tabWidget, &TabWidget::createTab);
    fileMenu->addAction(newTabAction);

    //fileMenu->addAction(tr("&Open File..."), this, &BrowserWindow::handleFileOpenTriggered, QKeySequence::Open);
    fileMenu->addSeparator();

    QAction *savePage = new QAction(tr("&Save page"), this);
    connect(savePage, &QAction::triggered, [this]() {
        SavePageDialog * dialog = new SavePageDialog(nullptr,QWebEngineDownloadItem::SavePageFormat::UnknownSaveFormat,this->currentTab());
        dialog->exec();
        //this->currentTab()->page()->save(nullptr);
        //tabWidget->closeTab(tabWidget->currentIndex());
    });
    fileMenu->addAction(savePage);

    QAction *closeTabAction = new QAction(tr("&Close Tab"), this);
    closeTabAction->setShortcuts(QKeySequence::Close);
    connect(closeTabAction, &QAction::triggered, [tabWidget]() {
        tabWidget->closeTab(tabWidget->currentIndex());
    });
    fileMenu->addAction(closeTabAction);

    QAction *closeAction = new QAction(tr("&Quit"),this);
    closeAction->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Q));
    connect(closeAction, &QAction::triggered, this, &QWidget::close);
    fileMenu->addAction(closeAction);

    connect(fileMenu, &QMenu::aboutToShow, [this, closeAction]() {
        if (m_browser->windows().count() == 1)
            closeAction->setText(tr("&Quit"));
        else
            closeAction->setText(tr("&Close Window"));
    });
    return fileMenu;
}

QMenu *BrowserWindow::createViewMenu()//QToolBar *toolbar
{
    QMenu *viewMenu = new QMenu(tr("&View"));
    m_stopAction = viewMenu->addAction(tr("&Stop"));
    QList<QKeySequence> shortcuts;
    shortcuts.append(QKeySequence(Qt::CTRL | Qt::Key_Period));
    shortcuts.append(Qt::Key_Escape);
    m_stopAction->setShortcuts(shortcuts);
    /*connect(m_stopAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Stop);
    });
*/
    m_reloadAction = viewMenu->addAction(tr("Reload Page"));
    /*m_reloadAction->setShortcuts(QKeySequence::Refresh);
    connect(m_reloadAction, &QAction::triggered, [this]() {
        m_tabWidget->triggerWebPageAction(QWebEnginePage::Reload);
    });*/

    QAction *zoomIn = viewMenu->addAction(tr("Zoom &In"));
    zoomIn->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Plus));
    connect(zoomIn, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(currentTab()->zoomFactor() + 0.1);
    });

    QAction *zoomOut = viewMenu->addAction(tr("Zoom &Out"));
    zoomOut->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_Minus));
    connect(zoomOut, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(currentTab()->zoomFactor() - 0.1);
    });

    QAction *resetZoom = viewMenu->addAction(tr("Reset &Zoom"));
    resetZoom->setShortcut(QKeySequence(Qt::CTRL | Qt::Key_0));
    connect(resetZoom, &QAction::triggered, [this]() {
        if (currentTab())
            currentTab()->setZoomFactor(1.0);
    });


    /*viewMenu->addSeparator();

    QAction *viewStatusbarAction = new QAction(tr("Hide Status Bar"), this);
    viewStatusbarAction->setShortcut(tr("Ctrl+/"));
    connect(viewStatusbarAction, &QAction::triggered, [this, viewStatusbarAction]() {
        if (statusBar()->isVisible()) {
            viewStatusbarAction->setText(tr("Show Status Bar"));
            statusBar()->close();
        } else {
            viewStatusbarAction->setText(tr("Hide Status Bar"));
            statusBar()->show();
        }
    });
    viewMenu->addAction(viewStatusbarAction);*/
    return viewMenu;
}

QMenu *BrowserWindow::createOptionsMenu()
{
    QMenu *menu = new QMenu(tr("&Options"));

    QAction *showHistory = new QAction(tr("History"), this);
    connect(showHistory, &QAction::triggered, this, [this](){
        HistoryManager * manager = new HistoryManager(this);
        manager->show();
    });
    menu->addAction(showHistory);

    QAction *showCookie = new QAction(tr("Cookie"), this);
    connect(showCookie, &QAction::triggered, this, [this](){
        m_cookiemanager->show();
    });
    menu->addAction(showCookie);

    QAction *showSettings = new QAction(tr("Settings"), this);
    connect(showSettings, &QAction::triggered, [this](){
        Settings * settings = new Settings();
        settings->show();
    });
    menu->addAction(showSettings);
    /*connect(menu, &QMenu::aboutToShow, [this, menu, nextTabAction, previousTabAction]() {
        menu->clear();
        menu->addAction(nextTabAction);
        menu->addAction(previousTabAction);
        menu->addSeparator();

        QVector<BrowserWindow*> windows = m_browser->windows();
        int index(-1);
        for (auto window : windows) {
            QAction *action = menu->addAction(window->windowTitle(), this, &BrowserWindow::handleShowWindowTriggered);
            action->setData(++index);
            action->setCheckable(true);
            if (window == this)
                action->setChecked(true);
        }
    });*/
    return menu;
}

History *BrowserWindow::history() const
{
    return m_browser->m_history;
}

TabWidget *BrowserWindow::tabWidget() const
{
    return m_tabWidget;
}

WebView *BrowserWindow::currentTab() const
{
    return reinterpret_cast<WebView*>(m_tabWidget->currentWebView());
}

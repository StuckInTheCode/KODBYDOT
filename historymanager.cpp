#include "historymanager.h"
#include "ui_historymanager.h"
#include "browserwindow.h"
#include "history.h"
#include "historytreeview.h"
#include "tabwidget.h"
#include <QMenu>
#include <QAction>
#include <QMessageBox>
#include <QClipboard>
#include <QKeyEvent>

HistoryManager::HistoryManager(BrowserWindow* window, QWidget* parent)
    : QWidget(parent)
    , ui(new Ui::HistoryManager)
    , m_window(window)
    , m_history(window->history())
{
    setWindowTitle("History");
    ui->setupUi(this);

    //ui->historyTree->setViewType(HistoryTreeView::HistoryManagerViewType);
    ui->historyTree->Init(m_history);
    connect(ui->historyTree,&HistoryTreeView::urlActivated,this,&HistoryManager::urlActivated);
    connect(ui->historyTree, SIGNAL(contextMenuRequested(QPoint)), this, SLOT(createContextMenu(QPoint)));

    connect(ui->deleteB, SIGNAL(clicked()), ui->historyTree, SLOT(removeSelectedItems()));
    connect(ui->clearAll, SIGNAL(clicked()), this, SLOT(clearHistory()));
    connect(ui->searchButton,SIGNAL(clicked()),this,SLOT(searchName()));
}

BrowserWindow* HistoryManager::getWindow()
{
    return m_window.data();
}

void HistoryManager::setMainWindow(BrowserWindow* window)
{
    if (window) {
        m_window = window;
    }
}

void HistoryManager::clearHistory()
{
    QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                         tr("Are you sure you want to delete all history?"), QMessageBox::Yes | QMessageBox::No);
    if (button != QMessageBox::Yes) {
        return;
    }
    m_history->clearHistory();
}

void HistoryManager::keyPressEvent(QKeyEvent *event)
{
    switch (event->key()) {
    case Qt::Key_Delete:
        ui->historyTree->removeSelectedItems();
        break;
    }

    QWidget::keyPressEvent(event);
}

void HistoryManager::searchName()
{
    search(ui->searchEdit->text());
}

void HistoryManager::search(const QString &searchText)
{
    ui->historyTree->search(searchText);
}

void HistoryManager::urlActivated(const QUrl &url)
{
    openUrl(url);
}

void HistoryManager::urlCtrlActivated(const QUrl &url)
{
    openUrlInNewTab(url);
}

void HistoryManager::openUrl(const QUrl &url)
{
    const QUrl u = !url.isEmpty() ? url : ui->historyTree->selectedUrl();
    m_window->loadURL(u);
}

void HistoryManager::openUrlInNewTab(const QUrl &url)
{
    const QUrl u = !url.isEmpty() ? url : ui->historyTree->selectedUrl();
    m_window->tabWidget()->createTab();
    m_window->tabWidget()->loadURL(u);
}

void HistoryManager::openUrlInNewPrivateWindow(const QUrl &url)
{
    const QUrl u = !url.isEmpty() ? url : ui->historyTree->selectedUrl();
    m_window->tabWidget()->createIncognitoTab();
    m_window->tabWidget()->loadURL(u);
}

void HistoryManager::createContextMenu(const QPoint &pos)
{
    QMenu menu;
    QAction* actNewTab = menu.addAction(tr("Open in new tab"));
    QAction* actNewPrivateWindow = menu.addAction( tr("Open in new private tab"));

    menu.addSeparator();
    QAction* actCopyUrl = menu.addAction(tr("Copy url"), this, SLOT(copyUrl()));
    QAction* actCopyTitle = menu.addAction(tr("Copy title"), this, SLOT(copyTitle()));

    menu.addSeparator();
    QAction* actDelete = menu.addAction(tr("Delete"));

    connect(actNewTab, SIGNAL(triggered()), this, SLOT(openUrlInNewTab()));
    connect(actNewPrivateWindow, SIGNAL(triggered()), this, SLOT(openUrlInNewPrivateWindow()));
    connect(actDelete, SIGNAL(triggered()), ui->historyTree, SLOT(removeSelectedItems()));

    if (ui->historyTree->selectedUrl().isEmpty()) {
        actNewTab->setDisabled(true);
        actNewPrivateWindow->setDisabled(true);
        actCopyTitle->setDisabled(true);
        actCopyUrl->setDisabled(true);
    }

    menu.exec(pos);

}

void HistoryManager::copyUrl()
{
    QApplication::clipboard()->setText(ui->historyTree->selectedUrl().toString());
}

void HistoryManager::copyTitle()
{
    QApplication::clipboard()->setText(ui->historyTree->currentIndex().data().toString());
}

HistoryManager::~HistoryManager()
{
    delete ui;
}

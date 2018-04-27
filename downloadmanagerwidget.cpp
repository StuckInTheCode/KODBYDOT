#include "downloadmanagerwidget.h"
#include "browser.h"
#include "browserwindow.h"
#include "downloadwidget.h"

#include <QFileDialog>
#include <QWebEngineDownloadItem>
#include <QWidget>
DownloadManagerWidget::DownloadManagerWidget(QWidget *parent)
: QWidget(parent)
{
}
void DownloadManagerWidget::downloadRequested(QWebEngineDownloadItem *download)
{
    Q_ASSERT(download && download->state() == QWebEngineDownloadItem::DownloadRequested);

    QString path = QFileDialog::getSaveFileName(this, tr("Save as"), download->path());
    if (path.isEmpty())
        return;

    download->setPath(path);
    download->accept();
    //add(new DownloadWidget(download));

    show();
}

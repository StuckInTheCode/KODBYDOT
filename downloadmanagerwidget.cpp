#include "downloadmanagerwidget.h"
#include "browser.h"
#include "browserwindow.h"
#include "downloadwidget.h"

#include <QFileDialog>
#include <QWebEngineDownloadItem>
#include <QWidget>
DownloadManagerWidget::DownloadManagerWidget(QWidget *parent)
: QWidget(parent)
,m_itemsLayout(new QVBoxLayout)
{
    m_itemsLayout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_itemsLayout->setContentsMargins(0, 0, 0, 0);
    m_itemsLayout->setSpacing(0);
    this->setLayout(m_itemsLayout);
}
void DownloadManagerWidget::downloadRequested(QWebEngineDownloadItem *download)
{
    Q_ASSERT(download && download->state() == QWebEngineDownloadItem::DownloadRequested);

    QString path = QFileDialog::getSaveFileName(this, tr("Save as"), download->path());
    if (path.isEmpty())
        return;

    download->setPath(path);
    download->accept();
    add(new DownloadWidget(download ));

    show();
}
void DownloadManagerWidget::add(DownloadWidget *downloadWidget)
{
    //connect(downloadWidget, &DownloadWidget::removeClicked, this, &DownloadManagerWidget::remove);
    m_itemsLayout->insertWidget(0, downloadWidget, 0, Qt::AlignTop);
}

void DownloadManagerWidget::remove(DownloadWidget *downloadWidget)
{
    m_itemsLayout->removeWidget(downloadWidget);
    downloadWidget->deleteLater();

}

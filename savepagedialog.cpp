#include "savepagedialog.h"
#include "ui_savepagedialog.h"

#include <QtCore/QDir>
#include <QtWidgets/QFileDialog>


const QWebEngineDownloadItem::SavePageFormat SavePageDialog::m_indexToFormatTable[] = {
    QWebEngineDownloadItem::SingleHtmlSaveFormat,
    QWebEngineDownloadItem::CompleteHtmlSaveFormat,
    QWebEngineDownloadItem::MimeHtmlSaveFormat
};

SavePageDialog::SavePageDialog(QWidget *parent, QWebEngineDownloadItem::SavePageFormat format,
                               QWebEngineView * webView)
    : QDialog(parent)
    , ui(new Ui::SavePageDialog)
    , m_webView(webView)
{
    ui->setupUi(this);
    //ui->comboBox->setCurrentIndex(formatToIndex(format));
    connect(ui->buttonBox,&QDialogButtonBox::accepted ,this,&SavePageDialog::save);
    connect(ui->buttonBox,&QDialogButtonBox::rejected ,this,&SavePageDialog::close);
}

SavePageDialog::~SavePageDialog()
{
    delete ui;
}
void SavePageDialog::save()
{
    m_webView->page()->save(nullptr,pageFormat());
    //m_webView->page()->
    //this->close();
}

QWebEngineDownloadItem::SavePageFormat SavePageDialog::pageFormat() const
{
    return indexToFormat(ui->comboBox->currentIndex());
}

int SavePageDialog::formatToIndex(QWebEngineDownloadItem::SavePageFormat format)
{
    for (auto i : m_indexToFormatTable) {
        if (m_indexToFormatTable[i] == format)
            return i;
    }
    Q_UNREACHABLE();
}

QWebEngineDownloadItem::SavePageFormat SavePageDialog::indexToFormat(int idx)
{
    Q_ASSERT(idx >= 0 && size_t(idx) < (sizeof(m_indexToFormatTable)
                                        / sizeof(QWebEngineDownloadItem::SavePageFormat)));
    return m_indexToFormatTable[idx];
}


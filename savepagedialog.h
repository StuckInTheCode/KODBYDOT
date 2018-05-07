
#ifndef SAVEPAGEDIALOG_H
#define SAVEPAGEDIALOG_H

#include <QtWidgets/QDialog>
#include <QtWebEngineWidgets/QWebEngineDownloadItem>
#include <QWebEngineView>

QT_BEGIN_NAMESPACE
namespace Ui {
class SavePageDialog;
}
QT_END_NAMESPACE

class SavePageDialog : public QDialog
{
    Q_OBJECT

public:
    explicit SavePageDialog(QWidget *parent, QWebEngineDownloadItem::SavePageFormat format,
                            QWebEngineView * webView);
    ~SavePageDialog();

    QWebEngineDownloadItem::SavePageFormat pageFormat() const;

private slots:
    void save();
private:
    static int formatToIndex(QWebEngineDownloadItem::SavePageFormat format);
    static QWebEngineDownloadItem::SavePageFormat indexToFormat(int idx);
    static const QWebEngineDownloadItem::SavePageFormat m_indexToFormatTable[];
    Ui::SavePageDialog *ui;
    QWebEngineView * m_webView;
};

#endif // SAVEPAGEDIALOG_H

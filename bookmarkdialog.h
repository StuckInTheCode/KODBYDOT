#ifndef BOOKMARKDIALOG_H
#define BOOKMARKDIALOG_H

#include <QDialog>
#include <QString>
#include "ui_bookmark.h"
#include "bookmark.h"
namespace Ui {
class BookmarkDialog;
}
class QWebEngineView;
class BookmarkDialog : public QDialog
{
    Q_OBJECT

public:
    enum SaveFormat {
        Json, Binary
    };
    explicit BookmarkDialog(QString filename,QWebEngineView * webView, QWidget *parent = 0);
    bool saveToFile(SaveFormat saveFormat = Json);
    bool loadFromFile(SaveFormat saveFormat = Json);
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    void accept();
    ~BookmarkDialog();
signals:
    void newBookmarkTab(const QUrl &url);
private:
    QString filename;
    QWebEngineView * m_webView;
    QVector<Bookmark> m_bookmarks;
    QVBoxLayout * m_layout;
    Ui::BookmarkDialog *ui;
};

class BookmarkWidget : public QWidget,  public Ui_Bookmark
{
    Q_OBJECT
public:
    BookmarkWidget( Bookmark &bookmark, QWidget *parent = nullptr)
    {
        setupUi(this);
        this->name->setText(bookmark.name());
        this->url->setText(bookmark.url().toDisplayString());
        connect(loadButton, &QPushButton::clicked, this, &BookmarkWidget::loadClicked);
        connect(delButton, &QPushButton::clicked, this, &BookmarkWidget::deleteClicked);
    }
signals:
    void deleteClicked();
    void loadClicked();
};
#endif // BOOKMARKDIALOG_H

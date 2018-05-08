#ifndef BOOKMARKDIALOG_H
#define BOOKMARKDIALOG_H

#include <QDialog>
#include <QString>
namespace Ui {
class BookmarkDialog;
}

class BookmarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookmarkDialog(QWidget *parent = 0);
    bool saveToFile(QString filename);
    bool loadFromFile(QString filename);
    ~BookmarkDialog();

private:

    Ui::BookmarkDialog *ui;
};

#endif // BOOKMARKDIALOG_H

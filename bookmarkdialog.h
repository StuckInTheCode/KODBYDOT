#ifndef BOOKMARKDIALOG_H
#define BOOKMARKDIALOG_H

#include <QDialog>

namespace Ui {
class BookmarkDialog;
}

class BookmarkDialog : public QDialog
{
    Q_OBJECT

public:
    explicit BookmarkDialog(QWidget *parent = 0);
    ~BookmarkDialog();

private:

    Ui::BookmarkDialog *ui;
};

#endif // BOOKMARKDIALOG_H

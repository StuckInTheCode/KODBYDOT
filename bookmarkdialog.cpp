#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
BookmarkDialog::BookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookmarkDialog)
{
    ui->setupUi(this);
}

BookmarkDialog::~BookmarkDialog()
{
    delete ui;
}

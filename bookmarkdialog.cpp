#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLineEdit>
#include <QMessageBox>
BookmarkDialog::BookmarkDialog(QString filename,QWebEngineView * webView,QWidget *parent) :
    QDialog(parent),
    m_webView(webView),
    m_layout(new QVBoxLayout()),
    ui(new Ui::BookmarkDialog)
{
    this->filename = filename;
    ui->setupUi(this);

    m_layout->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    m_layout->setContentsMargins(0, 0, 0, 0);
    m_layout->setSpacing(0);
    ui->scrollAreaWidgetContents->setLayout(m_layout);
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    loadFromFile(Json);

    for(Bookmark b : m_bookmarks) {
        BookmarkWidget* widget = new BookmarkWidget(b);
        m_layout->insertWidget(0,widget);
        connect(widget,&BookmarkWidget::deleteClicked,[this,b,widget](){
            QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                                 tr("Are you sure you want to delete bookmark?"), QMessageBox::Yes | QMessageBox::No);
            if (button != QMessageBox::Yes) {
                return;
            }
            if(m_bookmarks.size()==1)
               m_bookmarks.clear();
            else
                m_bookmarks.removeOne(b);
            delete widget;
            saveToFile(Json);
        });
        connect(widget,&BookmarkWidget::loadClicked,[this,b](){
            emit newBookmarkTab(b.url());
        });
    }
    connect(this->ui->deletebutton,&QPushButton::clicked,[this](){
        QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Confirmation"),
                                             tr("Are you sure to delete ALL bookmark?"), QMessageBox::Yes | QMessageBox::No);
        if (button != QMessageBox::Yes) {
            return;
        }
        m_bookmarks.clear();
        for (int i = m_layout->count() - 1; i >= 0; i--)
            delete m_layout->itemAt(i)->widget();
        saveToFile(Json);
    });
}

bool BookmarkDialog::loadFromFile(BookmarkDialog::SaveFormat saveFormat)
{
    /*QFile loadFile(saveFormat == Json
                   ?filename+=".json"
                   :filename+=".dat");*/
    QFile loadFile(saveFormat == Json
                       ?filename
                       :filename+=".dat");

    if (!loadFile.open(QIODevice::ReadOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QByteArray saveData = loadFile.readAll();

    QJsonDocument loadDoc(saveFormat == Json
        ? QJsonDocument::fromJson(saveData)
        : QJsonDocument::fromBinaryData(saveData));

    read(loadDoc.object());

    QTextStream(stdout) << "Loaded save for "
                        << (saveFormat != Json ? "binary " : "") << "JSON...\n";
    return true;
}

bool BookmarkDialog::saveToFile(BookmarkDialog::SaveFormat saveFormat)
{
    /*QFile saveFile(saveFormat == Json
                   ?filename+=".json"
                   :filename+=".dat");*/
    QFile saveFile(saveFormat == Json
                       ?filename
                       :filename+=".dat");

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveFormat == Json
        ? saveDoc.toJson()
        : saveDoc.toBinaryData());

    return true;
}

void BookmarkDialog::read(const QJsonObject &json)
{
    if (json.contains("bookmarks") && json["bookmarks"].isArray()) {
        QJsonArray Array = json["bookmarks"].toArray();
        m_bookmarks.clear();
        m_bookmarks.reserve(Array.size());
        for (int Index = 0; Index < Array.size(); ++Index) {
            QJsonObject bookmarkObject = Array[Index].toObject();
            Bookmark bookmark;
            bookmark.read(bookmarkObject);
            m_bookmarks.append(bookmark);
        }
    }
}

void BookmarkDialog::write(QJsonObject &json) const
{
    QJsonArray Array;
    foreach (const Bookmark bookmark, m_bookmarks) {
        QJsonObject bookmarkObject;
        bookmark.write(bookmarkObject);
        Array.append(bookmarkObject);
    }
    json["bookmarks"] = Array;
}
/*void BookmarkDialog::deleteAll()
{
    m_bookmarks.clear();
}*/

void BookmarkDialog::accept()
{
    Bookmark bookmark(this->ui->name->text(),m_webView->url());
    loadFromFile(Json);
    if(m_bookmarks.contains(bookmark))
    {

        return;
    }
    /*if(m_bookmarks.contains(bookmark))
    {
        return;
    }*/
    m_bookmarks.append(bookmark);
    saveToFile(Json);
    QDialog::accept();
}


BookmarkDialog::~BookmarkDialog()
{
    delete ui;
}

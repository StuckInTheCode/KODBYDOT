#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
#include <QVBoxLayout>
#include <QWebEngineView>
#include <QFile>
#include <QJsonDocument>
#include <QJsonArray>
#include <QLineEdit>
BookmarkDialog::BookmarkDialog(QString filename,QWebEngineView * webView,QWidget *parent) :
    QDialog(parent),
    m_webView(webView),
    ui(new Ui::BookmarkDialog)
{
    this->filename = filename;
    ui->setupUi(this);
    //ui->listWidget->setLayout(new QVBoxLayout());
    loadFromFile(Json);
}

bool BookmarkDialog::loadFromFile(BookmarkDialog::SaveFormat saveFormat)
{
    QFile loadFile(saveFormat == Json
                   ?filename+=".json"
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
    QFile saveFile(saveFormat == Json
                   ?filename+=".json"
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

void BookmarkDialog::accept()
{
    Bookmark bookmark(this->ui->name->text(),m_webView->url());
    loadFromFile(Json);
    /*if(m_bookmarks.contains(bookmark))
    {
        return;
    }*/
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

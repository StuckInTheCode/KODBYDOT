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
    ui->scrollArea->setWidgetResizable(true);
    ui->scrollAreaWidgetContents->setLayout(new QVBoxLayout());
    //ui->scrollAreaWidgetContents->layout()->addItem(new QSpacerItem(0,0, QSizePolicy::Minimum, QSizePolicy::Expanding));
    ui->scrollAreaWidgetContents->layout()->setContentsMargins(0, 0, 0, 0);
    ui->scrollAreaWidgetContents->layout()->setSpacing(0);
    //ui->scrollArea->setWidgetResizable(true);
    ui->scrollArea->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    //ui->scrollArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->listWidget->setLayout(new QVBoxLayout());
    loadFromFile(Json);
    for(Bookmark b : m_bookmarks) {
        BookmarkWidget* widget = new BookmarkWidget(b);
        ui->scrollAreaWidgetContents->layout()->addWidget(widget);
        /*connect(widget, &CookieWidget::deleteClicked, [this, cookie, widget]() {
            m_store->deleteCookie(cookie);
            delete widget;
            m_cookies.removeOne(cookie);
            for (int i = 0; i < m_layout->count() - 1; i++) {
                // fix background colors
                auto widget = qobject_cast<CookieWidget*>(m_layout->itemAt(i)->widget());
                widget->setHighlighted(i % 2);
            }
        });*/
        connect(widget,&BookmarkWidget::deleteClicked,[this,b,widget](){
           // if(qWarning("Bookmark will be delete permanently, are you sure?")==Qt:accept()){
            m_bookmarks.removeOne(b);
            delete widget;
            //ui->scrollAreaWidgetContents->layout()->removeWidget(widget);

            saveToFile(Json);
          //  }
        });
        //connect(widget->loadButton,&QPushButton::clicked,b,&BookmarkWidget::loadClicked);
    }
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
/*void BookmarkDialog::delete()
{

}*/

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

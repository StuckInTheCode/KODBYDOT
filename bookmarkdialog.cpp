#include "bookmarkdialog.h"
#include "ui_bookmarkdialog.h"
#include <QFile>
BookmarkDialog::BookmarkDialog(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::BookmarkDialog)
{
    ui->setupUi(this);
}

bool BookmarkDialog::loadFromFile(QString filename)
{
    /*QFile loadFile(saveFormat == Json
        ? QStringLiteral(filename+".json")
        : QStringLiteral(filename+".dat"));

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
                        << loadDoc["player"]["name"].toString()
                        << " using "
                        << (saveFormat != Json ? "binary " : "") << "JSON...\n";*/
    return true;
}

bool BookmarkDialog::saveToFile(QString filename)
{
    /*QFile saveFile(saveFormat == Json
                   ? QStringLiteral(filename+".json")
                   : QStringLiteral(filename+".dat"));

    if (!saveFile.open(QIODevice::WriteOnly)) {
        qWarning("Couldn't open save file.");
        return false;
    }

    QJsonObject gameObject;
    write(gameObject);
    QJsonDocument saveDoc(gameObject);
    saveFile.write(saveFormat == Json
        ? saveDoc.toJson()
        : saveDoc.toBinaryData());*/

    return true;
}

BookmarkDialog::~BookmarkDialog()
{
    delete ui;
}

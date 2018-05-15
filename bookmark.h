#ifndef BOOKMARK_H
#define BOOKMARK_H
#include <QJsonObject>
#include <QUrl>

class Bookmark
{
public:
    Bookmark();
    Bookmark(const Bookmark & bookmark);
    Bookmark(QString name, QUrl url);
    QString name();
    QUrl url() const;
    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;
    friend bool operator ==(const Bookmark &bookmark1,const Bookmark &bookmark2);
private:
    QString mName;
    QUrl mUrl;
};

#endif // BOOKMARK_H

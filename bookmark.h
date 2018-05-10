#ifndef BOOKMARK_H
#define BOOKMARK_H
#include <QJsonObject>
#include <QUrl>

class Bookmark
{
public:
    Bookmark();
    Bookmark(QString name, QUrl url)
    {
        mName=name;
        mUrl=url;
    }
    QString name()
    {
        return mName;
    }
    QUrl url()
    {
        return mUrl;
    }
    void read(const QJsonObject &json)
    {
        if (json.contains("name") && json["name"].isString())
            mName = json["name"].toString();

        if (json.contains("url") && json["url"].isString())
            mUrl = QUrl( json["url"].toString());
    }
    void write(QJsonObject &json) const
    {
        json["name"] = mName;
        json["url"] = mUrl.toDisplayString();
    }
    /*bool operator ==(const Bookmark &bookmark)
    {
        //const Bookmark bookmark2 =*this;
        //if(this->name().compare(bookmark.name()) && this->url().matches(bookmark.url()))
        //if(QString::compare(bookmark.name(),bookmark2.name()) && bookmark.url().matches(bookmark2.url()))
            return true;
        return false;
    }*/
private:
    QString mName;
    QUrl mUrl;
};

#endif // BOOKMARK_H

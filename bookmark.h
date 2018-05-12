#ifndef BOOKMARK_H
#define BOOKMARK_H
#include <QJsonObject>
#include <QUrl>

class Bookmark
{
public:
    Bookmark();
    Bookmark(const Bookmark & bookmark)
    {
        mName=bookmark.mName;
        mUrl=bookmark.mUrl;

    }
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
    /*bool operator ==(Bookmark &bookmark)
    {
        const Bookmark *bookmark2 =this;
        //if(this->name().compare(bookmark.name()) && this->url()==bookmark.url())
        //if(QString::compare(bookmark.name(),bookmark2->name()))
         //   if( bookmark.url()==bookmark2->url())
        if(this->name().compare(bookmark.name()))
               if(this->url()==bookmark.url())
            return true;
        return false;
    }*/
    friend bool operator ==(const Bookmark &bookmark1,const Bookmark &bookmark2)
    {
        //if(this->name().compare(bookmark.name()) && this->url()==bookmark.url())
        //if(QString::compare(bookmark.name(),bookmark2->name()))
         //   if( bookmark.url()==bookmark2->url())
        if(bookmark1.mName.compare(bookmark2.mName))
               if(bookmark1.mUrl==bookmark2.mUrl)
            return true;
        return false;
    }
private:
    QString mName;
    QUrl mUrl;
};

#endif // BOOKMARK_H

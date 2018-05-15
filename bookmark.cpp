#include "bookmark.h"

Bookmark::Bookmark()
{

}
Bookmark::Bookmark(const Bookmark & bookmark)
{
    mName=bookmark.mName;
    mUrl=bookmark.mUrl;

}
Bookmark::Bookmark(QString name, QUrl url)
{
    mName=name;
    mUrl=url;
}
QString Bookmark::name()
{
    return mName;
}
QUrl Bookmark::url() const
{
    return mUrl;
}
void Bookmark::read(const QJsonObject &json)
{
    if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("url") && json["url"].isString())
        mUrl = QUrl( json["url"].toString());
}
void Bookmark::write(QJsonObject &json) const
{
    json["name"] = mName;
    json["url"] = mUrl.toDisplayString();
}
bool operator ==(const Bookmark &bookmark1,const Bookmark &bookmark2)
{
    if(bookmark1.mName==bookmark2.mName)
        return true;
    return false;
}

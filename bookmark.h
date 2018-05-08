#ifndef BOOKMARK_H
#define BOOKMARK_H
#include <QJsonObject>
#include <QUrl>

class Bookmark
{
public:
    Bookmark();
    void read(const QJsonObject &json);
    /*if (json.contains("name") && json["name"].isString())
        mName = json["name"].toString();

    if (json.contains("level") && json["level"].isDouble())
        mLevel = json["level"].toInt();

    if (json.contains("classType") && json["classType"].isDouble())
        mClassType = ClassType(json["classType"].toInt());
      */
    void write(QJsonObject &json) const;
    /*
    json["name"] = mName;
    json["level"] = mLevel;
    json["classType"] = mClassType;
    */
private:
    QString mName;
    QUrl mUrl;
};

/*
#include <QJsonObject>
#include <QVector>

#include "character.h"

//! [0]
class Level
{
public:
    Level() = default;
    Level(const QString &name);

    QString name() const;

    QVector<Character> npcs() const;
    void setNpcs(const QVector<Character> &npcs);

    void read(const QJsonObject &json);
    void write(QJsonObject &json) const;

    void print(int indentation = 0) const;
private:
    QString mName;
    QVector<Character> mNpcs;
};*/

#endif // BOOKMARK_H

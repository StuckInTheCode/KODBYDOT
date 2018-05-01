#ifndef HISTORY_H
#define HISTORY_H

#include <QObject>
#include <QList>
#include <QDateTime>
#include <QUrl>

//#include "qzcommon.h"

class QIcon;

class WebView;
class HistoryModel;

class History : public QObject
{
    Q_OBJECT
public:
    History(QObject* parent);

    struct HistoryEntry {
        int id;
        int count;
        QDateTime date;
        QUrl url;
        QString urlString;
        QString title;
    };

    static QString titleCaseLocalizedMonth(int month);

    HistoryModel* model();

    void addHistoryEntry(WebView* view);
    void addHistoryEntry(const QUrl &url, QString title);

    void deleteHistoryEntry(int index);
    void deleteHistoryEntry(const QList<int> &list);
    void deleteHistoryEntry(const QString &url, const QString &title);

    QList<int> indexesFromTimeRange(qint64 start, qint64 end);

    bool urlIsStored(const QString &url);

    QVector<HistoryEntry> mostVisited(int count);

    void clearHistory();
    bool isSaving();
    void setSaving(bool state);

    void loadSettings();

signals:
    void historyEntryAdded(const HistoryEntry &entry);
    void historyEntryDeleted(const HistoryEntry &entry);
    void historyEntryEdited(const HistoryEntry &before, const HistoryEntry &after);

    void resetHistory();

private:
    bool m_isSaving;
    HistoryModel* m_model;
};

typedef History::HistoryEntry HistoryEntry;

// Hint to QVector to use std::realloc on item moving
Q_DECLARE_TYPEINFO(HistoryEntry, Q_MOVABLE_TYPE);

#endif // HISTORY_H

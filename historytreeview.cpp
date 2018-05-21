#include "historytreeview.h"
#include "historymodel.h"
#include "historyitem.h"
#include "browserwindow.h"
#include "browser.h"
#include <QClipboard>
#include <QKeyEvent>
#include <QLineEdit>
#include <QMenu>
#include <QHeaderView>
#include <QSqlQuery>
#include <sqldatabase.h>
HistoryTreeView::HistoryTreeView(QWidget* parent)
    : QTreeView(parent)
    , m_history(0)
    , m_filter(0)
{
    setUniformRowHeights(true);
    setAllColumnsShowFocus(true);
}

void HistoryTreeView::Init(History * history)
{
    m_history=history;
    m_filter=new HistoryFilterModel(m_history->model());
    setModel(m_filter);
}

QUrl HistoryTreeView::selectedUrl() const
{
    const QList<QModelIndex> indexes = selectionModel()->selectedRows();

    if (indexes.count() != 1)
        return QUrl();
    return indexes.at(0).data(HistoryModel::UrlRole).toUrl();
}

void HistoryTreeView::search(const QString &string)
{
    m_filter->setFilterFixedString(string);
}

void HistoryTreeView::removeSelectedItems()
{
    QList<int> list;
    QList<QPersistentModelIndex> topLevelIndexes;

    foreach (const QModelIndex &index, selectedIndexes()) {
        if (index.column() > 0) {
            continue;
        }

        if (index.data(HistoryModel::IsTopLevelRole).toBool()) {
            qint64 start = index.data(HistoryModel::TimestampStartRole).toLongLong();
            qint64 end = index.data(HistoryModel::TimestampEndRole).toLongLong();

            list.append(m_history->indexesFromTimeRange(start, end));

            topLevelIndexes.append(index);
        }
        else {
            int id = index.data(HistoryModel::IdRole).toInt();
            if (!list.contains(id)) {
                list.append(id);
            }
        }
    }

    m_history->deleteHistoryEntry(list);
    m_history->model()->removeTopLevelIndexes(topLevelIndexes);
}

void HistoryTreeView::contextMenuEvent(QContextMenuEvent* event)
{
    emit contextMenuRequested(viewport()->mapToGlobal(event->pos()));
}

void HistoryTreeView::mouseMoveEvent(QMouseEvent* event)
{
    QTreeView::mouseMoveEvent(event);
}

void HistoryTreeView::mousePressEvent(QMouseEvent* event)
{
    QTreeView::mousePressEvent(event);

    if (selectionModel()->selectedRows().count() == 1) {
        QModelIndex index = indexAt(event->pos());
        Qt::MouseButtons buttons = event->buttons();
        Qt::KeyboardModifiers modifiers = event->modifiers();

        if (index.isValid() && !index.data(HistoryModel::IsTopLevelRole).toBool()) {
            const QUrl url = index.data(HistoryModel::UrlRole).toUrl();
            if (buttons == Qt::MiddleButton || (buttons == Qt::LeftButton && modifiers == Qt::ControlModifier)) {
                emit urlCtrlActivated(url);
            }
        }
    }
}

void HistoryTreeView::mouseReleaseEvent(QMouseEvent* event)
{
    QTreeView::mouseReleaseEvent(event);

    if (selectionModel()->selectedRows().count() == 1) {
        QModelIndex index = indexAt(event->pos());

        if (index.isValid() && !index.data(HistoryModel::IsTopLevelRole).toBool()) {
            const QUrl url = index.data(HistoryModel::UrlRole).toUrl();

        }
    }
}

void HistoryTreeView::mouseDoubleClickEvent(QMouseEvent* event)
{
    QTreeView::mouseDoubleClickEvent(event);

    if (selectionModel()->selectedRows().count() == 1) {
        QModelIndex index = indexAt(event->pos());

        if (index.isValid() && !index.data(HistoryModel::IsTopLevelRole).toBool()) {
            const QUrl url = index.data(HistoryModel::UrlRole).toUrl();
            Qt::MouseButtons buttons = event->buttons();
        }
    }
}

void HistoryTreeView::keyPressEvent(QKeyEvent* event)
{
    QTreeView::keyPressEvent(event);

    if (selectionModel()->selectedRows().count() == 1) {
        QModelIndex index = selectionModel()->selectedRows().at(0);
        const QUrl url = index.data(HistoryModel::UrlRole).toUrl();
        const bool isTopLevel = index.data(HistoryModel::IsTopLevelRole).toBool();

        switch (event->key()) {
        case Qt::Key_Return:
        case Qt::Key_Enter:
            if (isTopLevel && (event->modifiers() == Qt::NoModifier || event->modifiers() == Qt::KeypadModifier)) {
                setExpanded(index, !isExpanded(index));
            }
            else {
                Qt::KeyboardModifiers modifiers = event->modifiers();
                if (modifiers == Qt::ControlModifier) {
                    emit urlCtrlActivated(url);
                }
                else if (modifiers == Qt::NoModifier || modifiers == Qt::KeypadModifier) {
                    emit urlActivated(url);
                }
            }
            break;

        case Qt::Key_Delete:
            removeSelectedItems();
            break;
        }
    }
}

void HistoryTreeView::drawRow(QPainter* painter, const QStyleOptionViewItem &options, const QModelIndex &index) const
{
   bool itemTopLevel = index.data(HistoryModel::IsTopLevelRole).toBool();
   bool iconLoaded = !index.data(HistoryModel::IconRole).value<QIcon>().isNull();

   QUrl url = index.data(HistoryModel::UrlRole).toUrl();
   const QByteArray encodedUrl = url.toEncoded();

   QSqlQuery query(SqlDatabase::instance()->database());
   QString str = QString::fromUtf8(encodedUrl);
   query.prepare("SELECT icon FROM icons WHERE url GLOB ? LIMIT 1");
   str.replace('[', QStringLiteral("[["));
   str.replace(']', QStringLiteral("[]]"));
   str.replace(QStringLiteral("[["), QStringLiteral("[[]"));
   str.replace('*', QStringLiteral("[*]"));
   str.replace('?', QStringLiteral("[?]"));
   query.addBindValue(QString("%1*").arg(str));
   query.exec();
   QImage image;
   if (query.next()) {
       image = QImage::fromData(query.value(0).toByteArray());
   }
   QIcon img(QPixmap::fromImage(image));
   if (index.isValid() && !itemTopLevel && !iconLoaded) {
        const QPersistentModelIndex idx = index;
        model()->setData(idx, img, HistoryModel::IconRole);
   }

   QTreeView::drawRow(painter, options, index);
}

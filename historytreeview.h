#ifndef HISTORYTREEVIEW_H
#define HISTORYTREEVIEW_H

#include <QTreeView>

class History;
class HistoryFilterModel;
//class HeaderView;
class QHeaderView;
class HistoryTreeView : public QTreeView
{
    Q_OBJECT
public:
    explicit HistoryTreeView(QWidget* parent = 0);

    QUrl selectedUrl() const;

    QHeaderView* header() const;
    void Init(History * history);
signals:
    // Open url in current tab
    void urlActivated(const QUrl &url);
    // Open url in new tab
    void urlCtrlActivated(const QUrl &url);
    // Context menu signal with point mapped to global
    void contextMenuRequested(const QPoint &point);

public slots:
    void search(const QString &string);
    void removeSelectedItems();

protected:
    void contextMenuEvent(QContextMenuEvent* event);
    void mouseMoveEvent(QMouseEvent* event);
    void mousePressEvent(QMouseEvent* event);
    void mouseReleaseEvent(QMouseEvent* event);
    void mouseDoubleClickEvent(QMouseEvent* event);
    void keyPressEvent(QKeyEvent* event);

    void drawRow(QPainter* painter, const QStyleOptionViewItem &options, const QModelIndex &index) const;

private:
    History* m_history;
    HistoryFilterModel* m_filter;
    QHeaderView* m_header;
};

#endif // HISTORYTREEVIEW_H

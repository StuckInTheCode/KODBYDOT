#include "toolbarsearch.h"
#include "browser.h"
#include <QtCore/QSettings>
#include <QtCore/QUrl>
#include <QtCore/QUrlQuery>

#include <QtWidgets/QCompleter>
#include <QtWidgets/QMenu>
#include <QtCore/QStringListModel>

#include <QWebEngineSettings>

ToolbarSearch::ToolbarSearch(QWidget *parent)
    : QLineEdit(parent)
    , m_maxSavedSearches(10)
    , m_stringListModel(new QStringListModel(this))
{
    connect(this, SIGNAL(returnPressed()), SLOT(searchNow()));
   // setInactiveText(tr("Google"));
    setWhatsThis(tr("Google"));
    setPlaceholderText("Search");
    setClearButtonEnabled(true);
    //setText(tr("Google"));
    //load();
}

ToolbarSearch::~ToolbarSearch()
{
   // m_autosaver->saveIfNeccessary();
}

void ToolbarSearch::save()
{
    /*QSettings settings;
    settings.beginGroup(QLatin1String("toolbarsearch"));
    settings.setValue(QLatin1String("recentSearches"), m_stringListModel->stringList());
    settings.setValue(QLatin1String("maximumSaved"), m_maxSavedSearches);
    settings.endGroup();*/
}

void ToolbarSearch::load()
{
    /*QSettings settings;
    settings.beginGroup(QLatin1String("toolbarsearch"));
    QStringList list = settings.value(QLatin1String("recentSearches")).toStringList();
    m_maxSavedSearches = settings.value(QLatin1String("maximumSaved"), m_maxSavedSearches).toInt();
    m_stringListModel->setStringList(list);
    settings.endGroup();*/
}

void ToolbarSearch::searchNow()
{
    QString searchText = this->text();
    QStringList newList = m_stringListModel->stringList();
    if (newList.contains(searchText))
        newList.removeAt(newList.indexOf(searchText));
    newList.prepend(searchText);
    if (newList.size() >= m_maxSavedSearches)
        newList.removeLast();

    QUrl url(QLatin1String("http://www.google.com/search"));
    QUrlQuery urlQuery;
    urlQuery.addQueryItem(QLatin1String("q"), searchText);
    urlQuery.addQueryItem(QLatin1String("ie"), QLatin1String("UTF-8"));
    urlQuery.addQueryItem(QLatin1String("oe"), QLatin1String("UTF-8"));
    urlQuery.addQueryItem(QLatin1String("client"), QLatin1String("KODBYDOT"));
    url.setQuery(urlQuery);
    emit search(url);
}

void ToolbarSearch::aboutToShowMenu()
{/*
    //lineEdit()->selectAll();
    //QMenu *m = menu();
    //m->clear();
    QStringList list = m_stringListModel->stringList();
    if (list.isEmpty()) {
        //m->addAction(tr("No Recent Searches"));
        return;
    }

    //QAction *recent = m->addAction(tr("Recent Searches"));
    //recent->setEnabled(false);
    for (int i = 0; i < list.count(); ++i) {
        QString text = list.at(i);
        //m->addAction(text)->setData(text);
    }
    //m->addSeparator();
    //m->addAction(tr("Clear Recent Searches"), this, SLOT(clear()));
    */
}

void ToolbarSearch::triggeredMenuAction(QAction *action)
{/*
    QVariant v = action->data();
    if (v.canConvert<QString>()) {
        QString text = v.toString();
        //lineEdit()->setText(text);
        this->setText(text);
        searchNow();
    }
    */
}

void ToolbarSearch::clear()
{
    m_stringListModel->setStringList(QStringList());
}
/*QMenu *ToolbarSearch::menu() const
{
    if (!m_searchButton->m_menu) {
        m_searchButton->m_menu = new QMenu(m_searchButton);
        if (isVisible())
            (const_cast<SearchLineEdit*>(this))->updateGeometries();
    }
    return m_searchButton->m_menu;
}*/

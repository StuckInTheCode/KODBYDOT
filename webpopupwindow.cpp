#include "webpopupwindow.h"

WebPopupWindow::WebPopupWindow(QWebEngineProfile *profile):
    m_urlLineEdit(new QLineEdit(this))
    ,m_favAction(new QAction(this))
    ,m_view(new WebView(this))
{
    setAttribute(Qt::WA_DeleteOnClose);
    setSizePolicy(QSizePolicy::Minimum, QSizePolicy::Minimum);

    QVBoxLayout *layout = new QVBoxLayout;
    layout->setMargin(0);
    setLayout(layout);
    layout->addWidget(m_urlLineEdit);
    layout->addWidget(m_view);

    m_view->setPage(new WebPage(profile, m_view));
    m_view->setFocus();

    m_urlLineEdit->setReadOnly(true);
    m_urlLineEdit->addAction(m_favAction, QLineEdit::LeadingPosition);
    connect(m_view->page(), &WebPage::windowCloseRequested, this, &QWidget::close);
}

WebView *WebPopupWindow::view() const
{
    return m_view;
}

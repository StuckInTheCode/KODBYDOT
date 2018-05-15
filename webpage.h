 #ifndef WEBPAGE_H
#define WEBPAGE_H
#include "ui_sslerror.h"
#include <QWebEnginePage>
#include <QMessageBox>
class QWebEngineCertificateError;
class QWebEngineProfile;
class WebPage : public QWebEnginePage
{
    Q_OBJECT

public:
    WebPage(QWebEngineProfile *profile, QObject *parent = nullptr);
    bool certificateError(const QWebEngineCertificateError &error) override;

};

#endif // WEBPAGE_H

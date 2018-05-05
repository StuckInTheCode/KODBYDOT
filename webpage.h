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
    WebPage(QWebEngineProfile *profile, QObject *parent = nullptr){}
    bool certificateError(const QWebEngineCertificateError &error) override
    {
         QWidget *mainWindow = new QWidget();
         if (error.isOverridable()) {
             QDialog dialog(mainWindow);
             dialog.setModal(true);
             dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
             Ui::SSLError certificateDialog;
             certificateDialog.setupUi(&dialog);
             //certificateDialog.m_iconLabel->setText(QString());
             //QIcon icon(mainWindow->style()->standardIcon(QStyle::SP_MessageBoxWarning, 0, mainWindow));
              //certificateDialog.m_iconLabel->setPixmap(icon.pixmap(32, 32));
                //certificateDialog.m_errorLabel->setText(error.errorDescription());
                dialog.setWindowTitle(tr("Certificate Error"));
                return dialog.exec() == QDialog::Accepted;
            }

            QMessageBox::critical(mainWindow, tr("Certificate Error"), error.errorDescription());
            return false;
    }

};

#endif // WEBPAGE_H

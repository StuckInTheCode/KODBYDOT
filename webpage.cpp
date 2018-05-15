#include "webpage.h"

WebPage::WebPage(QWebEngineProfile *profile, QObject *parent){}

bool WebPage::certificateError(const QWebEngineCertificateError &error)
{
     QWidget *mainWindow = new QWidget();
     if (error.isOverridable()) {
         QDialog dialog(mainWindow);
         dialog.setModal(true);
         dialog.setWindowFlags(dialog.windowFlags() & ~Qt::WindowContextHelpButtonHint);
         Ui::SSLError certificateDialog;
         certificateDialog.setupUi(&dialog);
         dialog.setWindowTitle(tr("Certificate Error"));
          return dialog.exec() == QDialog::Accepted;
        }

        QMessageBox::critical(mainWindow, tr("Certificate Error"), error.errorDescription());
        return false;
}

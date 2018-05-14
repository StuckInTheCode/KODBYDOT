#include "settings.h"

//#include "browserapplication.h"
//#include "browsermainwindow.h"
//#if defined(QWEBENGINEPAGE_SETNETWORKACCESSMANAGER)
#include "cookiejar.h"
//#endif
#include "history.h"
#include "webview.h"

#include <QtCore/QLocale>
#include <QtCore/QSettings>
#include <QtWidgets/QtWidgets>
#include <QtWebEngineWidgets/QtWebEngineWidgets>

Settings::Settings(QWidget *parent)
    : QDialog(parent)
{
    setupUi(this);
    connect(this->m_homeButton,&QPushButton::clicked,[this](){
    QSettings settings;
    settings.beginGroup("Home-Page");
    settings.setValue(QLatin1String("url"), m_homePage->text());
    settings.endGroup();
    }
    );
    loadDefaults();
    loadFromSettings();
}

static QString defaultAcceptLanguage()
{
    const QStringList langs = QLocale().uiLanguages();
    if (langs.isEmpty())
        return QString();
    QString str = langs.first();
    const float qstep = 1.0f / float(langs.count());
    float q = 1.0f - qstep;
    for (int i = 1; i < langs.count(); ++i) {
        str += QStringLiteral(", ") + langs.at(i) + QStringLiteral(";q=") + QString::number(q, 'f', 2);
        q -= qstep;
    }
    return str;
}

void Settings::loadDefaults()
{

}

void Settings::loadFromSettings()
{
    QSettings settings;
    settings.beginGroup("Cookie-Settings");
    this->m_checkCookie->setChecked(settings.value("allowCookies", true).toBool());
    //m_allowCookies = settings.value("allowCookies", true).toBool();
    //m_filterThirdParty = settings.value("filterThirdPartyCookies", false).toBool();
    //m_filterTrackingCookie = settings.value("filterTrackingCookie", false).toBool();
    settings.endGroup();

    settings.beginGroup("Web-Browser-Settings");
    this->m_checkHistory->setChecked(settings.value("allowHistory", true).toBool());
    settings.endGroup();

    //QSettings settings;
    //settings.beginGroup("Web-Browser-Settings");
    //m_globalUserAgent = settings.value("UserAgent", QString()).toString();
    //settings.endGroup();

    settings.beginGroup("User-Agent-Settings");
    this->m_checkUserDomain->setChecked(settings.value("UsePerDomainUA", false).toBool());
    //m_usePerDomainUserAgent = settings.value("UsePerDomainUA", false).toBool();
    //QStringList domainList = settings.value("DomainList", QStringList()).toStringList();
    //QStringList userAgentsList = settings.value("UserAgentsList", QStringList()).toStringList();
    settings.endGroup();

    settings.beginGroup("Home-Page");
    m_homePage->setText(settings.value("url", QString()).toString());
    settings.endGroup();
}

void Settings::saveToSettings()
{
    QSettings settings;
    settings.beginGroup("Cookie-Settings");
    settings.setValue(QLatin1String("allowCookies"), this->m_checkCookie->isChecked());
    //this->m_checkCookie->setChecked(settings.value("allowCookies", true).toBool());
    //m_allowCookies = settings.value("allowCookies", true).toBool();
    //m_filterThirdParty = settings.value("filterThirdPartyCookies", false).toBool();
    //m_filterTrackingCookie = settings.value("filterTrackingCookie", false).toBool();
    settings.endGroup();

    settings.beginGroup("Web-Browser-Settings");
    settings.setValue(QLatin1String("allowHistory"), this->m_checkHistory->isChecked());
    //this->m_checkHistory->setChecked(settings.value("allowHistory", true).toBool());
    //m_isSaving = settings.value("allowHistory", true).toBool();
    settings.endGroup();

    //settings.beginGroup("Web-Browser-Settings");
    //m_globalUserAgent = settings.value("UserAgent", QString()).toString();
    //settings.endGroup();

    settings.beginGroup("User-Agent-Settings");
    settings.setValue(QLatin1String("UsePerDomainUA"), this->m_checkUserDomain->isChecked());
    //this->m_checkUserDomain->setChecked(settings.value("UsePerDomainUA", false).toBool());
    //m_usePerDomainUserAgent = settings.value("UsePerDomainUA", false).toBool();
    //QStringList domainList = settings.value("DomainList", QStringList()).toStringList();
    //QStringList userAgentsList = settings.value("UserAgentsList", QStringList()).toStringList();
    settings.endGroup();

    settings.beginGroup("Home-Page");
    settings.setValue(QLatin1String("url"), m_homePage->text());
    settings.endGroup();
}

void Settings::accept()
{
    saveToSettings();
    QMessageBox::StandardButton button = QMessageBox::warning(this, tr("Notification"),
                                         tr("To install new setting, please, reload the browser"), QMessageBox::Ok);
    QDialog::accept();
}



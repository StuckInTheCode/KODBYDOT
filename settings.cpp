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
    //connect(setHomeToCurrentPageButton, SIGNAL(clicked()), this, SLOT(setHomeToCurrentPage()));
    //connect(standardFontButton, SIGNAL(clicked()), this, SLOT(chooseFont()));
    //connect(fixedFontButton, SIGNAL(clicked()), this, SLOT(chooseFixedFont()));
    //connect(this->buttonBox,&QDialogButtonBox::accepted,this,&Settings::accept());
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

    //QSettings settings;
    settings.beginGroup("Web-Browser-Settings");
    this->m_checkHistory->setChecked(settings.value("allowHistory", true).toBool());
    //m_isSaving = settings.value("allowHistory", true).toBool();
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

   /* QSettings settings;
    settings.beginGroup(QLatin1String("MainWindow"));
    const QString defaultHome = QLatin1String(BrowserMainWindow::defaultHome);
    homeLineEdit->setText(settings.value(QLatin1String("home"), defaultHome).toString());
    settings.endGroup();

    settings.beginGroup(QLatin1String("downloadmanager"));
    QString downloadDirectory = settings.value(QLatin1String("downloadDirectory"), downloadsLocation->text()).toString();
    downloadsLocation->setText(downloadDirectory);
    settings.endGroup();

    settings.beginGroup(QLatin1String("general"));
    openLinksIn->setCurrentIndex(settings.value(QLatin1String("openLinksIn"), openLinksIn->currentIndex()).toInt());

    settings.endGroup();

    // Appearance
    settings.beginGroup(QLatin1String("websettings"));
    fixedFont = qvariant_cast<QFont>(settings.value(QLatin1String("fixedFont"), fixedFont));
    standardFont = qvariant_cast<QFont>(settings.value(QLatin1String("standardFont"), standardFont));

    standardLabel->setText(QString(QLatin1String("%1 %2")).arg(standardFont.family()).arg(standardFont.pointSize()));
    fixedLabel->setText(QString(QLatin1String("%1 %2")).arg(fixedFont.family()).arg(fixedFont.pointSize()));

    enableJavascript->setChecked(settings.value(QLatin1String("enableJavascript"), enableJavascript->isChecked()).toBool());
    enablePlugins->setChecked(settings.value(QLatin1String("enablePlugins"), enablePlugins->isChecked()).toBool());
    userStyleSheet->setPlainText(settings.value(QLatin1String("userStyleSheet")).toString());
    enableScrollAnimator->setChecked(settings.value(QLatin1String("enableScrollAnimator"), enableScrollAnimator->isChecked()).toBool());
    httpUserAgent->setText(settings.value(QLatin1String("httpUserAgent"), httpUserAgent->text()).toString());
    httpAcceptLanguage->setText(settings.value(QLatin1String("httpAcceptLanguage"), httpAcceptLanguage->text()).toString());
    faviconDownloadMode->setCurrentIndex(settings.value(QLatin1String("faviconDownloadMode"), faviconDownloadMode->currentIndex()).toInt());
    settings.endGroup();

    // Privacy
    settings.beginGroup(QLatin1String("cookies"));

    int persistentCookiesPolicy = settings.value(QLatin1String("persistentCookiesPolicy"), sessionCookiesCombo->currentIndex()).toInt();
    sessionCookiesCombo->setCurrentIndex(persistentCookiesPolicy);

    QString pdataPath = settings.value(QLatin1String("persistentDataPath"), persistentDataPath->text()).toString();
    persistentDataPath->setText(pdataPath);

    settings.endGroup();

    // Proxy
    settings.beginGroup(QLatin1String("proxy"));
    proxySupport->setChecked(settings.value(QLatin1String("enabled"), false).toBool());
    proxyType->setCurrentIndex(settings.value(QLatin1String("type"), 0).toInt());
    proxyHostName->setText(settings.value(QLatin1String("hostName")).toString());
    proxyPort->setValue(settings.value(QLatin1String("port"), 1080).toInt());
    proxyUserName->setText(settings.value(QLatin1String("userName")).toString());
    proxyPassword->setText(settings.value(QLatin1String("password")).toString());
    settings.endGroup();*/
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

    //QSettings settings;
    settings.beginGroup("Web-Browser-Settings");
    settings.setValue(QLatin1String("allowHistory"), this->m_checkHistory->isChecked());
    //this->m_checkHistory->setChecked(settings.value("allowHistory", true).toBool());
    //m_isSaving = settings.value("allowHistory", true).toBool();
    settings.endGroup();

    //QSettings settings;
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

    //BrowserApplication::cookieJar()->loadSettings();
    //BrowserApplication::historyManager()->loadSettings();

   /* QSettings settings;
    settings.beginGroup(QLatin1String("MainWindow"));
    settings.setValue(QLatin1String("home"), homeLineEdit->text());
    settings.endGroup();

    settings.beginGroup(QLatin1String("general"));
    settings.setValue(QLatin1String("openLinksIn"), openLinksIn->currentIndex());
    settings.endGroup();

    // Appearance
    settings.beginGroup(QLatin1String("websettings"));
    settings.setValue(QLatin1String("fixedFont"), fixedFont);
    settings.setValue(QLatin1String("standardFont"), standardFont);
    settings.setValue(QLatin1String("enableJavascript"), enableJavascript->isChecked());
    settings.setValue(QLatin1String("enablePlugins"), enablePlugins->isChecked());
    settings.setValue(QLatin1String("enableScrollAnimator"), enableScrollAnimator->isChecked());
    settings.setValue(QLatin1String("userStyleSheet"), userStyleSheet->toPlainText());
    settings.setValue(QLatin1String("httpUserAgent"), httpUserAgent->text());
    settings.setValue(QLatin1String("httpAcceptLanguage"), httpAcceptLanguage->text());
    settings.setValue(QLatin1String("faviconDownloadMode"), faviconDownloadMode->currentIndex());
    settings.endGroup();

    //Privacy
    settings.beginGroup(QLatin1String("cookies"));

    int persistentCookiesPolicy = sessionCookiesCombo->currentIndex();
    settings.setValue(QLatin1String("persistentCookiesPolicy"), persistentCookiesPolicy);

    QString pdataPath = persistentDataPath->text();
    settings.setValue(QLatin1String("persistentDataPath"), pdataPath);

    settings.endGroup();

    BrowserApplication::instance()->loadSettings();
//#if defined(QWEBENGINEPAGE_SETNETWORKACCESSMANAGER)
    BrowserApplication::cookieJar()->loadSettings();
//#endif
    BrowserApplication::historyManager()->loadSettings();*/
}

void Settings::accept()
{
    saveToSettings();
    QDialog::accept();
}



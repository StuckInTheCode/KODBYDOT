QT += core gui
QT += webenginewidgets
CONFIG += c++11

TARGET = KODBYDOT
TEMPLATE = app

# The following define makes your compiler emit warnings if you use
# any feature of Qt which has been marked as deprecated (the exact warnings
# depend on your compiler). Please consult the documentation of the
# deprecated API in order to know how to port your code away from it.
DEFINES += QT_DEPRECATED_WARNINGS

# You can also make your code fail to compile if you use deprecated APIs.
# In order to do so, uncomment the following line.
# You can also select to disable deprecated APIs only up to a certain version of Qt.
DEFINES += QT_DISABLE_DEPRECATED_BEFORE=0x060000    # disables all the APIs deprecated before Qt 6.0.0


SOURCES += \
        main.cpp \
    browser.cpp \
    browserwindow.cpp \
    webview.cpp \
    downloadmanagerwidget.cpp \
    cookiejar.cpp \
    urlinterceptor.cpp \
    securesocketsmanager.cpp \
    cookiemanager.cpp \
    tabbar.cpp \
    history.cpp

HEADERS += \
    browser.h \
    browserwindow.h \
    downloadmanagerwidget.h \
    downloadwidget.h \
    tabwidget.h \
    webpage.h \
    webpopupwindow.h \
    webview.h \
    cookiejar.h \
    urlinterceptor.h \
    securesocketsmanager.h \
    cookiemanager.h \
    tabbar.h \
    history.h

FORMS += \
    window.ui \
    cookiejar.ui \
    cookiemanager.ui \
    cookiedialog.ui \
    search.ui \
    sslerror.ui

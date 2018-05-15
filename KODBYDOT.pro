QT += core gui sql
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
    cookiemanager.cpp \
    history.cpp \
    historymodel.cpp \
    historyitem.cpp \
    sqldatabase.cpp \
    historymanager.cpp \
    historytreeview.cpp \
    toolbarsearch.cpp \
    savepagedialog.cpp \
    settings.cpp \
    bookmarkdialog.cpp \
    bookmark.cpp \
    tabwidget.cpp \
    webpage.cpp \
    webpopupwindow.cpp

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
    cookiemanager.h \
    history.h \
    historymodel.h \
    historyitem.h \
    sqldatabase.h \
    historymanager.h \
    historytreeview.h \
    toolbarsearch.h \
    savepagedialog.h \
    settings.h \
    bookmarkdialog.h \
    bookmark.h

FORMS += \
    cookiejar.ui \
    cookiemanager.ui \
    cookiedialog.ui \
    search.ui \
    sslerror.ui \
    historymanager.ui \
    savepagedialog.ui \
    settings.ui \
    downloadwidget.ui \
    bookmarkdialog.ui \
    bookmark.ui

RESOURCES += \
    resources.qrc

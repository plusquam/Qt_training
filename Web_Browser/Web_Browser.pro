#-------------------------------------------------
#
# Project created by QtCreator 2017-11-20T17:33:56
#
#-------------------------------------------------

QT       += core gui\
            webkitwidgets

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Web_Browser
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    webnavigator.cpp

HEADERS  += mainwindow.h \
    webnavigator.h

FORMS    += mainwindow.ui

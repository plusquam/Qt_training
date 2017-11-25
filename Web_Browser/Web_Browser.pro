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
    zoomdialog.cpp \
    historybrowser.cpp

HEADERS  += mainwindow.h \
    zoomdialog.h \
    historybrowser.h

FORMS    += mainwindow.ui \
    zoomdialog.ui \
    historybrowser.ui

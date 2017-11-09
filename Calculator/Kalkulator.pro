#-------------------------------------------------
#
# Project created by QtCreator 2017-10-23T17:32:33
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = Kalkulator
TEMPLATE = app


SOURCES += main.cpp\
        calculatorinterface.cpp \
    calculator.cpp

HEADERS  += calculatorinterface.h \
    calculator.h

FORMS    += calculatorinterface.ui

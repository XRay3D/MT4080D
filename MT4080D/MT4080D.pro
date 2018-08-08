#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T14:36:09
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MT4080D
TEMPLATE = app

win32:RC_FILE = myapp.rc

include(../MT4080/mt4080.pri)
INCLUDEPATH += ../MT4080

SOURCES += main.cpp\
    mainwindow.cpp

HEADERS  += mainwindow.h

FORMS    += mainwindow.ui

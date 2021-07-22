#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T14:36:09
#
#-------------------------------------------------

QT       += core gui serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MT4080D_AUTO
TEMPLATE = app

include(../MT4080/mt4080.pri)
include(../XrProtokol/XrProtokol.pri)
include(../CommonInterfaces/CommonInterfaces.pri)

INCLUDEPATH += range-v3/include

QMAKE_CXXFLAGS += /std:c++latest

win32:RC_FILE = myapp.rc

SOURCES += \
    chekableTableView/header.cpp \
    chekableTableView/model.cpp \
    chekableTableView/tableview.cpp \
    main.cpp\
    mainwindow.cpp \
    measuringinterface/interface.cpp \
    measuringinterface/relay.cpp \
#    mymodel.cpp \


HEADERS  += \
    chekableTableView/header.h \
    chekableTableView/model.h \
    chekableTableView/tableview.h \
    mainwindow.h \
    measuringinterface/interface.h \
    measuringinterface/relay.h \
#    mymodel.h \


FORMS += mainwindow.ui

DISTFILES += \
    myapp.ico \
    myapp.xcf \
    myapp.rc \
    MT4080D.xlsx

RESOURCES += \
    res.qrc

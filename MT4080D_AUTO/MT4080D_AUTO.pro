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
include(../../MyProtokol/myprotokol.pri)

INCLUDEPATH += ../MT4080

win32:RC_FILE = myapp.rc

SOURCES += \
    main.cpp\
    mainwindow.cpp \
    table.cpp \
    measuringinterface/interface.cpp \
#    measuringinterface/myprotokol.cpp \
    measuringinterface/relay.cpp \
    mymodel.cpp \
    mytable.cpp

HEADERS  += \
    mainwindow.h \
    table.h \
    measuringinterface/common_interfaces.h \
    measuringinterface/interface.h \
#    measuringinterface/myprotokol.h \
    measuringinterface/relay.h \
    mymodel.h \
    mytable.h

FORMS += mainwindow.ui

DISTFILES += \
    myapp.ico \
    myapp.xcf \
    myapp.rc \
    MT4080D.xlsx

RESOURCES += \
    res.qrc

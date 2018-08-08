#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T14:36:09
#
#-------------------------------------------------

QT       += core gui serialport multimedia charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MT4080D_AUTO_TRANS
TEMPLATE = app

win32:RC_FILE = main_icon/myapp.rc

include(../MT4080/mt4080.pri)
INCLUDEPATH += ../MT4080

SOURCES += main.cpp\
	mainwindow.cpp \

HEADERS  += mainwindow.h \

FORMS    += mainwindow.ui

DISTFILES += \
	myapp.ico \
	myapp.xcf \
	myapp.rc \
	MT4080D.xlsx

RESOURCES += \
	res.qrc

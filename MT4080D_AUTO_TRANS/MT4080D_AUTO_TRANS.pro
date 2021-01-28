#-------------------------------------------------
#
# Project created by QtCreator 2016-03-31T14:36:09
#
#-------------------------------------------------

QT += core gui serialport multimedia charts

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = MT4080D_AUTO_TRANS
TEMPLATE = app

CONFIG += c++17
QMAKE_CXXFLAGS += /std:c++latest
QMAKE_CXXFLAGS += /await
DEFINES += __cpp_lib_coroutine

win32:RC_FILE = main_icon/myapp.rc

DESTDIR = $$_PRO_FILE_PWD_/../bin

include(../MT4080/mt4080.pri)
INCLUDEPATH += ../MT4080
INCLUDEPATH += ../../magic_get/include
INCLUDEPATH += C:/local/boost_1_71_0

SOURCES += main.cpp\
        mainwindow.cpp \
        model.cpp \
        transmodel.cpp

HEADERS  += mainwindow.h \
        magicgetruntime.h \
        model.h \
        transmodel.h

FORMS    += mainwindow.ui

DISTFILES += \
	myapp.ico \
	myapp.xcf \
	myapp.rc \
	MT4080D.xlsx

RESOURCES += \
	res.qrc

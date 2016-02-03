#-------------------------------------------------
#
# Project created by QtCreator 2014-02-07T17:15:48
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = NetworkServer
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    networkserver.cpp \
    requestprocessor.cpp \
    globalresources.cpp

HEADERS  += mainwindow.h \
    networkserver.h \
    requestprocessor.h \
    globalresources.h

FORMS    += mainwindow.ui

RESOURCES += \
    Myresources.qrc

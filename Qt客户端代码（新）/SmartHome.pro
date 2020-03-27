#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T14:58:03
#
#-------------------------------------------------

QT       += core gui
QT       +=network
QT       += multimedia
QT       +=multimediawidgets


greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    registerwindow.cpp \
    tcpsocket.cpp \
    severaddress.cpp \
    userinformation.cpp \
    protol.cpp \
    mainwindow.cpp \
    room.cpp \
    musicwindow.cpp \
    widget.cpp

HEADERS  += loginwindow.h \
    registerwindow.h \
    tcpsocket.h \
    severaddress.h \
    userinformation.h \
    protol.h \
    mainwindow.h \
    room.h \
    musicwindow.h \
    widget.h

FORMS    += loginwindow.ui \
    registerwindow.ui \
    severaddress.ui \
    mainwindow.ui \
    room.ui \
    musicwindow.ui \
    widget.ui

RESOURCES += \
    resources.qrc

SUBDIRS += \
    C:/Users/14331/Desktop/摄像头模块/QT应用程序/CameraHttp/CameraHttp.pro

DISTFILES +=

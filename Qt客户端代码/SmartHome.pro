#-------------------------------------------------
#
# Project created by QtCreator 2019-06-30T14:58:06
#
#-------------------------------------------------

QT       += core gui
QT       += network



greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = SmartHome
TEMPLATE = app


SOURCES += main.cpp\
        loginwindow.cpp \
    registerwindow.cpp \
    tcpsocket.cpp \
    serveraddressdialog.cpp

HEADERS  += loginwindow.h \
    registerwindow.h \
    tcpsocket.h \
    serveraddressdialog.h

FORMS    += loginwindow.ui \
    registerwindow.ui \
    serveraddressdialog.ui

RESOURCES += \
    resources.qrc

QT += core gui multimedia widgets

TARGET = iRadio
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++11

win32: LIBS += -lUser32

SOURCES = src/main.cpp \
          src/mainwindow.cpp

HEADERS = src/mainwindow.h

FORMS = src/mainwindow.ui

RESOURCES = res/resources.qrc

mac: QMAKE_INFO_PLIST = res/Info.plist

#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T11:12:53
#
#-------------------------------------------------

QT   += core widgets printsupport gui xml

CONFIG += debug

TARGET = dastoryboard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        startupmenu.cpp

HEADERS  += mainwindow.h \
    startupmenu.h

FORMS    += mainwindow.ui \
    startupmenu.ui

TRANSLATIONS += \
    lang/dastoryboard_da.ts

RESOURCES += \
    icons.qrc \
    lang.qrc

DISTFILES += \
    icons/lightblue.png \
    icons/lightgray.png \
    icons/lightgreen.png \
    icons/lightred.png \
    lang/dastoryboard_da.ts

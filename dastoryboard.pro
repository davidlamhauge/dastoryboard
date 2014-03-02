#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T11:12:53
#
#-------------------------------------------------

QT   += core gui xml

CONFIG += debug

TARGET = dastoryboard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        sketchpad.cpp \
        penchooser.cpp \
        animatic.cpp \
        dialogs/prefdialog.cpp \
        dialogs/infodialog.cpp \
    textoutput.cpp

HEADERS  += mainwindow.h \
        sketchpad.h \
        penchooser.h \
        animatic.h \
        dialogs/prefdialog.h \
        dialogs/infodialog.h \
    textoutput.h

FORMS    += mainwindow.ui

TRANSLATIONS += \
    lang/dastoryboard_da.ts

RESOURCES += \
    lang.qrc

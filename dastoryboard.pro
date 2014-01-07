#-------------------------------------------------
#
# Project created by QtCreator 2012-12-23T11:12:53
#
#-------------------------------------------------

QT   += core gui xml

TARGET = dastoryboard
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
        sketchpad.cpp \
    penchooser.cpp \
    prefdialog.cpp

HEADERS  += mainwindow.h \
        sketchpad.h \
    penchooser.h \
    prefdialog.h

FORMS    += mainwindow.ui

TRANSLATIONS += \
    lang/dastoryboard_da.ts
RESOURCES += \
    lang.qrc

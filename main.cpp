#include "mainwindow.h"
#include <QApplication>
#include <QTranslator>
#include <QLocale>
#include <QLibraryInfo>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    a.setApplicationName("dastoryboard");

    // a TRANSLATOR for the QT strings
    QTranslator qtTranslator;
    qtTranslator.load("qt_" + QLocale::system().name(),
            QLibraryInfo::location(QLibraryInfo::TranslationsPath));
    a.installTranslator(&qtTranslator);
    // a TRANSLATOR for the text in the program
    QTranslator appTranslator;
    appTranslator.load("lang/dastoryboard_" + QLocale::system().name());
    a.installTranslator(&appTranslator);

    MainWindow w;
    w.showMaximized();

    return a.exec();
}

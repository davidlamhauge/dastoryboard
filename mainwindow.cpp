#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QScreen>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    init();
    ui->setupUi(this);
}

MainWindow::~MainWindow()
{
    // set settings for next session
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("winSize", size());
    qDebug() << settings.value("winsize") << " EXIT";
    settings.setValue("winPos", pos());


    delete ui;
}

void MainWindow::init()
{
    // position where we left it
    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daStoryboard");
    qDebug() << settings.value("winsize") << " INIT";
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());

}

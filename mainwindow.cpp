#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QDir>

#include "startupmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // position where we left it
    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    qDebug() << "scr: " << scr;
    QSettings settings("TeamLamhauge", "daStoryboard");
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());

    init();

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::setupProject);
    connect(ui->btnResetPalette, &QPushButton::clicked, this, &MainWindow::resetPalette);

    ui->gvSketchPad->setEnabled(false);
    ui->btnAddStoryboard->setEnabled(false);
    ui->btnSaveStoryboard->setEnabled(false);
    ui->btnSaveProject->setEnabled(false);
    ui->btnBG->setEnabled(false);
}

MainWindow::~MainWindow()
{
    // set settings for next session
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("winSize", size());
    settings.setValue("winPos", pos());

    delete ui;
}

bool MainWindow::eventFilter(QObject *obj, QEvent *e)
{
    return QWidget::eventFilter(obj, e);
}

void MainWindow::init()
{
}

void MainWindow::setupProject()
{
    QSettings settings("TeamLamhauge", "daStoryboard");
    mStartupMenu = new StartupMenu();
    mStartupMenu->exec();

    mActiveProjectFull = settings.value("project").toString();
    mActiveStoryboardFull = settings.value("scene").toString();
    QStringList a = mActiveStoryboardFull.split("/");
    mActiveProject = a.at(a.size() - 2);
    mActiveStoryboard = a.at(a.size() - 1);

    if (settings.value("project").toString().isEmpty() ||
            settings.value("scene").toString().isEmpty() ||
            !mActiveStoryboardFull.startsWith(mActiveProjectFull))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Works only with Project and Storyboard chosen!\nStoryboard folder must be in Project folder!"));
        msgBox.exec();
    }
    else
    {
        setWindowTitle("daStoryboard - " + mActiveProject);
        ui->labStoryboardInfo->setText(mActiveStoryboard);
        ui->gvSketchPad->setEnabled(true);
        ui->btnAddStoryboard->setEnabled(true);
        ui->btnSaveStoryboard->setEnabled(true);
        ui->btnSaveProject->setEnabled(true);
        loadScene(mActiveStoryboardFull);
    }
}

void MainWindow::resetPalette()
{
    ui->btn0->setStyleSheet(QString("background-color: %1").arg(mLIGHTBLUE.name()));
    ui->lab0->setText(tr("Lighth blue"));
    ui->btn1->setStyleSheet(QString("background-color: %1").arg(mLIGHTGREEN.name()));
    ui->lab1->setText(tr("Lighth green"));
    ui->btn2->setStyleSheet(QString("background-color: %1").arg(mLIGHTRED.name()));
    ui->lab2->setText(tr("Lighth red"));
    ui->btn3->setStyleSheet(QString("background-color: %1").arg(mLIGHTYELLOW.name()));
    ui->lab3->setText(tr("Lighth yellow"));
    ui->btn4->setStyleSheet(QString("background-color: %1").arg(mLIGHTBROWN.name()));
    ui->lab4->setText(tr("Lighth brown"));
    ui->btn5->setStyleSheet(QString("background-color: %1").arg(mLIGHTPURPLE.name()));
    ui->lab5->setText(tr("Lighth purple"));
    ui->btn6->setStyleSheet(QString("background-color: %1").arg(mWHITE.name()));
    ui->lab6->setText(tr("White"));
    ui->btn7->setStyleSheet(QString("background-color: %1").arg(mBLACK.name()));
    ui->lab7->setText(tr("Black"));
    ui->btn8->setStyleSheet(QString("background-color: %1").arg(mLIGHTGRAY.name()));
    ui->lab8->setText(tr("Lighth gray"));
    ui->btn9->setStyleSheet(QString("background-color: %1").arg(mDARKGRAY.name()));
    ui->lab9->setText(tr("Dark gray"));
}

void MainWindow::loadScene(QString scene)
{
    QDir scDir(scene);
    scDir.setNameFilters(QStringList() << "*.png");
    QStringList list = scDir.entryList();
    if (!list.isEmpty())
    {

    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Scene is empty..."));
        msgBox.exec();
    }
}

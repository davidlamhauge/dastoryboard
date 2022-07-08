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

    ui->gvSketchPad->setEnabled(false);
    ui->btnAddStoryboard->setEnabled(false);
    ui->btnSaveStoryboard->setEnabled(false);
    ui->btnSaveProject->setEnabled(false);
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
    mActiveSceneFull = settings.value("scene").toString();
    QStringList a = mActiveSceneFull.split("/");
    qDebug() << a;
    mActiveProject = a.at(a.size() - 2);
    mActiveScene = a.at(a.size() - 1);

    if (settings.value("project").toString().isEmpty() ||
            settings.value("scene").toString().isEmpty() ||
            !mActiveSceneFull.startsWith(mActiveProjectFull))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Works only with Project and Storyboard chosen!\nStoryboard folder must be in Project folder!"));
        msgBox.exec();
    }
    else
    {
        setWindowTitle("daStoryboard - " + mActiveProject);
        ui->labStoryboardInfo->setText(mActiveScene);
        ui->gvSketchPad->setEnabled(true);
        ui->btnAddStoryboard->setEnabled(true);
        ui->btnSaveStoryboard->setEnabled(true);
        ui->btnSaveProject->setEnabled(true);
        loadScene(mActiveSceneFull);
    }
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

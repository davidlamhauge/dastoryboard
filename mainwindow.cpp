#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QDir>
#include <QListWidgetItem>

#include "startupmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // position where we left it
    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daStoryboard");
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());
    qDebug() << "scr: " << scr << " size: " << size() << " pos: " << pos();

    init();

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::setupProject);
    connect(ui->btnResetPal, &QPushButton::clicked, this, &MainWindow::resetPalette);

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
    QList<QColor> colors;
    colors << mLIGHTBLUE << mLIGHTGREEN << mLIGHTRED << mLIGHTYELLOW << mLIGHTBROWN
           << mLIGHTPURPLE << mWHITE << mBLACK << mLIGHTGRAY << mDARKGRAY;
    QStringList txt;
    txt << tr("Lighth blue") << tr("Lighth green") << tr("Lighth red") << tr("Lighth yellow") << tr("Lighth brown")
           << tr("Lighth purple") << tr("White") << tr("Black") << tr("Lighth gray") << tr("Dark gray");
    QListWidgetItem* item;
    ui->lwPalette->clear();
    for (int i = 0; i < 10; i++)
    {
        item = new QListWidgetItem(txt.at(i));
        item->setBackground(QBrush(colors.at(i)));
        int gCol = qGray(colors.at(i).red(), colors.at(i).green(), colors.at(i).blue());
        if (gCol > 127)
            item->setForeground(QBrush(Qt::black));
        else
            item->setForeground(QBrush(Qt::white));
        ui->lwPalette->addItem(item);
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

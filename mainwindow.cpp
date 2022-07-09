#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QDir>
#include <QListWidgetItem>

#include "startupmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    // position where we left it
//    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daStoryboard");
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
//    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());
    move(settings.value("winPos", QPoint(520, 390)).toPoint());

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnLoad, &QPushButton::clicked, this, &MainWindow::setupProject);
    connect(ui->btnResetPal, &QPushButton::clicked, this, &MainWindow::resetPalette);
    connect(ui->btnSavePal, &QPushButton::clicked, this, &MainWindow::savePalette);
    connect(ui->btnLoadPal, &QPushButton::clicked, this, &MainWindow::loadPalette);
    connect(ui->lwPalette, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);

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
    mOrgPalette << mLIGHTBLUE << mLIGHTGREEN << mLIGHTRED << mLIGHTYELLOW << mLIGHTBROWN
           << mLIGHTPURPLE << mWHITE << mBLACK << mLIGHTGRAY << mDARKGRAY;
    mCurPalette = mOrgPalette;
    mActivePaletteList = mPaletteList;

    QSettings settings("TeamLamhauge", "daStoryboard");
    ui->lwPalette->clear();
    QListWidgetItem* item;
    for (int i = 0; i < 10; i++)
    {
        QString s = settings.value("palette/" + QString::number(i), "").toString();
        item = new QListWidgetItem();
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        if (s == "")
        {
            item->setText(mPaletteList.at(i));
            item->setBackground(QBrush(mOrgPalette.at(i)));
            int gCol = qGray(item->background().color().red(), item->background().color().green(), item->background().color().blue());
            if (gCol > 127)
                item->setForeground(QBrush(Qt::black));
            else
                item->setForeground(QBrush(Qt::white));
            ui->lwPalette->addItem(item);
            settings.setValue("palette/" + QString::number(i), QString(QString::number(mOrgPalette.at(i).red()) + "," +
                                                                       QString::number(mOrgPalette.at(i).green()) + "," +
                                                                       QString::number(mOrgPalette.at(i).blue()) + "," +
                                                                       mPaletteList.at(i)));
        }
        else
        {
            QStringList list = s.split(",");
            item->setText(list.at(3));
            QColor color = QColor(list.at(0).toInt(), list.at(1).toInt(), list.at(2).toInt());
            item->setBackground(QBrush(color));
            int gCol = qGray(item->background().color().red(), item->background().color().green(), item->background().color().blue());
            if (gCol > 127)
                item->setForeground(QBrush(Qt::black));
            else
                item->setForeground(QBrush(Qt::white));
            ui->lwPalette->addItem(item);
            settings.setValue("palette/" + QString::number(i),  QString(QString::number(color.red()) + "," +
                                                                        QString::number(color.green()) + "," +
                                                                        QString::number(color.blue()) + "," +
                                                                        mPaletteList.at(i)));
            mActivePaletteList.replace(i, list.at(3));
        }

    }
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
    QDir(mActiveProjectFull).mkdir("misc");

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
    QListWidgetItem* item;
    ui->lwPalette->clear();
    for (int i = 0; i < 10; i++)
    {
        item = new QListWidgetItem(mPaletteList.at(i));
        item->setFlags(item->flags() | Qt::ItemIsEditable);
        item->setBackground(QBrush(mOrgPalette.at(i)));
        int gCol = qGray(mOrgPalette.at(i).red(), mOrgPalette.at(i).green(), mOrgPalette.at(i).blue());
        if (gCol > 127)
            item->setForeground(QBrush(Qt::black));
        else
            item->setForeground(QBrush(Qt::white));
        ui->lwPalette->addItem(item);
    }
}

void MainWindow::savePalette()
{
    QString filename = QFileDialog::getSaveFileName(this,
                                                    tr("Save palette as"),
                                                    "",
                                                    tr("Palette files (*.dpal)"));
    if (filename.isEmpty())
        return;
    else
    {
        QFile file(filename);
        if (!file.open(QIODevice::WriteOnly | QIODevice::Text))
            return;
        QListWidgetItem* item;
        QTextStream out(&file);
        for (int i = 0; i < 10; i++)
        {
            item = ui->lwPalette->item(i);
            QColor color = item->background().color();
            out << QString(QString::number(color.red()) + "," +
                           QString::number(color.green()) + "," +
                           QString::number(color.blue()) + "," +
                           mActivePaletteList.at(i) + "\n");
        }
    }
}

void MainWindow::loadPalette()
{
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Open palette"),
                                                    "",
                                                    tr("Palette files (*.dpal)"));
    if (filename.isEmpty())
        return;

    QFile file(filename);
    if (!file.open(QIODevice::ReadOnly | QIODevice::Text))
        return;

    QTextStream in(&file);
    QSettings settings("TeamLamhauge", "daStoryboard");
    int i = 0;
    while (i < 10)
    {
        QListWidgetItem* item = ui->lwPalette->takeItem(i);
        QString line = in.readLine();
        QStringList list = line.split(",");
        QColor color = QColor(list.at(0).toInt(), list.at(1).toInt(), list.at(2).toInt());
        item->setBackground(QBrush(color));
        int gCol = qGray(item->background().color().red(), item->background().color().green(), item->background().color().blue());
        if (gCol > 127)
            item->setForeground(QBrush(Qt::black));
        else
            item->setForeground(QBrush(Qt::white));
        item->setText(list.at(3));
        ui->lwPalette->insertItem(i, item);
        settings.setValue("palette/" + QString::number(i),  QString(QString::number(color.red()) + "," +
                                                                    QString::number(color.green()) + "," +
                                                                    QString::number(color.blue()) + "," +
                                                                    item->text()));
        mActivePaletteList.replace(i, list.at(3));
        i++;
    }
}

void MainWindow::onItemChanged(QListWidgetItem *item)
{
    int row = ui->lwPalette->currentRow();
    mActivePaletteList.replace(row, item->text());
    QSettings settings("TeamLamhauge", "daStoryboard");
    QColor color = item->background().color();
    settings.setValue("palette/" + QString::number(row),  QString(QString::number(color.red()) + "," +
                                                                  QString::number(color.green()) + "," +
                                                                  QString::number(color.blue()) + "," +
                                                                  mActivePaletteList.at(row)));
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

#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QSettings>
#include <QScreen>
#include <QDebug>
#include <QMessageBox>
#include <QFileDialog>
#include <QColorDialog>
#include <QDir>
#include <QListWidgetItem>
#include <QKeyEvent>
#include <QMouseEvent>
#include <QGraphicsSceneMouseEvent>
#include <QScrollBar>

#include "startupmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    ui->lwPalette->installEventFilter(this);
    mScene->installEventFilter(this);

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
    connect(ui->lwPalette, &QListWidget::currentRowChanged, this, &MainWindow::onCurrentRowChanged);
    connect(ui->sbPenWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onPenWidthChanged);

    ui->gvSketchPad->setEnabled(false);
    ui->btnAddStoryboard->setEnabled(false);
    ui->btnSaveStoryboard->setEnabled(false);
    ui->btnSaveProject->setEnabled(false);

    ui->btnLoadBG->setEnabled(false);
    ui->btnRemoveBG->setEnabled(false);
    ui->btnClearCanvas->setEnabled(false);
    ui->btnAddStoryboardPad->setEnabled(false);
    ui->cbBG->setEnabled(false);
    ui->sbPenWidth->setValue(settings.value("penwidth", 5).toInt());
    ui->gvStoryboard->setStyleSheet("QScrollBar:horizontal { height: 9px; }");
    ui->gvSketchPad->setScene(mScene);
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
    if (obj == ui->lwPalette)
    {
        if (e->type() == QEvent::KeyPress)
        {
            QKeyEvent* k = static_cast<QKeyEvent*>(e);
            if (k->key() == Qt::Key_Space)
            {
                changePaletteColor();
                return true;
            }
        }
    }
    if (obj == mScene)
    {
        QGraphicsSceneMouseEvent* m = static_cast<QGraphicsSceneMouseEvent*>(e);
        if (m->type() == QEvent::GraphicsSceneMousePress && !mPenIsPressed)
        {
            mPenIsPressed = true;
            mPrevPoint = m->scenePos().toPoint();
            mScene->addLine(QLine(m->lastScenePos().toPoint(), m->scenePos().toPoint()), mPen);
            return true;
        }
        else if (m->type() == QEvent::GraphicsSceneMouseMove && mPenIsPressed)
        {
            mNextPoint = m->scenePos().toPoint();
            mScene->addLine(QLine(mPrevPoint, mNextPoint), mPen);
            mPrevPoint = mNextPoint;
            return true;
        }
        else if (m->type() == QEvent::GraphicsSceneMouseRelease && mPenIsPressed)
        {
            mPenIsPressed = false;
            mNextPoint = m->scenePos().toPoint();
            mScene->addLine(QLine(mPrevPoint, mNextPoint), mPen);
            return true;
        }
    }
    return QWidget::eventFilter(obj, e);
}

void MainWindow::init()
{
    mOrgPalette << mLIGHTBLUE << mLIGHTGREEN << mLIGHTRED << mLIGHTYELLOW << mLIGHTBROWN
           << mLIGHTPURPLE << mWHITE << mBLACK << mLIGHTGRAY << mDARKGRAY;
    mCurPalette = mOrgPalette;
    mActivePaletteList = mPaletteList;
    mScene = new QGraphicsScene(ui->gvSketchPad->sceneRect());

    QSettings settings("TeamLamhauge", "daStoryboard");
    mPen.setColor(settings.value("pencolor", QColor(Qt::black)).value<QColor>());
    ui->labPencolor->setText("");
    ui->labPencolor->setStyleSheet("QLabel { background-color : " + mPen.color().name() +  " ; }");
    mPen.setWidth(settings.value("penwidth", 5).toInt());

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
        mActiveProjectFull = settings.value("project").toString();
        mActiveStoryboardFull = settings.value("scene").toString();
        mFps = settings.value("fps", 25).toInt();
        mRatio = settings.value("ratio", "Standard").toString();
        if (mRatio == "Standard")
        {
            ui->gvSketchPad->setFixedSize(800, 600);
            mScene->setSceneRect(0,0,800,600);
            mSceneStoryboard = new QGraphicsScene(0, 0, 200, 150);
        }
        else
        {
            ui->gvSketchPad->setFixedSize(800, 450);
            mScene->setSceneRect(0,0,800,450);
            mSceneStoryboard = new QGraphicsScene(0, 0, 200, 112.5);
        }
        ui->gvStoryboard->setFixedHeight(ui->gvSketchPad->height() / 4 + 10);
        ui->gvStoryboard->setScene(mSceneStoryboard);

        QStringList a = mActiveStoryboardFull.split("/");
        mActiveProject = a.at(a.size() - 2);
        mActiveStoryboard = a.at(a.size() - 1);
        QDir(mActiveProjectFull).mkdir("misc");
        QDir(mActiveProjectFull).mkdir("backup");

        setWindowTitle("daStoryboard - " + mActiveProject);

        ui->labStoryboardInfo->setText(mActiveStoryboard);
        ui->gvSketchPad->setEnabled(true);
        ui->btnAddStoryboard->setEnabled(true);
        ui->btnSaveStoryboard->setEnabled(true);
        ui->btnSaveProject->setEnabled(true);

        ui->btnLoadBG->setEnabled(true);
        ui->btnRemoveBG->setEnabled(true);
        ui->btnClearCanvas->setEnabled(true);
        ui->btnAddStoryboardPad->setEnabled(true);
        ui->cbBG->setEnabled(true);

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

void MainWindow::changePaletteColor()
{
    QListWidgetItem* item = ui->lwPalette->currentItem();
    int i = ui->lwPalette->currentRow();
    QColor color = QColorDialog::getColor();

    if (color.isValid())
    {
        item->setBackground(QBrush(color));
        int gCol = qGray(color.red(), color.green(), color.blue());
        if (gCol > 127)
            item->setForeground(QBrush(Qt::black));
        else
            item->setForeground(QBrush(Qt::white));
        QSettings settings("TeamLamhauge", "daStoryboard");
        settings.setValue("palette/" + QString::number(i),  QString(QString::number(color.red()) + "," +
                                                                    QString::number(color.green()) + "," +
                                                                    QString::number(color.blue()) + "," +
                                                                    item->text()));
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
                           mActivePaletteList.at(i));
            if (i != 9)
                out << "\n";
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
    for (int i = 0; i < 10; i++)
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
    }
}

void MainWindow::onItemChanged(QListWidgetItem *item)
{
    int row = ui->lwPalette->currentRow();
    mActivePaletteList.replace(row, item->text());
    QSettings settings("TeamLamhauge", "daStoryboard");
    QColor color = item->background().color();
    mPen.setColor(color);
    ui->labPencolor->setStyleSheet("QLabel { background-color : " + mPen.color().name() +  " ; }");
    settings.setValue("palette/" + QString::number(row),  QString(QString::number(color.red()) + "," +
                                                                  QString::number(color.green()) + "," +
                                                                  QString::number(color.blue()) + "," +
                                                                  mActivePaletteList.at(row)));
}

void MainWindow::onCurrentRowChanged(int row)
{
    QColor color = ui->lwPalette->item(row)->background().color();
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("pencolor", color);
    mPen.setColor(color);
    ui->labPencolor->setStyleSheet("QLabel { background-color : " + color.name() +  " ; }");
}

void MainWindow::onPenWidthChanged(int w)
{
    mPen.setWidth(w);
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("penwidth", w);
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

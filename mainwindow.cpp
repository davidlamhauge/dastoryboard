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
#include <QGraphicsItem>
#include <QGraphicsLineItem>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QPixmap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>

#include "startupmenu.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    // position where we left it
//    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daStoryboard");
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
//    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());
    move(settings.value("winPos", QPoint(520, 390)).toPoint());

    init();

    ui->lwPalette->installEventFilter(this);
    mScene->installEventFilter(this);

    connect(ui->btnExit, &QPushButton::clicked, this, &MainWindow::close);
    connect(ui->btnLoadProject, &QPushButton::clicked, this, &MainWindow::loadProject);
    connect(ui->btnResetPal, &QPushButton::clicked, this, &MainWindow::resetPalette);
    connect(ui->btnSavePal, &QPushButton::clicked, this, &MainWindow::savePalette);
    connect(ui->btnLoadPal, &QPushButton::clicked, this, &MainWindow::loadPalette);
    connect(ui->btnSaveProject, &QPushButton::clicked, this, &MainWindow::saveProject);
    connect(ui->btnNewProject, &QPushButton::clicked, this, &MainWindow::newProject);
    connect(ui->lwPalette, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
    connect(ui->lwPalette, &QListWidget::currentRowChanged, this, &MainWindow::onPaletteRowChanged);
    connect(ui->twStoryboard, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);
    connect(ui->sbPenWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onPenWidthChanged);
    connect(ui->btnClearCanvas, &QPushButton::clicked, this, &MainWindow::clearCanvas);
    connect(ui->btnClearSelColor, &QPushButton::clicked, this, &MainWindow::clearSelected);
    connect(ui->btnClearButSelColor, &QPushButton::clicked, this, &MainWindow::clearButSelected);
    connect(ui->btnUndo, &QPushButton::clicked, this, &MainWindow::undoLast);
    connect(ui->btnRedo, &QPushButton::clicked, this, &MainWindow::redoLast);
    connect(ui->btnAddStoryboardPad, &QPushButton::clicked, this, &MainWindow::addPad);
    connect(ui->btnRemoveStoryboardPad, &QPushButton::clicked, this, &MainWindow::removePad);

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
            ui->twStoryboard->item(0, mActiveStoryboardPad)->setSelected(false);
            mPenIsPressed = true;
            mPrevPoint = m->scenePos();
            mEntry.first = mScene->items().size();
            return true;
        }
        else if (m->type() == QEvent::GraphicsSceneMouseMove && mPenIsPressed)
        {
            mNextPoint = m->scenePos();
            mScene->addLine(QLineF(mPrevPoint, mNextPoint), mPen);
            mPrevPoint = mNextPoint;
            mNeedSave = true;
            return true;
        }
        else if (m->type() == QEvent::GraphicsSceneMouseRelease && mPenIsPressed)
        {
            mPenIsPressed = false;
            mNextPoint = m->scenePos().toPoint();
            mScene->addLine(QLineF(mPrevPoint, mNextPoint), mPen);
            mEntry.last = mScene->items().size() - 1;
            if (entryList.count() == 10)
                entryList.removeFirst();
            entryList.append(mEntry);
            mNeedSave = true;
            setUndoRedoButtons();
            return true;
        }
    }

    return QWidget::eventFilter(obj, e);
}

void MainWindow::init()
{
    mOrgPalette << mLIGHTBLUE << mLIGHTGREEN << mLIGHTRED << mLIGHTYELLOW << mLIGHTBROWN
           << mLIGHTPURPLE << mBLACK << mLIGHTGRAY << mDARKGRAY << mWHITE ;
    mCurPalette = mOrgPalette;
    mActivePaletteList = mPaletteList;
    mScene = new QGraphicsScene(ui->gvSketchPad->sceneRect());
    ui->twStoryboard->setFixedHeight(190);
    ui->twStoryboard->horizontalHeader()->setFixedHeight(20);
    ui->twStoryboard->setRowHeight(0, 150);
    ui->twStoryboard->setColumnCount(0);

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

void MainWindow::newProject()
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
        mStoryboardPads.clear();
        mDrawingPads.clear();
        mItemRedoList.clear();
        mActiveProjectFull = settings.value("project").toString();
        mActiveStoryboardFull = settings.value("scene").toString();
        mActiveStoryboardPad = 0;
        mFps = settings.value("fps", 25).toInt();
        mRatio = settings.value("ratio", "Standard").toString();
        if (mRatio == "Standard")
        {
            ui->gvSketchPad->setFixedSize(800, 600);
            mScene->setSceneRect(0,0,800,600);
        }
        else
        {
            ui->gvSketchPad->setFixedSize(800, 450);
            mScene->setSceneRect(0,0,800,450);
        }
        QGraphicsScene* sc = new QGraphicsScene;
        copyFrom_mScene(sc);
        mDrawingPads.append(sc);

        ui->twStoryboard->setRowHeight(0, ui->gvSketchPad->height() / 4  + 20);
        ui->twStoryboard->setColumnCount(mDrawingPads.size());

        QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
        QDir(mActiveStoryboardFull).mkdir("backup");
        if (!pix.isNull())
        {
            pix = pix.scaledToWidth(200);
            QFile file(mActiveStoryboardFull + "/" + QString::number(mActiveStoryboardPad) + ".png");
            file.open(QIODevice::WriteOnly);
            pix.save(&file, "PNG");
            file.close();
            QIcon icon(mActiveProjectFull + QString::number(mActiveStoryboardPad) + ".png");
            mStoryboardPads.append(pix);
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setIcon(icon);
            ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
        }

        QStringList a = mActiveStoryboardFull.split("/");
        mActiveProject = a.at(a.size() - 2);
        mActiveStoryboard = a.at(a.size() - 1);

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

        updateTimer = new QTimer(this);
        connect(updateTimer, &QTimer::timeout, this, QOverload<>::of(&MainWindow::updateStoryboard));
        updateTimer->start(3000);
        loadProject();
    }
}

void MainWindow::addPad()
{
    // first copy active pad from mScene
    QGraphicsScene* scene = mDrawingPads.at(mActiveStoryboardPad);
    copyFrom_mScene(scene);

    // then add new scene and column and make ready
    QGraphicsScene* sceneNew = new QGraphicsScene;
    mDrawingPads.append(sceneNew);
    ui->twStoryboard->setColumnCount(mDrawingPads.size());

    // then save new, empty pixmap to file
    mScene->clear();
    mActiveStoryboardPad += 1;
    QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
    if (!pix.isNull())
    {
        pix = pix.scaledToWidth(200);
        QFile file(mActiveStoryboardFull + "/" + QString::number(mActiveStoryboardPad) + ".png");
        file.open(QIODevice::WriteOnly);
        pix.save(&file, "PNG");
        file.close();
        QIcon icon(mActiveProjectFull + QString::number(mActiveStoryboardPad) + ".png");
        mStoryboardPads.append(pix);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setIcon(icon);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
    }
    entryList.clear();
}

void MainWindow::removePad()
{
    if (1 == 1)
    {

    }
}

void MainWindow::swapPads(int active, int neighbor)
{

}

void MainWindow::onCellClicked(int row, int column)
{
    Q_UNUSED(row);
    if (mNeedSave)
        updateStoryboard();
    if (column != mActiveStoryboardPad)
    {
        copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));
        copyTo_mScene(mDrawingPads.at(column));
        mActiveStoryboardPad = column;
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
    if (ui->lwPalette->currentRow() == 9)
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Eraser can't be changed! Only the width..."));
        msgBox.exec();
    }
    else
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
            mCurPalette.replace(i, color);
        }
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

void MainWindow::onPaletteRowChanged(int row)
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

void MainWindow::loadProject()
{
    updateTimer->stop();

    QDir scDir("");
    scDir.setNameFilters(QStringList() << "*.png");
    QStringList list = scDir.entryList();
    if (!list.isEmpty())
    {

    }
    else
    {
    }
    updateTimer->start(1000);
}

void MainWindow::saveProject()
{
    updateTimer->stop();
    // first copy active pad from mScene
    copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));

    QString filePath = mActiveProjectFull + "/" + mActiveProject + ".dsb";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {

        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);
        stream.setAutoFormattingIndent(2);

        // start dokument
        stream.writeStartDocument();

        // 'info' is basic information about the project
        stream.writeStartElement("info");
        stream.writeTextElement("project_name", mActiveProject);
        stream.writeTextElement("project_path", mActiveProjectFull);
        stream.writeEndElement();

        // '
        QDir scDir(mActiveProjectFull); // get storyboards
        scDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        QStringList list = scDir.entryList();
        for(int i = 0; i < list.size();i++)
        {
            QString s = list.at(i);
            stream.writeStartElement(s);

            for (int j = 0; j < mDrawingPads.size(); j++)
            {
                stream.writeStartElement(QString::number(j));
                QList<QGraphicsItem*> items = mDrawingPads.at(j)->items();
                for (int k = 0; k < items.size(); k++)
                {
                    if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(k)))
                    {
                        stream.writeStartElement(QString::number(k));
                        stream.writeTextElement("p1x", QString::number( line->line().p1().x()));
                        stream.writeTextElement("p1y", QString::number( line->line().p1().y()));
                        stream.writeTextElement("p2x", QString::number( line->line().p2().x()));
                        stream.writeTextElement("p2x", QString::number( line->line().p2().y()));
                        stream.writeTextElement("rgb", QString::number( line->pen().color().rgb()));
                        stream.writeEndElement();
                    }
                }
                stream.writeEndElement();
            }
            stream.writeEndElement();
        }
        stream.writeEndDocument();
        copyTo_mScene(mDrawingPads.at(mActiveStoryboardPad));
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Couldn't open file...."));
        msgBox.exec();
    }
    updateTimer->start(1000);
}

void MainWindow::updateStoryboard()
{
    QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
    if (!pix.isNull()) // () && mNeedSave)
    {
        mNeedSave = false;
        pix = pix.scaledToWidth(200);
        mStoryboardPads.replace(mActiveStoryboardPad, pix);
        QFile file(mActiveStoryboardFull + "/" + QString::number(mActiveStoryboardPad) + ".png");
        file.open(QIODevice::WriteOnly);
        pix.save(&file, "PNG");
        file.close();

        QIcon icon(mActiveStoryboardFull + "/"  + QString::number(mActiveStoryboardPad) + ".png");
        QTableWidgetItem* item = ui->twStoryboard->takeItem(0, mActiveStoryboardPad);
        item->setIcon(icon);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
        updateTimer->start(1000);
    }
}

void MainWindow::copyFrom_mScene(QGraphicsScene *scene)
{
    qDebug() << "START Mscene items " << mScene->items().size() << " scene items: " << scene->items().count();
    scene->clear();
    QList<QGraphicsItem*> items = mScene->items();
    for (int i = 0; i < items.size(); i++)
        if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i)))
            scene->addItem(line);
    qDebug() << "DONE  Mscene items " << mScene->items().size() << " scene items: " << scene->items().count();
}

void MainWindow::copyTo_mScene(QGraphicsScene *scene)
{
    mScene->clear();
    QList<QGraphicsItem*> items = scene->items();
    for (int i = 0; i < items.size(); i++)
        if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i)))
            mScene->addItem(line);
}

void MainWindow::clearCanvas()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Are you sure? Can not be undone..."));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok)
    {
        mScene->clear();
        entryList.clear();
        redoEntryList.clear();
        setUndoRedoButtons();
    }
}

void MainWindow::clearSelected()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Are you sure? Can not be undone..."));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok)
    {
        QColor col = mPen.color();
        QList<QGraphicsItem*> items = mScene->items();
        for (int i = 0; i < items.size(); i++)
        {
            if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i)))
            {
                if (line->pen().color() == col)
                    mScene->removeItem(line);
            }
        }
        entryList.clear();
        redoEntryList.clear();
        setUndoRedoButtons();
    }
}

void MainWindow::clearButSelected()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Are you sure? Can not be undone..."));
    msgBox.setStandardButtons(QMessageBox::Cancel | QMessageBox::Ok);
    msgBox.setDefaultButton(QMessageBox::Cancel);
    int ret = msgBox.exec();
    if (ret == QMessageBox::Ok)
    {
        QColor col = mPen.color();
        QList<QGraphicsItem*> items = mScene->items();
        for (int i = 0; i < items.size(); i++)
        {
            if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i)))
            {
                if (line->pen().color() != col)
                    mScene->removeItem(line);
            }
        }
        entryList.clear();
        redoEntryList.clear();
        setUndoRedoButtons();
    }
}

void MainWindow::undoLast()
{
    if (!entryList.isEmpty())
    {
        QList<QGraphicsItem*> items = mScene->items(Qt::AscendingOrder);
        mEntry = entryList.takeLast();
        mRedoEntry.first = mItemRedoList.size();
        for (int i = mEntry.last; i >= mEntry.first; i--)
        {
            if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i)))
            {
                mItemRedoList.append(line);
                mScene->removeItem(line);
            }
        }
        mRedoEntry.last = mItemRedoList.size() - 1;
        redoEntryList.append(mRedoEntry);
        setUndoRedoButtons();
    }
}

void MainWindow::redoLast()
{
    if (!redoEntryList.isEmpty())
    {
        mRedoEntry = redoEntryList.takeLast();
        mEntry.first = mScene->items().size();
        for (int i = mRedoEntry.last; i >= mRedoEntry.first; i--)
        {
            if (QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(mItemRedoList.takeLast()))
            {
                mScene->addLine(line->line(), line->pen());
            }
        }
        mEntry.last = mScene->items().size() -1;
        entryList.append(mEntry);
        setUndoRedoButtons();
    }
}

void MainWindow::setUndoRedoButtons()
{
    if (entryList.isEmpty())
        ui->btnUndo->setEnabled(false);
    else
        ui->btnUndo->setEnabled(true);
    if (redoEntryList.isEmpty())
        ui->btnRedo->setEnabled(false);
    else
        ui->btnRedo->setEnabled(true);
}

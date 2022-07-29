#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QAction>
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
#include <QGraphicsPixmapItem>
#include <QTableWidgetItem>
#include <QScrollBar>
#include <QPixmap>
#include <QXmlStreamWriter>
#include <QXmlStreamReader>
#include <QDomDocument>

#include <QElapsedTimer>
#include <QTimer>

#include "startupmenu.h"
#include "preferencemanager.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    init();

    // position where we left it
    QSize scr = QGuiApplication::primaryScreen()->availableSize();
    QSettings settings("TeamLamhauge", "daStoryboard");
    resize(settings.value("winSize", QSize(1040, 780)).toSize());
    move(settings.value("winPos", QPoint(scr.width()/2 - 1040/2, scr.height()/2 - 780/2)).toPoint());

    ui->lwPalette->installEventFilter(this);
    mScene->installEventFilter(this);

    mAutoSaveTimer = new QTimer(this);
    int interval = settings.value("autosaveInterval", 2).toInt() * 60 * 1000;
    mAutoSaveTimer->setInterval(interval);
    connect(mAutoSaveTimer, &QTimer::timeout, this, &MainWindow::autoSaveInvoked);

    // menu 'file'...
    connect(ui->actionOpen_project, &QAction::triggered, this, &MainWindow::loadProject);
    connect(ui->actionSave_Project, &QAction::triggered, this, &MainWindow::saveProject);
    connect(ui->actionNew_project, &QAction::triggered, this, &MainWindow::newProject);
    connect(ui->actionPreferences, &QAction::triggered, this, &MainWindow::setPreferences);
    connect(ui->actionExit, &QAction::triggered, this, &MainWindow::close);

    // menu 'edit'...
    connect(ui->actionUndo, &QAction::triggered, this, &MainWindow::undoLast);
    connect(ui->actionRedo, &QAction::triggered, this, &MainWindow::redoLast);
    connect(ui->actionClear_Pad, &QAction::triggered, this, &MainWindow::clearCanvas);
    connect(ui->actionClear_selected_color, &QAction::triggered, this, &MainWindow::clearSelected);
    connect(ui->actionKeep_only_selected_color, &QAction::triggered, this, &MainWindow::clearButSelected);

    // menu 'storyboard'...
    connect(ui->actionAdd_Pad, &QAction::triggered, this, &MainWindow::addPad);
    connect(ui->actionRemove_Pad, &QAction::triggered, this, &MainWindow::removePad);
    connect(ui->actionInsert_Pad, &QAction::triggered, this, &MainWindow::insertPad);
    connect(ui->actionMove_Pad_back, &QAction::triggered, this, &MainWindow::movePadLeft);
    connect(ui->actionMove_Pad_forward, &QAction::triggered, this, &MainWindow::movePadRight);
    connect(ui->actionLoad_Background, &QAction::triggered, this, &MainWindow::loadBackground);
    connect(ui->actionRemove_Background, &QAction::triggered, this, &MainWindow::removeBackground);
    connect(ui->actionHide_Background, &QAction::triggered, this, &MainWindow::hideBackground);
    ui->actionLoad_Background->setEnabled(false);
    ui->actionRemove_Background->setEnabled(false);
    ui->actionHide_Background->setEnabled(false);
    ui->actionToggle_overlay->setEnabled(false);

    // menu 'palette'...
    connect(ui->actionSave_palette, &QAction::triggered, this, &MainWindow::savePalette);
    connect(ui->actionLoad_palette, &QAction::triggered, this, &MainWindow::loadPalette);
    connect(ui->actionReset_Palette, &QAction::triggered, this, &MainWindow::resetPalette);

    // other signals...
    connect(ui->lwPalette, &QListWidget::itemChanged, this, &MainWindow::onItemChanged);
    connect(ui->lwPalette, &QListWidget::currentRowChanged, this, &MainWindow::onPaletteRowChanged);
    connect(ui->twStoryboard, &QTableWidget::cellClicked, this, &MainWindow::onCellClicked);
    connect(ui->sbPenWidth, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onPenWidthChanged);
    connect(ui->sbFrames, QOverload<int>::of(&QSpinBox::valueChanged), this, &MainWindow::onTimingChanged);

    connect(ui->leDialogue, &QLineEdit::textChanged, this, &MainWindow::updateDialogue);
    connect(ui->leAction, &QLineEdit::textChanged, this, &MainWindow::updateAction);
    connect(ui->leSlug, &QLineEdit::textChanged, this, &MainWindow::updateSlug);


    ui->gvSketchPad->setEnabled(false);

    ui->sbPenWidth->setValue(settings.value("penwidth", 5).toInt());
    ui->gvSketchPad->setScene(mScene);

    mPrefs = new PreferenceManager();
    int loadLast = settings.value("loadLast", 0).toInt();
    if (loadLast == 2)
    {
        QString fileName = settings.value("project", "").toString();
        QString pName = settings.value("project_folder", "").toString();
        settings.setValue("lastProjPath", fileName);
        fileName = fileName + "/" + pName + ".dsb";
        if (QFile::exists(fileName))
            autoLoad(fileName);
    }
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
            return true;
        }
        else if (m->type() == QEvent::GraphicsSceneMouseRelease && mPenIsPressed)
        {
            mPenIsPressed = false;
            mNeedSave = true;
            mNextPoint = m->scenePos().toPoint();
            mScene->addLine(QLineF(mPrevPoint, mNextPoint), mPen);
            mEntry.last = mScene->items().size() - 1;
            if (entryList.count() == 10)
                entryList.removeFirst();
            entryList.append(mEntry);
            updateStoryboard();
            return true;
        }
    }

    return QWidget::eventFilter(obj, e);
}

void MainWindow::init()
{
    mOrgPalette << mWHITE  << mLIGHTBLUE << mLIGHTGREEN << mLIGHTRED << mLIGHTYELLOW
                << mLIGHTBROWN << mLIGHTPURPLE << mBLACK << mLIGHTGRAY << mDARKGRAY;
    mCurPalette = mOrgPalette;
    mActivePaletteList = mPaletteList;
    mScene = new QGraphicsScene(ui->gvSketchPad->sceneRect());
    ui->twStoryboard->setFixedHeight(190);
    ui->twStoryboard->horizontalHeader()->setFixedHeight(20);
    ui->twStoryboard->setRowHeight(0, 150);
    ui->twStoryboard->setColumnCount(0);
    mActiveComments.d = ui->leDialogue->text();
    mActiveComments.a = ui->leAction->text();
    mActiveComments.s = ui->leSlug->text();
    commentList.append(mActiveComments);

    QSettings settings("TeamLamhauge", "daStoryboard");
    mLastProjPath = settings.value("lastProjPath", "").toString();
    mAutosave = settings.value("autosave", false).toBool();

    mPen.setColor(settings.value("pencolor", QColor(Qt::black)).value<QColor>());
    ui->labPencolor->setText("");
    ui->labPencolor->setStyleSheet("QLabel { background-color : " + mPen.color().name() +  " ; }");
    mPen.setWidth(settings.value("penwidth", 5).toInt());
    ui->labPencolor->setFixedHeight(mPen.width());

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
            settings.value("storyboard").toString().isEmpty() ||
            !mActiveStoryboardFull.startsWith(mActiveProjectFull))
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Works only with Project and Storyboard chosen!\nStoryboard folder must be in Project folder!"));
        msgBox.exec();
    }
    else
    {
        mScene->clear();
        mStoryboardPads.clear();
        mDrawingPads.clear();
        mTiming.clear();
        mItemRedoList.clear();
        mActiveProjectFull = settings.value("project").toString();
        mActiveStoryboardFull = settings.value("storyboard").toString();
        QStringList a = mActiveStoryboardFull.split("/");
        mActiveProject = a.at(a.size() - 2);
        settings.setValue("project_folder", mActiveProject);
        mActiveStoryboard = a.at(a.size() - 1);
        ui->cbStoryboards->addItem(mActiveStoryboard);
        QDir dir(mActiveStoryboardFull);
        dir.mkdir(mActiveStoryboardFull + "/" + "backup");
        dir.mkdir(mActiveStoryboardFull + "/" + "bg");
        dir.mkdir(mActiveStoryboardFull + "/" + "misc");

        setWindowTitle("daStoryboard - " + mActiveProject);

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
        mTiming.append(ui->sbFrames->value());

        ui->leDialogue->clear();
        ui->leAction->clear();
        ui->leSlug->clear();
        mActiveComments.d = ui->leDialogue->text();
        mActiveComments.a = ui->leAction->text();
        mActiveComments.s = ui->leSlug->text();
        commentList.append(mActiveComments);

        ui->twStoryboard->setRowHeight(0, ui->gvSketchPad->height() / 4  + 20);
        ui->twStoryboard->setColumnCount(mDrawingPads.size());

        QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
        if (!pix.isNull())
        {
            pix = pix.scaledToWidth(200);
            QIcon icon(pix);
            mStoryboardPads.append(pix);
            QTableWidgetItem* item = new QTableWidgetItem();
            item->setIcon(icon);
            ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
        }

        ui->labStoryboardInfo->setText(mActiveStoryboard);
        ui->gvSketchPad->setEnabled(true);
    }
    if (mAutosave)
        mAutoSaveTimer->start();
}

void MainWindow::loadProject()
{
        QString fileName = QFileDialog::getOpenFileName(this,
                                                tr("Open project file"),
                                                mLastProjPath,
                                                tr("Project Files (*.dsb)"));
        autoLoad(fileName);
}

void MainWindow::autoLoad(QString fileName)
{
    QElapsedTimer* timer = new QElapsedTimer;
    timer->start();
    QSettings settings("TeamLamhauge", "daStoryboard");
    QFile file(fileName);
    if (file.open(QIODevice::ReadOnly | QFile::Text))
    {
        // reset local vars
        mStoryboardPads.clear();
        mDrawingPads.clear();
        mTiming.clear();
        mItemRedoList.clear();
        ui->gvSketchPad->setEnabled(true);

        // start DOM gymnastics...
        QDomDocument doc;
        doc.setContent(&file);
        file.close();
        QDomElement root = doc.documentElement();

        // first load info
        QDomNode n = root.firstChild();
        if (n.nodeName() == "info")
        {
            QDomElement e = n.toElement();

            mActiveProject = e.attribute("project_name");
            mActiveProjectFull = e.attribute("project_path");
            settings.setValue("lastProjPath", mActiveProjectFull);
            int width = e.attribute("pad_width").toInt();
            int height = e.attribute("pad_height").toInt();
            mScene->setSceneRect(0, 0, width, height);

            if (height == 600)
                settings.setValue("ratio", "Standard");
            else
                settings.setValue("ratio", "HD");

            mRatio = settings.value("ratio", "Standard").toString();
            if (mRatio == "Standard")
                ui->gvSketchPad->setFixedSize(800, 600);
            else
                ui->gvSketchPad->setFixedSize(800, 450);


        }

        // now load palette

        QDomNode pal = n.nextSibling();
        QDomNode col = pal.firstChild();
        while (!col.isNull())
        {
            QDomElement colEle = col.toElement();
            int pos = colEle.attribute("pos").toInt();
            int rgb = colEle.attribute("col").toUInt();
            QString s = colEle.attribute("text");
            QListWidgetItem* item = ui->lwPalette->takeItem(pos);
            item->setBackground(QColor::fromRgb(rgb));
            item->setText(s);
            ui->lwPalette->insertItem(pos, item);

            col = col.nextSibling();
        }

        // now load Storyboards...
        QDomNode stb = pal.nextSibling();
        while (!stb.isNull())
        {   // in "storyboard"
            QDomElement stbEle = stb.toElement();
            int pads = stbEle.attribute("padCount").toInt();
            mActiveStoryboard = stbEle.attribute("folder", "");
            mActiveStoryboardFull = mActiveProjectFull + "/" + mActiveStoryboard;
            for (int i = 0; i < pads; i++)
            {
                QGraphicsScene* scene = new QGraphicsScene();
                scene->setSceneRect(QRectF(0, 0, mScene->width(), mScene->height()));
                mDrawingPads.append(scene);
            }
            ui->twStoryboard->clear();
            ui->twStoryboard->setColumnCount(pads);

            // now load pads
            QDomNode pad = stb.firstChild();
            mActiveStoryboardPad = -1;
            commentList.clear();
            while (!pad.isNull())
            {   // in "pad"
                QDomElement padEle = pad.toElement();
                mActiveStoryboardPad++;
                mScene->clear();
                int timing = padEle.attribute("timing").toInt();
                mTiming.append(timing);
                mActiveComments.d = padEle.attribute("dial");
                mActiveComments.a = padEle.attribute("action");
                mActiveComments.s = padEle.attribute("slug");
                commentList.append(mActiveComments);

                // now load lines that make up the drawing
                QDomNode line = pad.firstChild();
                while (!line.isNull())
                {   // in "line"
                    QDomElement linesEle = line.toElement();
                    int p1x = linesEle.attribute("p1x").toInt();
                    int p1y = linesEle.attribute("p1y").toInt();
                    int p2x = linesEle.attribute("p2x").toInt();
                    int p2y = linesEle.attribute("p2y").toInt();
                    int rgb = linesEle.attribute("rgb").toUInt();
                    int w = linesEle.attribute("width").toInt();
                    int z = linesEle.attribute("z", 0).toInt();
                    if (z == 0)
                    {
                        QColor col = QColor::fromRgb(rgb);
                        mPen.setColor(col);
                        mPen.setWidth(w);
                        mScene->addLine(p1x, p1y, p2x, p2y, mPen);
                    }
                    else if (z == -1)
                    {

                    }

                    line = line.nextSibling();
                }
                QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
                mStoryboardPads.append(pix);
                pix = pix.scaledToWidth(200);
                QIcon icon(pix);
                QTableWidgetItem* item = new QTableWidgetItem();
                item->setIcon(icon);
                ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
                copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));

                pad = pad.nextSibling();
            }
            // are there more storyboards?
            stb = stb.nextSibling();
        }

    }

    updateTimingLabel();
    updateCommentLineEdits(mActiveComments);

    ui->labStoryboardInfo->setText(mActiveStoryboard);
    ui->cbStoryboards->addItem(mActiveStoryboard);
    qDebug() << "ms load: " << timer->elapsed();
    if (mAutosave)
        mAutoSaveTimer->start();
}

void MainWindow::autoSaveInvoked()
{
    if (mNeedSave && mAutosave)
    {
        saveProject();
        QSettings settings("TeamLamhauge", "daStoryboard");
        int interval = settings.value("autosaveInterval", 2).toInt() * 60 * 1000;
        mAutoSaveTimer->stop();
        mAutoSaveTimer->setInterval(interval);
        mAutoSaveTimer->start();
        mNeedSave = false;
    }
}

void MainWindow::saveProject()
{
    QElapsedTimer* timer = new QElapsedTimer;
    timer->start();
    // first copy active pad from mScene
    copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));

    QString filePath = mActiveProjectFull + "/" + mActiveProject + ".dsb";
    QFile file(filePath);
    if (file.open(QIODevice::WriteOnly))
    {

        QXmlStreamWriter stream(&file);
        stream.setAutoFormatting(true);

        // start dokument
        stream.writeStartDocument();

        // Main tag
        stream.writeStartElement("project");

        // 'info' is basic information about the project
        stream.writeStartElement("info");
        stream.writeAttribute("project_name", mActiveProject);
        stream.writeAttribute("project_path", mActiveProjectFull);
        stream.writeAttribute("pad_width", QString::number(mScene->width()));
        stream.writeAttribute("pad_height", QString::number(mScene->height()));
        stream.writeEndElement();

        // 'palette' will be the start tag for the palette
        stream.writeStartElement("palette");

        // 'color' will be the start tag for each palette color
        QListWidgetItem* item;
        for (int i = 0; i < 10; i++)
        {
            stream.writeStartElement("color");
            item = ui->lwPalette->item(i);
            stream.writeAttribute("pos", QString::number(i));
            stream.writeAttribute("col", QString::number(item->background().color().rgb()));
            stream.writeAttribute("text", item->text());
            stream.writeEndElement(); // for color
        }

        stream.writeEndElement(); // for palette

        // 'storyboard' will be start tag for each storyboard
        QDir scDir(mActiveProjectFull); // get storyboards
        scDir.setFilter(QDir::AllDirs | QDir::NoDotAndDotDot);
        QStringList list = scDir.entryList();
        for(int i = 0; i < list.size();i++)
        {
            QString s = list.at(i);
            stream.writeStartElement("storyboard");
            stream.writeAttribute("padCount", QString::number(mDrawingPads.size()));
            stream.writeAttribute("folder", s);

            for (int j = 0; j < mDrawingPads.size(); j++)
            {
                stream.writeStartElement("pad");
                QList<QGraphicsItem*> items = mDrawingPads.at(j)->items();
                stream.writeAttribute("timing", QString::number(mTiming.at(j)));
                mActiveComments = commentList.at(j);
                stream.writeAttribute("dial", mActiveComments.d);
                stream.writeAttribute("action", mActiveComments.a);
                stream.writeAttribute("slug", mActiveComments.s);
                for (int k = 0; k < items.size(); k++)
                {
                    if (items.at(k)->zValue() == 0)
                    {
                        QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(k));
                        stream.writeStartElement("item");
                        stream.writeAttribute("p1x", QString::number( line->line().p1().x()));
                        stream.writeAttribute("p1y", QString::number( line->line().p1().y()));
                        stream.writeAttribute("p2x", QString::number( line->line().p2().x()));
                        stream.writeAttribute("p2y", QString::number( line->line().p2().y()));
                        stream.writeAttribute("rgb", QString::number( line->pen().color().rgb()));
                        stream.writeAttribute("width", QString::number(line->pen().width()));
                        stream.writeEndElement(); // for line item
                    }
                    if (items.at(k)->zValue() == -1)
                    {
                        QGraphicsPixmapItem* pix = static_cast<QGraphicsPixmapItem*>(items.at(k));
                        stream.writeStartElement("item");
                        stream.writeAttribute("z", QString::number(pix->zValue()));
                        stream.writeEndElement(); // for line item
                    }
                }
                stream.writeEndElement(); // for pad
            }
            stream.writeEndElement(); // for storyboard
        }
        stream.writeEndElement(); // for project
        stream.writeEndDocument();
        mActiveComments = commentList.at(mActiveStoryboardPad);
    }
    else
    {
        QMessageBox msgBox;
        msgBox.setText(tr("Couldn't open file...."));
        msgBox.exec();
    }
    mNeedSave = false;
    qDebug() << "ms save: " << timer->elapsed();
}

void MainWindow::addPad()
{
    // first copy active pad from mScene
    QGraphicsScene* scene = mDrawingPads.at(mActiveStoryboardPad);
    copyFrom_mScene(scene);

    // then add new scene and column and make ready
    QGraphicsScene* sceneNew = new QGraphicsScene;
    mDrawingPads.append(sceneNew);
    mActiveStoryboardPad = mDrawingPads.size() - 1;
    ui->twStoryboard->setColumnCount(mDrawingPads.size());
    ui->twStoryboard->setCurrentCell(0, mActiveStoryboardPad);
    mTiming.append(ui->sbFrames->value());
    ui->sbFrames->setValue(50); // resets the value just appended

    ui->leDialogue->clear();
    ui->leAction->clear();
    ui->leSlug->clear();
    mActiveComments.d = ui->leDialogue->text();
    mActiveComments.a = ui->leAction->text();
    mActiveComments.s = ui->leSlug->text();
    commentList.append(mActiveComments);

    // then save new, empty pixmap to file
    mScene->clear();
    QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
    if (!pix.isNull())
    {
        pix = pix.scaledToWidth(200);
        QIcon icon(pix);
        mStoryboardPads.append(pix);
        QTableWidgetItem* item = new QTableWidgetItem();
        item->setIcon(icon);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
    }
    entryList.clear();
    mNeedSave = true;
}

void MainWindow::removePad()
{
    int newPos = 0;
    if (mActiveStoryboardPad == mDrawingPads.size() - 1)
        newPos = mDrawingPads.size() - 1;
    else
        newPos = mActiveStoryboardPad;
    mDrawingPads.remove(mActiveStoryboardPad);
    mActiveComments = commentList.at(newPos);
    updateCommentLineEdits(mActiveComments);
    commentList.removeAt(mActiveStoryboardPad);
    ui->twStoryboard->removeColumn(mActiveStoryboardPad);
    entryList.clear();
    copyTo_mScene(mDrawingPads.at(newPos));
    mNeedSave = true;
}

void MainWindow::insertPad()
{
    copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));
    int tmp = mActiveStoryboardPad;
    int goal = mActiveStoryboardPad + 1;
    addPad();
    mActiveStoryboardPad = tmp;
    if (mActiveStoryboardPad + 2 < mDrawingPads.size()) // if not, it equals append()
    {
        int start = mDrawingPads.size() - 1;
        do
        {
            mDrawingPads.swapItemsAt(start - 1, start);
            copyTo_mScene(mDrawingPads.at(start));
            mActiveStoryboardPad = start;
            updateStoryboard();
            start--;
        } while (goal < start);
        mActiveStoryboardPad = start;
        copyTo_mScene(mDrawingPads.at(start));
        updateStoryboard();
    }
    mNeedSave = true;
}

void MainWindow::movePadLeft()
{
    if (mActiveStoryboardPad > 0)
    {
        QTableWidgetItem* itemA = ui->twStoryboard->takeItem(0, mActiveStoryboardPad - 1);
        QTableWidgetItem* itemZ = ui->twStoryboard->takeItem(0, mActiveStoryboardPad);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, itemA);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad - 1, itemZ);

        mDrawingPads.swapItemsAt(mActiveStoryboardPad - 1, mActiveStoryboardPad);
        mStoryboardPads.swapItemsAt(mActiveStoryboardPad - 1, mActiveStoryboardPad);
        commentList.swapItemsAt(mActiveStoryboardPad - 1, mActiveStoryboardPad);
        mActiveStoryboardPad--;
        copyTo_mScene(mDrawingPads.at(mActiveStoryboardPad));
        ui->twStoryboard->clearSelection();
        ui->twStoryboard->setCurrentCell(0, mActiveStoryboardPad);
    }
    mNeedSave = true;
}

void MainWindow::movePadRight()
{
    if (mActiveStoryboardPad < mDrawingPads.size() - 1)
    {
        QTableWidgetItem* itemA = ui->twStoryboard->takeItem(0, mActiveStoryboardPad + 1);
        QTableWidgetItem* itemZ = ui->twStoryboard->takeItem(0, mActiveStoryboardPad);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, itemA);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad + 1, itemZ);

        mDrawingPads.swapItemsAt(mActiveStoryboardPad, mActiveStoryboardPad + 1);
        mStoryboardPads.swapItemsAt(mActiveStoryboardPad, mActiveStoryboardPad + 1);
        commentList.swapItemsAt(mActiveStoryboardPad, mActiveStoryboardPad + 1);
        mActiveStoryboardPad++;
        copyTo_mScene(mDrawingPads.at(mActiveStoryboardPad));
        ui->twStoryboard->clearSelection();
        ui->twStoryboard->setCurrentCell(0, mActiveStoryboardPad);
    }
    mNeedSave = true;
}

void MainWindow::onCellClicked(int row, int column)
{
    Q_UNUSED(row);
    if (column != mActiveStoryboardPad)
    {
        copyFrom_mScene(mDrawingPads.at(mActiveStoryboardPad));
        copyTo_mScene(mDrawingPads.at(column));
        commentList.replace(mActiveStoryboardPad, mActiveComments);
        mActiveComments = commentList.at(column);
        updateCommentLineEdits(mActiveComments);
        mActiveStoryboardPad = column;
        ui->sbFrames->setValue(mTiming.at(column));
        updateCommentLineEdits(mActiveComments);
        ui->labActivePadValue->setText(QString::number(mActiveStoryboardPad + 1));
    }
    ui->gvSketchPad->setFocus();
}

void MainWindow::loadBackground()
{
    // code works, but I need to find a way to save BG with xml file...
    /*
    QString filename = QFileDialog::getOpenFileName(this,
                                                    tr("Select background image"),
                                                    mLastProjPath,
                                                    tr("Image files (*.png *.jpg)"));
    if (filename.isEmpty())
        return;

    QFile file(filename);
    QStringList list = filename.split("/");
    QString bgFile = mActiveStoryboardFull + "/" + "bg/" + list.last();
    bool b = false;
    if (!QFile::exists(bgFile))
        b = file.copy(bgFile);
    else
        b = true;
    if (b)
    {
        if (!file.open(QIODevice::ReadOnly))
            return;

        QPixmap pix(bgFile);
        pix = pix.scaled(ui->gvSketchPad->size(), Qt::IgnoreAspectRatio);
        QGraphicsPixmapItem* item = new QGraphicsPixmapItem;
        item->setPixmap(pix);
        item->setZValue(-1);
        mScene->addItem(item);
        updateStoryboard();
    }
*/
}

void MainWindow::removeBackground()
{

}

void MainWindow::hideBackground()
{

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
    mNeedSave = true;
}

void MainWindow::changePaletteColor()
{
    if (ui->lwPalette->currentRow() == 0)
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
    mNeedSave = true;
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
    mNeedSave = true;
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
    ui->labPencolor->setFixedHeight(w);
    mNeedSave = true;
}

void MainWindow::onTimingChanged(int timing)
{
    mTiming.replace(mActiveStoryboardPad, timing);
    updateTimingLabel();
    mNeedSave = true;
}

void MainWindow::updateTimingLabel()
{
    int t = 0;
    for (int i = 0; i < mTiming.size(); i++)
        t = t + mTiming.at(i);
    ui->labFramesCountValue->setText(QString::number(t));
    int sec = t / mFps;
    int fr  = t - (sec * mFps);
    QString code(QString::number(sec) + ":" + QString::number(fr));
    ui->labTimeValue->setText(code);
    ui->labActivePadValue->setText(QString::number(mActiveStoryboardPad + 1));
}

void MainWindow::updateStoryboard()
{
    QPixmap pix = ui->gvSketchPad->grab(ui->gvSketchPad->rect());
    if (!pix.isNull())
    {
        pix = pix.scaledToWidth(200);
        QIcon icon(pix);
        QTableWidgetItem* item = ui->twStoryboard->takeItem(0, mActiveStoryboardPad);
        item->setIcon(icon);
        ui->twStoryboard->setItem(0, mActiveStoryboardPad, item);
    }
    mNeedSave = true;
}

void MainWindow::refreshStoryboard()
{
    for (int i = 0; i < mStoryboardPads.size(); i++)
    {

    }
}

void MainWindow::copyFrom_mScene(QGraphicsScene *scene)
{
    scene->clear();
    QList<QGraphicsItem*> items = mScene->items();
    for (int i = 0; i < items.size(); i++)
    {
        if (items.at(i)->zValue() == 0)
        {
            QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i));
            scene->addLine(line->line(), line->pen());
        }
        else if (items.at(i)->zValue() == -1)
        {
            QGraphicsPixmapItem* pix = static_cast<QGraphicsPixmapItem*>(items.at(i));
            qDebug() << "test1";
            pix->setZValue(-1);
            scene->addItem(pix);
        }
    }
}

void MainWindow::copyTo_mScene(QGraphicsScene *scene)
{
    mScene->clear();
    QList<QGraphicsItem*> items = scene->items();
    for (int i = 0; i < items.size(); i++)
        if (items.at(i)->zValue() == 0)
        {
            QGraphicsLineItem* line = static_cast<QGraphicsLineItem*>(items.at(i));
            mScene->addLine(line->line(), line->pen());
        }
        else if (items.at(i)->zValue() == -1)
        {
            QGraphicsPixmapItem* pix = static_cast<QGraphicsPixmapItem*>(items.at(i));
            qDebug() << "test1";
            pix->setZValue(-1);
            qDebug() << "test2";
            mScene->addItem(pix);
            qDebug() << "test3";
        }
}

void MainWindow::clearCanvas()
{
    qDebug() << "entry list size: " << entryList.size();
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
        updateStoryboard();
        mNeedSave = true;
    }
}

void MainWindow::clearSelected()
{
    qDebug() << "entry list size: " << entryList.size();
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
        updateStoryboard();
        mNeedSave = true;
    }
}

void MainWindow::clearButSelected()
{
    qDebug() << "entry list size: " << entryList.size();
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
        updateStoryboard();
        mNeedSave = true;
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
        updateStoryboard();
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
        updateStoryboard();
    }
}

void MainWindow::updateCommentLineEdits(MainWindow::comments c)
{
    {
    const QSignalBlocker b1(ui->leDialogue);
    ui->leDialogue->setText(c.d);
    }
    {
    const QSignalBlocker b2(ui->leAction);
    ui->leAction->setText(c.a);
    }
    {
    const QSignalBlocker b3(ui->leSlug);
    ui->leSlug->setText(c.s);
    }
    mNeedSave = true;
}

void MainWindow::setPreferences()
{
    mPrefs->exec();
}


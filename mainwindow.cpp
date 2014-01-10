#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateInterval = 1000;      // millisecs. to be set as preference TODO
    saveInterval = 10000;       // millisecs. to be set as preference TODO
    fps = 25;
    scenePath = "";
    scenePaths.clear();
    sceneList.clear();
    sceneList << "Scene" << "Shot";
    autoNumber = true;
    pad = new QGraphicsScene(this);
    ui->gvSketchPad->setFixedSize(642,482);
    ui->gvSketchPad->setScene(pad);
    board = new QGraphicsScene(this);
    QBrush grayBrush(Qt::gray);
    board->setBackgroundBrush(grayBrush);
    ui->gvStoryboard->setScene(board);
    ui->gvStoryboard->show();
    setupConnects();
    projFileName = loadSettings();    // gets the fileName if sbFileName exists!
    if (projFileName.isEmpty()){
        disableStoryPad();
        disableScene();
    }else{
        QFile file(projFileName );
        if (file.exists()){
            initStoryboard();
            readProjXML();
            readStoryboardXML();
        }else{
            disableStoryPad();
            disableScene();
            QMessageBox msgBox;
            msgBox.setText(tr("File: %1 not found!").arg(projFileName));
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
    connect(ui->action_New_Storyboard,SIGNAL(triggered()),this,SLOT(newStoryboard()));
    connect(ui->action_Open_Storyboard,SIGNAL(triggered()),this,SLOT(openStoryboard()));
    connect(ui->action_Save_Storyboard,SIGNAL(triggered()),this,SLOT(writeStoryboardXML()));
    connect(ui->action_Open_Scene,SIGNAL(triggered()),this,SLOT(openScene()));
    connect(ui->action_New_Scene,SIGNAL(triggered()),this,SLOT(newScene()));
    connect(ui->actionPreferences,SIGNAL(triggered()),this,SLOT(setPrefs()));
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionAppend_Sketchpad,SIGNAL(triggered()),this,SLOT(appendSketchPad()));
    connect(ui->actionLoad_Pen_1,SIGNAL(triggered()),this,SLOT(penF5()));
    connect(ui->actionErase_Sketch_Pen,SIGNAL(triggered()),this,SLOT(eraseF5()));
    connect(ui->actionLoad_Pen_2,SIGNAL(triggered()),this,SLOT(penF6()));
    connect(ui->actionLoad_Pen_3,SIGNAL(triggered()),this,SLOT(penF7()));
    connect(ui->actionLoad_Pen_4,SIGNAL(triggered()),this,SLOT(penF8()));
    connect(ui->actionCenter_Storyboard,SIGNAL(triggered()),this,SLOT(centerStoryboard()));

    connect(ui->actionErase_All,SIGNAL(triggered()),this,SLOT(eraseAll()));
    // set pen width and color
    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penPick()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penPick()));

}

void MainWindow::startSaveImageTimer(int i)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateSaveImages()));
    timer->start(i);
}

void MainWindow::startUpdateImageTimer(int i)
{
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()),this,SLOT(updateSaveImages()));
    updateTimer->start(i);
}

void MainWindow::setPadSize(int w, int h)
{
    ui->gvSketchPad->setFixedSize(w,h);
}

void MainWindow::initStoryboard()
{
    padInfoList.clear();
    padInfo.clear();
    sPenList.clear();
    board->clear();
    for (int i = 0;i<5;i++)
    {
        sPen.penWidth = 6;
        sPen.penColor = QColor(80,80,80);
        sPenList.append(sPen);
    }
    lastNumber = 0;
    activePad = 0;
    activePen = 0;
    sketchPad = new SketchPad();
    sketchPad->setFixedSize(640,480);
    sketchPad->initPad(scenePath,lastNumber);
//    sketchPad->initPad(sbFileName,lastNumber);
    padInfoList.append(padInfo);
    initPadInfo();
    pad->addWidget(sketchPad);
    update();
    sketchPad->setFocus();
}

void MainWindow::initPadInfo() /* sketchPad info as strings */
{
    padInfo.clear();
    padInfo.append(QString::number(lastNumber) + ".png");  // image filename!
    padInfo.append("");
    padInfo.append("false");
    padInfo.append("");
    padInfo.append("false");
    padInfo.append("");
    padInfo.append("false");
    padInfo.append("50");
    padInfo.append("false");
    padInfoList.replace(activePad,padInfo);
    sketchPad->clearImage();

    // update text and values in padInfo, when changes are made
    disconnect(ui->leComment,SIGNAL(textChanged(QString)),this,SLOT(updateComment()));
    disconnect(ui->leScene,SIGNAL(textChanged(QString)),this,SLOT(updateScene()));
    disconnect(ui->leShot,SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    disconnect(ui->sbFrames,SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));
    disconnect(board,SIGNAL(selectionChanged()),this,SLOT(changeImage()));
    ui->leComment->clear();
    ui->leScene->clear();
    ui->leShot->clear();
    ui->sbFrames->setValue(50);
    connect(ui->leComment,SIGNAL(textChanged(QString)),this,SLOT(updateComment()));
    connect(ui->leScene,SIGNAL(textChanged(QString)),this,SLOT(updateScene()));
    connect(ui->leShot,SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    connect(ui->sbFrames,SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));
    connect(board,SIGNAL(selectionChanged()),this,SLOT(changeImage()));

    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    padThumbList.append(imageThumb);    // append pixmap to List...
    pixItem = new QGraphicsPixmapItem(imageThumb);
    board->addItem(pixItem);        //...and add it to storyboard as an Item..!
    pixItem->setPos(((activePad+1) *170) - 165 , 3); // place pixItem in storyboard
//    pixItem->setPos((padThumbList.size()*170) - 165 , 3); // place pixItem in storyboard

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()),this,SLOT(updateImages()));
    updateTimer->start(updateInterval);
}

QString MainWindow::getSbFileName()
{
    return QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));
}

QString MainWindow::loadSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (settings.contains("projFileName")){
        scenePath = settings.value("scenePath").toString();
        projFilePath = settings.value("projFilePath").toString();
        fps = settings.value("Fps").toInt();
        sceneList[0] = settings.value("Scene").toString();
        sceneList[1] = settings.value("Shot").toString();
        autoNumber = settings.value("autoNumber").toBool();
        return settings.value("projFileName").toString();
    }
    else
        return "";
}

void MainWindow::saveSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.clear();
    settings.setValue("projFileName", projFileName);
    settings.setValue("projFilePath",projFilePath);
    settings.setValue("scenePath",scenePath);
    settings.setValue("Fps",fps);
    settings.setValue("Scene",sceneList[0]);
    settings.setValue("Shot",sceneList[1]);
    settings.setValue("autoNumber",autoNumber);
}

void MainWindow::setPrefs()
{
    prefs = new PrefDialog();
    prefs->setModal(true);
    prefs->show();
    connect(prefs->btnCancel,SIGNAL(clicked()),this,SLOT(cancelPrefs()));
    connect(prefs->btnOk,SIGNAL(clicked()),this,SLOT(okPrefs()));
}

void MainWindow::okPrefs()
{
    if (prefs->cbFps->currentIndex() == 0) fps = 24;
    else if (prefs->cbFps->currentIndex() == 1) fps = 25;
    else fps = 30;

    sceneList.clear();
    if (prefs->cbSeqSc->currentIndex() == 0) sceneList << tr("Sequence") << tr("Scene");
    else sceneList << tr("Scene") << tr("Shot");

    if (prefs->cbAutoNumber->currentIndex() == 0) autoNumber = false;
    else autoNumber = true;
    saveSettings();
    prefs->close();
}

void MainWindow::cancelPrefs()
{
    prefs->close();
}

void MainWindow::disableStoryPad()
{
    ui->gvSketchPad->setEnabled(false);
    ui->labScene->setEnabled(false);
    ui->leScene->setEnabled(false);
    ui->labShot->setEnabled(false);
    ui->leShot->setEnabled(false);
    ui->labFrames->setEnabled(false);
    ui->sbFrames->setEnabled(false);
    ui->labComments->setEnabled(false);
    ui->leComment->setEnabled(false);
    ui->menuLoad_Pen->setEnabled(false);
    ui->menuSettings->setEnabled(false);
    ui->menuSketchpad->setEnabled(false);
    ui->action_Save_Storyboard->setEnabled(false);
}

void MainWindow::enableStoryPad()
{
    ui->gvSketchPad->setEnabled(true);
    ui->labScene->setEnabled(true);
    ui->leScene->setEnabled(true);
    ui->labShot->setEnabled(true);
    ui->leShot->setEnabled(true);
    ui->labFrames->setEnabled(true);
    ui->sbFrames->setEnabled(true);
    ui->labComments->setEnabled(true);
    ui->leComment->setEnabled(true);
    ui->menuLoad_Pen->setEnabled(true);
    ui->menuSketchpad->setEnabled(true);
    ui->menuSettings->setEnabled(true);
    ui->action_Save_Storyboard->setEnabled(true);
}

void MainWindow::disableScene()
{
    ui->menuScene->setEnabled(false);
}

void MainWindow::enableScene()
{
    ui->menuScene->setEnabled(true);
}

void MainWindow::newStoryboard()
{
    if (projFileName != "")
        writeProjXML();
    projFileName = QFileDialog::getSaveFileName(this,
        tr("dastoryboard project filename"), "",
        tr("dastoryboard project files (*.projdastoryboard)"));

    if (!projFileName.isEmpty()){
        if (!projFileName.endsWith(".projdastoryboard"))
            projFileName += ".projdastoryboard";
        projFilePath = projFileName.left(projFileName.lastIndexOf("/") + 1);
        writeProjXML();
        enableScene();
    }
}

void MainWindow::openStoryboard()
{
    if (projFileName != "")
        writeProjXML();
    projFileName = QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.projdastoryboard)"));
    if (!projFileName.isEmpty()){
        projFilePath = projFileName.left(projFileName.lastIndexOf("/") + 1);
        enableScene();
        readProjXML();
    }
}

void MainWindow::newScene()
{
    bool ok;
    scenePath = QInputDialog::getText(this, tr("New Scene"),
                                      tr("Scene name: (maximum 6 char.)"),
                                      QLineEdit::Normal,"", &ok);
    if (ok && !scenePath.isEmpty()){
        QDir dir = QDir(projFilePath);
        dir.mkdir(projFilePath + scenePath);
        sbFileName = projFilePath + scenePath + "/" + scenePath + ".dastoryboard";
        scenePath = projFilePath + scenePath + "/";
        sceneList.append(sbFileName);
        saveSettings();

        enableStoryPad();
        initStoryboard();
        writeProjXML();
        startSaveImageTimer(saveInterval);
    }
}

void MainWindow::openScene()
{
    QStringList dirs;
    QDir dir = QDir(projFilePath);
    dirs = dir.entryList(QStringList("*"),QDir::AllDirs);
    for (int i = dirs.size() - 1;i > -1;i--){
        QFile f(projFilePath + dirs[i] + "/" + dirs[i] + ".dastoryboard");
        if (!f.exists())
            dirs.removeAt(i);
    }
    if (dirs.isEmpty()){
        QMessageBox msgBox;
        msgBox.setText(tr("No scenes found!").arg(sbFileName));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }else{
        bool ok;
        QString sc = QInputDialog::getItem(this, tr("Scene"),
                                           tr("Choose Scene to open:"), dirs, 0, false, &ok);
        if (ok && !sc.isEmpty()){
            sbFileName = projFilePath + sc + "/" + sc + ".dastoryboard";
            scenePath = projFilePath + sc + "/";
        }
    }
    if (!sbFileName.isEmpty()){     // if storyboard-file has been chosen
        enableStoryPad();
        if (!sceneList.contains(sbFileName))
            sceneList.append(sbFileName);
        writeProjXML();
        readStoryboardXML();
        startSaveImageTimer(saveInterval);
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    updateSaveImages();
    e->accept(); // TODO!!!
}

void MainWindow::penPick()
{
    pc = new penChooser();
    pc->colordialog->setCurrentColor(sketchPad->penColor());
    pc->sbWidth->setValue(sketchPad->penWidth());
    pc->cbPen->setCurrentIndex(activePen);
    pc->setModal(true);
    pc->show();
    connect(pc->btnCancel,SIGNAL(clicked()),this,SLOT(cancelPenPick()));
    connect(pc->btnOk,SIGNAL(clicked()),this,SLOT(okPenPick()));
}

void MainWindow::okPenPick()
{
    activePen = pc->cbPen->currentIndex();
    sPen = sPenList[activePen];
    sPen.penColor = pc->colordialog->currentColor();
    sketchPad->setPenColor(sPen.penColor);
    sPen.penWidth = pc->sbWidth->value();
    sketchPad->setPenWidth(sPen.penWidth);
    sPenList.replace(activePen,sPen);
    pc->close();
}

void MainWindow::cancelPenPick()
{
    pc->close();
}

void MainWindow::penF5()
{
    sPen = sPenList[1];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF6()
{
    sPen = sPenList[2];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF7()
{
    sPen = sPenList[3];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF8()
{
    sPen = sPenList[4];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::eraseF5()
{
    sketchPad->eraseSketchPen(sPenList[1].penColor.red(),
            sPenList[1].penColor.green(),sPenList[1].penColor.blue());
}

void MainWindow::eraseAll()
{
    int ret = QMessageBox::warning(this, tr("Erase drawing"),
                                    tr("Do you want to erase the drawing?\n"
                                       "It can NOT be undone!\n"                                       ),
                                    QMessageBox::Ok | QMessageBox::Cancel,
                                    QMessageBox::Cancel);
    switch (ret)
    {
       case QMessageBox::Ok:
        sketchPad->clearImage();
           break;
       case QMessageBox::Cancel:
       default:
           break;
     }
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About dastoryboard"),
            tr("<p><b>dastoryboard</b> is an Open Source storyboard software "
               "for your conveniance. Please enjoy!"));
}

void MainWindow::updateComment()
{
    padInfoList[activePad][comment] = ui->leComment->text();
}

void MainWindow::updateScene()
{
   padInfoList[activePad][scene] = ui->leScene->text();
}

void MainWindow::updateShot()
{
    padInfoList[activePad][shot] = ui->leShot->text();
}

void MainWindow::updateFrames()
{
    padInfoList[activePad][frames] = QString::number(ui->sbFrames->value());
}

void MainWindow::updateSaveImages()
{
    sketchPad->image.save(scenePath + padInfoList[activePad][fileName]);
    QImage img = sketchPad->image;
    img = img.scaled(160,120,Qt::KeepAspectRatio,Qt::FastTransformation);
    img.save(scenePath + "t" + padInfoList[activePad][fileName]);
    QFile f(scenePath + "t" + padInfoList[activePad][fileName]);
    if (!f.exists()){
        QMessageBox::information(this, tr("File does no exist!"),
                tr("It was not possible to save the storyboard image."
                   "Do you have write access to the directory?"));
    }
}

void MainWindow::addThumbLabels()       // Adds labels to all thumbnails
{
    for (int i = 0;i<padInfoList.size();i++){
        txt = new QGraphicsTextItem();
        txt->setHtml("<div style=\'background-color:#ffffff;\'> "
                     + padInfoList[i][scene] + " , "
                     + padInfoList[i][shot] + " </div>");
        board->addItem(txt);
        txt->setPos(((i + 1)*170) - 165 , 3);
    }
}

void MainWindow::updateImages() // updates storyboard thumbnails
{
    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    pixItem = new QGraphicsPixmapItem(imageThumb);
    board->removeItem(board->itemAt(((activePad+1)*170) - 165 , 3));
    board->addItem(pixItem);
    pixItem->setPos(((activePad + 1)*170) - 165 , 3);
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
    ui->labActivePadInfo->setText(tr("Scene %1, Shot %2")
                                  .arg(padInfo[scene]).arg(padInfo[shot]));
    addThumbLabels();
    update();
    ui->leComment->setText(padInfoList[activePad][comment]);
    ui->leScene->setText(padInfoList[activePad][scene]);
    ui->leShot->setText(padInfoList[activePad][shot]);
    ui->sbFrames->setValue(padInfoList[activePad][frames].toInt());
    sketchPad->update();

}

void MainWindow::centerStoryboard()
{
    ui->gvStoryboard->ensureVisible(QRectF((activePad + 1)*170-165, 3, 160, 120),800,0);
}

void MainWindow::changeImage()
{
    if (!board->selectedItems().isEmpty()){
        item = board->selectedItems().at(0);
        int i = item->pos().x();        // find x-value
        activePad = (i-5) / 170;
        padInfo = padInfoList.at(activePad);
        sketchPad->image.load(scenePath + padInfo[fileName]);
        updateImages();
    }
}

void MainWindow::appendSketchPad()
{
    updateSaveImages();
 //   sketchPad->image.save(scenePath + padInfoList[activePad][fileName]);
    padInfoList.append(padInfo);
    lastNumber += 1;
    activePad = padInfoList.size() - 1;
    initPadInfo();
    writeStoryboardXML();  // ****************************************
    startSaveImageTimer(saveInterval);
}

void MainWindow::insertSketchPad()
{
    sketchPad->image.save(scenePath + padInfoList[activePad][fileName]);
    padInfoList.insert(activePad+1,padInfo);
    lastNumber += 1;
    activePad += 1;
    initPadInfo();
    startSaveImageTimer(saveInterval);
}

void MainWindow::writeProjXML()
{
    if (!projFileName.isEmpty()){
        QFile file(projFileName);
        if (file.open(QFile::ReadWrite)){
            saveSettings();
            QXmlStreamWriter xmlwriter(&file);
            xmlwriter.setAutoFormatting(true);
            xmlwriter.writeStartDocument();                 // document START
            xmlwriter.writeStartElement("projstoryboard");  // storyboard START

            xmlwriter.writeStartElement("variables");       // variables START
            xmlwriter.writeTextElement("projFileName",projFileName);
            xmlwriter.writeTextElement("sbFileName",sbFileName);
            xmlwriter.writeTextElement("Fps",QString::number(fps));
            xmlwriter.writeTextElement("Scene",sceneList[0]);
            xmlwriter.writeTextElement("Shot",sceneList[1]);
            xmlwriter.writeTextElement("autoNumber",boolToString(autoNumber));
            xmlwriter.writeEndElement();                    // variables STOP
            if (scenePaths.size() > 0){
                xmlwriter.writeStartElement("scenes");          // scenes START
                for (int i = 0; i < scenePaths.size(); i++){
                    xmlwriter.writeTextElement("scenePaths",scenePaths[i]);
                }
                xmlwriter.writeEndElement();                    // scenes STOP
            }
            xmlwriter.writeEndDocument();               // document and storyboard STOP
        }
    }
}

void MainWindow::readProjXML()
{
    QFile sbFile(projFileName);
    if (sbFile.open(QIODevice::ReadOnly)){
        sceneList.clear();
        scenePaths.clear();
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "projFileName")
                projFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "Fps")
                fps = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "Scene")
                sceneList.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "Shot")
                sceneList.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "autoNumber")
                autoNumber = stringToBool(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scenePaths")
                scenePaths.append(xmlreader.readElementText());
        }
    }
}

void MainWindow::writeStoryboardXML()
{
    if (!sbFileName.isEmpty()){
        updateSaveImages();         // saves activeimages
        QFile file(sbFileName);
        if (file.open(QFile::ReadWrite)){
            saveSettings();
            QXmlStreamWriter xmlwriter(&file);
            xmlwriter.setAutoFormatting(true);
            xmlwriter.writeStartDocument();             // document START
            xmlwriter.writeStartElement("storyboard");  // storyboard START
            xmlwriter.writeStartElement("variables");   // variables START
            xmlwriter.writeTextElement("sbFileName",sbFileName);
            xmlwriter.writeTextElement("lastNumber",QString::number(lastNumber));
            xmlwriter.writeTextElement("activePad",QString::number(activePad));
            xmlwriter.writeTextElement("activePen",QString::number(activePen));
            xmlwriter.writeEndElement();                // variables STOP

            xmlwriter.writeStartElement("penlist");     // penlist START
            for (int i = 0; i < sPenList.size();i++)
            {
                xmlwriter.writeStartElement("pen");     // pen START
                xmlwriter.writeTextElement("width",QString::number(sPenList[i].penWidth));
                xmlwriter.writeTextElement("red",QString::number(sPenList[i].penColor.red()));
                xmlwriter.writeTextElement("green",QString::number(sPenList[i].penColor.green()));
                xmlwriter.writeTextElement("blue",QString::number(sPenList[i].penColor.blue()));
                xmlwriter.writeEndElement();            // pen STOP
            }
            xmlwriter.writeEndElement();                // penlist STOP

            xmlwriter.writeStartElement("sketchpads");  // sketchpads START
            for (int i = 0;i < padInfoList.size() ; i++){ // TODO !!!!!!!!!!!!
                padInfo = padInfoList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpad START
                xmlwriter.writeTextElement("fileName",padInfo[fileName]);
                xmlwriter.writeTextElement("comment",padInfo[comment]);
                xmlwriter.writeTextElement("showComment",padInfo[showComment]);
                xmlwriter.writeTextElement("scene",padInfo[scene]);
                xmlwriter.writeTextElement("showScene",padInfo[showScene]);
                xmlwriter.writeTextElement("shot",padInfo[shot]);
                xmlwriter.writeTextElement("showShot",padInfo[showShot]);
                xmlwriter.writeTextElement("frames",padInfo[frames]);
                xmlwriter.writeTextElement("showFrames",padInfo[showFrames]);
                xmlwriter.writeEndElement();                // sketchpad STOP
            }
            xmlwriter.writeEndElement();         // sketchpads STOP
            xmlwriter.writeEndDocument();        // document and storyboard STOP
        }

    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("No filename chosen!"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::readStoryboardXML()
{
    QFile sbFile(sbFileName);           // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
//        writeStoryboardXML();
        padInfoList.clear();            // clear list for reading file
        padInfo.clear();
        padThumbList.clear();
        sPenList.clear();
        board->clear();
//        update();
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "lastNumber")
                lastNumber = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePad")
                activePad = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePen")
                activePen = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "width")
                sPen.penWidth = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "red")
                sPen.penColor.setRed(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "green")
                sPen.penColor.setGreen(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "blue"){
                sPen.penColor.setBlue(xmlreader.readElementText().toInt());
                sPenList.append(sPen);
            }
            else if (xmlreader.isStartElement() && xmlreader.name() == "comment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showComment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scene")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showScene")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showShot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showFrames"){
                padInfo.append(xmlreader.readElementText());
                sketchPad->image.load(scenePath + padInfo[fileName]);
                imageThumb = QPixmap::fromImage(sketchPad->image);
                imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
                padThumbList.append(imageThumb);
                pixItem = new QGraphicsPixmapItem(imageThumb);
                board->addItem(pixItem);
                pixItem->setPos((padThumbList.size()*170) - 165 , 3); // place pixItem in storyboard
                pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
                update();
                padInfoList.append(padInfo);
                padInfo.clear();
            }
        }
        sPen = sPenList[activePen];
        sketchPad->setPenColor(sPen.penColor);
        sketchPad->setPenWidth(sPen.penWidth);
        padInfo = padInfoList.at(activePad);
        sketchPad->image.load(scenePath + padInfo[fileName]);
        updateImages();
        addThumbLabels();
        ui->leComment->setText(padInfo[comment]);
        ui->leScene->setText(padInfo[scene]);
        ui->leShot->setText(padInfo[shot]);
        ui->sbFrames->setValue(padInfo[frames].toInt());
        startSaveImageTimer(saveInterval);
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("File: %1 not found!").arg(sbFileName));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

QString MainWindow::boolToString(bool b)
{
    if (b == true)
        return "yes";
    else
        return "no";
}

QString MainWindow::intToString(int i)
{
    QString s;
    return s.setNum(i);
}

int MainWindow::strToInt(QString s)
{
    return s.toInt();
}

bool MainWindow::stringToBool(QString s)
{
    if (s == "yes")
        return true;
    else
        return false;
}


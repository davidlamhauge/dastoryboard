#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"
#include <QGraphicsPixmapItem>
#include <QFileDialog>
#include <QInputDialog>
#include <QDebug>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QTextCodec::setCodecForLocale(QTextCodec::codecForName("UTF-8"));
    projFileName = "";          // project filename, absolute path
    projFilePath = "";          // filepath, including the last '/'
    prefPath = "";
    initVars();
    initScenes();
    setupGlobalConnects();
    projFileName = loadSettings();    // get fileName from settings if it exists!
    if (projFileName.isEmpty()){
        disableStoryPad();
        disableScene();
    }else{
        QFile file(projFileName );
        if (file.exists()){
            initStoryboard();
            readProjXML();
            readStoryboardXML();
            updateInfoLabels();
            setupNewSceneConnect();
            setupAllConnects();
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

// public slots:

void MainWindow::updateCommentDialogue(QString string)
{
    padInfoList[activePad][dialogue] = string;
}

void MainWindow::updateCommentAction(QString string)
{
    padInfoList[activePad][action] = string;
}

void MainWindow::updateCommentSlug(QString string)
{
    padInfoList[activePad][slug] = string;
}

// protected:

void MainWindow::closeEvent(QCloseEvent *e)
{
    saveImages();
    writeStoryboardXML();
    writeProjXML();
    saveSettings();
    e->accept();
}

// private slots:

void MainWindow::newStoryboard()
{
    if (projFileName != ""){
        writeProjXML();
        writeStoryboardXML();
        Q_ASSERT(updateTimer->isActive());
        updateTimer->stop();
    }
    projFileName = QFileDialog::getSaveFileName(this,
        tr("dastoryboard project filename"), prefPath,
        tr("dastoryboard project files (*.projdastoryboard)"));

    if (!projFileName.isEmpty()){
        if (!projFileName.endsWith(".projdastoryboard"))
            projFileName += ".projdastoryboard";
        projFilePath = projFileName.left(projFileName.lastIndexOf("/") + 1);
        prefPath = projFilePath;
        disconnectAllConnects();
        setupNewSceneConnect();

        initVars();
        resetPenList();         // reset sPenList, amd
        setBtnColors();         // ... set correct labels on them
        board->clear();
        pad->clear();
        enableScene();
        disableStoryPad();
        updateInfoLabels();
    }else{
        updateTimer->start(updateInterval);
    }
}

void MainWindow::openStoryboard()
{
    if (projFileName != "")
        writeProjXML();
    projFileName = QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), projFilePath,
        tr("dastoryboard files (*.projdastoryboard)"));
    if (!projFileName.isEmpty()){
        projFilePath = projFileName.left(projFileName.lastIndexOf("/") + 1);
        setupAllConnects();
        setupNewSceneConnect();
        enableScene();
        enableStoryPad();
        initStoryboard();
        readProjXML();
        readStoryboardXML();
        updateImages();
        updateInfoLabels();
    }
}

void MainWindow::newScene()
{
    bool ok;
    scenePath = QInputDialog::getText(this, tr("New Scene"),
                                      tr("Scene name: (maximum 6 char.)"),
                                      QLineEdit::Normal,"", &ok);
    if (scenePath.length() > 6)
        QMessageBox::information(this, tr("Scene not created!"),
                                 tr("Scene name must not exceed 6 chars"));
    if (ok && !scenePath.isEmpty() && scenePath.length() < 7){
        sceneDir = scenePath;
        QDir dir = QDir(projFilePath);
        dir.mkdir(projFilePath + sceneDir);
        sbFileName = projFilePath + sceneDir + "/" + sceneDir + ".dastoryboard";
        scenePath = projFilePath + sceneDir + "/";
        sceneList.append(sbFileName);
        scenePaths.append(scenePath);
        setupAllConnects();
        saveSettings();
        enableStoryPad();
        initStoryboard();
        writeProjXML();
        updateScenelist();
        setBtnColors();
        updateInfoLabels();
    }
}

void MainWindow::openScene()
{
    QString sc = ui->cbScenes->currentText();
    sbFileName = projFilePath + sc + "/" + sc + ".dastoryboard";
    scenePath = projFilePath + sc + "/";
    sceneDir = sc;                                  // sceneDir = sc
    if (!sbFileName.isEmpty()){     // if storyboard-file has been chosen
        enableStoryPad();
        if (!sceneList.contains(sbFileName))
            sceneList.append(sbFileName);
        if (!scenePaths.contains(scenePath))
            scenePaths.append(scenePath);
        writeProjXML();
        readStoryboardXML();
        updateScenelist();
    }
    int i;
    i = ui->cbScenes->findText(sc);
    ui->cbScenes->setCurrentIndex(i);
}

void MainWindow::addAudio()
{
    QString s = QFileDialog::getOpenFileName(this, tr("Select audio file"),
                                                    projFilePath,
                                                    tr("Audio files (*.ogg *.mp3 *.wav)"));
    QFile f(s);
    if (f.exists()){
        audioFileName = s;
        writeStoryboardXML();
        ui->action_Remove_audio->setEnabled(true);
    }
}

void MainWindow::rmAudio()
{
    QMessageBox msgBox;
    msgBox.setText(tr("Remove audiofile from storyboard"));
    msgBox.setInformativeText(tr("Do you want to remove the audiofile\n"
                                 "%1\n"
                                 "from the storyboard?\n\n"
                                 "It will not be erased from the harddisc").arg(audioFileName));
    msgBox.setStandardButtons(QMessageBox::No | QMessageBox::Yes );
    msgBox.setDefaultButton(QMessageBox::No);
    int ret = msgBox.exec();
    switch (ret)
    {
    case QMessageBox::Yes:
        audioFileName = "";
        ui->action_Remove_audio->setEnabled(false);
        writeStoryboardXML();
        break;
    case QMessageBox::No:
    default:
        break;
    }
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
            xmlwriter.writeTextElement("projFilePath",projFilePath);
            xmlwriter.writeTextElement("sbFileName",sbFileName);
            xmlwriter.writeTextElement("sceneDir",sceneDir);
            xmlwriter.writeTextElement("Fps",QString::number(fps));
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

void MainWindow::writeStoryboardXML()
{
    if (!sbFileName.isEmpty()){
        saveImages();         // saves activeimages
        QFile file(sbFileName);
        if (file.open(QFile::ReadWrite))
        {
            saveSettings();
            QXmlStreamWriter xmlwriter(&file);
            xmlwriter.setAutoFormatting(true);
            xmlwriter.writeStartDocument();             // document START
            xmlwriter.writeStartElement("storyboard");  // storyboard START
            xmlwriter.writeStartElement("variables");   // variables START
            xmlwriter.writeTextElement("sbFileName",sbFileName);
            xmlwriter.writeTextElement("scenePath",scenePath);
            xmlwriter.writeTextElement("videoFormat",videoFormat);
            xmlwriter.writeTextElement("audioFileName",audioFileName);
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
            for (int i = 0;i < padInfoList.size() ; i++){
                padInfo = padInfoList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpad START
                xmlwriter.writeTextElement("fileName",padInfo[fileName]);
                xmlwriter.writeTextElement("dialogue",padInfo[dialogue]);
                xmlwriter.writeTextElement("action",padInfo[action]);
                xmlwriter.writeTextElement("slug",padInfo[slug]);
                xmlwriter.writeTextElement("scene",padInfo[scene]);
                xmlwriter.writeTextElement("shot",padInfo[shot]);
                xmlwriter.writeTextElement("frames",padInfo[frames]);
                xmlwriter.writeTextElement("showFrames",padInfo[showFrames]);
                xmlwriter.writeEndElement();                // sketchpad STOP
            }
            padInfo = padInfoList[activePad];
            xmlwriter.writeEndElement();         // sketchpads STOP
            xmlwriter.writeEndDocument();        // document and storyboard STOP
        }
        file.resize(file.pos());
        updateInfoLabels();
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("No filename chosen!"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::saveSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.clear();
    settings.setValue("projFileName", projFileName);
    settings.setValue("projFilePath",projFilePath);
    settings.setValue("scenePath",scenePath);
    settings.setValue("sceneDir",sceneDir);
    settings.setValue("Fps",fps);
    settings.setValue("autoNumber",autoNumber);
    settings.setValue("videoFormat",videoFormat);
    settings.setValue("canvasWidth", canvasW);
    settings.setValue("canvasHeight", canvasH);
}

void MainWindow::setPrefs()
{
    prefs = new PrefDialog(scenePath);
    prefs->setModal(true);
    prefs->show();
    connect(prefs->btnCancel,SIGNAL(clicked()),this,SLOT(cancelPrefs()));
    connect(prefs->btnOk,SIGNAL(clicked()),this,SLOT(okPrefs()));
}

void MainWindow::okPrefs()
{
    // set freferred frames per second
    if (prefs->cbFps->currentIndex() == 0) fps = 24;
    else if (prefs->cbFps->currentIndex() == 1) fps = 25;
    else fps = 30;

    // Set preferred videoformat
    if (prefs->cbVideoFormat->currentIndex() == 0) videoFormat = ".ogv";
    else videoFormat = ".mpg";

    // set preferred numbering: auto or manual
    if (prefs->cbAutoNumber->currentIndex() == 0) autoNumber = false;
    else autoNumber = true;
    saveSettings();
    updateInfoLabels();
    prefs->close();
}

void MainWindow::cancelPrefs()
{
    prefs->close();
}

void MainWindow::padSizeVGA()
{
    setPadSize(640, 480);
}

void MainWindow::padSizeSVGA()
{
    setPadSize(800, 600);
}

void MainWindow::padSizeXGA()
{
    setPadSize(1024, 768);
}

void MainWindow::padSizenHD()
{
    setPadSize(640, 360);
}

void MainWindow::padSizeqHD()
{
    setPadSize(960, 540);
}

void MainWindow::padSize720p()
{
    setPadSize(1280, 720);
}

void MainWindow::penStd()
{
    sPen = sPenList[0];
    activePen = 0;
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
    setBtnColors();
}

void MainWindow::penF5()
{
    sPen = sPenList[1];
    activePen = 1;
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
    setBtnColors();
}

void MainWindow::penF6()
{
    sPen = sPenList[2];
    activePen = 2;
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
    setBtnColors();
}

void MainWindow::penF7()
{
    sPen = sPenList[3];
    activePen = 3;
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
    setBtnColors();
}

void MainWindow::penF8()
{
    sPen = sPenList[4];
    activePen = 4;
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
    setBtnColors();
}

void MainWindow::penPick()
{
    penchooser = new penChooser();
    penchooser->colordialog->setCurrentColor(sketchPad->penColor());
    penchooser->sbWidth->setValue(sketchPad->penWidth());
    penchooser->cbPen->setCurrentIndex(0);
    penchooser->setModal(true);
    connect(penchooser->btnExit, SIGNAL(clicked()), this, SLOT(cancelPenPick()));
    connect(penchooser->btnChange, SIGNAL(clicked()), this, SLOT(okPenPick()));
    penchooser->show();
}

void MainWindow::okPenPick()
{
    activePen = penchooser->cbPen->currentIndex();
    sPen = sPenList[activePen];
    sPen.penColor = penchooser->colordialog->currentColor();
    sketchPad->setPenColor(sPen.penColor);
    sPen.penWidth = penchooser->sbWidth->value();
    sketchPad->setPenWidth(sPen.penWidth);
    sPenList.replace(activePen,sPen);
    setBtnColors();
}

void MainWindow::cancelPenPick()
{
    penchooser->close();
}


void MainWindow::eraseF5()
{
    sketchPad->eraseSketchPen(sPenList[1].penColor.red(),
            sPenList[1].penColor.green(),sPenList[1].penColor.blue());
}

void MainWindow::eraseAll()
{
    int ret = QMessageBox::warning(this, tr("Erase drawing"),
                                   tr("Do you want to erase the drawing?"),
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

void MainWindow::deleteDrawing()
{
    if (board->selectedItems().size() == 1 && padThumbList.size() > 1){
        int ret = QMessageBox::warning(this, tr("Delete drawing from harddisc"),
                                       tr("Do you want to delete the drawing?\n"
                                          "It can NOT be undone!\n"),
                                       QMessageBox::Ok | QMessageBox::Cancel,
                                       QMessageBox::Cancel);
        QFile fPad;
        fPad.setFileName(projFilePath + sceneDir + "/" + padInfo[fileName]);
        QFile fTmb;
        fTmb.setFileName(projFilePath + sceneDir + "/t" + padInfo[fileName]);
        QPixmap imageThumb;
        switch (ret) {
        case QMessageBox::Ok:
            updateTimer->stop();
            if (!fPad.remove())
                qDebug() << "delete file failed!";
            if (!fTmb.remove())
                qDebug() << ("delete thumb file failed!");
            padThumbList.removeAt(activePad);
            padInfoList.removeAt(activePad);
            if (padThumbList.size() > 0)
                if (activePad + 1 > padThumbList.size())
                    activePad -= 1;
            padInfo = padInfoList.at(activePad);
            sketchPad->image.load(scenePath + padInfo[fileName]);

            reloadThumbs();

            updateImages();
            board->itemAt((activePad + 1) * padWidth - 155, 100, transform)->setSelected(true);
            startUpdateImageTimer(updateInterval);
            break;
        case QMessageBox::Cancel:
        default:
            break;
        }
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("You can't manually delete all drawings."));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About dastoryboard"),
            tr("<p><b>dastoryboard</b> is an Open Source storyboard software "
               "for your convenience. Please enjoy!"));
}

void MainWindow::appendSketchPad()
{
    updateImages();
    saveImages();
    padInfoList.append(padInfo);
    lastNumber += 1;
    activePad = padInfoList.size() - 1;
    initPadInfo();
    padInfo[scene] = sceneDir;
    ui->leShot->setText(padInfo[shot]);
    initPad();
    board->setSceneRect(0, 0, padThumbList.size() * padWidth, padHeight);
    ui->gvStoryboard->resize(padThumbList.size() * padWidth, padHeight);
    updateImages();
    centerStoryboard();
    writeStoryboardXML();
}

void MainWindow::insertSketchPad()
{
    if (board->selectedItems().size() == 1 &&
            board->selectedItems().at(0)->x() < ((activePad + 1) * padWidth) - 160){
        updateImages();
        saveImages();
        QPixmap imageThumb;
        imageThumb = QPixmap::fromImage(sketchPad->image);
        imageThumb = imageThumb.scaled( 160, 120, Qt::KeepAspectRatio);
        padThumbList.insert(activePad+1, imageThumb);    // append pixmap to List...
        padInfoList.insert(activePad+1, padInfo);

        reloadThumbs();

        lastNumber += 1;
        activePad += 1;
        initPadInfo();
        padInfo[scene] = sceneDir;
        ui->leShot->setText(padInfo[shot]);
        sketchPad->clearImage();
        updateImages();
        board->itemAt((activePad+1) * padWidth - 155, 100, transform)->setSelected(true);
        centerStoryboard();
        writeStoryboardXML();
    }
}

void MainWindow::movePadLeft()
{
    movePad(-1);
}

void MainWindow::movePadRight()
{
    movePad(1);
}

void MainWindow::updateLineEdits()
{
    ui->leDialogue->setText(padInfoList[activePad][dialogue]);
    ui->leAction->setText(padInfoList[activePad][action]);
    ui->leSlug->setText(padInfoList[activePad][slug]);
}

void MainWindow::clearLineEdits()
{
    ui->leDialogue->clear();
    ui->leAction->clear();
    ui->leSlug->clear();
}

void MainWindow::updateScene()
{
   padInfoList[activePad][scene] = ui->labSceneInfo->text();
}

void MainWindow::updateShot()
{
    padInfoList[activePad][shot] = ui->leShot->text();
}

void MainWindow::updateFrames()
{
    padInfoList[activePad][frames] = QString::number(ui->sbFrames->value());
    updateInfoLabels();
}

void MainWindow::updateScenelist()
{
    if (scenePaths.size() > 0){
        disconnect(ui->cbScenes,SIGNAL(currentIndexChanged(int)),this,SLOT(openScene()));
        ui->cbScenes->clear();
        for (int i = 0; i < scenePaths.size();i++){
            QStringList sl;
            sl = scenePaths[i].split('/');
            sl.removeLast();
            ui->cbScenes->addItem(sl.last());
        }
        ui->cbScenes->setCurrentIndex(ui->cbScenes->findText(sceneDir));
        connect(ui->cbScenes,SIGNAL(currentIndexChanged(int)),this,SLOT(openScene()));
    }
}

QImage *MainWindow::resizeImageNoRatio(QImage *img, int width, int height)
{
    img->scaled(width, height, Qt::IgnoreAspectRatio, Qt::FastTransformation);
    return img;
}

QImage *MainWindow::resizeImageKeepRatio(QImage *img, int width, int height)
{
    img->scaled(width, height, Qt::KeepAspectRatio, Qt::FastTransformation);
    return img;
}

void MainWindow::saveImages()
{
    // save sketchpad image
    sketchPad->image.save(scenePath + padInfoList[activePad][fileName]);

    // save thumbnail
    QImage img = sketchPad->image;
    img = img.scaled(160, 120, Qt::KeepAspectRatio, Qt::FastTransformation);
    if (!img.save(scenePath + "t" + padInfoList[activePad][fileName])){
        QMessageBox::information(this, tr("File does no exist!"),
                                 tr("It was not possible to save the storyboard image."
                                    "Do you have write access to the directory?"));
    }
}

void MainWindow::updateImages() // updates storyboard thumbnails
{
    if (padThumbList.size() > 0 && padThumbList.size() > activePad){
        if (autoNumber){                         // autonumber the Shot
            for (int i = 0; i < padInfoList.size();i++){
                padInfoList[i][shot] = QString::number(i+1);
            }
        }
        QPixmap imageThumb;
        imageThumb = QPixmap::fromImage(sketchPad->image);
        imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
        padThumbList.replace(activePad,imageThumb); // update padThumbList
        QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(imageThumb);
        board->removeItem(board->itemAt((activePad+1) * padWidth - 165 , 3, transform));
        board->addItem(pixItem);
        pixItem->setPos(((activePad + 1) * padWidth) - 165 , 3);
        pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
        ui->labActivePadInfo->setText(tr("%1 of %2")
                                      .arg(padInfo[shot]).arg(padInfoList.size()));
        addThumbLabels();
        ui->labSceneInfo->setText(padInfoList[activePad][scene]);
        ui->leShot->setText(padInfoList[activePad][shot]);
        ui->sbFrames->setValue(padInfoList[activePad][frames].toInt());
        sketchPad->update();
    }
}

void MainWindow::centerStoryboard()
{
    ui->gvStoryboard->ensureVisible(QRectF((activePad + 1) * padWidth - 165, 3, 160, 120),800,0);
}

void MainWindow::changeImage()
{
    if (!board->selectedItems().isEmpty()){
        saveImages();
        QGraphicsItem *item;
        item = board->selectedItems().at(0);
        int i = static_cast<int>(item->pos().x());        // find x-value
        activePad = (i-5) / padWidth;
        padInfo = padInfoList.at(activePad);
        sketchPad->image.load(scenePath + padInfo[fileName]);
        updateImages();
        board->setFocusItem(board->itemAt((activePad + 1) * padWidth - 165, 3, transform));
        updateLineEdits();
    }
}

void MainWindow::runAnimatic()
{
    writeStoryboardXML();
    updateTimer->stop();
    anim = new animatic(fps, scenePath, this);
    anim->setModal(true);
    anim->show();
    connect(anim,SIGNAL(aniClose()),this,SLOT(restartTimer()));
}

void MainWindow::exportPdf()
{
    textOutput *t = new textOutput(scenePath,this);
    QMessageBox msgBox;
    msgBox.setText(tr("Storyboard has been exported to pdf!"));
    msgBox.setIcon(QMessageBox::Information);
    msgBox.exec();
    t->close();
}

void MainWindow::showInfoDialog()
{
    QString s;
    infoDial = new infodialog();
    infoDial->labProjInfo->setText(projFileName);
    infoDial->labSceneInfo->setText(sceneDir);
    infoDial->labImagesInfo->setText(s.setNum(padInfoList.count()));
    infoDial->labFramesInfo->setText(ui->labFramesCountValue->text());
    infoDial->labFpsInfo->setText(s.setNum(fps));
    infoDial->labDurationInfo->setText(tr("%1 (mm:ss:ff)","mm:ss:ff = minutes:seconds:frames")
                                       .arg(ui->labTimeValue->text()));
    infoDial->labAudioInfo->setText(audioFileName);
    infoDial->setModal(true);
    infoDial->show();
}

void MainWindow::restartTimer()
{
    disconnect(anim,SIGNAL(aniClose()),this,SLOT(restartTimer()));
    startUpdateImageTimer(updateInterval);
}

// private:

void MainWindow::initVars()
{       // initiates vars, EXCEPT projFileName and projFilePath
    updateInterval = 2013;      // millisecs. to be set as preference TODO
    fps = 25;                   // can be changed from loadSettings
    autoNumber = true;          // can be changed from loadSettings
    videoFormat = ".ogv";       // can be changed from loadsettings
    scenePath = "";             // path to scenes images + thumbs
    sbFileName = "";            // storyboard filename, absolute path
    audioFileName = "";         // audio filenam, absolute path
    scenePaths.clear();         // List with scene paths to sub-dirs
    sceneList.clear();          // List with scenes in project
    sceneDir = "";              // name of directory of scene
    padInfo.clear();            // fileName, comment, shot name etc
    padInfoList.clear();        // list of stringlists with padInfo
    padThumbList.clear();       // list of all resized images as 160x120 pixmaps
    sPenList.clear();
}

void MainWindow::initScenes()
{
    pad = new QGraphicsScene(this);
    ui->gvSketchPad->setFixedSize(642,482);
    ui->gvSketchPad->setScene(pad);
    board = new QGraphicsScene(this);
    QBrush grayBrush(Qt::gray);
    board->setBackgroundBrush(grayBrush);
    ui->gvStoryboard->setScene(board);
    ui->gvStoryboard->show();
}

void MainWindow::setupGlobalConnects()
{
    connect(ui->action_New_Storyboard, SIGNAL(triggered()),this,SLOT(newStoryboard()));
    connect(ui->action_Open_Storyboard, SIGNAL(triggered()),this,SLOT(openStoryboard()));
    connect(ui->action_Save_Storyboard, SIGNAL(triggered()),this,SLOT(writeStoryboardXML()));
    connect(ui->actionPreferences, SIGNAL(triggered()),this,SLOT(setPrefs()));
    connect(ui->actionE_xit, SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->action_About, SIGNAL(triggered()),this,SLOT(about()));
}

void MainWindow::setupNewSceneConnect()
{
    connect(ui->action_New_Scene, SIGNAL(triggered()),this,SLOT(newScene()));
}

void MainWindow::setupAllConnects()
{
    connect(ui->action_Add_audio, SIGNAL(triggered()),this,SLOT(addAudio()));
    connect(ui->action_Remove_audio, SIGNAL(triggered()),this,SLOT(rmAudio()));
    connect(ui->actionAppend_Sketchpad, SIGNAL(triggered()),this,SLOT(appendSketchPad()));
    connect(ui->actionInsert_Sketchpad, SIGNAL(triggered()),this,SLOT(insertSketchPad()));
    connect(ui->actionLoad_Pen_1, SIGNAL(triggered()),this,SLOT(penF5()));
    connect(ui->actionErase_Sketch_Pen, SIGNAL(triggered()),this,SLOT(eraseF5()));
    connect(ui->actionLoad_Pen_2, SIGNAL(triggered()),this,SLOT(penF6()));
    connect(ui->actionLoad_Pen_3, SIGNAL(triggered()),this,SLOT(penF7()));
    connect(ui->actionLoad_Pen_4, SIGNAL(triggered()),this,SLOT(penF8()));
    connect(ui->btnStandardPen, SIGNAL(pressed()),this,SLOT(penStd()));
    connect(ui->btnF5, SIGNAL(pressed()),this,SLOT(penF5()));
    connect(ui->btnF6, SIGNAL(pressed()),this,SLOT(penF6()));
    connect(ui->btnF7, SIGNAL(pressed()),this,SLOT(penF7()));
    connect(ui->btnF8, SIGNAL(pressed()),this,SLOT(penF8()));
    connect(ui->actionCenter_Storyboard, SIGNAL(triggered()),this,SLOT(centerStoryboard()));

    connect(ui->actionVGA, SIGNAL(triggered()), this, SLOT(padSizeVGA()));
    connect(ui->actionSVGA, SIGNAL(triggered()), this, SLOT(padSizeSVGA()));
    connect(ui->actionXGA, SIGNAL(triggered()), this, SLOT(padSizeXGA()));
    connect(ui->actionnHD, SIGNAL(triggered()), this, SLOT(padSizenHD()));
    connect(ui->actionqHD, SIGNAL(triggered()), this, SLOT(padSizeqHD()));
    connect(ui->action720p, SIGNAL(triggered()), this, SLOT(padSize720p()));

    connect(ui->actionErase_All, SIGNAL(triggered()),this,SLOT(eraseAll()));
    connect(ui->actionDelete_drawing, SIGNAL(triggered()),this,SLOT(deleteDrawing()));
    connect(ui->actionMovePadLeft, SIGNAL(triggered()),this,SLOT(movePadLeft()));
    connect(ui->actionMovePadRight, SIGNAL(triggered()),this,SLOT(movePadRight()));

    connect(ui->leDialogue, &QLineEdit::textEdited, this, &MainWindow::updateCommentDialogue);
    connect(ui->leAction, &QLineEdit::textEdited, this, &MainWindow::updateCommentAction);
    connect(ui->leSlug, &QLineEdit::textEdited, this, &MainWindow::updateCommentSlug);
    connect(ui->leShot, SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    connect(ui->sbFrames, SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));
    connect(board, SIGNAL(selectionChanged()),this,SLOT(changeImage()));

    // set pen width and color
    connect(ui->actionSet_Pen_Color, SIGNAL(triggered()),this,SLOT(penPick()));
    connect(ui->actionSet_Pen_width, SIGNAL(triggered()),this,SLOT(penPick()));

    connect(ui->actionRun_Scene, SIGNAL(triggered()),this,SLOT(runAnimatic()));
    connect(ui->actionExport_pdf, SIGNAL(triggered()),this,SLOT(exportPdf()));
    connect(ui->actionShow_project_info, SIGNAL(triggered()),this,SLOT(showInfoDialog()));

}

void MainWindow::disconnectAllConnects()
{
    disconnect(ui->action_Add_audio, SIGNAL(triggered()),this,SLOT(addAudio()));
    disconnect(ui->action_Remove_audio, SIGNAL(triggered()),this,SLOT(rmAudio()));
    disconnect(ui->action_New_Scene, SIGNAL(triggered()),this,SLOT(newScene()));
    disconnect(ui->actionAppend_Sketchpad, SIGNAL(triggered()),this,SLOT(appendSketchPad()));
    disconnect(ui->actionInsert_Sketchpad, SIGNAL(triggered()),this,SLOT(insertSketchPad()));
    disconnect(ui->actionLoad_Pen_1, SIGNAL(triggered()),this,SLOT(penF5()));
    disconnect(ui->actionErase_Sketch_Pen, SIGNAL(triggered()),this,SLOT(eraseF5()));
    disconnect(ui->actionLoad_Pen_2, SIGNAL(triggered()),this,SLOT(penF6()));
    disconnect(ui->actionLoad_Pen_3, SIGNAL(triggered()),this,SLOT(penF7()));
    disconnect(ui->actionLoad_Pen_4, SIGNAL(triggered()),this,SLOT(penF8()));
    disconnect(ui->btnStandardPen, SIGNAL(pressed()),this,SLOT(penStd()));
    disconnect(ui->btnF5, SIGNAL(pressed()),this,SLOT(penF5()));
    disconnect(ui->btnF6, SIGNAL(pressed()),this,SLOT(penF6()));
    disconnect(ui->btnF7, SIGNAL(pressed()),this,SLOT(penF7()));
    disconnect(ui->btnF8, SIGNAL(pressed()),this,SLOT(penF8()));
    disconnect(ui->actionCenter_Storyboard, SIGNAL(triggered()),this,SLOT(centerStoryboard()));

    disconnect(ui->actionVGA, SIGNAL(triggered()), this, SLOT(padSizeVGA()));
    disconnect(ui->actionSVGA, SIGNAL(triggered()), this, SLOT(padSizeSVGA()));
    disconnect(ui->actionXGA, SIGNAL(triggered()), this, SLOT(padSizeXGA()));
    disconnect(ui->actionnHD, SIGNAL(triggered()), this, SLOT(padSizenHD()));
    disconnect(ui->actionqHD, SIGNAL(triggered()), this, SLOT(padSizeqHD()));
    disconnect(ui->action720p, SIGNAL(triggered()), this, SLOT(padSize720p()));

    disconnect(ui->actionErase_All, SIGNAL(triggered()),this,SLOT(eraseAll()));
    disconnect(ui->actionDelete_drawing, SIGNAL(triggered()),this,SLOT(deleteDrawing()));
    disconnect(ui->actionMovePadLeft, SIGNAL(triggered()),this,SLOT(movePadLeft()));
    disconnect(ui->actionMovePadRight, SIGNAL(triggered()),this,SLOT(movePadRight()));

    disconnect(ui->leDialogue, &QLineEdit::textEdited, this, &MainWindow::updateCommentDialogue);
    disconnect(ui->leAction, &QLineEdit::textEdited, this, &MainWindow::updateCommentAction);
    disconnect(ui->leSlug, &QLineEdit::textEdited, this, &MainWindow::updateCommentSlug);
    disconnect(ui->leShot, SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    disconnect(ui->sbFrames, SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));
    disconnect(board, SIGNAL(selectionChanged()),this,SLOT(changeImage()));

    // set pen width and color
    disconnect(ui->actionSet_Pen_Color, SIGNAL(triggered()),this,SLOT(penPick()));
    disconnect(ui->actionSet_Pen_width, SIGNAL(triggered()),this,SLOT(penPick()));

    disconnect(ui->actionRun_Scene, SIGNAL(triggered()),this,SLOT(runAnimatic()));
    disconnect(ui->actionExport_pdf, SIGNAL(triggered()),this,SLOT(exportPdf()));
    disconnect(ui->actionShow_project_info, SIGNAL(triggered()),this,SLOT(showInfoDialog()));
}

void MainWindow::disableStoryPad()
{
    ui->gvSketchPad->setEnabled(false);
    ui->leShot->setEnabled(false);
    ui->cbScenes->setEnabled(false);
    ui->sbFrames->setEnabled(false);
    ui->btnStandardPen->setEnabled(false);
    ui->btnF5->setEnabled(false);
    ui->btnF6->setEnabled(false);
    ui->btnF7->setEnabled(false);
    ui->btnF8->setEnabled(false);
    ui->leDialogue->setEnabled(false);
    ui->leAction->setEnabled(false);
    ui->leSlug->setEnabled(false);
    ui->menuLoad_Pen->setEnabled(false);
    ui->menuSettings->setEnabled(false);
    ui->menuSketchpad->setEnabled(false);
    ui->action_Save_Storyboard->setEnabled(false);
    ui->action_Add_audio->setEnabled(false);
    ui->action_Remove_audio->setEnabled(false);
    ui->actionExport_pdf->setEnabled(false);
    ui->actionShow_project_info->setEnabled(false);
}

void MainWindow::enableStoryPad()
{
    ui->gvSketchPad->setEnabled(true);
    ui->leShot->setEnabled(true);
    ui->cbScenes->setEnabled(true);
    ui->btnStandardPen->setEnabled(true);
    ui->btnF5->setEnabled(true);
    ui->btnF6->setEnabled(true);
    ui->btnF7->setEnabled(true);
    ui->btnF8->setEnabled(true);
    ui->sbFrames->setEnabled(true);
    ui->leDialogue->setEnabled(true);
    ui->leAction->setEnabled(true);
    ui->leSlug->setEnabled(true);
    ui->menuLoad_Pen->setEnabled(true);
    ui->menuSketchpad->setEnabled(true);
    ui->menuSettings->setEnabled(true);
    ui->action_Save_Storyboard->setEnabled(true);
    ui->action_Add_audio->setEnabled(true);
    ui->action_Remove_audio->setEnabled(true);
    ui->actionExport_pdf->setEnabled(true);
    ui->actionShow_project_info->setEnabled(true);
}

void MainWindow::closeActiveStoryboard()
{
    writeProjXML();
    writeStoryboardXML();
    disableScene();
}

void MainWindow::disableScene()
{
    ui->menuScene->setEnabled(false);
}

void MainWindow::enableScene()
{
    ui->menuScene->setEnabled(true);
}

void MainWindow::startUpdateImageTimer(int i)
{
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()),this,SLOT(updateImages()));
    updateTimer->start(i);
}

void MainWindow::movePad(int move)
{
    if (move > 0)       // move == 1
    {
        if (board->selectedItems().size() == 1
                && activePad + move == padThumbList.size())
            return;
    }
    else                // move == -1
    {
        if (board->selectedItems().size() == 1
                && activePad == 0)
            return;
    }

    padInfoList.swap(activePad, activePad + move);
    padThumbList.swap(activePad, activePad + move);

    reloadThumbs();
    /*
    QPixmap imageThumb;
    QGraphicsPixmapItem *pixItem;
    board->clear();
    for (int i = 0;i < padThumbList.size();i++){
        imageThumb = padThumbList.at(i);
        pixItem = new QGraphicsPixmapItem(imageThumb);
        board->addItem(pixItem);
        pixItem->setPos((i + 1) * padWidth - 165, 3);
        pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
    }
    */
    activePad = activePad + move;
    addThumbLabels();
    updateInfoLabels();
    disconnect(board,SIGNAL(selectionChanged()),this,SLOT(changeImage()));
    board->itemAt((activePad + 1) * padWidth - 155, 100, transform)->setSelected(true);
    ui->labActivePadInfo->setText(tr("%1 of %2")
                                  .arg(padInfo[shot]).arg(padInfoList.size()));
    connect(board,SIGNAL(selectionChanged()),this,SLOT(changeImage()));
    centerStoryboard();
}

void MainWindow::reloadThumbs()
{
    board->clear();
    QPixmap imageThumb;
    QGraphicsPixmapItem *pixItem;
    for (int i = 0;i < padThumbList.size();i++){
        imageThumb = padThumbList.at(i);
        pixItem = new QGraphicsPixmapItem(imageThumb);
        board->addItem(pixItem);
        pixItem->setPos((i + 1) * padWidth - 165, 3);
        pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
    }
}

void MainWindow::setPadSize(int w, int h)
{
    QString message = tr("All Images in all scenes,\nwill automatically be resized to %1x%2!")
            .arg(QString::number(w)).arg(QString::number(h));
    if (canvasW * h != canvasH * w)
        message = message + "\n" + "NB! NOT same aspect ratio!";
    int ret = QMessageBox::warning(this,
                                   tr("Are you sure?"),
                                   message,
                                   QMessageBox::Cancel | QMessageBox::Ok,
                                   QMessageBox::Cancel);
    if (ret == QMessageBox::Ok)
    {
        canvasW = w;
        canvasH = h;
        ui->gvSketchPad->setFixedSize(canvasW + 2, canvasH + 2);
        update();
    }
}

void MainWindow::resetPenList()
{
    sPenList.clear();
    for (int i = 0;i<5;i++)
    {
        sPen.penWidth = 6;
        sPen.penColor = QColor(80,80,80);
        sPenList.append(sPen);
    }
}

void MainWindow::initStoryboard()
{
    padInfoList.clear();
    padThumbList.clear();
    padInfo.clear();
    resetPenList();
    board->clear();
    lastNumber = 0;
    activePad = 0;
    activePen = 0;
    audioFileName = "";
    sketchPad = new SketchPad();
    sketchPad->setFixedSize(canvasW, canvasH);
    sketchPad->initPad(scenePath,lastNumber);
    padInfoList.append(padInfo);
    initPadInfo();
    initPad();
    pad->addWidget(sketchPad);
    update();
    sketchPad->setFocus();
}

void MainWindow::initPad()
{
    sketchPad->clearImage();
    QPixmap imageThumb;
    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    padThumbList.append(imageThumb);    // append pixmap to List...
    QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(imageThumb);
    board->addItem(pixItem);        //...and add it to storyboard as an Item..!
    pixItem->setPos(((activePad + 1) * padWidth) - 165 , 3); // place pixItem in storyboard

    startUpdateImageTimer(updateInterval);
}

void MainWindow::initPadInfo() /* sketchPad info as strings */
{           // initiates padinfo, and information about the pad
    padInfo.clear();
    padInfo.append(QString::number(lastNumber) + ".png");  // image filename!
    padInfo.append("");         // dialogue
    padInfo.append("");         // action
    padInfo.append("");         // slug
    padInfo.append(sceneDir);
    padInfo.append("");
    padInfo.append("50");
    padInfo.append("false");
    padInfoList.replace(activePad, padInfo);
            // update text and values in padInfo, when changes are made
    ui->leDialogue->clear();
    ui->leAction->clear();
    ui->leSlug->clear();
    ui->leShot->clear();
    ui->sbFrames->setValue(50);
}

void MainWindow::addThumbLabels()       // Adds labels to all thumbnails
{
    for (int i = 0;i<padInfoList.size();i++){
        QGraphicsTextItem *txt = new QGraphicsTextItem();
        txt->setHtml("<div style=\'background-color:#ffffff;\'> "
                     + padInfoList[i][scene] + ","
                     + padInfoList[i][shot] + ",("
                     + padInfoList[i][frames] + ")</div>");
        board->addItem(txt);
        txt->setPos(((i + 1)*padWidth) - 165 , 3);
    }
    ui->gvStoryboard->update();
}

void MainWindow::updateInfoLabels()
{
    if (padInfoList.size() > 0){
        QStringList sl = projFileName.split('/');
        QString s = sl.last();
        s.chop(17);
        MainWindow::setWindowTitle(tr("dastoryboard:     Project: %1     Scene: ").arg(s) + sceneDir);
        //MainWindow::setWindowFlags(Qt::);
        ui->labSceneInfo->setText(sceneDir);
        ui->labActivePadInfo->setText(tr("%1 of %2")
                                      .arg(padInfo[shot]).arg(padInfoList.size()));
        int fr = 0;
        for (int i = 0; i < padInfoList.size();i++){
            fr += padInfoList[i][frames].toInt();
        }
        ui->labFramesCountValue->setText(QString::number(fr));
        int mm = fr / (60 * fps);
        int ss = (fr - (mm * 60)) / fps ;
        int ff = fr - (mm * 60) - (ss * fps);
        ui->labTimeValue->setText(tr("%1:%2:%3","DO NOT TRANSLATE THIS").arg(QString::number(mm),2,'0')
                                  .arg(QString::number(ss),2,'0').arg(QString::number(ff),2,'0'));
    }else{
        MainWindow::setWindowTitle("dastoryboard");
        ui->labSceneInfo->setText("");
        ui->labActivePadInfo->setText("");
        ui->labFramesCountValue->setText("");
        ui->labTimeValue->setText("00:00:00");
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
            if (xmlreader.isStartElement() && xmlreader.name() == "projFilePath")
                projFilePath = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "sceneDir")
                sceneDir = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "Fps")
                fps = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "autoNumber")
                autoNumber = stringToBool(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scenePaths")
                scenePaths.append(xmlreader.readElementText());
        }
    }
    prefPath = projFilePath;
    updateScenelist();
}

void MainWindow::readStoryboardXML()
{
    QFile sbFile(sbFileName);           // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
        padInfoList.clear();            // clear list for reading file
        padInfo.clear();
        padThumbList.clear();
        sPenList.clear();
        board->clear();
        audioFileName = "";
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "scenePath")
                scenePath = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "videoFormat")
                videoFormat = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "audioFileName")
                audioFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "lastNumber")
                lastNumber = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePad")
                activePad = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePen")
                activePen = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "width")
                sPen.penWidth = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "red")
                sPen.penColor.setRed(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "green")
                sPen.penColor.setGreen(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "blue")
            {
                sPen.penColor.setBlue(xmlreader.readElementText().toInt());
                sPenList.append(sPen);
            }
            else if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "dialogue")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "action")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "slug")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scene")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showFrames")
            {
                padInfo.append(xmlreader.readElementText());
                sketchPad->image.load(scenePath + padInfo[fileName]);
                QPixmap imageThumb;
                imageThumb = QPixmap::fromImage(sketchPad->image);
                imageThumb = imageThumb.scaled(160, 120, Qt::KeepAspectRatio);
                padThumbList.append(imageThumb);
                QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(imageThumb);
                board->addItem(pixItem);                // place pixItem in storyboard
                pixItem->setPos((padThumbList.size() * padWidth) - 165 , 3);
                pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
                update();
                padInfoList.append(padInfo);
                padInfo.clear();
            }
        }
        if (audioFileName.length() < 1)
            ui->action_Remove_audio->setEnabled(false);
        else
            ui->action_Remove_audio->setEnabled(true);
        updateScenelist();
        board->setSceneRect(0,0,padThumbList.size() * padWidth, padHeight);
        ui->gvStoryboard->resize(padThumbList.size() * padWidth, padHeight);
        sPen = sPenList[activePen];
        sketchPad->setPenColor(sPen.penColor);
        sketchPad->setPenWidth(sPen.penWidth);
        padInfo = padInfoList.at(activePad);            // load active padinfo
        sketchPad->image.load(scenePath + padInfo[fileName]);
        ui->leDialogue->setText(padInfo[dialogue]);
        ui->leAction->setText(padInfo[action]);
        ui->leSlug->setText(padInfo[slug]);
        ui->labSceneInfo->setText(padInfo[scene]);
        ui->leShot->setText(padInfo[shot]);
        ui->sbFrames->setValue(padInfo[frames].toInt());
        setBtnColors();
        updateImages();
        addThumbLabels();
        board->itemAt((activePad+1)*padWidth-155, 100, transform)->setSelected(true);
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("File: %1 not found!").arg(sbFileName));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::setBtnColors()
{
    for (int i = 0; i < 5;i++){
        int r = sPenList[i].penColor.red();
        int g = sPenList[i].penColor.green();
        int b = sPenList[i].penColor.blue();
        int rgb = r+g+b;
        QColor c;
        if (rgb > 350) c = QColor(Qt::black);
        else c = QColor(Qt::white);
        if (i == 0){
            ui->btnStandardPen->setText(tr("Standard Pen: %1px").arg(QString::number(sPenList[i].penWidth)));
            ui->btnStandardPen->setStyleSheet(tr("QPushButton { background: %1 ; color: %2 }","DO NOT TRANSLATE THIS")
                                              .arg(sPenList[i].penColor.name()).arg(c.name()));
            if (i == activePen)
                ui->btnStandardPen->setText(tr("ACTIVE"));
        }else if (i == 1){
            ui->btnF5->setText(tr("F5 erasable: %1px","DO NOT TRANSLATE THIS").arg(QString::number(sPenList[i].penWidth)));
            ui->btnF5->setStyleSheet(tr("QPushButton { background: %1 ; color: %2 }","DO NOT TRANSLATE THIS")
                                              .arg(sPenList[i].penColor.name()).arg(c.name()));
            if (i == activePen)
                ui->btnF5->setText(tr("Erasable ACTIVE"));
        }else if (i == 2){
            ui->btnF6->setText(tr("F6: %1px","DO NOT TRANSLATE THIS").arg(QString::number(sPenList[i].penWidth)));
            ui->btnF6->setStyleSheet(tr("QPushButton { background: %1 ; color: %2 }","DO NOT TRANSLATE THIS")
                                              .arg(sPenList[i].penColor.name()).arg(c.name()));
            if (i == activePen)
                ui->btnF6->setText(tr("ACTIVE"));
        }else if (i == 3){
            ui->btnF7->setText(tr("F7: %1px","DO NOT TRANSLATE THIS").arg(QString::number(sPenList[i].penWidth)));
            ui->btnF7->setStyleSheet(tr("QPushButton { background: %1 ; color: %2 }","DO NOT TRANSLATE THIS")
                                              .arg(sPenList[i].penColor.name()).arg(c.name()));
            if (i == activePen)
                ui->btnF7->setText(tr("ACTIVE"));
        }else{
            ui->btnF8->setText(tr("F8: %1px","DO NOT TRANSLATE THIS").arg(QString::number(sPenList[i].penWidth)));
            ui->btnF8->setStyleSheet(tr("QPushButton { background: %1 ; color: %2 }","DO NOT TRANSLATE THIS")
                                              .arg(sPenList[i].penColor.name()).arg(c.name()));
            if (i == activePen)
                ui->btnF8->setText(tr("ACTIVE"));
        }
    }
}

QString MainWindow::loadSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (settings.contains("projFileName")){             // if projFileName exists...
        scenePath = settings.value("scenePath").toString();
        sceneDir = settings.value("sceneDir").toString();
        projFilePath = settings.value("projFilePath").toString();
        fps = settings.value("Fps").toInt();
        autoNumber = settings.value("autoNumber").toBool();
        videoFormat = settings.value("videoFormat").toString();
        canvasW = settings.value("canvasWidth").toInt();
        canvasH = settings.value("canvasHeight").toInt();
        return settings.value("projFileName").toString();
    }
    else
        return "";                                      // else return empty string
}

QString MainWindow::getSbFileName()
{
    return QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"),prefPath,
        tr("dastoryboard files (*.dastoryboard)"));
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

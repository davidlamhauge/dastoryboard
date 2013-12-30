#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    QMainWindow::showMaximized();
    setupConnects();

    updateInterval = 10000;     // millisecs. to be set as preference TODO
    scene = new QGraphicsScene(this);
    ui->gvSketchPad->setScene(scene);
    board = new QGraphicsScene(this);
    ui->gvStoryboard->setScene(board);
    ui->gvStoryboard->show();

    sbFileName = loadSettings();    // gets a fileName if it exists!
    if (sbFileName.isEmpty()){
        disableStoryPad();
    }else{
        QFile file(sbFileName );
        if (file.exists()){
            initStoryboard();
            readXML();
        }else{
            disableStoryPad();
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
    connect(ui->action_Save_Storyboard,SIGNAL(triggered()),this,SLOT(writeXML()));
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionAppend_Sketchpad,SIGNAL(triggered()),this,SLOT(appendSketchPad()));

    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penColor()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penWidth()));

    connect(ui->leComment,SIGNAL(textChanged(QString)),this,SLOT(updateComment()));
    connect(ui->leShot,SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    connect(ui->sbFrames,SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));
}

void MainWindow::startUpdateImageTimer(int i)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateImages()));
    timer->start(i);
}

void MainWindow::initStoryboard()
{
    padInfoList.clear();
    padInfo.clear();
    sPenList.clear();
    lastNumber = 0;
    activePad = 0;
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    sketchPad->initPad(sbFileName,lastNumber);
    padInfoList.append(padInfo);
    initPadInfo();
    scene->addWidget(sketchPad);
    update();
    sketchPad->setFocus();
}

void MainWindow::initPadInfo() /* sketchPad info as strings */
{
    padInfo.clear();
    padInfo.append(QString::number(lastNumber) + ".png");  // image filename!
    ui->leComment->clear();
    padInfo.append("");
    padInfo.append("false");
    ui->leShot->clear();
    padInfo.append("");
    padInfo.append("false");
    ui->sbFrames->setValue(50);
    padInfo.append("50");
    padInfo.append("false");
    padInfoList.replace(activePad,padInfo);
    sketchPad->clearImage();
    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    board->addPixmap(imageThumb);
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
    if (settings.contains("sbFileName")){
        return settings.value("sbFileName").toString();
    }
    else
        return "";
}

void MainWindow::saveSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.setValue("sbFileName", sbFileName);
}

void MainWindow::disableStoryPad()
{
    ui->gvSketchPad->setEnabled(false);
    ui->labShot->setEnabled(false);
    ui->labFrames->setEnabled(false);
    ui->leShot->setEnabled(false);
    ui->sbFrames->setEnabled(false);
    ui->labComments->setEnabled(false);
    ui->leComment->setEnabled(false);
    ui->menuSettings->setEnabled(false);
    ui->menuEdit->setEnabled(false);
    ui->action_Save_Storyboard->setEnabled(false);
}

void MainWindow::enableStoryPad()
{
    ui->gvSketchPad->setEnabled(true);
    ui->labShot->setEnabled(true);
    ui->labFrames->setEnabled(true);
    ui->leShot->setEnabled(true);
    ui->sbFrames->setEnabled(true);
    ui->labComments->setEnabled(true);
    ui->leComment->setEnabled(true);
    ui->menuSettings->setEnabled(true);
    ui->menuEdit->setEnabled(true);
    ui->action_Save_Storyboard->setEnabled(true);
}

void MainWindow::newStoryboard()
{
    sbFileName = QFileDialog::getSaveFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));

    if (!sbFileName.isEmpty()){
        if (!sbFileName.endsWith(".dastoryboard"))
            sbFileName += ".dastoryboard";
        sbFilePath = sbFileName.left(sbFileName.lastIndexOf("/") + 1);
        enableStoryPad();
        initStoryboard();
        startUpdateImageTimer(updateInterval);
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->accept(); // TODO!!!
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(sketchPad->penColor());
    if (newColor.isValid())
        sketchPad->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInteger(this, tr("Sketch Pad"),
                                            tr("Select pen width:"),
                                            sketchPad->penWidth(),
                                            1, 50, 1, &ok);
    if (ok)
        sketchPad->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About dastoryboard"),
            tr("<p><b>dastoryboard</b> is an Open Source storyboard software "
               "for your conveniance. Please enjoy!"));
}

void MainWindow::updateComment()
{
    padInfoList[activePad][1] = ui->leComment->text();
}

void MainWindow::updateShot()
{
    padInfoList[activePad][3] = ui->leShot->text();
}

void MainWindow::updateFrames()
{
    padInfoList[activePad][5] = QString::number(ui->sbFrames->value());
}

void MainWindow::updateImages()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][0]);
    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    board->update();
}

void MainWindow::appendSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][0]);
    padInfoList.append(padInfo);
    lastNumber += 1;
    activePad = padInfoList.size() - 1;
    initPadInfo();
    startUpdateImageTimer(updateInterval);
}

void MainWindow::insertSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][0]);
    padInfoList.insert(activePad+1,padInfo);
    lastNumber += 1;
    activePad += 1;
    initPadInfo();
    startUpdateImageTimer(updateInterval);
}


void MainWindow::writeXML()
{
    if (sbFileName.isEmpty()){
        sbFileName = QFileDialog::getSaveFileName(this,
            tr("Save dastoryboard information"), "",
            tr("dastoryboard files (*.dastoryboard)"));
    }

    if (!sbFileName.isEmpty()){
        updateImages();         // saves activeimages
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

            xmlwriter.writeEndElement();                // variables STOP
            xmlwriter.writeStartElement("sketchpads");  // sketchpads START

            for (int i = 0;i < padInfoList.size() ; i++){ // TODO !!!!!!!!!!!!
                padInfo = padInfoList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpad START
                xmlwriter.writeTextElement("fileName",padInfo[0]);
                xmlwriter.writeTextElement("comment",padInfo[1]);
                xmlwriter.writeTextElement("showComment",padInfo[2]);
                xmlwriter.writeTextElement("shot",padInfo[3]);
                xmlwriter.writeTextElement("showShot",padInfo[4]);
                xmlwriter.writeTextElement("frames",padInfo[5]);
                xmlwriter.writeTextElement("showFrames",padInfo[6]);
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

void MainWindow::readXML()
{
    QFile sbFile(sbFileName);
//    saveSettings();
    if (sbFile.open(QIODevice::ReadOnly)){
        padInfoList.clear();            // clear list for reading file
        padInfo.clear();
        padThumbList.clear();
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "lastNumber")
                lastNumber = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePad")
                activePad = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "comment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showComment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showShot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showFrames"){
                padInfo.append(xmlreader.readElementText());
                sbFilePath = sbFileName.left(sbFileName.lastIndexOf("/") + 1);
                sketchPad->image.load(sbFilePath + padInfo[0]);
                imageThumb = QPixmap::fromImage(sketchPad->image);
                imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
                padThumbList.append(imageThumb);
                QGraphicsPixmapItem *pixItem = new QGraphicsPixmapItem(imageThumb);
                board->addItem(pixItem);
                pixItem->setPos(5 + (padThumbList.size()*170),3);
                board->addPixmap(imageThumb);
                update();

                padInfoList.append(padInfo);
                padInfo.clear();
            }
        }
        padInfo = padInfoList.at(activePad);
        ui->leComment->setText(padInfo[1]);
        ui->leShot->setText(padInfo[3]);
        ui->sbFrames->setValue(padInfo[5].toInt());
        startUpdateImageTimer(updateInterval);
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


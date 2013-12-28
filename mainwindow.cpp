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

    scene = new QGraphicsScene(this);
    ui->gvSketchPad->setScene(scene);

    sbFileName = loadSettings();    // gets a fileName if it exists!
    if (sbFileName.isEmpty()){
        disableStoryPad();
    }else{
        QFile file(sbFileName );
        if (file.exists()){
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
    sketchPad->setFocus();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateImages()));
    timer->start(10000);
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

void MainWindow::appendSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][0]);
    padInfoList.append(padInfo);
    lastNumber += 1;
    activePad = padInfoList.size() - 1;
    initPadInfo();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateImages()));
    timer->start(10000);
}

void MainWindow::insertSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][0]);
    padInfoList.insert(activePad+1,padInfo);
    lastNumber += 1;
    activePad += 1;
    initPadInfo();
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateImages()));
    timer->start(10000);
}

void MainWindow::saveTest()
{
    sketchPad->image.save("/home/david/test.png");
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

}

void MainWindow::writeXML()
{
    if (sbFileName.isEmpty()){
        sbFileName = QFileDialog::getSaveFileName(this,
            tr("Save dastoryboard information"), "",
            tr("dastoryboard files (*.dastoryboard)"));
    }

    if (!sbFileName.isEmpty()){
        QFile file(sbFileName);
        if (file.open(QFile::ReadWrite)){
            saveSettings();
            QXmlStreamWriter xmlwriter(&file);
            xmlwriter.setAutoFormatting(true);
            xmlwriter.writeStartDocument();             // document START
            xmlwriter.writeStartElement("variables");   // variables START
            xmlwriter.writeTextElement("fileName",sbFileName);
            xmlwriter.writeTextElement("lastNumber",QString::number(lastNumber));
            xmlwriter.writeTextElement("activePad",QString::number(activePad));

            xmlwriter.writeEndElement();                // variables STOP
            xmlwriter.writeStartElement("storyboard");  // storyboard START

            for (int i = 0;i < padInfoList.size() ; i++){ // TODO !!!!!!!!!!!!
                padInfo = padInfoList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpads START
                xmlwriter.writeTextElement("fileName",padInfo[0]);
                xmlwriter.writeTextElement("comment",padInfo[1]);
                xmlwriter.writeTextElement("showComment",padInfo[2]);
                xmlwriter.writeTextElement("shot",padInfo[3]);
                xmlwriter.writeTextElement("showShot",padInfo[4]);
                xmlwriter.writeTextElement("frames",padInfo[5]);
                xmlwriter.writeTextElement("showFrames",padInfo[6]);
                xmlwriter.writeEndElement();                // sketchpads STOP
            }
            xmlwriter.writeEndDocument();        // document and storyboard STOP
        }

    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("No filename chosen!"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}
/*
void MainWindow::readXMLfile()
{
    framePhonemeList.clear();
    mouthList.clear();
    phonemeList.clear();
    tcList.clear();
    QFile audioFil(audioFileName);      // with the extension '.dalipsync'
    if (audioFil.open(QIODevice::ReadOnly)){

        QSettings settings("dalanima/dalipsync","dalipsync");
        settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
        settings.setValue("audioFileName", audioFileName);

        QXmlStreamReader xmlreader(&audioFil);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "audioFileName")
                audioFileName = xmlreader.readElementText();

            else if (xmlreader.isStartElement() && xmlreader.name() == "phoneme")
                framePhonemeList.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "comment")
                commentList.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "timecode")
                tcList.append(xmlreader.readElementText().toInt());

            else if (xmlreader.isStartElement() && xmlreader.name() == "mouthFileName")
                mouthFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "mouthFileNamePath")
                mouthFileNamePath = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "fps")
                fps = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "bitsPerSample")
                bitsPerSample = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "channels")
                channels = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "sampleRate")
                sampleRate = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "samplesPerFrame")
                samplesPerFrame = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "framesTotal")
                framesTotal = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "audioCodec")
                audioCodec = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "blockAlign")
                blockAlign = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "byteRate")
                byteRate = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "dataOffset")
                dataOffset = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "framesToPlay")
                framesToPlay = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "searchPreRoll")
                searchPreRoll = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activeFrame")
                activeFrame = xmlreader.readElementText().toInt();
        }
        samplesPerFrame = (int) sampleRate / fps;
        samplesTotal = samplesPerFrame * framesTotal;
    }
}
*/
void MainWindow::readXML()
{
    QFile file(sbFileName);

    saveSettings();
    if (file.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlreader(&file);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
        }
    }else{
        // TODO something went wrong
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


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

    sbFileName = loadSettings();    // gets a fileName if t exists!
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
    connect(ui->action_Save_Storyboard,SIGNAL(triggered()),this,SLOT(saveStorybard()));
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penColor()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penWidth()));

    connect(ui->btnApplyComment,SIGNAL(clicked()),this,SLOT(updateComment()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(cancelShotFrames()));
    connect(ui->btnApplyShotFrames,SIGNAL(clicked()),this,SLOT(updateShotFrames()));
}

void MainWindow::initStoryboard()
{

    padList.clear();
    padInfo.clear();
    sPenList.clear();
    lastNumber = 0;
    activePad = 0;
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    sketchPad->initPad(sbFilePath,lastNumber);
    padList.append(padInfo);
    initPadInfo();
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
}

void MainWindow::initPadInfo()
{
    QStringList sl = padList.at(activePad);
    sl.append(sbFilePath);
    sl.append(sbFileName);
    sl.append("");
    sl.append("false");
    sl.append("");
    sl.append("false");
    sl.append("50");
    sl.append("false");
    padList.replace(activePad,sl);
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
    ui->btnCancel->setEnabled(false);
    ui->btnApplyShotFrames->setEnabled(false);
    ui->labComments->setEnabled(false);
    ui->leComment->setEnabled(false);
    ui->btnApplyComment->setEnabled(false);
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
    ui->btnCancel->setEnabled(true);
    ui->btnApplyShotFrames->setEnabled(true);
    ui->labComments->setEnabled(true);
    ui->leComment->setEnabled(true);
    ui->btnApplyComment->setEnabled(true);
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
        sbFilePath = sbFileName;
        sbFileName = sbFileName.right(sbFileName.length() - sbFileName.lastIndexOf("/") - 1);
        sbFilePath.chop(sbFileName.length() - sbFileName.lastIndexOf("/") - 1);
        enableStoryPad();
        initStoryboard();
    }
}

void MainWindow::saveStorybard()
{
    writeXML();
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
}

void MainWindow::insertSketchPad()
{
}

void MainWindow::saveTest()
{
    sketchPad->image.save("/home/david/test.png");
}

void MainWindow::updateComment()
{
    /*
    QStringList sl = padList[activePad];
    sl[2] = ui->leComment->text();
    padList.replace(activePad,sl);*/
    padList[activePad][2] = ui->leComment->text();
}

void MainWindow::updateShotFrames()
{
}

void MainWindow::cancelShotFrames()
{
}

void MainWindow::writeXML()
{
    if (sbFileName.isEmpty()){
        sbFileName = QFileDialog::getOpenFileName(this,
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
            xmlwriter.writeTextElement("filePath",sbFilePath);
            xmlwriter.writeTextElement("lastNumber",QString::number(lastNumber));

            xmlwriter.writeEndElement();                // variables STOP
            xmlwriter.writeStartElement("storyboard");  // storyboard START

            for (int i = 0;i < padList.size() ; i++){ // TODO !!!!!!!!!!!!
                padInfo = padList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpads START
                xmlwriter.writeTextElement("filePath",padInfo[0]);
                xmlwriter.writeTextElement("fileName",padInfo[1]);
                xmlwriter.writeTextElement("comment",padInfo[2]);
                xmlwriter.writeTextElement("showComment",padInfo[3]);
                xmlwriter.writeTextElement("shot",padInfo[4]);
                xmlwriter.writeTextElement("showShot",padInfo[5]);
                xmlwriter.writeTextElement("frames",padInfo[6]);
                xmlwriter.writeTextElement("showFrames",padInfo[7]);
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

void MainWindow::readXML()
{
}
/*
void MainWindow::initStoryboard()
{
    padList.clear();
    lastNumber = 0;
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
    initPad(pad);

}

*/
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


/*
    QString s = audioFileName;
    s.chop(3);
    s += "dalipsync";
    QFile audioFil(s);
    if (audioFil.open(QFile::ReadWrite)){
        saveSettings();
        QXmlStreamWriter xmlwriter(&audioFil);
        xmlwriter.setAutoFormatting(true);
        xmlwriter.writeStartDocument();             // document START->
        xmlwriter.writeStartElement("lipsync");     // lipsync START

        xmlwriter.writeStartElement("variables");     // variables START
        xmlwriter.writeTextElement("audioFileName",audioFileName);
        xmlwriter.writeTextElement("mouthFileName",mouthFileName);
        xmlwriter.writeTextElement("mouthFileNamePath",mouthFileNamePath);
        xmlwriter.writeTextElement("fps",s.setNum(fps));
        xmlwriter.writeTextElement("bitsPerSample",s.setNum(bitsPerSample));
        xmlwriter.writeTextElement("channels",s.setNum(channels));
        xmlwriter.writeTextElement("sampleRate",s.setNum(sampleRate));
        xmlwriter.writeTextElement("samplesPerFrame",s.setNum(samplesPerFrame));
        xmlwriter.writeTextElement("framesTotal",s.setNum(framesTotal));
        xmlwriter.writeTextElement("audioCodec",s.setNum(audioCodec));
        xmlwriter.writeTextElement("blockAlign",s.setNum(blockAlign));
        xmlwriter.writeTextElement("byteRate",s.setNum(byteRate));
        xmlwriter.writeTextElement("dataOffset",s.setNum(dataOffset));
        xmlwriter.writeTextElement("framesToPlay",s.setNum(framesToPlay));
        xmlwriter.writeTextElement("searchPreRoll",s.setNum(searchPreRoll));
        xmlwriter.writeTextElement("activeFrame",s.setNum(activeFrame));
        xmlwriter.writeEndElement();                // variables STOP

        xmlwriter.writeStartElement("phonemes");    // phonemes START
        for (int i = 0;i < framesTotal; i++){
            xmlwriter.writeTextElement("phoneme", framePhonemeList[i]);
        }
        xmlwriter.writeEndElement();                // phonemes STOP
        xmlwriter.writeStartElement("comments");    // comments START
        for (int i = 0;i < framesTotal; i++){
            xmlwriter.writeTextElement("comment", commentList[i]);
        }
        xmlwriter.writeEndElement();                // comments STOP
        xmlwriter.writeStartElement("timecodes");   // timecodes START
        for (int i = 0;i < 3; i++){
            s.setNum(tcList[i]);
            xmlwriter.writeTextElement("timecode", s);
        }
        xmlwriter.writeEndElement();                // timecodes STOP

        xmlwriter.writeEndDocument();               // document and lipsync STOP

        QMessageBox msgBox;
        msgBox.setText(tr("Project file saved"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();

*/

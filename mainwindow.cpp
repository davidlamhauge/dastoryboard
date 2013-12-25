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
    loadSettings();
    scene = new QGraphicsScene(this);
    ui->gvSketchPad->setScene(scene);

    sbFileName = loadSettings();
    if (sbFileName.isEmpty()){
    }else{
    }

    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penColor()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penWidth()));

    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(saveTest()));
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

void MainWindow::writeXML()
{
    if (sbFileName.isEmpty()){
    }else{
    }
}

void MainWindow::readXML()
{
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

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

    sbFileName = loadSettings();    // gets a fieName if t exists!
    if (sbFileName.isEmpty()){
        disableStoryPad();
    }else{
        QFile file(sbFileName);
        if (file.exists()){
        }else{
            disableStoryPad();
        }
    }
/*
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
    */
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
    connect(ui->action_New_Storyboard,SIGNAL(triggered()),this,SLOT(newStoryboard()));
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penColor()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penWidth()));

    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(saveTest()));
}

void MainWindow::initStoryboard()
{
    padList.clear();
    lastNumber = 0;
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
    padInfo pad;
    initPad(pad);

}

/*
struct padInfo{
    QString filePath;   // full path, including the ending "/"
    QString fileName;   // the files name, without path
    QString comment;
    bool showComment;
    QString shot;
    bool showShot;
    int frames;
    bool showFrames;
};*/
void MainWindow::initPad(padInfo pad)
{
    pad.filePath = sbFilePath;
    lastNumber += 1;
    pad.fileName = QString::number(lastNumber) + ".png";
    ui->leComment->clear();
    pad.comment = ui->leComment->text();
    pad.showComment = false;
    ui->leShot->clear();
    pad.shot = ui->leShot->text();
    pad.showShot = false;
    ui->sbFrames->setValue(50);
    pad.frames = ui->sbFrames->value();
    pad.showFrames = false;
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

QString MainWindow::getSbFileName()
{
    return QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));
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
        sbFilePath = sbFileName.remove(".dastoryboard",Qt::CaseInsensitive);
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
            xmlwriter.writeStartElement("storyboard");  // storyboard START

            for (int i = 0;i < padList.size(); i++){
                xmlwriter.writeStartElement("sketchpad");  // sketchpads START
                xmlwriter.writeAttribute("comment",padList[i].comment);
                xmlwriter.writeAttribute("showComment",boolToString(padList[i].showComment));
                xmlwriter.writeAttribute("shot",padList[i].shot);
                xmlwriter.writeAttribute("showShot",boolToString(padList[i].showShot));
                xmlwriter.writeAttribute("frames",intToString(padList[i].frames));
                xmlwriter.writeAttribute("showFrames",boolToString(padList[i].showFrames));
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

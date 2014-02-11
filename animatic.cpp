#include "animatic.h"

animatic::animatic(const int &fpsec, const QString &scPath, QWidget *parent) :
    QDialog(parent)
{
    sc = new QGraphicsScene(QRectF(0,0,640,480));
    QBrush grayBrush(QColor(Qt::gray));
    sc->setBackgroundBrush(grayBrush);
    view = new QGraphicsView(sc);

    labStartPad = new QLabel(tr("Video start-pad:"));
    cbStartPad = new QComboBox();

    btnExportVideo = new QPushButton(tr("Export video"));
    btnExportImages = new QPushButton(tr("Export images"));
//    labAudioOffset = new QLabel(tr("Audio Offset in frames:"));
//    sbAudioOffset = new QSpinBox();

    btnFromStart = new QPushButton(tr("Play","Meaning: Play from chosen start"));
    btnStop = new QPushButton(tr("Stop"));
    btnQuit = new QPushButton(tr("Quit"));

    buttonlayout = new QGridLayout();
    buttonlayout->addWidget(labStartPad,0,0);
    buttonlayout->addWidget(cbStartPad,0,1);
    buttonlayout->addWidget(btnExportVideo,0,2);
    buttonlayout->addWidget(btnExportImages,1,2);
//    buttonlayout->addWidget(labAudioOffset,1,0);
//    buttonlayout->addWidget(sbAudioOffset,1,1);
    buttonlayout->addWidget(btnFromStart,2,0);
    buttonlayout->addWidget(btnStop,2,1);
    buttonlayout->addWidget(btnQuit,2,2);

    vertLayout = new QVBoxLayout();
    vertLayout->addWidget(view);
    vertLayout->addLayout(buttonlayout);

    setLayout(vertLayout);
    setWindowTitle(tr("View Animatic"));

    fps = fpsec;
    run = false;

    timer = new QTimer();
    loop = new QEventLoop();

    scenePath = scPath;
    QString s = scenePath;
    QStringList sl = s.split('/');
    sceneDir = sl[sl.size()-2];

    readXml();              // read XML and load pixmaps, filenames and frames into list
    initComboBox();
    initConnects();

//    sbAudioOffset->setMinimum(1);
//    sbAudioOffset->setMaximum(framesTotal);

    btnReadyMode();

//    qDebug() << (float) 83/fps;
}
/*
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (settings.contains("projFileName")){             // if projFileName exists...
        scenePath = settings.value("scenePath").toString();
        sceneDir = settings.value("sceneDir").toString();
        projFilePath = settings.value("projFilePath").toString();
        fps = settings.value("Fps").toInt();
        autoNumber = settings.value("autoNumber").toBool();
        videoFormat = settings.value("videoFormat").toString();

*/
void animatic::initConnects()
{
    connect(btnFromStart,SIGNAL(clicked()),this,SLOT(btnPlayClicked()));
    connect(btnStop,SIGNAL(clicked()),this,SLOT(btnStopClicked()));
    connect(btnQuit,SIGNAL(clicked()),this,SLOT(btnQuitClicked()));
    connect(btnExportVideo,SIGNAL(clicked()),this,SLOT(exportAnimatic()));
    connect(btnExportImages,SIGNAL(clicked()),this,SLOT(exportImages()));
}

void animatic::initComboBox()
{
    cbStartPad->clear();
    for (int i = 1;i < infoList.size()+1;i++){
        cbStartPad->addItem(QString::number(i));
    }
    cbStartPad->setCurrentIndex(0);
}

float animatic::calculateAudioOffset()
{
    float teller;
    teller = 0;
    if (cbStartPad->currentIndex() > 0){
        for (int i = 0; i < cbStartPad->currentIndex() + 1;i++)
            teller += infoList[i][frames].toFloat();
    }
    teller += (float) sbAudioOffset->value();
    return teller;
}

void animatic::renderVideo()
{
//        QTime t;                              // for checking time accuracy (1)
//        t.start();                            // for checking time accuracy (2)
    btnExportVideo->setEnabled(false);
    btnQuit->setEnabled(false);
    btnFromStart->setEnabled(false);

    proc = new QProcess(this);
    // Make images in numeric order
    exportImages();                         // separate function for exporting images

//    qDebug() << t.elapsed() << " ms, files made";     // for checking time accuracy (3)

    // Add parameters to a stringlist
    QStringList sl;
    sl << "-loglevel" << "info";
    sl << "-i" << scenePath + "tmp/" + sceneDir + "_%5d.png";
    QFile f(audioFileName);
    if (f.exists()){
        /*
        if (sbAudioOffset->value() > 1){    // for setting a audio offest. Does not work!
            float f;                        // probably because of libav obstruction...
            QString s;
            f = (float) sbAudioOffset->value()/fps;
            sl << "-itsoffset" << s.setNum(f);
            qDebug() << sl << " efter offset";
        }
        */
        sl << "-i" << audioFileName;
    }
    QString sr;
    sl << "-r" << sr.setNum(fps);

    sl << scenePath + sceneDir + videoFormat;

    // start process to export video
    proc->start("ffmpeg",sl);
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Export to video..."));
    msgBox.show();
    if (proc->state() > 0){      // if process is STARTING or RUNNING:
//        proc->setReadChannel(QProcess::StandardOutput);
        connect(proc,SIGNAL(readyReadStandardOutput()),this,SLOT(writeStat()));
        msgBox.setText(tr("Video is generating!\n"
                          "- Please wait...- it can take a while\n"
                          "This message box will close when finished."));
        while (proc->state() > 0){
            sleep(4);
        }
        disconnect(proc,SIGNAL(readyRead()),this,SLOT(writeStat()));
        msgBox.setText(tr("Deleting images..."));
        sl.clear();
        sl << "-r" << "-d" << scenePath + "tmp/";
        proc->start("rm",sl);
        msgBox.close();
    }else{
        sl.clear();
        sl << "-r" << "-d" << scenePath + "tmp/";
        proc->start("rm",sl);
        QMessageBox msgBox;
        msgBox.setText(tr("Video export failed!\nIs Ffmpeg installed and in the PATH?"));
        msgBox.exec();
    }
//    qDebug() << t.elapsed() << " ms, video produced";     // for checking time accuracy (3)
    //
    btnExportVideo->setEnabled(true);
    btnFromStart->setEnabled(true);
    btnQuit->setEnabled(true);
    btnQuit->setFocus();
//    qDebug() << t.elapsed() << " ms, dir+files deleted";     // for checking time accuracy (3)
}

void animatic::btnPlayClicked()
{
    if (infoList.size() > 0){
        btnPlayMode();
        run = true;
//        QTime t;                              // for checking time accuracy (1)
//        t.start();                            // for checking time accuracy (2)
        for (int i = cbStartPad->currentIndex();i < infoList.size();i++){
            setWindowTitle(tr("Image number: %1").arg(infoList[i][shot]));
            sc->addPixmap(pixmapList[i]);                       // add pixmap
            sleep((1000/fps) * infoList[i][frames].toInt());    // sleep x millisecs
            if (run == false)                                   // break if run == false
                break;
        }
//        qDebug() << t.elapsed() << " ms";     // for checking time accuracy (3)
        setWindowTitle(tr("View Animatic"));
        sc->clear();
        btnReadyMode();
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("No images to show!!"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void animatic::sleep(int milliseconds) {
    timer->setInterval(milliseconds);
    timer->start();
    connect(timer, SIGNAL(timeout()), loop, SLOT(quit()));
    loop->exec();
}

void animatic::btnStopClicked()
{
    run = false;        // set run to false, and...
    loop->exit();       // ...exit the loop, to stop animatic from running
}

void animatic::btnQuitClicked()
{
    emit aniClose();
    close();            // close window
}

void animatic::exportAnimatic()
{
    QFile f(scenePath + sceneDir + videoFormat);
    if (f.exists()){
        int ret = QMessageBox::warning(this, tr("Erase video-file"),
                                       tr("The file %1 exists!\n"
                                          "Do you want to overwrite it?").arg(sceneDir + videoFormat),
                                       QMessageBox::No | QMessageBox::Yes,
                                       QMessageBox::No);
        switch (ret)
        {
        case QMessageBox::No:
            btnQuit->setFocus();
            break;
        case QMessageBox::Yes:;
            f.remove();
            renderVideo();
        default:;
        }
    }else
        renderVideo();
}

void animatic::exportImages()
{
    proc = new QProcess(this);
    // Make directory for images to convert later
    proc->start("mkdir",QStringList() << scenePath + "tmp/");
    while (proc->state() > 0)
        sleep(2);
    int teller = 1;
    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Exporting images..."));
    msgBox.setText(tr("Generating image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
    msgBox.show();

    QString fname;
    for (int i = 0; i < pixmapList.size();i++){
        QImage image = pixmapList[i].toImage();
        for (int j = 0;j < infoList[i][frames].toInt();j++){
            if (j == 0){ // IF it is the first drawing
                msgBox.setText(tr("Generating image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
                 fname = scenePath + "tmp/" + sceneDir + QString("_%1.png").arg(QString::number(teller),5,'0');
                if (image.save(fname))
                    teller += 1;
                else{
                    msgBox.setText(tr("Error while saving image..."));
                    break;
                }
            }else{
                msgBox.setText(tr("Generating image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
                proc->start("cp",QStringList() << fname
                           << scenePath + "tmp/" + sceneDir +  QString("_%1.png").arg(QString::number(teller),5,'0'));
                while (proc->state() > 0)
                    sleep(2);
                teller += 1;
            }
        }
    }
    msgBox.close();
}

void animatic::writeStat()
{
    QString s = (QString) proc->readAllStandardOutput();
    qDebug() << s << " debug";
}

void animatic::readXml()
{
    framesTotal = 0;
    QFile sbFile(scenePath + sceneDir + ".dastoryboard");    // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "videoFormat")
                videoFormat = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "audioFileName")
                audioFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames"){
                infos.append(xmlreader.readElementText());
                QPixmap im;
                if (im.load(scenePath + infos[fileName])){
                    pixmapList.append(im);  // add pixmap to pixmapList
                    framesTotal += infos[frames].toInt();
                    infoList.append(infos); // append infos to the infoList, and..
                    infos.clear();          // .. clear the infos
                }
            }
        }
        infos = infoList[0];
    }
}

void animatic::btnReadyMode()
{
    btnFromStart->setEnabled(true);
    btnStop->setEnabled(false);
    btnFromStart->setFocus();
}

void animatic::btnPlayMode()
{
    btnFromStart->setEnabled(false);
    btnStop->setEnabled(true);
    btnStop->setFocus();
}

void animatic::btnDisableAll()
{
    btnFromStart->setEnabled(false);
    btnStop->setEnabled(false);
    btnQuit->setEnabled(false);
    btnExportVideo->setEnabled(false);
}

void animatic::btnEnableAll()
{
    btnFromStart->setEnabled(true);
    btnStop->setEnabled(true);
    btnQuit->setEnabled(true);
    btnExportVideo->setEnabled(true);
}


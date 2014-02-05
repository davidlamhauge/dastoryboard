#include "animatic.h"

animatic::animatic(const int &fpsec, const QString &projPath, const QString &scDir, QWidget *parent) :
    QDialog(parent)
{
    sc = new QGraphicsScene(QRectF(0,0,640,480));
    QBrush grayBrush(QColor(Qt::gray));
    sc->setBackgroundBrush(grayBrush);
    view = new QGraphicsView(sc);

    labStartPad = new QLabel(tr("From:"));
    startPad = new QComboBox();

    btnExport = new QPushButton(tr("Export video"));

    btnFromStart = new QPushButton(tr("Play","Meaning: Play from chosen start"));
    btnStop = new QPushButton(tr("Stop"));
    btnQuit = new QPushButton(tr("Quit"));

    buttonlayout = new QGridLayout();
    buttonlayout->addWidget(labStartPad,0,0);
    buttonlayout->addWidget(startPad,0,1);
    buttonlayout->addWidget(btnExport,0,2);
    buttonlayout->addWidget(btnFromStart,1,0);
    buttonlayout->addWidget(btnStop,1,1);
    buttonlayout->addWidget(btnQuit,1,2);

    vertLayout = new QVBoxLayout();
    vertLayout->addWidget(view);
    vertLayout->addLayout(buttonlayout);

    setLayout(vertLayout);
    setWindowTitle(tr("View Animatic"));

    projFilePath = projPath;
    sceneDir = scDir;
    fps = fpsec;
    run = false;

    timer = new QTimer();
    loop = new QEventLoop();
    readXml();              // read XML and load pixmaps, filenames and frames into list
    initComboBox();
    initConnects();

    btnReadyMode();
}

void animatic::initConnects()
{
    connect(btnFromStart,SIGNAL(clicked()),this,SLOT(btnPlayClicked()));
    connect(btnStop,SIGNAL(clicked()),this,SLOT(btnStopClicked()));
    connect(btnQuit,SIGNAL(clicked()),this,SLOT(btnQuitClicked()));
    connect(btnExport,SIGNAL(clicked()),this,SLOT(exportAnimatic()));
}

void animatic::initComboBox()
{
    startPad->clear();
    for (int i = 1;i < infoList.size()+1;i++){
        startPad->addItem(QString::number(i));
    }
    startPad->setCurrentIndex(0);
}

void animatic::btnPlayClicked()
{
    if (infoList.size() > 0 && proc.state() == 0){
        btnPlayMode();
        run = true;
//        QTime t;                              // for checking time accuracy (1)
//        t.start();                            // for checking time accuracy (2)
        for (int i = startPad->currentIndex();i < infoList.size();i++){
            sc->addPixmap(pixmapList[i]);                       // add pixmap
            sleep((1000/fps) * infoList[i][frames].toInt());    // sleep x millisecs
            if (run == false)                                   // break if run == false
                break;
        }
//        qDebug() << t.elapsed() << " ms";     // for checking time accuracy (3)
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
//        QTime t;                              // for checking time accuracy (1)
//        t.start();                            // for checking time accuracy (2)
    QFile f(projFilePath + sceneDir + "/" + sceneDir + ".mp4");
    if (f.exists()){
        int ret = QMessageBox::warning(this, tr("Erase mpg-file"),
                                       tr("The file %1 exists!\n"
                                          "Do you want to overwrite it?").arg(sceneDir + ".mp4"),
                                       QMessageBox::No | QMessageBox::Yes,
                                       QMessageBox::No);
        switch (ret)
        {
        case QMessageBox::No:
            btnQuit->setFocus();
            break;
        case QMessageBox::Yes:;
            f.remove();
        default:;
        }
    }

    btnExport->setEnabled(false);
    btnQuit->setEnabled(false);
    btnFromStart->setEnabled(false);
    // Make directory for images to convert later
    proc.start("mkdir",QStringList() << projFilePath + sceneDir + "/tmp/");
    while (proc.state() > 0)
        sleep(2);
//    qDebug() << t.elapsed() << " ms, directory tmp made";     // for checking time accuracy (3)
    // Make images in numeric order
    int teller = 1;

    QMessageBox msgBox;
    msgBox.setWindowTitle(tr("Export to video..."));
    msgBox.setText(tr("Image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
    msgBox.show();

    QString fname;
    for (int i = 0; i < pixmapList.size();i++){
        QImage image = pixmapList[i].toImage();
        for (int j = 0;j < infoList[i][frames].toInt();j++){
            if (j == 0){ // IF it is the first drawing
                msgBox.setText(tr("Image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
                 fname= projFilePath + sceneDir + "/tmp/" + sceneDir +
                        tr("_%1.png","DO NOT TRANSLATE").arg(QString::number(teller),5,'0');
                if (image.save(fname))
                    teller += 1;
                else{
                    msgBox.setText(tr("Error while saving image..."));
                    break;
                }
            }else{
                msgBox.setText(tr("Image %1 of %2").arg(QString::number(teller)).arg(QString::number(framesTotal)));
                proc.start("cp",QStringList() << fname
                           << projFilePath + sceneDir + "/tmp/" + sceneDir +
                           tr("_%1.png","DO NOT TRANSLATE").arg(QString::number(teller),5,'0'));
                while (proc.state() > 0)
                    sleep(2);
                    teller += 1;
            }
        }
    }
//    qDebug() << t.elapsed() << " ms, files made";     // for checking time accuracy (3)
    QStringList sl;
    sl << "-i" << projFilePath + sceneDir + "/tmp/" + sceneDir + "_%5d.png";
    QString sr;
    sl << "-r" << sr.setNum(fps) ;
    sl << projFilePath + sceneDir + "/" + sceneDir + ".mp4";
    msgBox.setText(tr("Video is generated - Please wait..."));
    proc.start("ffmpeg",sl);
    while (proc.state() > 0)
        sleep(4);
//    qDebug() << t.elapsed() << " ms, video produced";     // for checking time accuracy (3)
    sl.clear();
    sl << "-r" << "-d" << projFilePath + sceneDir + "/tmp/";
    proc.start("rm",sl);
    msgBox.close();
    //
    btnExport->setEnabled(true);
    btnFromStart->setEnabled(true);
    btnQuit->setEnabled(true);
    btnQuit->setFocus();
//    qDebug() << t.elapsed() << " ms, files and dir deleted";     // for checking time accuracy (3)
}

void animatic::readXml()
{
    framesTotal = 0;
    QString activePath = projFilePath + sceneDir + "/";
    QFile sbFile(activePath + sceneDir + ".dastoryboard");    // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                infos.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames"){
                infos.append(xmlreader.readElementText());
                QPixmap im;
                if (im.load(activePath + infos[fileName])){
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
    btnExport->setEnabled(false);
}

void animatic::btnEnableAll()
{
    btnFromStart->setEnabled(true);
    btnStop->setEnabled(true);
    btnQuit->setEnabled(true);
    btnExport->setEnabled(true);
}


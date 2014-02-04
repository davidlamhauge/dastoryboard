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
    if (infoList.size() > 0){
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
    QFile f(projFilePath + sceneDir + "/" + sceneDir + ".mp4");
    if (f.exists()){
        int ret = QMessageBox::warning(this, tr("Erase mp4-file"),
                                       tr("The file %1 exists!\n"
                                          "Do you want to overwrite it?").arg(sceneDir + ".mp4"),
                                       QMessageBox::No | QMessageBox::Yes,
                                       QMessageBox::No);
        switch (ret)
        {
        case QMessageBox::No:
            btnQuit->setFocus();
            break;
        default:;
        }
    }
    btnExport->setEnabled(false);
    btnQuit->setEnabled(false);
    btnFromStart->setEnabled(false);
    f.remove();
    int teller = 1;
    for (int i = 0; i < pixmapList.size();i++){
        QImage image = pixmapList[i].toImage();
        for (int j = 0;j < infoList[i][frames].toInt();j++){
            image.save(projFilePath + sceneDir + "/" + sceneDir +
                       tr("_%1.png","DO NOT TRANSLATE").arg(QString::number(teller),5,'0'));
            teller += 1;
        }
    }
    QStringList sl;
    sl << "-i" << projFilePath + sceneDir + "/" + sceneDir + "_%5d.png";
    QString sr;
    sl << "-r" << sr.setNum(fps) ;
    sl << projFilePath + sceneDir + "/" + sceneDir + ".mp4";
    proc.start("ffmpeg",sl);
    while (proc.state() > 0)
        sleep(5);
    sl.clear();
    QDir dir(projFilePath + sceneDir + "/");
    dir.setNameFilters(sl << sceneDir + "*.png");
    dir.setFilter(QDir::Files);
    foreach (QString dirfile, dir.entryList()) {
        dir.remove(dirfile);
    }
    btnExport->setEnabled(true);
    btnFromStart->setEnabled(true);
    btnQuit->setEnabled(true);
    btnQuit->setFocus();
}

void animatic::readXml()
{
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


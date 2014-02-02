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

    btnFromStart = new QPushButton(tr("Play","Meaning: Play from chosen start"));
    btnStop = new QPushButton(tr("Stop"));
    btnQuit = new QPushButton(tr("Quit"));

    buttonlayout = new QGridLayout();
    buttonlayout->addWidget(labStartPad,0,0);
    buttonlayout->addWidget(startPad,0,1);
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
    connect(btnStop,SIGNAL(clicked()),this,SLOT(btnPauseClicked()));
    connect(btnQuit,SIGNAL(clicked()),this,SLOT(btnQuitClicked()));
    connect(timer, SIGNAL(timeout()),this,SLOT(clearTimer()));
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
        QTime t;
        t.start();
        for (int i = startPad->currentIndex();i < infoList.size();i++){
            sc->addPixmap(pixmapList[i]);
            view->update();
            sleep((1000/fps) * infoList[i][frames].toInt());
        }
        int tid = t.elapsed();
        qDebug() << tid << " ms";
        sc->clear();
        view->update();
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

void animatic::btnPauseClicked()
{

}

void animatic::btnQuitClicked()
{
    close();
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
                    pixmapList.append(im);
                    infoList.append(infos);
                    infos.clear();
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
}

void animatic::btnPlayMode()
{
    btnFromStart->setEnabled(false);
    btnStop->setEnabled(true);
}

void animatic::clearTimer()
{
    timer->stop();
    return;
}

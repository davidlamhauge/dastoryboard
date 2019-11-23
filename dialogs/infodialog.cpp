#include "infodialog.h"

infodialog::infodialog(QWidget *parent) :
    QDialog(parent)
{
    // header in htlm sized letters
    labHeader = new QLabel(tr("dastoryboard info:"));
    labHeader->setStyleSheet("background-color: gray;"
                             "border-radius: 20px;"
                             "padding: 10px;"
                             "font: bold 20px;"
                             "color: white;");

    // project name
    labProj = new QLabel(tr("Project name: "));
    labProjInfo = new QLabel();

    // scene name
    labScene = new QLabel(tr("Scene name: "));
    labSceneInfo = new QLabel();

    // number of images + accumulated filesizes
    labImages = new QLabel(tr("Number of shots: "));
    labImagesInfo = new QLabel();

    // frames total
    labFrames = new QLabel(tr("Total number of frames: "));
    labFramesInfo = new QLabel();

    // frames per second
    labFps = new QLabel(tr("Frames per second: "));
    labFpsInfo = new QLabel();

    // Timecode + human readable (2 min. 23,62 sec.) TODO
    labDuration = new QLabel(tr("Duration: "));
    labDurationInfo = new QLabel();

    // filename + filesize
    labAudio = new QLabel(tr("Audio file: "));
    labAudioInfo = new QLabel();

    // close button
    btnClose = new QPushButton(tr("Close"));

    // layouts...
    buttonLayout = new QGridLayout();
    buttonLayout->addWidget(labProj,0,0);
    buttonLayout->addWidget(labProjInfo,0,1);
    buttonLayout->addWidget(labScene,1,0);
    buttonLayout->addWidget(labSceneInfo,1,1);
    buttonLayout->addWidget(labImages,2,0);
    buttonLayout->addWidget(labImagesInfo,2,1);
    buttonLayout->addWidget(labFrames,3,0);
    buttonLayout->addWidget(labFramesInfo,3,1);
    buttonLayout->addWidget(labFps,4,0);
    buttonLayout->addWidget(labFpsInfo,4,1);
    buttonLayout->addWidget(labDuration,5,0);
    buttonLayout->addWidget(labDurationInfo,5,1);
    buttonLayout->addWidget(labAudio,6,0);
    buttonLayout->addWidget(labAudioInfo,6,1);
    buttonLayout->addWidget(btnClose,8,0);

    layout = new QVBoxLayout();
    layout->addWidget(labHeader);
    layout->addLayout(buttonLayout);
    setLayout(layout);
    setWindowTitle(tr("Information"));

    connect(btnClose,SIGNAL(clicked()),this,SLOT(closeDialog()));
}

void infodialog::closeDialog()
{
    close();
}

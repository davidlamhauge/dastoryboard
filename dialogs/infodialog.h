#ifndef INFODIALOG_H
#define INFODIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>

class infodialog : public QDialog
{
    Q_OBJECT
public:
    explicit infodialog(QWidget *parent = nullptr);

    QLabel *labHeader;          // header in htlm sized letters

    QLabel *labProj;
    QLabel *labProjInfo;        // project name

    QLabel *labScene;
    QLabel *labSceneInfo;       // scene name

    QLabel *labImages;
    QLabel *labImagesInfo;      // number of images + accumulated filesizes

    QLabel *labFrames;
    QLabel *labFramesInfo;      // frames total

    QLabel *labFps;
    QLabel *labFpsInfo;         // frames per second total

    QLabel *labDuration;
    QLabel *labDurationInfo;    // Timecode + human readable (2 min. 23,62 sec.)

    QLabel *labAudio;
    QLabel *labAudioInfo;       // filename + filesize

    QPushButton *btnClose;      // close button

    QGridLayout *buttonLayout;
    QVBoxLayout *layout;


signals:

public slots:
    void closeDialog();

};

#endif // INFODIALOG_H

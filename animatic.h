#ifndef ANIMATIC_H
#define ANIMATIC_H

#include <QDialog>
#include <QColorDialog>
#include <QLabel>
#include <QPushButton>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QGraphicsScene>
#include <QGraphicsView>
#include <QFile>
#include <QDir>
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QComboBox>
#include <QSpinBox>
#include <QProcess>
#include <QByteArray>

class animatic : public QDialog
{
    Q_OBJECT
public:
    explicit animatic(const int &fpsec, const QString &scPath, QWidget *parent = 0);

    enum padInfoLabels {
        fileName    = 0,
        shot        = 1,
        frames      = 2
    };

    QGraphicsScene *sc;
    QGraphicsView *view;
    QLabel *labStartPad;
    QComboBox *cbStartPad;
    QPushButton *btnExportVideo;
    QPushButton *btnExportImages;

    QLabel *labFromStart;
    QPushButton *btnFromStart;
    QLabel *labStop;
    QPushButton *btnStop;
    QLabel *labQuit;
    QPushButton *btnQuit;
    QVBoxLayout *vertLayout;
    QGridLayout *buttonlayout;

signals:
    void aniClose();

public slots:
    void btnPlayClicked();
    void btnStopClicked();
    void btnQuitClicked();
    void exportAnimatic();      // export animatic to mp4 or avi
    void exportImages();        // export images to scenepath/tmp
    void writeStat();
    void calculateAudioOffset();    // calculates the float audioOffset

private:
    void initConnects();
    void initComboBox();
    void renderVideo();             // the actual rendering of the video
    void readXml();
    void btnReadyMode();
    void btnPlayMode();
    void btnDisableAll();
    void btnEnableAll();
    void sleep(int milliseconds);

    int fps;
    int framesTotal;                // frames in the animatic from start to end
    float audioOffset;              // offset from beginning of audio-file
    bool run;

    QTimer *timer;
    QEventLoop *loop;
    QProcess *proc;
    QString projFilePath;
    QString sceneDir;           // scene directory, without slashes
    QString videoFormat;        // .ogv or .mpg
    QString scenePath;          // path to scene inclusive the last '/'
    QString audioFileName;      // absolute path to audiofile

    QStringList infos;                // fileName, comment, shot name etc
    QList<QStringList> infoList;     // list of stringlists with padInfo
    QList<QPixmap> pixmapList;          // list of all pixmaps in the animatic
};

#endif // ANIMATIC_H

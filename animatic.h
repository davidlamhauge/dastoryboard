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
#include <QXmlStreamReader>
#include <QDebug>
#include <QMessageBox>
#include <QTimer>
#include <QTime>
#include <QEventLoop>
#include <QComboBox>

class animatic : public QDialog
{
    Q_OBJECT
public:
    explicit animatic(const int &fpsec, const QString &projPath, const QString &scDir, QWidget *parent = 0);

    enum padInfoLabels {
        fileName    = 0,
        frames      = 1,
    };

    QGraphicsScene *sc;
    QGraphicsView *view;
    QLabel *labStartPad;
    QComboBox *startPad;

    QLabel *labFromStart;
    QPushButton *btnFromStart;
    QLabel *labStop;
    QPushButton *btnStop;
    QLabel *labQuit;
    QPushButton *btnQuit;
    QVBoxLayout *vertLayout;
    QGridLayout *buttonlayout;

signals:

public slots:
    void btnPlayClicked();
    void btnPauseClicked();
    void btnQuitClicked();
    void clearTimer();

private:
    void initConnects();
    void initComboBox();
    void readXml();
    void btnReadyMode();
    void btnPlayMode();
    void sleep(int milliseconds);

    int fps;

    QTimer *timer;
    QEventLoop *loop;

    QString projFilePath;
    QString sceneDir;

    QStringList infos;                // fileName, comment, shot name etc
    QList<QStringList> infoList;     // list of stringlists with padInfo
    QList<QPixmap> pixmapList;          // list of all pixmaps in the animatic
};

#endif // ANIMATIC_H

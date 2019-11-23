#ifndef TEXTOUTPUT_H
#define TEXTOUTPUT_H

#include <QDialog>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextDocument>
#include <QPrinter>
#include <QPainter>
#include <QDebug>

class textOutput : public QDialog
{
    Q_OBJECT
public:                 // 's' is the absolute path to the scene
    explicit textOutput(const QString &s, QWidget *parent = nullptr);

    enum padInfoLabels {
        fileName    = 0,
        comment     = 1,
        scene       = 2,
        shot        = 3,
        frames      = 4
    };

signals:

public slots:
    void exportPdf();               // exports pdf with drawings, comments etc

private:
    void readxml();                 // reads xml and finds necessary information

    int framesTotal;                // frames in the animatic from start to end

    QString sceneDir;               // scene directory, without slashes
    QString videoFormat;            // .ogv or .mpg
    QString scenePath;              // path to scene inclusive the last '/'
    QString audioFileName;          // absolute path to audiofile
    QString sceneName;              // scenename as absolute path

    QStringList infos;              // fileName, comment, shot name etc
    QList<QStringList> infoList;    // list of stringlists with padInfo
    QList<QPixmap> pixmapList;      // list of all pixmaps in the animatic

};

#endif // TEXTOUTPUT_H

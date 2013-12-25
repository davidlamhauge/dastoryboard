#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QtGui>
#include <QMainWindow>

class SketchPad;

struct padInfo{
    QString filePath;   // full path, including the ending "/"
    QString fileName;   // the files name, without path
    QString comment;
    bool showComment;
    QString shot;
    bool showShot;
    int frames;
    bool showFrames;
};

struct standardPen{     // 4 standardpenne kan gemmes
    int penWidth;
    QColor penColor;
};

namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void disableStoryPad();     // disables storypad + buttons etc
    void enableStoryPad();      // enables storypad + buttons etc
    void newStoryboard();       // new storyboard created and initialised
    void saveStorybard();       // storyboard is saved to
    void saveSettings();        // saves settings
    void penColor();            // set new Pen Color from colorpicker
    void penWidth();            // set new Pen Width from 1 to 99 pixels
    void about();
    void appendSketchPad();     // saves active pad and appends new       ALT+A
    void insertSketchPad();     // saves active pad and inserts new       ALT+I
    void saveTest();            // dummy to test image-filesave

private:
    Ui::MainWindow *ui;

    void setupConnects();       // initiates connects
    void initStoryboard();      // initiaqtes a new storyboard
    void initPad(padInfo pad);  // initates pad and its values in struct
    QString loadSettings();     // returns sbFileName or ""
    QString sbFileName;         // storyboard filename, absolute path
    QString sbFilePath;         // path to sbFile, incl. last "/"
    QString getSbFileName();    // gets new storybard filename
    void writeXML();            // writes .dastoryboard info to xml-file
    void readXML();             // reads .dastoryboard info from xml file
    QString boolToString(bool b);
    QString intToString(int i);
    int strToInt(QString s);
    bool stringToBool(QString s);

    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QGraphicsScene *scene;
    SketchPad *sketchPad;
    QList<padInfo> padList;
    int lastNumber;             // last number given to a sketchpad
};

#endif // MAINWINDOW_H

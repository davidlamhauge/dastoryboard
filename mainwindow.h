#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QtGui>
#include <QMainWindow>

class SketchPad;


struct standardPen{     // 4 standard pens can be saved in F5 ,F6, F7 og F8
    int penWidth;       // The pen in F5 is the sketchcolor that can be erased
    QColor penColor;    // if the artist presses SHIFT + F5
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
    void writeXML();            // writes .dastoryboard info to xml-file
    void saveSettings();        // saves settings
    void penColor();            // set new Pen Color from colorpicker
    void penWidth();            // set new Pen Width from 1 to 99 pixels
    void about();
    void appendSketchPad();     // saves active pad and appends new       ALT+A
    void insertSketchPad();     // saves active pad and inserts new       ALT+I
    void updateComment();       // udates comment for pad struct
    void updateShot();
    void updateFrames();        // updates shot and frames for pad struct
    void updateSaveImages();    // saves activeImage + thumbnail
    void updateImages();        // repaints storyboard

private:
    Ui::MainWindow *ui;

    void setupConnects();       // initiates connects
    void startSaveImageTimer(int i); // starts timer for 'i' millisecs
    void startUpdateImageTimer(int i); // starts timer for 'i' millisecs
    void initStoryboard();      // initiaqtes a new storyboard
    void initPadInfo();         // initiates values n padInfo
    QString loadSettings();     // returns sbFileName or ""
    QString sbFileName;         // storyboard filename, absolute path
    QString sbFilePath;         // filepath, including the last '/'
    QString getSbFileName();    // gets new storybard filename
    void readXML();             // reads .dastoryboard info from xml file
    QString boolToString(bool b);
    QString intToString(int i);
    int strToInt(QString s);
    bool stringToBool(QString s);

    bool maybeSave();
    QTimer *timer;
    QTimer *updateTimer;

    QGraphicsScene *board;      // scene with minimized images
    QGraphicsScene *scene;      // scene with active image
    SketchPad *sketchPad;
    QStringList padInfo;        // fileName, comment, shot name etc
    QList<QStringList> padInfoList; // list of stringlists with padInfo
    QPixmap imageThumb;         // 160x120 pixmap of the active image
    QList<QPixmap> padThumbList;// list of all resized images as 160x120 pixmaps
    int activePad;              // pad number in padInfoList
    int lastNumber;             // last number given to a sketchpad
    int updateInterval;         // interval for updateImageTimer
    int saveInterval;
    standardPen sPen;
    QList<standardPen> sPenList;
};

#endif // MAINWINDOW_H

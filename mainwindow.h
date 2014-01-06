#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "penchooser.h"
#include "prefdialog.h"

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

    enum padInfoLabels {
        fileName    = 0,
        comment     = 1,
        showComment = 2,
        scene       = 3,
        showScene   = 4,
        shot        = 5,
        showShot    = 6,
        frames      = 7,
        showFrames  = 8
    };

public slots:

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void disableStoryPad();     // disables storypad + buttons etc
    void enableStoryPad();      // enables storypad + buttons etc
    void newStoryboard();       // new storyboard created and initialised
    void openStoryboard();      // opens existing storyboard, and reads xml-file
    void writeXML();            // writes .dastoryboard info to xml-file
    void saveSettings();        // saves settings
    void penF5();               // select sPen F5                           F5
    void penF6();               // select sPen F6                           F6
    void penF7();               // select sPen F7                           F7
    void penF8();               // select sPen F8                           F8
    void penPick();             // set new Pen Color, width and type from penChooser
    void okPenPick();           // if 'OK' is pressed in penChooser
    void cancelPenPick();       // if 'cancel' is pressed in penChooser
    void eraseF5();             // erases lines with sketchpen-color        Shift-F5
    void eraseAll();            // erases entire picture                    F9
    void about();
    void appendSketchPad();     // saves active pad and appends new         ALT+A
    void insertSketchPad();     // saves active pad and inserts new         ALT+I
    void updateComment();       // udates comment for pad
    void updateScene();         // updates scene info
    void updateShot();          // updates shot info
    void updateFrames();        // updates shot and frames for pad struct
    void updateSaveImages();    // saves activeImage + thumbnail
    void updateImages();        // repaints storyboard
    void changeImage();

private:
    Ui::MainWindow *ui;

    void setupConnects();       // initiates connects
    void startSaveImageTimer(int i); // starts timer for 'i' millisecs
    void startUpdateImageTimer(int i); // starts timer for 'i' millisecs
    void initStoryboard();      // initiaqtes a new storyboard
    void initPadInfo();         // initiates values n padInfo
    void addThumbLabels();      // adds labels on thumbs with (scene,shot)
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

    QGraphicsItem *item;
    QGraphicsTextItem *txt;
    QGraphicsScene *board;      // scene with minimized images
    QGraphicsScene *pad;      // scene with active image
    SketchPad *sketchPad;
    QStringList padInfo;        // fileName, comment, shot name etc
    QList<QStringList> padInfoList; // list of stringlists with padInfo
    QPixmap imageThumb;         // 160x120 pixmap of the active image
    QList<QPixmap> padThumbList;// list of all resized images as 160x120 pixmaps
    QGraphicsPixmapItem *pixItem;
    int activePad;              // pad number in padInfoList
    int activePen;              // pen number in sPenList (from 0 to 4)
    int lastNumber;             // last number given to a sketchpad
    int updateInterval;         // interval for updateImageTimer
    int saveInterval;
    standardPen sPen;
    QList<standardPen> sPenList;

    penChooser *pc;
};

#endif // MAINWINDOW_H

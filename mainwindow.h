#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "penchooser.h"
#include "dialogs/prefdialog.h"
#include "animatic.h"
#include "dialogs/infodialog.h"
#include "textoutput.h"

#include <QList>
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsScene>


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
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    enum numberingInfo {
        autonumber  = 0,
        autoDecimal = 1,
        selfNumber  = 2
    };

    enum padInfoLabels {
        fileName     = 0,
        dialogue     = 1,
        action       = 2,
        slug         = 3,
        scene        = 4,
        shot         = 5,
        frames       = 6,
        showFrames   = 7
    };

public slots:
    void updateCommentDialogue(QString string);
    void updateCommentAction(QString string);
    void updateCommentSlug(QString string);

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void newStoryboard();       // new storyboard created and initialised
    void openStoryboard();      // opens existing storyboard, and reads xml-file
    void newScene();            // new scene created and initialised
    void openScene();           // opens existing scene, and reads xml-file
    void addAudio();            // add audiofile to the storyboard
    void rmAudio();             // remove audiofile from the storyboard

    void writeProjXML();        // writes .projdastoryboard info to xml-file
    void writeStoryboardXML();  // writes .dastoryboard info to xml-file
    void saveSettings();        // saves settings
    void setPrefs();            // set preferences via PrefDialog
    void okPrefs();
    void cancelPrefs();

    void padSizeVGA();
    void padSizeSVGA();
    void padSizeXGA();
    void padSizenHD();
    void padSizeqHD();
    void padSize720p();

    void penStd();              // select Standard Pen
    void penF5();               // select sPen F5                           F5
    void penF6();               // select sPen F6                           F6
    void penF7();               // select sPen F7                           F7
    void penF8();               // select sPen F8                           F8
    void penPick();             // set new Pen Color, width and type from penChooser
    void okPenPick();           // if 'OK' is pressed in penChooser
    void cancelPenPick();       // if 'cancel' is pressed in penChooser
    void eraseF5();             // erases lines with sketchpen-color        Shift-F5
    void eraseAll();            // erases entire picture                    F9
    void deleteDrawing();       // erases drawing from board and harddisc   Del

    void about();

    void appendSketchPad();     // saves active pad and appends new         ALT+A
    void insertSketchPad();     // saves active pad and inserts new         ALT+I
    void movePadLeft();         // moves pad to the left, if possible       SHIFT+Left
    void movePadRight();        // moves pad to the right, if possible      SHIFT+RIGHT

    void updateLineEdits();
    void clearLineEdits();

    void updateScene();         // updates scene info
    void updateShot();          // updates shot info
    void updateFrames();        // updates shot and frames for pad struct
    void updateScenelist();     // updates scene names to comboBox

    QImage* resizeImageNoRatio(QImage* img, int width, int height);
    QImage* resizeImageKeepRatio(QImage* img, int width, int height);
    void saveImages();          // saves activeImage + thumbnail
    void updateImages();        // repaints storyboard
    void centerStoryboard();    // centers storyboard around the active pads thumb
    void changeImage();
    void resizeAllDrawings(int w, int h);

    void runAnimatic();         // opens window to run animatic
    void exportPdf();           // exports storyboard to pdf
    void showInfoDialog();      // opens infoDialog window;
    void restartTimer();        // restarts timer after animatic

private:
    Ui::MainWindow *ui;

    void initVars();                    // initiates variables (strings, int etc)
    void initScenes();                  // initiates scenes for pad and thumbs
    void setupGlobalConnects();         // initiates connects
    void setupNewSceneConnect();        // initiates connect for New Scene
    void setupAllConnects();            // initiates the rest af the connects
    void disconnectAllConnects();       // disconnects all except Global Connects
    void disableStoryPad();             // disables storypad + buttons etc
    void enableStoryPad();              // enables storypad + buttons etc
    void closeActiveStoryboard();       // clears lists etc, so a new storyboard can begin

    void disableScene();
    void enableScene();

    void startUpdateImageTimer(int i);  // starts timer for 'i' millisecs

    void movePad(int move);
    void reloadThumbs();

    bool setPadSize(int w, int h);      // sets size to (w x h) pixels
    void resetPenList();                // resets sPenList to five gray pens
    void initStoryboard();              // initiaqtes a new storyboard
    void initPad();                     // initiates the new pad
    void initPadInfo();                 // initiates values n padInfo
    void addThumbLabels();              // adds labels on thumbs with (scene,shot)
    void updateInfoLabels();            // updates labels for frames total etc
    void readProjXML();                 // reads .projdastoryboard info from xml file
    void readStoryboardXML();           // reads .dastoryboard info from xml file
    void setBtnColors();                // sets colors on the Pen buttons

    QString loadSettings();             // returns sbFileName or ""
    QString getSbFileName();            // gets new storybard filename
    QString boolToString(bool b);
    QString intToString(int i);
    int strToInt(QString s);
    bool stringToBool(QString s);

    int fps;
    int activePad;                      // pad number in padInfoList
    int activeScene;
    int activePen;                      // pen number in sPenList (from 0 to 4)
    int lastNumber;                     // last number given to a sketchpad
    int updateInterval;                 // interval for updateTimer

    int padWidth = 170;
    int padHeight = 140;
    int canvasW;
    int canvasH;

    bool autoNumber;
    QTimer *updateTimer;

    QString projFileName;               // project filename, absolute path
    QString projFilePath;               // filepath, including the last '/'
    QString sbFileName;                 // storyboard filename, absolute path
    QString audioFileName;              // full path to audiofile
    QString scenePath;                  // path to scenes images + thumbs
    QString sceneDir;                   // name of directory of scene
    QString prefPath;                   // path to use for new storyboards
    QString videoFormat;                // preferred video format in export video

    QStringList scenePaths;             // List with scene paths to sub-dirs
    QStringList sceneList;              // List with scenes in project
    QStringList padInfo;                // fileName, comment, shot name etc

    QList<QStringList> padInfoList;     // list of stringlists with padInfo
    QList<QPixmap> padThumbList;        // list of all resized images as 160x120 pixmaps
    QList<standardPen> sPenList;

    QGraphicsScene *board;              // scene with minimized images
    QGraphicsScene *pad;                // scene with active image
    QTransform transform;

    SketchPad *sketchPad;
    standardPen sPen;
    penChooser *penchooser;
    PrefDialog *prefs;
    animatic *anim;
    infodialog *infoDial;
};

#endif // MAINWINDOW_H

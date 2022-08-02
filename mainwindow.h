#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include "qpen.h"
#include "qtimer.h"
#include <QLabel>
#include "QGraphicsScene"
#include <QMainWindow>
#include <QDebug>

namespace Ui {
    class MainWindow;
}

class StartupMenu;
class PreferenceManager;

class MainWindow : public QMainWindow
{
    Q_OBJECT

    // where lines start and stop
    struct strokes{
        int first;
        int last;
    };

    // all info on the pads
    struct padInfo {
        QGraphicsScene* scene;
        QPixmap pix;
        int timing;
        QString dial;
        QString action;
        QString slug;
    };

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* obj, QEvent* e) override;

private:
    Ui::MainWindow *ui;

    void init();
    void newProject();
    void loadProject();
    void autoLoad(QString fileName);
    void autoSaveInvoked();
    void saveProject();

    void addPad();
    void removePad();
    void insertPad();
    void movePadLeft();
    void movePadRight();
    void onCellClicked(int row, int column);
    void loadBackground();
    void removeBackground();
    void hideBackground();

    void playFromBegining();
    void playFromActivePad();
    void stopPlaying();
    void animaticChange();

    void resetPalette();
    void changePaletteColor();
    void savePalette();
    void loadPalette();
    void onItemChanged(QListWidgetItem* item);
    void onPaletteRowChanged(int row);
    void onPenWidthChanged(int w);
    void onTimingChanged(int timing);
    void updateTimingLabel();

    void updateStoryboard();
    void copyFrom_mScene(QGraphicsScene* scene);
    void copyTo_mScene(QGraphicsScene* scene);
    void clearCanvas();
    void clearSelected();
    void clearButSelected();

    void undoLast();
    void redoLast();

    void updateDialogue(QString d);
    void updateAction(QString a);
    void updateSlug(QString s);
    void updateCommentLineEdits(padInfo active);

    void setPreferences();

    // STORYBOARD member vars
    QString mActiveProjectFull = "";
    QString mLastProjPath = "";
    QString mActiveStoryboardFull = "";
    QString mActiveProject = "";
    QString mActiveStoryboard = "";
    int mActiveStoryboardFrames = 0;
    int mActiveStoryboardPad = 0;
    int mFps = 25;
    QString mRatio = "Standard";
    QVector<padInfo> mPadInfo;
    QList<QGraphicsItem*> mItemRedoList;
    QList<strokes> entryList;
    QList<strokes> redoEntryList;
    QPen mPen;
    bool mPenIsPressed = false;
    bool mNeedSave = false;
    bool mAutosave = false;

    // palette default colors
    const QColor mWHITE = QColor(255, 255, 255);
    const QColor mLIGHTBLUE = QColor(160, 215, 255);
    const QColor mLIGHTGREEN = QColor(135, 255, 145);
    const QColor mLIGHTRED = QColor(240, 180, 180);
    const QColor mLIGHTYELLOW = QColor(245, 245, 125);
    const QColor mLIGHTBROWN = QColor(200, 115, 50);
    const QColor mLIGHTPURPLE = QColor(240, 155, 240);
    const QColor mBLACK = QColor(10, 10, 10);
    const QColor mLIGHTGRAY  = QColor(220, 220, 220);
    const QColor mDARKGRAY = QColor(150, 150, 150);
    const QStringList mPaletteList = QStringList() << tr("ERASER White") << tr("Light blue") << tr("Light green") << tr("Light red") << tr("Light yellow")
                                                   << tr("Light brown") << tr("Light purple") << tr("Black") << tr("Light gray") << tr("Dark gray");
    const int mMAX_ENTRIES = 50;

    QStringList mActivePaletteList;
    QList<QColor> mOrgPalette;
    QList<QColor> mCurPalette;

    QGraphicsScene* mScene = nullptr;
    QPointF mPrevPoint;
    QPointF mNextPoint;
    strokes mEntry;
    strokes mRedoEntry;
    padInfo mActivePadInfo;
    StartupMenu* mStartupMenu = nullptr;
    PreferenceManager* mPrefs = nullptr;
    QTimer* mAutoSaveTimer = nullptr;
    QTimer* mAnimaticTimer = nullptr;
};

#endif // MAINWINDOW_H

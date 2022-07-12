#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include "qlistwidget.h"
#include "qpen.h"
#include "QGraphicsScene"
#include <QMainWindow>

namespace Ui {
    class MainWindow;
}

class StartupMenu;

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();

    bool eventFilter(QObject* obj, QEvent* e) override;

private:
    Ui::MainWindow *ui;

    void init();
    void setupProject();

    void resetPalette();
    void changePaletteColor();
    void savePalette();
    void loadPalette();
    void onItemChanged(QListWidgetItem* item);
    void onCurrentRowChanged(int row);
    void onPenWidthChanged(int w);

    void loadScene(QString scene);


    // STORYBOARD member vars
    QString mActiveProjectFull = "";
    QString mActiveStoryboardFull = "";
    QString mActiveProject = "";
    QString mActiveStoryboard = "";
    QString mMiscFolderFull = "";
    int mActiveStoryboardFrames = 0;
    int mActiveStoryboardPads = 0;
    int mFps = 25;
    QString mRatio = "Standard";
    QVector<QPixmap> mPixmaps;
    QPen mPen;
    bool mPenIsPressed = false;

    // palette default colors
    const QColor mLIGHTBLUE = QColor(160, 215, 255);
    const QColor mLIGHTGREEN = QColor(135, 255, 145);
    const QColor mLIGHTRED = QColor(240, 180, 180);
    const QColor mLIGHTYELLOW = QColor(245, 245, 125);
    const QColor mLIGHTBROWN = QColor(200, 115, 50);
    const QColor mLIGHTPURPLE = QColor(240, 155, 240);
    const QColor mWHITE = QColor(255, 255, 255);
    const QColor mBLACK = QColor(10, 10, 10);
    const QColor mLIGHTGRAY  = QColor(220, 220, 220);
    const QColor mDARKGRAY = QColor(150, 150, 150);
    const QStringList mPaletteList = QStringList() << tr("Light blue") << tr("Light green") << tr("Light red") << tr("Light yellow") << tr("Light brown")
                                      << tr("Light purple") << tr("White") << tr("Black") << tr("Light gray") << tr("Dark gray");
    QStringList mActivePaletteList;
    QList<QColor> mOrgPalette;
    QList<QColor> mCurPalette;

    QGraphicsScene* mScene = nullptr;
    QGraphicsScene* mSceneStoryboard = nullptr;
    QPoint mPrevPoint;
    QPoint mNextPoint;
    StartupMenu* mStartupMenu = nullptr;
};

#endif // MAINWINDOW_H

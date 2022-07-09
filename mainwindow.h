#ifndef MAINWINDOW_H
#define MAINWINDOW_H

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
    void loadScene(QString scene);


    // SCENE member vars
    QString mActiveProjectFull = "";
    QString mActiveStoryboardFull = "";
    QString mActiveProject = "";
    QString mActiveStoryboard = "";
    int mActiveStoryboardFrames = 0;
    int mActiveStoryboardPads = 0;
    QVector<QPixmap> mPixmaps;

    // palette default colors
    const QColor mLIGHTBLUE = QColor(180, 180, 240);
    const QColor mLIGHTGREEN = QColor(180, 240, 180);
    const QColor mLIGHTRED = QColor(240, 180, 180);
    const QColor mLIGHTYELLOW = QColor(240, 240, 180);
    const QColor mLIGHTBROWN = QColor(180, 140, 140);
    const QColor mLIGHTPURPLE = QColor(240, 180, 240);
    const QColor mWHITE = QColor(250, 250, 250);
    const QColor mBLACK = QColor(10, 10, 10);
    const QColor mLIGHTGRAY = QColor(220, 220, 220);
    const QColor mDARKGRAY = QColor(150, 150, 150);

    StartupMenu* mStartupMenu = nullptr;
};

#endif // MAINWINDOW_H

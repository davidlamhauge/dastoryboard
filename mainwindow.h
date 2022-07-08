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
    QString mActiveSceneFull = "";
    QString mActiveProject = "";
    QString mActiveScene = "";
    int mActiveSceneFrames = 0;
    int mActiveScenePads = 0;
    QVector<QPixmap> mPixmaps;

    StartupMenu* mStartupMenu = nullptr;
};

#endif // MAINWINDOW_H

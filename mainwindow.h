#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QtGui>
#include <QMainWindow>

class SketchPad;

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
    void disableStoryPad();     // disables storypad + buttons etc
    void enableStoryPad();      // enables storypad + buttons etc

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void penColor();
    void penWidth();
    void about();

private:
    Ui::MainWindow *ui;

    void setupConnects();   // initiates connects

    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    QGraphicsScene *scene;
    SketchPad *sketchPad;
};

#endif // MAINWINDOW_H

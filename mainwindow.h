#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
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
    void hideStoryPad();    // hides storypad + buttons etc
    void showStoryPad();    // shows storypad + buttons etc

protected:
    void closeEvent(QCloseEvent *e);

private slots:
    void penColor();
    void penWidth();
    void about();

private:
    Ui::MainWindow *ui;
    void setupConnects();   // initiates connects
    void enFunktion();
    void haHa();

    void createMenus();
    bool maybeSave();
    bool saveFile(const QByteArray &fileFormat);

    SketchPad *sketchPad;

    QMenu *fileMenu;
    QMenu *optionMenu;
    QMenu *helpMenu;

    QAction *exitAct;
    QAction *penColorAct;
    QAction *penWidthAct;
    QAction *clearScreenAct;
    QAction *aboutAct;
    QAction *aboutQtAct;

};

#endif // MAINWINDOW_H

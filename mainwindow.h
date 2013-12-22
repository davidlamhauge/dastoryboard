#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

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

private:
    Ui::MainWindow *ui;
    void setupConnects();   // initiates connects
};

#endif // MAINWINDOW_H

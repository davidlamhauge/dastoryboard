#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QList>
#include <QtGui>
#include <QMainWindow>
#include <QGraphicsScene>



namespace Ui {
    class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:
     explicit MainWindow(QWidget *parent = nullptr);
    ~MainWindow();


private:
    Ui::MainWindow *ui;

};

#endif // MAINWINDOW_H

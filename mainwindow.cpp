#include "mainwindow.h"
#include "ui_mainwindow.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
  //  hideStoryPad();
    setupConnects();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
}

void MainWindow::hideStoryPad()
{
    ui->gvStoryPad->hide();
    ui->labShot->hide();
    ui->labFrames->hide();
    ui->leShot->hide();
    ui->sbFrames->hide();
    ui->btnCancel->hide();
    ui->btnApplyShotFrames->hide();
    ui->labComments->hide();
    ui->leComment->hide();
}

void MainWindow::showStoryPad()
{
    ui->gvStoryPad->show();
    ui->labShot->show();
    ui->labFrames->show();
    ui->leShot->show();
    ui->sbFrames->show();
    ui->btnCancel->show();
    ui->btnApplyShotFrames->show();
    ui->labComments->show();
    ui->leComment->show();
}

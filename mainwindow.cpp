#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"

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
    ui->gvSketchPad->hide();
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
    ui->gvSketchPad->show();
    ui->labShot->show();
    ui->labFrames->show();
    ui->leShot->show();
    ui->sbFrames->show();
    ui->btnCancel->show();
    ui->btnApplyShotFrames->show();
    ui->labComments->show();
    ui->leComment->show();
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->ignore(); // TODO!!!
}

void MainWindow::penColor()
{
    QColor newColor = QColorDialog::getColor(sketchPad->penColor());
    if (newColor.isValid())
        sketchPad->setPenColor(newColor);
}

void MainWindow::penWidth()
{
    bool ok;
    int newWidth = QInputDialog::getInteger(this, tr("Sketch Pad"),
                                            tr("Select pen width:"),
                                            sketchPad->penWidth(),
                                            1, 50, 1, &ok);
    if (ok)
        sketchPad->setPenWidth(newWidth);
}

void MainWindow::about()
{
    QMessageBox::about(this, tr("About dastoryboard"),
            tr("<p><b>dastoryboard</b> is an Open Source storyboard software "
               "for your conveniance. Please enjoy!"));
}

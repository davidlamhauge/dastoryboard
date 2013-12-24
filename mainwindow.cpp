#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    setupConnects();
    scene = new QGraphicsScene(this);
    ui->gvSketchPad->setScene(scene);

    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    scene->addWidget(sketchPad);
    sketchPad->setFocus();
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));
    connect(ui->btnCancel,SIGNAL(clicked()),this,SLOT(saveTest()));
}

void MainWindow::disableStoryPad()
{
    ui->gvSketchPad->setEnabled(false);
    ui->labShot->setEnabled(false);
    ui->labFrames->setEnabled(false);
    ui->leShot->setEnabled(false);
    ui->sbFrames->setEnabled(false);
    ui->btnCancel->setEnabled(false);
    ui->btnApplyShotFrames->setEnabled(false);
    ui->labComments->setEnabled(false);
    ui->leComment->setEnabled(false);
    ui->btnApplyComment->setEnabled(false);
}

void MainWindow::enableStoryPad()
{
    ui->gvSketchPad->setEnabled(true);
    ui->labShot->setEnabled(true);
    ui->labFrames->setEnabled(true);
    ui->leShot->setEnabled(true);
    ui->sbFrames->setEnabled(true);
    ui->btnCancel->setEnabled(true);
    ui->btnApplyShotFrames->setEnabled(true);
    ui->labComments->setEnabled(true);
    ui->leComment->setEnabled(true);
    ui->btnApplyComment->setEnabled(true);
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->accept(); // TODO!!!
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

void MainWindow::appendSketchPad()
{
}

void MainWindow::insertSketchPad()
{
}

void MainWindow::saveTest()
{
    sketchPad->image.save("/home/david/test.png");
}

#include <QtGui>

#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "sketchpad.h"

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);

    updateInterval = 4015;      // millisecs. to be set as preference TODO
    saveInterval = 10000;       // millisecs. to be set as preference TODO
    pad = new QGraphicsScene(this);
    ui->gvSketchPad->setScene(pad);
    board = new QGraphicsScene(this);
    QBrush grayBrush(Qt::gray);
    board->setBackgroundBrush(grayBrush);
    ui->gvStoryboard->setScene(board);
    ui->gvStoryboard->show();
    setupConnects();

    sbFileName = loadSettings();    // gets a fileName if it exists!
    if (sbFileName.isEmpty()){
        disableStoryPad();
    }else{
        QFile file(sbFileName );
        if (file.exists()){
            initStoryboard();
            readXML();
        }else{
            disableStoryPad();
            QMessageBox msgBox;
            msgBox.setText(tr("File: %1 not found!").arg(sbFileName));
            msgBox.setIcon(QMessageBox::Information);
            msgBox.exec();
        }
    }
}

MainWindow::~MainWindow()
{
    delete ui;
}

void MainWindow::setupConnects()
{
    connect(ui->action_New_Storyboard,SIGNAL(triggered()),this,SLOT(newStoryboard()));
    connect(ui->action_Open_Storyboard,SIGNAL(triggered()),this,SLOT(openStoryboard()));
    connect(ui->action_Save_Storyboard,SIGNAL(triggered()),this,SLOT(writeXML()));
    connect(ui->actionE_xit,SIGNAL(triggered()),this,SLOT(close()));

    connect(ui->actionAppend_Sketchpad,SIGNAL(triggered()),this,SLOT(appendSketchPad()));
    connect(ui->actionLoad_Pen_1,SIGNAL(triggered()),this,SLOT(penF5()));
    connect(ui->actionErase_Sketch_Pen,SIGNAL(triggered()),this,SLOT(eraseF5()));
    connect(ui->actionLoad_Pen_2,SIGNAL(triggered()),this,SLOT(penF6()));
    connect(ui->actionLoad_Pen_3,SIGNAL(triggered()),this,SLOT(penF7()));
    connect(ui->actionLoad_Pen_4,SIGNAL(triggered()),this,SLOT(penF8()));

    connect(ui->actionErase_All,SIGNAL(triggered()),this,SLOT(eraseAll()));
    // set pen width and color
    connect(ui->actionSet_Pen_Color,SIGNAL(triggered()),this,SLOT(penPick()));
    connect(ui->actionSet_Pen_width,SIGNAL(triggered()),this,SLOT(penPick()));
    // update text and values in padInfo, when changes are made
    connect(ui->leComment,SIGNAL(textChanged(QString)),this,SLOT(updateComment()));
    connect(ui->leShot,SIGNAL(textChanged(QString)),this,SLOT(updateShot()));
    connect(ui->sbFrames,SIGNAL(valueChanged(int)),this,SLOT(updateFrames()));

    connect(board,SIGNAL(selectionChanged()),this,SLOT(changeImage()));

}

void MainWindow::startSaveImageTimer(int i)
{
    timer = new QTimer(this);
    connect(timer, SIGNAL(timeout()),this,SLOT(updateSaveImages()));
    timer->start(i);
}

void MainWindow::startUpdateImageTimer(int i)
{
    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()),this,SLOT(updateSaveImages()));
    updateTimer->start(i);
}

void MainWindow::initStoryboard()
{
    padInfoList.clear();
    padInfo.clear();
    sPenList.clear();
    for (int i = 0;i<5;i++)
    {
        sPen.penWidth = 6;
        sPen.penColor = QColor(80,80,80);
        sPenList.append(sPen);
    }
    lastNumber = 0;
    activePad = 0;
    activePen = 0;
    sketchPad = new SketchPad;
    sketchPad->setFixedSize(640,480);
    sketchPad->initPad(sbFileName,lastNumber);
    padInfoList.append(padInfo);
    initPadInfo();
    pad->addWidget(sketchPad);
    update();
    sketchPad->setFocus();
}

void MainWindow::initPadInfo() /* sketchPad info as strings */
{
    padInfo.clear();
    padInfo.append(QString::number(lastNumber) + ".png");  // image filename!
    ui->leComment->clear();
    padInfo.append("");
    padInfo.append("false");
    ui->leScene->clear();
    padInfo.append("");
    padInfo.append("false");
    ui->leShot->clear();
    padInfo.append("");
    padInfo.append("false");
    ui->sbFrames->setValue(50);
    padInfo.append("50");
    padInfo.append("false");
    padInfoList.replace(activePad,padInfo);
    sketchPad->clearImage();

    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    padThumbList.append(imageThumb);    // append pixmap to List...
    pixItem = new QGraphicsPixmapItem(imageThumb);
    board->addItem(pixItem);        //...and add it to storyboard as an Item..!
    pixItem->setPos((padThumbList.size()*170) - 165 , 3);
    pixItem->setToolTip(tr("scene %1, shot %2")
                        .arg(padInfo[scene])
                        .arg(padInfo[shot]));

    updateTimer = new QTimer(this);
    connect(updateTimer, SIGNAL(timeout()),this,SLOT(updateImages()));
    updateTimer->start(updateInterval);

}

QString MainWindow::getSbFileName()
{
    return QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));
}

QString MainWindow::loadSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (settings.contains("sbFileName")){
        return settings.value("sbFileName").toString();
    }
    else
        return "";
}

void MainWindow::saveSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    settings.setValue("sbFileName", sbFileName);
}

void MainWindow::disableStoryPad()
{
    ui->gvSketchPad->setEnabled(false);
    ui->labScene->setEnabled(false);
    ui->leScene->setEnabled(false);
    ui->labShot->setEnabled(false);
    ui->leShot->setEnabled(false);
    ui->labFrames->setEnabled(false);
    ui->sbFrames->setEnabled(false);
    ui->labComments->setEnabled(false);
    ui->leComment->setEnabled(false);
    ui->menuSettings->setEnabled(false);
    ui->menuEdit->setEnabled(false);
    ui->action_Save_Storyboard->setEnabled(false);
}

void MainWindow::enableStoryPad()
{
    ui->gvSketchPad->setEnabled(true);
    ui->labScene->setEnabled(true);
    ui->leScene->setEnabled(true);
    ui->labShot->setEnabled(true);
    ui->leShot->setEnabled(true);
    ui->labFrames->setEnabled(true);
    ui->sbFrames->setEnabled(true);
    ui->labComments->setEnabled(true);
    ui->leComment->setEnabled(true);
    ui->menuSettings->setEnabled(true);
    ui->menuEdit->setEnabled(true);
    ui->action_Save_Storyboard->setEnabled(true);
}

void MainWindow::newStoryboard()
{
    sbFileName = QFileDialog::getSaveFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));

    if (!sbFileName.isEmpty()){
        if (!sbFileName.endsWith(".dastoryboard"))
            sbFileName += ".dastoryboard";
        sbFilePath = sbFileName.left(sbFileName.lastIndexOf("/") + 1);
        enableStoryPad();
        initStoryboard();
        startSaveImageTimer(saveInterval);
    }
}

void MainWindow::openStoryboard()
{
    sbFileName = QFileDialog::getOpenFileName(this,
        tr("dastoryboard filename"), "",
        tr("dastoryboard files (*.dastoryboard)"));
    if (!sbFileName.isEmpty()){
        sbFilePath = sbFileName.left(sbFileName.lastIndexOf("/") + 1);
        enableStoryPad();
        initStoryboard();
        readXML();
        startSaveImageTimer(saveInterval);
    }
}

void MainWindow::closeEvent(QCloseEvent *e)
{
    e->accept(); // TODO!!!
}

void MainWindow::penPick()
{
    pc = new penChooser();
    pc->colordialog->setCurrentColor(sketchPad->penColor());
    pc->sbWidth->setValue(sketchPad->penWidth());
    pc->cbPen->setCurrentIndex(activePen);
    pc->setModal(true);
    pc->show();
    connect(pc->btnCancel,SIGNAL(clicked()),this,SLOT(cancelPenPick()));
    connect(pc->btnOk,SIGNAL(clicked()),this,SLOT(okPenPick()));
}

void MainWindow::penF5()
{
    sPen = sPenList[1];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF6()
{
    sPen = sPenList[2];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF7()
{
    sPen = sPenList[3];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::penF8()
{
    sPen = sPenList[4];
    sketchPad->setPenColor(sPen.penColor);
    sketchPad->setPenWidth(sPen.penWidth);
}

void MainWindow::okPenPick()
{
    activePen = pc->cbPen->currentIndex();
    sPen = sPenList[activePen];
    sPen.penColor = pc->colordialog->currentColor();
    sketchPad->setPenColor(sPen.penColor);
    sPen.penWidth = pc->sbWidth->value();
    sketchPad->setPenWidth(sPen.penWidth);
    sPenList.replace(activePen,sPen);
    pc->close();
}

void MainWindow::cancelPenPick()
{
    pc->close();
}

void MainWindow::eraseF5()
{
    sketchPad->eraseSketchPen(sPenList[1].penColor.red(),
            sPenList[1].penColor.green(),sPenList[1].penColor.blue());
}

void MainWindow::eraseAll()
{
    int ret = QMessageBox::warning(this, tr("Erase drawing"),
                                    tr("Do you want to erase the drawing?\n"
                                       "It can NOT be undone!\n"                                       ),
                                    QMessageBox::Ok | QMessageBox::Cancel,
                                    QMessageBox::Cancel);
    switch (ret)
    {
       case QMessageBox::Ok:
        sketchPad->clearImage();
           break;
       case QMessageBox::Cancel:
           // Cancel was clicked
           break;
       default:
           // should never be reached
           break;
     }
}


void MainWindow::about()
{
    QMessageBox::about(this, tr("About dastoryboard"),
            tr("<p><b>dastoryboard</b> is an Open Source storyboard software "
               "for your conveniance. Please enjoy!"));
}

void MainWindow::updateComment()
{
    padInfoList[activePad][comment] = ui->leComment->text();
}

void MainWindow::updateScene()
{
   padInfoList[activePad][scene] = ui->leScene->text();
}

void MainWindow::updateShot()
{
    padInfoList[activePad][shot] = ui->leShot->text();
}

void MainWindow::updateFrames()
{
    padInfoList[activePad][frames] = QString::number(ui->sbFrames->value());
}

void MainWindow::updateSaveImages()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][fileName]);
    QImage img = sketchPad->image;
    img = img.scaled(160,120,Qt::KeepAspectRatio,Qt::FastTransformation);
    img.save(sbFilePath + "t" + padInfoList[activePad][fileName]);
    QFile f(sbFilePath + "t" + padInfoList[activePad][fileName]);
    if (!f.exists()){
        QMessageBox::information(this, tr("File does no exist!"),
                tr("It was not possible to save the storyboard image."
                   "Do you have write access to the directory?"));
    }
}

void MainWindow::updateImages() // updates storyboard thumbnails
{
    imageThumb = QPixmap::fromImage(sketchPad->image);
    imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
    pixItem = new QGraphicsPixmapItem(imageThumb);
    board->removeItem(board->itemAt(((activePad+1)*170) - 165 , 3));
    board->addItem(pixItem);
    pixItem->setPos(((activePad + 1)*170) - 165 , 3);
    pixItem->setToolTip(tr("scene %1, shot %2")
                        .arg(padInfo[scene])
                        .arg(padInfo[shot]));
    pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
    update();
    sketchPad->update();
}
/*
                sketchPad->image.load(sbFilePath + padInfo[fileName]);
                imageThumb = QPixmap::fromImage(sketchPad->image);
                imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
                padThumbList.append(imageThumb);
                pixItem = new QGraphicsPixmapItem(imageThumb);
                board->addItem(pixItem);
                pixItem->setPos((padThumbList.size()*170) - 165 , 3);
                pixItem->setToolTip(tr("scene %1, shot %2")
                                    .arg(padInfo[scene])
                                    .arg(padInfo[shot]));
                pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
                update();
*/
void MainWindow::changeImage()
{
    if (!board->selectedItems().isEmpty()){
        item = board->selectedItems().at(0);
        int i = item->pos().x();        // find x-value
        activePad = (i-5) / 170;
        padInfo = padInfoList.at(activePad);
        sketchPad->image.load(sbFilePath + padInfo[fileName]);
        updateImages();
    }
}

void MainWindow::appendSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][fileName]);
    padInfoList.append(padInfo);
    lastNumber += 1;
    activePad = padInfoList.size() - 1;
    initPadInfo();
    startSaveImageTimer(saveInterval);
}

void MainWindow::insertSketchPad()
{
    sketchPad->image.save(sbFilePath + padInfoList[activePad][fileName]);
    padInfoList.insert(activePad+1,padInfo);
    lastNumber += 1;
    activePad += 1;
    initPadInfo();
    startSaveImageTimer(saveInterval);
}


void MainWindow::writeXML()
{
    if (sbFileName.isEmpty()){
        sbFileName = QFileDialog::getSaveFileName(this,
            tr("Save dastoryboard information"), "",
            tr("dastoryboard files (*.dastoryboard)"));
    }

    if (!sbFileName.isEmpty()){
        updateSaveImages();         // saves activeimages
        QFile file(sbFileName);
        if (file.open(QFile::ReadWrite)){
            saveSettings();
            QXmlStreamWriter xmlwriter(&file);
            xmlwriter.setAutoFormatting(true);
            xmlwriter.writeStartDocument();             // document START
            xmlwriter.writeStartElement("storyboard");  // storyboard START
            xmlwriter.writeStartElement("variables");   // variables START
            xmlwriter.writeTextElement("sbFileName",sbFileName);
            xmlwriter.writeTextElement("lastNumber",QString::number(lastNumber));
            xmlwriter.writeTextElement("activePad",QString::number(activePad));
            xmlwriter.writeTextElement("activePen",QString::number(activePen));
            xmlwriter.writeEndElement();                // variables STOP

            xmlwriter.writeStartElement("penlist");     // penlist START
            for (int i = 0; i < sPenList.size();i++)
            {
                xmlwriter.writeStartElement("pen");     // pen START
                xmlwriter.writeTextElement("width",QString::number(sPenList[i].penWidth));
                xmlwriter.writeTextElement("red",QString::number(sPenList[i].penColor.red()));
                xmlwriter.writeTextElement("green",QString::number(sPenList[i].penColor.green()));
                xmlwriter.writeTextElement("blue",QString::number(sPenList[i].penColor.blue()));
                xmlwriter.writeEndElement();            // pen STOP
            }
            xmlwriter.writeEndElement();                // penlist STOP

            xmlwriter.writeStartElement("sketchpads");  // sketchpads START
            for (int i = 0;i < padInfoList.size() ; i++){ // TODO !!!!!!!!!!!!
                padInfo = padInfoList[i];
                xmlwriter.writeStartElement("sketchpad");  // sketchpad START
                xmlwriter.writeTextElement("fileName",padInfo[fileName]);
                xmlwriter.writeTextElement("comment",padInfo[comment]);
                xmlwriter.writeTextElement("showComment",padInfo[showComment]);
                xmlwriter.writeTextElement("scene",padInfo[scene]);
                xmlwriter.writeTextElement("showScene",padInfo[showScene]);
                xmlwriter.writeTextElement("shot",padInfo[shot]);
                xmlwriter.writeTextElement("showShot",padInfo[showShot]);
                xmlwriter.writeTextElement("frames",padInfo[frames]);
                xmlwriter.writeTextElement("showFrames",padInfo[showFrames]);
                xmlwriter.writeEndElement();                // sketchpad STOP
            }
            xmlwriter.writeEndElement();         // sketchpads STOP
            xmlwriter.writeEndDocument();        // document and storyboard STOP
        }

    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("No filename chosen!"));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

void MainWindow::readXML()
{
    QFile sbFile(sbFileName);
    if (sbFile.open(QIODevice::ReadOnly)){
        padInfoList.clear();            // clear list for reading file
        padInfo.clear();
        padThumbList.clear();
        sPenList.clear();
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "sbFileName")
                sbFileName = xmlreader.readElementText();
            else if (xmlreader.isStartElement() && xmlreader.name() == "lastNumber")
                lastNumber = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePad")
                activePad = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "activePen")
                activePen = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "fileName")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "width")
                sPen.penWidth = xmlreader.readElementText().toInt();
            else if (xmlreader.isStartElement() && xmlreader.name() == "red")
                sPen.penColor.setRed(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "green")
                sPen.penColor.setGreen(xmlreader.readElementText().toInt());
            else if (xmlreader.isStartElement() && xmlreader.name() == "blue"){
                sPen.penColor.setBlue(xmlreader.readElementText().toInt());
                sPenList.append(sPen);
            }
            else if (xmlreader.isStartElement() && xmlreader.name() == "comment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showComment")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "scene")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showScene")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "shot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showShot")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "frames")
                padInfo.append(xmlreader.readElementText());
            else if (xmlreader.isStartElement() && xmlreader.name() == "showFrames"){
                padInfo.append(xmlreader.readElementText());
                sbFilePath = sbFileName.left(sbFileName.lastIndexOf("/") + 1);
                sketchPad->image.load(sbFilePath + padInfo[fileName]);
                imageThumb = QPixmap::fromImage(sketchPad->image);
                imageThumb = imageThumb.scaled(160,120,Qt::KeepAspectRatio);
                padThumbList.append(imageThumb);
                pixItem = new QGraphicsPixmapItem(imageThumb);
                board->addItem(pixItem);
                pixItem->setPos((padThumbList.size()*170) - 165 , 3);
                pixItem->setToolTip(tr("scene %1, shot %2")
                                    .arg(padInfo[scene])
                                    .arg(padInfo[shot]));
                pixItem->setFlag(QGraphicsItem::ItemIsSelectable);
                update();
                padInfoList.append(padInfo);
                padInfo.clear();
            }
        }
        sPen = sPenList[activePen];
        sketchPad->setPenColor(sPen.penColor);
        sketchPad->setPenWidth(sPen.penWidth);
        padInfo = padInfoList.at(activePad);
        sketchPad->image.load(sbFilePath + padInfo[fileName]);
        updateImages();
        ui->leComment->setText(padInfo[comment]);
        ui->leScene->setText(padInfo[scene]);
        ui->leShot->setText(padInfo[shot]);
        ui->sbFrames->setValue(padInfo[frames].toInt());
        startSaveImageTimer(saveInterval);
    }else{
        QMessageBox msgBox;
        msgBox.setText(tr("File: %1 not found!").arg(sbFileName));
        msgBox.setIcon(QMessageBox::Information);
        msgBox.exec();
    }
}

QString MainWindow::boolToString(bool b)
{
    if (b == true)
        return "yes";
    else
        return "no";
}

QString MainWindow::intToString(int i)
{
    QString s;
    return s.setNum(i);
}

int MainWindow::strToInt(QString s)
{
    return s.toInt();
}

bool MainWindow::stringToBool(QString s)
{
    if (s == "yes")
        return true;
    else
        return false;
}


#include "prefdialog.h"

PrefDialog::PrefDialog(const QString &scPath, QDialog *parent) :
    QDialog(parent)
{
    scenePath = scPath;
    labFps = new QLabel(tr("Frames per second?"));
    cbFps = new QComboBox(this);
    QStringList sl;

    labVideoFormat= new QLabel(tr("Export to which video format?"));
    cbVideoFormat= new QComboBox(this);

    labAutoNumber = new QLabel(tr("Autonumber Seq/sc/shot?"));
    cbAutoNumber = new QComboBox(this);

    btnCancel = new QPushButton(tr("Cancel"),this);
    btnOk = new QPushButton(tr("OK"),this);

    buttonLayout = new QGridLayout();
    buttonLayout->addWidget(labFps,0,0);
    buttonLayout->addWidget(cbFps,0,1);
    buttonLayout->addWidget(labVideoFormat,1,0);
    buttonLayout->addWidget(cbVideoFormat,1,1);
    buttonLayout->addWidget(labAutoNumber,2,0);
    buttonLayout->addWidget(cbAutoNumber,2,1);
    buttonLayout->addWidget(btnCancel,3,0);
    buttonLayout->addWidget(btnOk,3,1);
    setLayout(buttonLayout);

    setWindowTitle(tr("Set Preferences"));

    loadSettings();
    readXml();

    sl.clear();
    sl << tr("24 fps.")  << tr("25 fps.") << tr("30 fps.");
    cbFps->addItems(sl);
    if (fps == 24)
        cbFps->setCurrentIndex(0);
    if (fps == 25)
        cbFps->setCurrentIndex(1);
    if (fps == 30)
        cbFps->setCurrentIndex(2);

    sl.clear();
    sl << tr(".ogv") << tr(".mpg");
    cbVideoFormat->addItems(sl);
    if (videoFormat == ".ogv")
        cbVideoFormat->setCurrentIndex(0);
    else
        cbVideoFormat->setCurrentIndex(1);

    sl.clear();
    sl << tr("No, I'll do it myself!")  << tr("Autonumbering - Yes!");
    cbAutoNumber->addItems(sl);
    if (autoNumber)
        cbAutoNumber->setCurrentIndex(1);
    else
        cbAutoNumber->setCurrentIndex(0);

}

void PrefDialog::loadSettings()
{
    QSettings settings("dalanima/dastoryboard","dastoryboard");
    settings.setIniCodec(QTextCodec::codecForName("UTF-8"));
    if (settings.contains("scenePath")){             // if scenePath exists...
        sceneDir = settings.value("sceneDir").toString();
        fps = settings.value("Fps").toInt();
        autoNumber = settings.value("autoNumber").toBool();
    }
}

void PrefDialog::readXml()
{
    QFile sbFile(scenePath + sceneDir + ".dastoryboard");    // open the storyboard file
    if (sbFile.open(QIODevice::ReadOnly)){
        QXmlStreamReader xmlreader(&sbFile);
        while(!xmlreader.atEnd()){
            xmlreader.readNext();
            if (xmlreader.isStartElement() && xmlreader.name() == "videoFormat"){
                videoFormat = xmlreader.readElementText();
                break;
            }
        }
    }
}

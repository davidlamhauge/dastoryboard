#include "prefdialog.h"

PrefDialog::PrefDialog(const int &fpsec, QDialog *parent) :
    QDialog(parent)
{
    fps = fpsec;
    labFps = new QLabel(tr("Frames per second?"));
    cbFps = new QComboBox(this);
    QStringList sl;
    sl.clear();
    sl << tr("24 fps.")  << tr("25 fps.") << tr("30 fps.");
    cbFps->addItems(sl);
    if (fps == 24)
        cbFps->setCurrentIndex(0);
    if (fps == 25)
        cbFps->setCurrentIndex(1);
    if (fps == 30)
        cbFps->setCurrentIndex(2);

    labVideoFormat= new QLabel(tr("Export to which video format?"));
    cbVideoFormat= new QComboBox(this);
    sl.clear();
    sl << tr(".ogv") << tr(".mpg");
    cbVideoFormat->addItems(sl);
    cbVideoFormat->setCurrentIndex(0);

    labAutoNumber = new QLabel(tr("Autonumber Seq/sc/shot?"));
    cbAutoNumber = new QComboBox(this);
    sl.clear();
    sl << tr("No, I'll do it myself!")  << tr("Autonumbering - Yes!");
    cbAutoNumber->addItems(sl);
    cbAutoNumber->setCurrentIndex(1);

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

}

#include "prefdialog.h"

PrefDialog::PrefDialog(QDialog *parent) :
    QDialog(parent)
{
    labPadSize = new QLabel(tr("Pad size?"));
    cbPadSize = new QComboBox(this);
    QStringList sl;
    sl << tr("640x480 pixel") << tr("800x600 pixel");
    cbPadSize->addItems(sl);
    cbPadSize->setCurrentIndex(0);

    labFps = new QLabel(tr("Frames per second?"));
    cbFps = new QComboBox(this);
    QStringList sl;
    sl << tr("24 fps.")  << tr("25 fps.") << tr("30 fps.");
    cbFps->addItems(sl);
    cbFps->setCurrentIndex(1);

    labSeqSc = new QLabel(tr("Seq/sc or Sc/shot?"));
    cbSeqSc = new QComboBox(this);
    QStringList sl;
    sl << tr("Sequence and Scene")  << tr("Scene and Shot");
    cbSeqSc->addItems(sl);
    cbSeqSc->setCurrentIndex(1);

    labAutoNumber = new QLabel(tr("Autonumber Seq/sc/shot?"));
    cbAutoNumber = new QComboBox(this);
    QStringList sl;
    sl << tr("No, I'll do it myself!")  << tr("Autonumbering - Yes!");
    cbAutoNumber->addItems(sl);
    cbAutoNumber->setCurrentIndex(1);

    setWindowTitle(tr("Set Preferences"));

}
/*
    QLabel *labPadSize;
    QComboBox *cbPadSize;

    QLabel *labFps;
    QComboBox *cbFps;

    QLabel *labSeqSc;
    QComboBox *cbSeqSc;

    QLabel *labAutoNumber;
    QComboBox *cbAutoNumber;


labWidth = new QLabel(tr("Pen width:"),this);

    sbWidth = new QSpinBox(this);
    sbWidth->setRange(1,50);
    sbWidth->setValue(6);

    labPen = new QLabel(tr("Pen type:"),this);

    cbPen = new QComboBox(this);
    QStringList sl;
    sl << tr("Standard") << tr("F5 sketching") << tr("F6 User defined")
       << tr("F7 User defined") << tr("F8 User defined");
    cbPen->addItems(sl);

    btnCancel = new QPushButton(tr("Cancel"),this);

    btnOk = new QPushButton(tr("OK"),this);

    buttonLayout = new QGridLayout();
    buttonLayout->addWidget(labWidth,0,0);
    buttonLayout->addWidget(sbWidth,0,1);
    buttonLayout->addWidget(labPen,1,0);
    buttonLayout->addWidget(cbPen,1,1);
    buttonLayout->addWidget(btnCancel,2,0);
    buttonLayout->addWidget(btnOk,2,1);

    layout = new QVBoxLayout();
    layout->addWidget(colordialog);
    layout->addLayout(buttonLayout);

    setLayout(layout);

    sbWidth->setFocus();

*/

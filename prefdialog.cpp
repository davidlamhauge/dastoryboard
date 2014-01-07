#include "prefdialog.h"

PrefDialog::PrefDialog(QDialog *parent) :
    QDialog(parent)
{
    labFps = new QLabel(tr("Frames per second?"));
    cbFps = new QComboBox(this);
    QStringList sl;
    sl.clear();
    sl << tr("24 fps.")  << tr("25 fps.") << tr("30 fps.");
    cbFps->addItems(sl);
    cbFps->setCurrentIndex(1);

    labSeqSc = new QLabel(tr("Seq/sc or Sc/shot?"));
    cbSeqSc = new QComboBox(this);
    sl.clear();
    sl << tr("Sequence and Scene")  << tr("Scene and Shot");
    cbSeqSc->addItems(sl);
    cbSeqSc->setCurrentIndex(1);

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
    buttonLayout->addWidget(labSeqSc,1,0);
    buttonLayout->addWidget(cbSeqSc,1,1);
    buttonLayout->addWidget(labAutoNumber,2,0);
    buttonLayout->addWidget(cbAutoNumber,2,1);
    buttonLayout->addWidget(btnCancel,3,0);
    buttonLayout->addWidget(btnOk,3,1);
    setLayout(buttonLayout);

    setWindowTitle(tr("Set Preferences"));

}

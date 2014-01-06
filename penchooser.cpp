#include "penchooser.h"

penChooser::penChooser(QDialog *parent) :
    QDialog(parent)
{
    colordialog = new QColorDialog();
    colordialog->setOption(QColorDialog::NoButtons);

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
}
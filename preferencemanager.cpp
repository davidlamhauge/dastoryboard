#include "preferencemanager.h"
#include "ui_preferencemanager.h"

#include <QSettings>

PreferenceManager::PreferenceManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceManager)
{
    ui->setupUi(this);

    QSettings settings("TeamLamhauge", "daStoryboard");
    mState = settings.value("loadLast", 0).toInt();
    if (mState == 0)
        ui->cbLoadLast->setChecked(false);
    else
        ui->cbLoadLast->setChecked(true);

    mFps = settings.value("prefFps", 25).toInt();
    ui->sbFps->setValue(mFps);

    connect(ui->cbLoadLast, &QCheckBox::stateChanged, this, &PreferenceManager::setLoadLastProject);
    connect(ui->sbFps, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferenceManager::setPreferredFps);
    connect(ui->btnDone, &QPushButton::clicked, this, &PreferenceManager::close);
}

PreferenceManager::~PreferenceManager()
{
    delete ui;
}

void PreferenceManager::setLoadLastProject(int state)
{
    mState = state;
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("loadLast", mState);
}

void PreferenceManager::setPreferredFps(int fps)
{
    mFps = fps;
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("prefFps", mFps);
}

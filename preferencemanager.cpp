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

    mAutosave = settings.value("autosave", false).toBool();
    if (mAutosave == false)
        ui->cbAutosave->setChecked(false);
    else
        ui->cbAutosave->setChecked(true);

    mFps = settings.value("prefFps", 25).toInt();
    ui->sbFps->setValue(mFps);

    mAutosaveInterval = settings.value("autosaveInterval", 2).toInt();
    ui->sbAutosave->setValue(mAutosaveInterval);

    connect(ui->cbLoadLast, &QCheckBox::stateChanged, this, &PreferenceManager::setLoadLastProject);
    connect(ui->sbFps, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferenceManager::setPreferredFps);
    connect(ui->cbAutosave, &QCheckBox::stateChanged, this, &PreferenceManager::setAutosaveEnabled);
    connect(ui->sbAutosave, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferenceManager::setPreferredAutosaveInterval);
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

void PreferenceManager::setAutosaveEnabled(int state)
{
    if (state == 0)
        mAutosave = false;
    else
        mAutosave = true;
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("autosave", mAutosave);
}

void PreferenceManager::setPreferredAutosaveInterval(int minutes)
{
    mAutosaveInterval = minutes;
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("autosaveInterval", mAutosaveInterval);
}


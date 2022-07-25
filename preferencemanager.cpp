#include "preferencemanager.h"
#include "ui_preferencemanager.h"

#include <QSettings>

PreferenceManager::PreferenceManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceManager)
{
    ui->setupUi(this);

    connect(ui->cbLoadLast, &QCheckBox::stateChanged, this, &PreferenceManager::setLoadLastProject);
    connect(ui->sbFps, QOverload<int>::of(&QSpinBox::valueChanged), this, &PreferenceManager::setPreferredFps);
}

PreferenceManager::~PreferenceManager()
{
    delete ui;
}

void PreferenceManager::setLoadLastProject(int state)
{
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("loadLast", state);
}

void PreferenceManager::setPreferredFps(int fps)
{
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("prefFps", fps);
}

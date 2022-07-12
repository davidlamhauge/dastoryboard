#include "startupmenu.h"
#include "ui_startupmenu.h"

#include <QSettings>
#include <QFileDialog>
#include <QDebug>

StartupMenu::StartupMenu(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::StartupMenu)
{
    ui->setupUi(this);

    QSettings settings("TeamLamhauge", "daStoryboard");
    mProjectPath = settings.value("project", "").toString();
    ui->labProject->setText(mProjectPath);
    mScenePath = settings.value("scene", "").toString();
    ui->labScene->setText(mScenePath);
    settings.setValue("ratio", "Standard");
    settings.setValue("fps", 25);

    if (mProjectPath.isEmpty() || mScenePath.isEmpty())
        ui->btnReady->setEnabled(false);

    connect(ui->btnSelectProject, &QPushButton::clicked, this, &StartupMenu::getProjectName);
    connect(ui->btnSelectScene, &QPushButton::clicked, this, &StartupMenu::getSceneName);
    connect(ui->btnReady, &QPushButton::clicked, this, &StartupMenu::close);
    connect(ui->sbFPS, QOverload<int>::of(&QSpinBox::valueChanged), this, &StartupMenu::setFps);
    connect(ui->rbHD, &QRadioButton::toggled, this, &StartupMenu::setRatio);
    connect(ui->rbStandard, &QRadioButton::toggled, this, &StartupMenu::setRatio);
}

StartupMenu::~StartupMenu()
{
    delete ui;
}

void StartupMenu::getProjectName()
{
    mProjectPath = QFileDialog::getExistingDirectory(this,
                                                tr("Select/Create project folder"),
                                                mLastFolder,
                                                QFileDialog::ShowDirsOnly);
    if (!mProjectPath.isEmpty())
    {
        mLastFolder = mProjectPath;
        ui->labProject->setText(mProjectPath);
        QSettings settings("TeamLamhauge", "daStoryboard");
        settings.setValue("project", mProjectPath);
        checkProgress();
    }
}

void StartupMenu::getSceneName()
{
    mScenePath = QFileDialog::getExistingDirectory(this,
                                                tr("Select/Create scene folder"),
                                                mLastFolder,
                                                QFileDialog::ShowDirsOnly);
    if (!mScenePath.isEmpty())
    {
        mLastFolder = mScenePath;
        ui->labScene->setText(mScenePath);
        QSettings settings("TeamLamhauge", "daStoryboard");
        settings.setValue("scene", mScenePath);
        checkProgress();
    }
}

void StartupMenu::setFps(int fps)
{
    QSettings settings("TeamLamhauge", "daStoryboard");
    settings.setValue("fps", fps);
}

void StartupMenu::setRatio()
{
    QSettings settings("TeamLamhauge", "daStoryboard");
    if (ui->rbStandard->isChecked())
        settings.setValue("ratio", "Standard");
    else
        settings.setValue("ratio", "HD");
}

void StartupMenu::checkProgress()
{
    if (mProjectPath != mScenePath && mScenePath.startsWith(mProjectPath))
        ui->btnReady->setEnabled(true);
    else
        ui->btnReady->setEnabled(false);
}

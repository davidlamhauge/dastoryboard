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
    mStoryBoardPath = settings.value("scene", "").toString();
    ui->labStoryboard->setText(mStoryBoardPath);
    settings.setValue("ratio", "Standard");
    settings.setValue("fps", 25);

    if (mProjectPath.isEmpty() || mStoryBoardPath.isEmpty())
        ui->btnReady->setEnabled(false);

    connect(ui->btnSelectProject, &QPushButton::clicked, this, &StartupMenu::getProjectName);
    connect(ui->btnSelectStoryboard, &QPushButton::clicked, this, &StartupMenu::getStoryboardName);
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

void StartupMenu::getStoryboardName()
{
    mStoryBoardPath = QFileDialog::getExistingDirectory(this,
                                                tr("Select/Create storyboard folder"),
                                                mLastFolder,
                                                QFileDialog::ShowDirsOnly);
    if (!mStoryBoardPath.isEmpty())
    {
        mLastFolder = mStoryBoardPath;
        ui->labStoryboard->setText(mStoryBoardPath);
        QSettings settings("TeamLamhauge", "daStoryboard");
        settings.setValue("scene", mStoryBoardPath);
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
    if (mProjectPath != mStoryBoardPath && mStoryBoardPath.startsWith(mProjectPath))
        ui->btnReady->setEnabled(true);
    else
        ui->btnReady->setEnabled(false);
}

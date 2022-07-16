#include "preferencemanager.h"
#include "ui_preferencemanager.h"

PreferenceManager::PreferenceManager(QWidget *parent) :
    QDialog(parent),
    ui(new Ui::PreferenceManager)
{
    ui->setupUi(this);
}

PreferenceManager::~PreferenceManager()
{
    delete ui;
}

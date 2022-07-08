#ifndef STARTUPMENU_H
#define STARTUPMENU_H

#include <QDialog>

namespace Ui {
class StartupMenu;
}

class StartupMenu : public QDialog
{
    Q_OBJECT

public:
    explicit StartupMenu(QWidget *parent = nullptr);
    ~StartupMenu();

private:
    Ui::StartupMenu *ui;

    void getProjectName();
    void setProjectName(QString name) { mProjectPath = name; }

    void getSceneName();
    void setSceneName(QString scene) { mScenePath = scene; }

    void checkProgress();

    QString mProjectPath = "";
    QString mScenePath = "";
    QString mLastFolder = "";
};

#endif // STARTUPMENU_H

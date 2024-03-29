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
    void getStoryboardName();

    void setFps(int fps);
    void setRatio();

    void checkProgress();

    QString mProjectPath = "";
    QString mStoryBoardPath = "";
    QString mLastFolder = "";
};

#endif // STARTUPMENU_H

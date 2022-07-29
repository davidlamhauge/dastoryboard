#ifndef PREFERENCEMANAGER_H
#define PREFERENCEMANAGER_H

#include <QDialog>

namespace Ui {
class PreferenceManager;
}

class PreferenceManager : public QDialog
{
    Q_OBJECT

public:
    explicit PreferenceManager(QWidget *parent = nullptr);
    ~PreferenceManager();

private:

    Ui::PreferenceManager *ui;

    void setLoadLastProject(int state);
    void setPreferredFps(int fps);
    void setAutosaveEnabled(int state);
    void setPreferredAutosaveInterval(int minutes);

    int mFps = 25;
    int mState = 0;
    bool mAutosave = false;
    int mAutosaveInterval = 2;
};

#endif // PREFERENCEMANAGER_H

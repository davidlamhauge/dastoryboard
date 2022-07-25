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

    int mFps = 25;

};

#endif // PREFERENCEMANAGER_H

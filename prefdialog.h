#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>
#include <QSettings>
#include <QFile>
#include <QXmlStreamReader>
#include <QTextCodec>


class PrefDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PrefDialog(const QString &scPath, QDialog *parent = 0);

    QLabel *labFps;
    QComboBox *cbFps;

    QLabel *labVideoFormat;
    QComboBox *cbVideoFormat;

    QLabel *labAutoNumber;
    QComboBox *cbAutoNumber;

    QPushButton *btnCancel;
    QPushButton *btnOk;
    QGridLayout *buttonLayout;
    QVBoxLayout *layout;


signals:
    
public slots:
private:
    void loadSettings();    // to get fps and autonumber
    void readXml();         // to get videoFormat

    QString sceneDir;       // name of scene directory
    QString scenePath;      // absolute path to scene

    int fps;                // frames per second
    QString videoFormat;    // .ogv or .mpg
    bool autoNumber;        // true or false


};

#endif // PREFDIALOG_H

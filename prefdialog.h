#ifndef PREFDIALOG_H
#define PREFDIALOG_H

#include <QDialog>
#include <QLabel>
#include <QPushButton>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>

class PrefDialog : public QDialog
{
    Q_OBJECT
public:
    explicit PrefDialog(QDialog *parent = 0);

    QLabel *labFps;
    QComboBox *cbFps;

    QLabel *labAutoNumber;
    QComboBox *cbAutoNumber;

    QPushButton *btnCancel;
    QPushButton *btnOk;
    QGridLayout *buttonLayout;
    QVBoxLayout *layout;


signals:
    
public slots:
    
};

#endif // PREFDIALOG_H

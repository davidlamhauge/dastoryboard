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

    QLabel *labPadSize;
    QComboBox *cbPadSize;

    QLabel *labFps;
    QComboBox *cbFps;

    QLabel *labSeqSc;
    QComboBox *cbSeqSc;

    QLabel *labAutoNumber;
    QComboBox *cbAutoNumber;

signals:
    
public slots:
    
};

#endif // PREFDIALOG_H

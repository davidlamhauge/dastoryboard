#ifndef PENCHOOSER_H
#define PENCHOOSER_H

#include <QColorDialog>
#include <QLabel>
#include <QPushButton>
#include <QSpinBox>
#include <QComboBox>
#include <QVBoxLayout>
#include <QGridLayout>

class penChooser : public QDialog
{
    Q_OBJECT
public:
    explicit penChooser(QDialog *parent = nullptr);

    QColorDialog *colordialog;
    QLabel *labWidth;
    QSpinBox *sbWidth;
    QLabel *labPen;
    QComboBox *cbPen;
    QPushButton *btnExit;
    QPushButton *btnChange;
    QGridLayout *buttonLayout;
    QVBoxLayout *layout;
signals:

public slots:

};

#endif // PENCHOOSER_H

/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Sun Dec 22 09:49:17 2013
**      by: Qt User Interface Compiler version 4.8.1
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QFormLayout>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenuBar>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QSpinBox>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_5;
    QWidget *imageContainer;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QLabel *labComments;
    QLineEdit *leComment;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnApplyComment;
    QVBoxLayout *verticalLayout;
    QFormLayout *formLayout;
    QLabel *labShot;
    QLabel *labFrames;
    QLineEdit *leShot;
    QSpinBox *sbFrames;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnCancel;
    QPushButton *btnApplyShotFrames;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *gvStoryPad;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1026, 818);
        QSizePolicy sizePolicy(QSizePolicy::Maximum, QSizePolicy::Maximum);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        imageContainer = new QWidget(centralWidget);
        imageContainer->setObjectName(QString::fromUtf8("imageContainer"));
        imageContainer->setMinimumSize(QSize(800, 130));
        imageContainer->setMaximumSize(QSize(16777215, 130));

        verticalLayout_5->addWidget(imageContainer);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        labComments = new QLabel(centralWidget);
        labComments->setObjectName(QString::fromUtf8("labComments"));

        verticalLayout_2->addWidget(labComments);

        leComment = new QLineEdit(centralWidget);
        leComment->setObjectName(QString::fromUtf8("leComment"));
        leComment->setMaxLength(100);

        verticalLayout_2->addWidget(leComment);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        btnApplyComment = new QPushButton(centralWidget);
        btnApplyComment->setObjectName(QString::fromUtf8("btnApplyComment"));
        QSizePolicy sizePolicy1(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(btnApplyComment->sizePolicy().hasHeightForWidth());
        btnApplyComment->setSizePolicy(sizePolicy1);

        horizontalLayout_2->addWidget(btnApplyComment);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout_3->addLayout(verticalLayout_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        formLayout = new QFormLayout();
        formLayout->setSpacing(6);
        formLayout->setObjectName(QString::fromUtf8("formLayout"));
        labShot = new QLabel(centralWidget);
        labShot->setObjectName(QString::fromUtf8("labShot"));

        formLayout->setWidget(0, QFormLayout::LabelRole, labShot);

        labFrames = new QLabel(centralWidget);
        labFrames->setObjectName(QString::fromUtf8("labFrames"));

        formLayout->setWidget(0, QFormLayout::FieldRole, labFrames);

        leShot = new QLineEdit(centralWidget);
        leShot->setObjectName(QString::fromUtf8("leShot"));
        leShot->setMaxLength(10);

        formLayout->setWidget(1, QFormLayout::LabelRole, leShot);

        sbFrames = new QSpinBox(centralWidget);
        sbFrames->setObjectName(QString::fromUtf8("sbFrames"));
        sbFrames->setMinimum(1);
        sbFrames->setMaximum(999);
        sbFrames->setValue(50);

        formLayout->setWidget(1, QFormLayout::FieldRole, sbFrames);


        verticalLayout->addLayout(formLayout);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_4 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_4);

        btnCancel = new QPushButton(centralWidget);
        btnCancel->setObjectName(QString::fromUtf8("btnCancel"));

        horizontalLayout->addWidget(btnCancel);

        btnApplyShotFrames = new QPushButton(centralWidget);
        btnApplyShotFrames->setObjectName(QString::fromUtf8("btnApplyShotFrames"));

        horizontalLayout->addWidget(btnApplyShotFrames);


        verticalLayout->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        verticalLayout_3->addLayout(verticalLayout);


        horizontalLayout_3->addLayout(verticalLayout_3);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gvStoryPad = new QGraphicsView(centralWidget);
        gvStoryPad->setObjectName(QString::fromUtf8("gvStoryPad"));
        gvStoryPad->setMinimumSize(QSize(640, 480));
        gvStoryPad->setMaximumSize(QSize(640, 480));

        verticalLayout_4->addWidget(gvStoryPad);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_4->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_4);


        verticalLayout_5->addLayout(horizontalLayout_3);


        gridLayout->addLayout(verticalLayout_5, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1026, 25));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy2(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy2);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "daStoryBoard", 0, QApplication::UnicodeUTF8));
        labComments->setText(QApplication::translate("MainWindow", "Comments:  (max 100 chars.)", 0, QApplication::UnicodeUTF8));
        btnApplyComment->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        labShot->setText(QApplication::translate("MainWindow", "Shot #", 0, QApplication::UnicodeUTF8));
        labFrames->setText(QApplication::translate("MainWindow", "Frames:", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        btnApplyShotFrames->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

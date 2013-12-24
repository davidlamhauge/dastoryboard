/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Tue Dec 24 11:14:33 2013
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
#include <QtGui/QFrame>
#include <QtGui/QGraphicsView>
#include <QtGui/QGridLayout>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
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
    QAction *action_New_Storyboard;
    QAction *action_Save_Storyboard;
    QAction *actionE_xit;
    QWidget *centralWidget;
    QGridLayout *gridLayout_2;
    QVBoxLayout *verticalLayout_4;
    QWidget *imageContainer;
    QFrame *line_3;
    QHBoxLayout *horizontalLayout_4;
    QVBoxLayout *verticalLayout;
    QVBoxLayout *verticalLayout_2;
    QLabel *labComments;
    QLineEdit *leComment;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *btnApplyComment;
    QFrame *line;
    QHBoxLayout *horizontalLayout_3;
    QSpacerItem *horizontalSpacer_2;
    QGridLayout *gridLayout;
    QLabel *labShot;
    QLabel *labFrames;
    QLineEdit *leShot;
    QSpinBox *sbFrames;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_4;
    QPushButton *btnCancel;
    QPushButton *btnApplyShotFrames;
    QFrame *line_2;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *gvSketchPad;
    QSpacerItem *verticalSpacer;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1026, 818);
        QSizePolicy sizePolicy(QSizePolicy::MinimumExpanding, QSizePolicy::MinimumExpanding);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action_New_Storyboard = new QAction(MainWindow);
        action_New_Storyboard->setObjectName(QString::fromUtf8("action_New_Storyboard"));
        action_Save_Storyboard = new QAction(MainWindow);
        action_Save_Storyboard->setObjectName(QString::fromUtf8("action_Save_Storyboard"));
        actionE_xit = new QAction(MainWindow);
        actionE_xit->setObjectName(QString::fromUtf8("actionE_xit"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_2 = new QGridLayout(centralWidget);
        gridLayout_2->setSpacing(6);
        gridLayout_2->setContentsMargins(11, 11, 11, 11);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        imageContainer = new QWidget(centralWidget);
        imageContainer->setObjectName(QString::fromUtf8("imageContainer"));
        QSizePolicy sizePolicy1(QSizePolicy::Expanding, QSizePolicy::Preferred);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(imageContainer->sizePolicy().hasHeightForWidth());
        imageContainer->setSizePolicy(sizePolicy1);
        imageContainer->setMinimumSize(QSize(0, 130));
        imageContainer->setMaximumSize(QSize(16777215, 130));

        verticalLayout_4->addWidget(imageContainer);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        verticalLayout_4->addWidget(line_3);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
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
        QSizePolicy sizePolicy2(QSizePolicy::Minimum, QSizePolicy::Preferred);
        sizePolicy2.setHorizontalStretch(0);
        sizePolicy2.setVerticalStretch(0);
        sizePolicy2.setHeightForWidth(btnApplyComment->sizePolicy().hasHeightForWidth());
        btnApplyComment->setSizePolicy(sizePolicy2);

        horizontalLayout_2->addWidget(btnApplyComment);


        verticalLayout_2->addLayout(horizontalLayout_2);


        verticalLayout->addLayout(verticalLayout_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labShot = new QLabel(centralWidget);
        labShot->setObjectName(QString::fromUtf8("labShot"));

        gridLayout->addWidget(labShot, 0, 0, 1, 1);

        labFrames = new QLabel(centralWidget);
        labFrames->setObjectName(QString::fromUtf8("labFrames"));

        gridLayout->addWidget(labFrames, 0, 1, 1, 1);

        leShot = new QLineEdit(centralWidget);
        leShot->setObjectName(QString::fromUtf8("leShot"));
        leShot->setMaxLength(10);

        gridLayout->addWidget(leShot, 1, 0, 1, 1);

        sbFrames = new QSpinBox(centralWidget);
        sbFrames->setObjectName(QString::fromUtf8("sbFrames"));
        sbFrames->setMinimum(1);
        sbFrames->setMaximum(999);
        sbFrames->setValue(50);

        gridLayout->addWidget(sbFrames, 1, 1, 1, 1);


        horizontalLayout_3->addLayout(gridLayout);


        verticalLayout->addLayout(horizontalLayout_3);

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

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line_2);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout->addItem(verticalSpacer_2);


        horizontalLayout_4->addLayout(verticalLayout);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gvSketchPad = new QGraphicsView(centralWidget);
        gvSketchPad->setObjectName(QString::fromUtf8("gvSketchPad"));
        gvSketchPad->setMinimumSize(QSize(642, 482));
        gvSketchPad->setMaximumSize(QSize(642, 482));
        gvSketchPad->setMouseTracking(true);

        verticalLayout_3->addWidget(gvSketchPad);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_4->addLayout(verticalLayout_3);


        verticalLayout_4->addLayout(horizontalLayout_4);


        gridLayout_2->addLayout(verticalLayout_4, 0, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1026, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        MainWindow->setMenuBar(menuBar);
        mainToolBar = new QToolBar(MainWindow);
        mainToolBar->setObjectName(QString::fromUtf8("mainToolBar"));
        QSizePolicy sizePolicy3(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy3.setHorizontalStretch(0);
        sizePolicy3.setVerticalStretch(0);
        sizePolicy3.setHeightForWidth(mainToolBar->sizePolicy().hasHeightForWidth());
        mainToolBar->setSizePolicy(sizePolicy3);
        MainWindow->addToolBar(Qt::TopToolBarArea, mainToolBar);
        statusBar = new QStatusBar(MainWindow);
        statusBar->setObjectName(QString::fromUtf8("statusBar"));
        MainWindow->setStatusBar(statusBar);

        menuBar->addAction(menu_File->menuAction());
        menu_File->addAction(action_New_Storyboard);
        menu_File->addAction(action_Save_Storyboard);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "daStoryBoard", 0, QApplication::UnicodeUTF8));
        action_New_Storyboard->setText(QApplication::translate("MainWindow", "&New Storyboard", 0, QApplication::UnicodeUTF8));
        action_New_Storyboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+N", 0, QApplication::UnicodeUTF8));
        action_Save_Storyboard->setText(QApplication::translate("MainWindow", "&Save Storyboard", 0, QApplication::UnicodeUTF8));
        action_Save_Storyboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+S", 0, QApplication::UnicodeUTF8));
        actionE_xit->setText(QApplication::translate("MainWindow", "E&xit", 0, QApplication::UnicodeUTF8));
        actionE_xit->setShortcut(QApplication::translate("MainWindow", "Ctrl+X", 0, QApplication::UnicodeUTF8));
        labComments->setText(QApplication::translate("MainWindow", "Comments:  (max 100 chars.)", 0, QApplication::UnicodeUTF8));
        btnApplyComment->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        labShot->setText(QApplication::translate("MainWindow", "Shot #", 0, QApplication::UnicodeUTF8));
        labFrames->setText(QApplication::translate("MainWindow", "Frames:", 0, QApplication::UnicodeUTF8));
        btnCancel->setText(QApplication::translate("MainWindow", "Cancel", 0, QApplication::UnicodeUTF8));
        btnApplyShotFrames->setText(QApplication::translate("MainWindow", "Apply", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

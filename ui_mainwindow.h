/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Jan 1 14:19:44 2014
**      by: Qt User Interface Compiler version 4.8.4
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
    QAction *actionSave_Pen_1;
    QAction *actionSave_Pen_2;
    QAction *actionSave_Pen_3;
    QAction *actionSave_Pen_4;
    QAction *actionLoad_Pen_1;
    QAction *actionLoad_Pen_2;
    QAction *actionLoad_Pen_3;
    QAction *actionLoad_Pen_4;
    QAction *actionSet_Pen_width;
    QAction *actionSet_Pen_Color;
    QAction *actionSave_Settings;
    QAction *actionAppend_Sketchpad;
    QAction *actionInsert_Sketchpad;
    QAction *action_Open_Storyboard;
    QWidget *centralWidget;
    QGridLayout *gridLayout;
    QVBoxLayout *verticalLayout_7;
    QGraphicsView *gvStoryboard;
    QHBoxLayout *horizontalLayout_2;
    QVBoxLayout *verticalLayout_6;
    QVBoxLayout *verticalLayout_2;
    QLabel *labComments;
    QLineEdit *leComment;
    QFrame *line;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout_5;
    QLabel *labScene;
    QLineEdit *leScene;
    QVBoxLayout *verticalLayout_4;
    QLabel *labShot;
    QLineEdit *leShot;
    QVBoxLayout *verticalLayout;
    QLabel *labFrames;
    QSpinBox *sbFrames;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *gvSketchPad;
    QSpacerItem *verticalSpacer;
    QFrame *line_3;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuSettings;
    QMenu *menuSave_Pen;
    QMenu *menuLoad_Pen;
    QMenu *menuEdit;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1058, 818);
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
        actionSave_Pen_1 = new QAction(MainWindow);
        actionSave_Pen_1->setObjectName(QString::fromUtf8("actionSave_Pen_1"));
        actionSave_Pen_2 = new QAction(MainWindow);
        actionSave_Pen_2->setObjectName(QString::fromUtf8("actionSave_Pen_2"));
        actionSave_Pen_3 = new QAction(MainWindow);
        actionSave_Pen_3->setObjectName(QString::fromUtf8("actionSave_Pen_3"));
        actionSave_Pen_4 = new QAction(MainWindow);
        actionSave_Pen_4->setObjectName(QString::fromUtf8("actionSave_Pen_4"));
        actionLoad_Pen_1 = new QAction(MainWindow);
        actionLoad_Pen_1->setObjectName(QString::fromUtf8("actionLoad_Pen_1"));
        actionLoad_Pen_2 = new QAction(MainWindow);
        actionLoad_Pen_2->setObjectName(QString::fromUtf8("actionLoad_Pen_2"));
        actionLoad_Pen_3 = new QAction(MainWindow);
        actionLoad_Pen_3->setObjectName(QString::fromUtf8("actionLoad_Pen_3"));
        actionLoad_Pen_4 = new QAction(MainWindow);
        actionLoad_Pen_4->setObjectName(QString::fromUtf8("actionLoad_Pen_4"));
        actionSet_Pen_width = new QAction(MainWindow);
        actionSet_Pen_width->setObjectName(QString::fromUtf8("actionSet_Pen_width"));
        actionSet_Pen_Color = new QAction(MainWindow);
        actionSet_Pen_Color->setObjectName(QString::fromUtf8("actionSet_Pen_Color"));
        actionSave_Settings = new QAction(MainWindow);
        actionSave_Settings->setObjectName(QString::fromUtf8("actionSave_Settings"));
        actionAppend_Sketchpad = new QAction(MainWindow);
        actionAppend_Sketchpad->setObjectName(QString::fromUtf8("actionAppend_Sketchpad"));
        actionInsert_Sketchpad = new QAction(MainWindow);
        actionInsert_Sketchpad->setObjectName(QString::fromUtf8("actionInsert_Sketchpad"));
        action_Open_Storyboard = new QAction(MainWindow);
        action_Open_Storyboard->setObjectName(QString::fromUtf8("action_Open_Storyboard"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout = new QGridLayout(centralWidget);
        gridLayout->setSpacing(6);
        gridLayout->setContentsMargins(11, 11, 11, 11);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        verticalLayout_7 = new QVBoxLayout();
        verticalLayout_7->setSpacing(6);
        verticalLayout_7->setObjectName(QString::fromUtf8("verticalLayout_7"));
        gvStoryboard = new QGraphicsView(centralWidget);
        gvStoryboard->setObjectName(QString::fromUtf8("gvStoryboard"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gvStoryboard->sizePolicy().hasHeightForWidth());
        gvStoryboard->setSizePolicy(sizePolicy1);
        gvStoryboard->setMinimumSize(QSize(0, 140));
        gvStoryboard->setMaximumSize(QSize(16777215, 140));

        verticalLayout_7->addWidget(gvStoryboard);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
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


        verticalLayout_6->addLayout(verticalLayout_2);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout_5 = new QVBoxLayout();
        verticalLayout_5->setSpacing(6);
        verticalLayout_5->setObjectName(QString::fromUtf8("verticalLayout_5"));
        labScene = new QLabel(centralWidget);
        labScene->setObjectName(QString::fromUtf8("labScene"));

        verticalLayout_5->addWidget(labScene);

        leScene = new QLineEdit(centralWidget);
        leScene->setObjectName(QString::fromUtf8("leScene"));

        verticalLayout_5->addWidget(leScene);


        horizontalLayout->addLayout(verticalLayout_5);

        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        labShot = new QLabel(centralWidget);
        labShot->setObjectName(QString::fromUtf8("labShot"));

        verticalLayout_4->addWidget(labShot);

        leShot = new QLineEdit(centralWidget);
        leShot->setObjectName(QString::fromUtf8("leShot"));
        leShot->setMaxLength(10);

        verticalLayout_4->addWidget(leShot);


        horizontalLayout->addLayout(verticalLayout_4);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labFrames = new QLabel(centralWidget);
        labFrames->setObjectName(QString::fromUtf8("labFrames"));

        verticalLayout->addWidget(labFrames);

        sbFrames = new QSpinBox(centralWidget);
        sbFrames->setObjectName(QString::fromUtf8("sbFrames"));
        sbFrames->setMinimum(1);
        sbFrames->setMaximum(999);
        sbFrames->setValue(50);

        verticalLayout->addWidget(sbFrames);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_6->addLayout(horizontalLayout);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_6->addItem(verticalSpacer_2);


        horizontalLayout_2->addLayout(verticalLayout_6);

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


        horizontalLayout_2->addLayout(verticalLayout_3);


        verticalLayout_7->addLayout(horizontalLayout_2);


        gridLayout->addLayout(verticalLayout_7, 0, 0, 1, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout->addWidget(line_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuSave_Pen = new QMenu(menuSettings);
        menuSave_Pen->setObjectName(QString::fromUtf8("menuSave_Pen"));
        menuLoad_Pen = new QMenu(menuSettings);
        menuLoad_Pen->setObjectName(QString::fromUtf8("menuLoad_Pen"));
        menuEdit = new QMenu(menuBar);
        menuEdit->setObjectName(QString::fromUtf8("menuEdit"));
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

        menuBar->addAction(menu_File->menuAction());
        menuBar->addAction(menuEdit->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menu_File->addAction(action_New_Storyboard);
        menu_File->addAction(action_Open_Storyboard);
        menu_File->addAction(action_Save_Storyboard);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);
        menuSettings->addAction(actionSet_Pen_width);
        menuSettings->addAction(actionSet_Pen_Color);
        menuSettings->addAction(menuLoad_Pen->menuAction());
        menuSettings->addAction(menuSave_Pen->menuAction());
        menuSave_Pen->addAction(actionSave_Pen_1);
        menuSave_Pen->addAction(actionSave_Pen_2);
        menuSave_Pen->addAction(actionSave_Pen_3);
        menuSave_Pen->addAction(actionSave_Pen_4);
        menuLoad_Pen->addAction(actionLoad_Pen_1);
        menuLoad_Pen->addAction(actionLoad_Pen_2);
        menuLoad_Pen->addAction(actionLoad_Pen_3);
        menuLoad_Pen->addAction(actionLoad_Pen_4);
        menuEdit->addAction(actionAppend_Sketchpad);
        menuEdit->addAction(actionInsert_Sketchpad);

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
        actionSave_Pen_1->setText(QApplication::translate("MainWindow", "Save Pen 1", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_1->setShortcut(QApplication::translate("MainWindow", "Ctrl+F5", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_2->setText(QApplication::translate("MainWindow", "Save Pen 2", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_2->setShortcut(QApplication::translate("MainWindow", "Ctrl+F6", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_3->setText(QApplication::translate("MainWindow", "Save Pen 3", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_3->setShortcut(QApplication::translate("MainWindow", "Ctrl+F7", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_4->setText(QApplication::translate("MainWindow", "Save Pen 4", 0, QApplication::UnicodeUTF8));
        actionSave_Pen_4->setShortcut(QApplication::translate("MainWindow", "Ctrl+F8", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_1->setText(QApplication::translate("MainWindow", "Load Pen 1", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_1->setShortcut(QApplication::translate("MainWindow", "F5", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_2->setText(QApplication::translate("MainWindow", "Load Pen 2", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_2->setShortcut(QApplication::translate("MainWindow", "F6", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_3->setText(QApplication::translate("MainWindow", "Load Pen 3", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_3->setShortcut(QApplication::translate("MainWindow", "F7", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_4->setText(QApplication::translate("MainWindow", "Load Pen 4", 0, QApplication::UnicodeUTF8));
        actionLoad_Pen_4->setShortcut(QApplication::translate("MainWindow", "F8", 0, QApplication::UnicodeUTF8));
        actionSet_Pen_width->setText(QApplication::translate("MainWindow", "Set Pen Width", 0, QApplication::UnicodeUTF8));
        actionSet_Pen_width->setShortcut(QApplication::translate("MainWindow", "Alt+W", 0, QApplication::UnicodeUTF8));
        actionSet_Pen_Color->setText(QApplication::translate("MainWindow", "Set Pen Color", 0, QApplication::UnicodeUTF8));
        actionSet_Pen_Color->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0, QApplication::UnicodeUTF8));
        actionSave_Settings->setText(QApplication::translate("MainWindow", "Save Settings", 0, QApplication::UnicodeUTF8));
        actionSave_Settings->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0, QApplication::UnicodeUTF8));
        actionAppend_Sketchpad->setText(QApplication::translate("MainWindow", "Append Sketchpad", 0, QApplication::UnicodeUTF8));
        actionAppend_Sketchpad->setShortcut(QApplication::translate("MainWindow", "Alt+A", 0, QApplication::UnicodeUTF8));
        actionInsert_Sketchpad->setText(QApplication::translate("MainWindow", "Insert Sketchpad", 0, QApplication::UnicodeUTF8));
        actionInsert_Sketchpad->setShortcut(QApplication::translate("MainWindow", "Alt+I", 0, QApplication::UnicodeUTF8));
        action_Open_Storyboard->setText(QApplication::translate("MainWindow", "&Open Storyboard", 0, QApplication::UnicodeUTF8));
        action_Open_Storyboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        labComments->setText(QApplication::translate("MainWindow", "Comments:  (max 100 chars.)", 0, QApplication::UnicodeUTF8));
        labScene->setText(QApplication::translate("MainWindow", "Scene", 0, QApplication::UnicodeUTF8));
        labShot->setText(QApplication::translate("MainWindow", "Shot", 0, QApplication::UnicodeUTF8));
        labFrames->setText(QApplication::translate("MainWindow", "Frames:", 0, QApplication::UnicodeUTF8));
        menu_File->setTitle(QApplication::translate("MainWindow", "&File", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Settings", 0, QApplication::UnicodeUTF8));
        menuSave_Pen->setTitle(QApplication::translate("MainWindow", "Save Pen", 0, QApplication::UnicodeUTF8));
        menuLoad_Pen->setTitle(QApplication::translate("MainWindow", "Load Pen", 0, QApplication::UnicodeUTF8));
        menuEdit->setTitle(QApplication::translate("MainWindow", "Sketchpads", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

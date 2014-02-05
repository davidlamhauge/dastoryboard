/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created: Wed Feb 5 16:59:49 2014
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
#include <QtGui/QComboBox>
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
    QAction *action_About;
    QAction *actionErase_All;
    QAction *actionErase_Sketch_Pen;
    QAction *actionPreferences;
    QAction *actionCenter_Storyboard;
    QAction *action_New_Scene;
    QAction *action_Open_Scene;
    QAction *actionDelete_drawing;
    QAction *actionMovePadLeft;
    QAction *actionMovePadRight;
    QAction *actionRun_Scene;
    QWidget *centralWidget;
    QGridLayout *gridLayout_4;
    QVBoxLayout *verticalLayout_4;
    QGraphicsView *gvStoryboard;
    QHBoxLayout *horizontalLayout_3;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer_2;
    QVBoxLayout *verticalLayout;
    QLabel *labComments;
    QLineEdit *leComment;
    QGridLayout *gridLayout_3;
    QLabel *labScene;
    QLabel *labSceneInfo;
    QLabel *labShot;
    QLineEdit *leShot;
    QLabel *labFrames;
    QSpinBox *sbFrames;
    QFrame *line;
    QHBoxLayout *horizontalLayout_4;
    QSpacerItem *horizontalSpacer;
    QVBoxLayout *verticalLayout_6;
    QHBoxLayout *horizontalLayout_2;
    QLabel *labScenes;
    QComboBox *cbScenes;
    QFrame *line_2;
    QGridLayout *gridLayout;
    QLabel *labPens;
    QPushButton *btnStandardPen;
    QPushButton *btnF5;
    QPushButton *btnF6;
    QPushButton *btnF7;
    QPushButton *btnF8;
    QFrame *line_4;
    QGridLayout *gridLayout_2;
    QLabel *labFrameCount;
    QLabel *labActivePadInfo;
    QLabel *labTimeValue;
    QLabel *labTime;
    QLabel *labActivePad;
    QLabel *labFramesCountValue;
    QSpacerItem *verticalSpacer_2;
    QVBoxLayout *verticalLayout_3;
    QGraphicsView *gvSketchPad;
    QSpacerItem *verticalSpacer;
    QSpacerItem *horizontalSpacer_3;
    QFrame *line_3;
    QMenuBar *menuBar;
    QMenu *menu_File;
    QMenu *menuSettings;
    QMenu *menuLoad_Pen;
    QMenu *menuSketchpad;
    QMenu *menu_Help;
    QMenu *menuScene;
    QToolBar *mainToolBar;
    QStatusBar *statusBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(1058, 815);
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
        action_About = new QAction(MainWindow);
        action_About->setObjectName(QString::fromUtf8("action_About"));
        actionErase_All = new QAction(MainWindow);
        actionErase_All->setObjectName(QString::fromUtf8("actionErase_All"));
        actionErase_Sketch_Pen = new QAction(MainWindow);
        actionErase_Sketch_Pen->setObjectName(QString::fromUtf8("actionErase_Sketch_Pen"));
        actionPreferences = new QAction(MainWindow);
        actionPreferences->setObjectName(QString::fromUtf8("actionPreferences"));
        actionCenter_Storyboard = new QAction(MainWindow);
        actionCenter_Storyboard->setObjectName(QString::fromUtf8("actionCenter_Storyboard"));
        action_New_Scene = new QAction(MainWindow);
        action_New_Scene->setObjectName(QString::fromUtf8("action_New_Scene"));
        action_Open_Scene = new QAction(MainWindow);
        action_Open_Scene->setObjectName(QString::fromUtf8("action_Open_Scene"));
        actionDelete_drawing = new QAction(MainWindow);
        actionDelete_drawing->setObjectName(QString::fromUtf8("actionDelete_drawing"));
        actionMovePadLeft = new QAction(MainWindow);
        actionMovePadLeft->setObjectName(QString::fromUtf8("actionMovePadLeft"));
        actionMovePadRight = new QAction(MainWindow);
        actionMovePadRight->setObjectName(QString::fromUtf8("actionMovePadRight"));
        actionRun_Scene = new QAction(MainWindow);
        actionRun_Scene->setObjectName(QString::fromUtf8("actionRun_Scene"));
        centralWidget = new QWidget(MainWindow);
        centralWidget->setObjectName(QString::fromUtf8("centralWidget"));
        gridLayout_4 = new QGridLayout(centralWidget);
        gridLayout_4->setSpacing(6);
        gridLayout_4->setContentsMargins(11, 11, 11, 11);
        gridLayout_4->setObjectName(QString::fromUtf8("gridLayout_4"));
        verticalLayout_4 = new QVBoxLayout();
        verticalLayout_4->setSpacing(6);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        gvStoryboard = new QGraphicsView(centralWidget);
        gvStoryboard->setObjectName(QString::fromUtf8("gvStoryboard"));
        QSizePolicy sizePolicy1(QSizePolicy::MinimumExpanding, QSizePolicy::Expanding);
        sizePolicy1.setHorizontalStretch(0);
        sizePolicy1.setVerticalStretch(0);
        sizePolicy1.setHeightForWidth(gvStoryboard->sizePolicy().hasHeightForWidth());
        gvStoryboard->setSizePolicy(sizePolicy1);
        gvStoryboard->setMinimumSize(QSize(0, 140));
        gvStoryboard->setMaximumSize(QSize(16777215, 140));

        verticalLayout_4->addWidget(gvStoryboard);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setSpacing(6);
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        verticalLayout_2 = new QVBoxLayout();
        verticalLayout_2->setSpacing(6);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setSpacing(6);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer_2 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer_2);

        verticalLayout = new QVBoxLayout();
        verticalLayout->setSpacing(6);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        labComments = new QLabel(centralWidget);
        labComments->setObjectName(QString::fromUtf8("labComments"));

        verticalLayout->addWidget(labComments);

        leComment = new QLineEdit(centralWidget);
        leComment->setObjectName(QString::fromUtf8("leComment"));
        leComment->setMaxLength(100);

        verticalLayout->addWidget(leComment);

        gridLayout_3 = new QGridLayout();
        gridLayout_3->setSpacing(6);
        gridLayout_3->setObjectName(QString::fromUtf8("gridLayout_3"));
        labScene = new QLabel(centralWidget);
        labScene->setObjectName(QString::fromUtf8("labScene"));

        gridLayout_3->addWidget(labScene, 0, 0, 1, 1);

        labSceneInfo = new QLabel(centralWidget);
        labSceneInfo->setObjectName(QString::fromUtf8("labSceneInfo"));
        QPalette palette;
        QBrush brush(QColor(0, 85, 255, 255));
        brush.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Active, QPalette::Text, brush);
        QBrush brush1(QColor(60, 60, 60, 255));
        brush1.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Inactive, QPalette::Text, brush1);
        QBrush brush2(QColor(159, 158, 158, 255));
        brush2.setStyle(Qt::SolidPattern);
        palette.setBrush(QPalette::Disabled, QPalette::Text, brush2);
        labSceneInfo->setPalette(palette);
        QFont font;
        font.setPointSize(12);
        font.setBold(true);
        font.setWeight(75);
        labSceneInfo->setFont(font);

        gridLayout_3->addWidget(labSceneInfo, 0, 1, 1, 1);

        labShot = new QLabel(centralWidget);
        labShot->setObjectName(QString::fromUtf8("labShot"));

        gridLayout_3->addWidget(labShot, 1, 0, 1, 1);

        leShot = new QLineEdit(centralWidget);
        leShot->setObjectName(QString::fromUtf8("leShot"));
        leShot->setMaxLength(10);

        gridLayout_3->addWidget(leShot, 1, 1, 1, 1);

        labFrames = new QLabel(centralWidget);
        labFrames->setObjectName(QString::fromUtf8("labFrames"));

        gridLayout_3->addWidget(labFrames, 2, 0, 1, 1);

        sbFrames = new QSpinBox(centralWidget);
        sbFrames->setObjectName(QString::fromUtf8("sbFrames"));
        sbFrames->setMinimum(1);
        sbFrames->setMaximum(999);
        sbFrames->setValue(50);

        gridLayout_3->addWidget(sbFrames, 2, 1, 1, 1);


        verticalLayout->addLayout(gridLayout_3);

        line = new QFrame(centralWidget);
        line->setObjectName(QString::fromUtf8("line"));
        line->setFrameShape(QFrame::HLine);
        line->setFrameShadow(QFrame::Sunken);

        verticalLayout->addWidget(line);


        horizontalLayout->addLayout(verticalLayout);


        verticalLayout_2->addLayout(horizontalLayout);

        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setSpacing(6);
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_4->addItem(horizontalSpacer);

        verticalLayout_6 = new QVBoxLayout();
        verticalLayout_6->setSpacing(6);
        verticalLayout_6->setObjectName(QString::fromUtf8("verticalLayout_6"));
        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setSpacing(6);
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        labScenes = new QLabel(centralWidget);
        labScenes->setObjectName(QString::fromUtf8("labScenes"));

        horizontalLayout_2->addWidget(labScenes);

        cbScenes = new QComboBox(centralWidget);
        cbScenes->setObjectName(QString::fromUtf8("cbScenes"));

        horizontalLayout_2->addWidget(cbScenes);


        verticalLayout_6->addLayout(horizontalLayout_2);

        line_2 = new QFrame(centralWidget);
        line_2->setObjectName(QString::fromUtf8("line_2"));
        line_2->setFrameShape(QFrame::HLine);
        line_2->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_2);

        gridLayout = new QGridLayout();
        gridLayout->setSpacing(6);
        gridLayout->setObjectName(QString::fromUtf8("gridLayout"));
        labPens = new QLabel(centralWidget);
        labPens->setObjectName(QString::fromUtf8("labPens"));

        gridLayout->addWidget(labPens, 0, 0, 1, 1);

        btnStandardPen = new QPushButton(centralWidget);
        btnStandardPen->setObjectName(QString::fromUtf8("btnStandardPen"));

        gridLayout->addWidget(btnStandardPen, 0, 1, 1, 1);

        btnF5 = new QPushButton(centralWidget);
        btnF5->setObjectName(QString::fromUtf8("btnF5"));

        gridLayout->addWidget(btnF5, 1, 0, 1, 1);

        btnF6 = new QPushButton(centralWidget);
        btnF6->setObjectName(QString::fromUtf8("btnF6"));

        gridLayout->addWidget(btnF6, 1, 1, 1, 1);

        btnF7 = new QPushButton(centralWidget);
        btnF7->setObjectName(QString::fromUtf8("btnF7"));

        gridLayout->addWidget(btnF7, 2, 0, 1, 1);

        btnF8 = new QPushButton(centralWidget);
        btnF8->setObjectName(QString::fromUtf8("btnF8"));

        gridLayout->addWidget(btnF8, 2, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout);

        line_4 = new QFrame(centralWidget);
        line_4->setObjectName(QString::fromUtf8("line_4"));
        line_4->setFrameShape(QFrame::HLine);
        line_4->setFrameShadow(QFrame::Sunken);

        verticalLayout_6->addWidget(line_4);

        gridLayout_2 = new QGridLayout();
        gridLayout_2->setSpacing(6);
        gridLayout_2->setObjectName(QString::fromUtf8("gridLayout_2"));
        labFrameCount = new QLabel(centralWidget);
        labFrameCount->setObjectName(QString::fromUtf8("labFrameCount"));

        gridLayout_2->addWidget(labFrameCount, 1, 0, 1, 1);

        labActivePadInfo = new QLabel(centralWidget);
        labActivePadInfo->setObjectName(QString::fromUtf8("labActivePadInfo"));

        gridLayout_2->addWidget(labActivePadInfo, 0, 1, 1, 1);

        labTimeValue = new QLabel(centralWidget);
        labTimeValue->setObjectName(QString::fromUtf8("labTimeValue"));

        gridLayout_2->addWidget(labTimeValue, 2, 1, 1, 1);

        labTime = new QLabel(centralWidget);
        labTime->setObjectName(QString::fromUtf8("labTime"));

        gridLayout_2->addWidget(labTime, 2, 0, 1, 1);

        labActivePad = new QLabel(centralWidget);
        labActivePad->setObjectName(QString::fromUtf8("labActivePad"));

        gridLayout_2->addWidget(labActivePad, 0, 0, 1, 1);

        labFramesCountValue = new QLabel(centralWidget);
        labFramesCountValue->setObjectName(QString::fromUtf8("labFramesCountValue"));

        gridLayout_2->addWidget(labFramesCountValue, 1, 1, 1, 1);


        verticalLayout_6->addLayout(gridLayout_2);


        horizontalLayout_4->addLayout(verticalLayout_6);


        verticalLayout_2->addLayout(horizontalLayout_4);

        verticalSpacer_2 = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_2->addItem(verticalSpacer_2);


        horizontalLayout_3->addLayout(verticalLayout_2);

        verticalLayout_3 = new QVBoxLayout();
        verticalLayout_3->setSpacing(6);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        gvSketchPad = new QGraphicsView(centralWidget);
        gvSketchPad->setObjectName(QString::fromUtf8("gvSketchPad"));
        gvSketchPad->setMinimumSize(QSize(0, 0));
        gvSketchPad->setMaximumSize(QSize(10000, 10000));
        gvSketchPad->setMouseTracking(true);

        verticalLayout_3->addWidget(gvSketchPad);

        verticalSpacer = new QSpacerItem(20, 40, QSizePolicy::Minimum, QSizePolicy::Expanding);

        verticalLayout_3->addItem(verticalSpacer);


        horizontalLayout_3->addLayout(verticalLayout_3);

        horizontalSpacer_3 = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_3->addItem(horizontalSpacer_3);


        verticalLayout_4->addLayout(horizontalLayout_3);


        gridLayout_4->addLayout(verticalLayout_4, 0, 0, 1, 1);

        line_3 = new QFrame(centralWidget);
        line_3->setObjectName(QString::fromUtf8("line_3"));
        line_3->setFrameShape(QFrame::HLine);
        line_3->setFrameShadow(QFrame::Sunken);

        gridLayout_4->addWidget(line_3, 1, 0, 1, 1);

        MainWindow->setCentralWidget(centralWidget);
        menuBar = new QMenuBar(MainWindow);
        menuBar->setObjectName(QString::fromUtf8("menuBar"));
        menuBar->setGeometry(QRect(0, 0, 1058, 25));
        menu_File = new QMenu(menuBar);
        menu_File->setObjectName(QString::fromUtf8("menu_File"));
        menuSettings = new QMenu(menuBar);
        menuSettings->setObjectName(QString::fromUtf8("menuSettings"));
        menuLoad_Pen = new QMenu(menuSettings);
        menuLoad_Pen->setObjectName(QString::fromUtf8("menuLoad_Pen"));
        menuSketchpad = new QMenu(menuBar);
        menuSketchpad->setObjectName(QString::fromUtf8("menuSketchpad"));
        menu_Help = new QMenu(menuBar);
        menu_Help->setObjectName(QString::fromUtf8("menu_Help"));
        menuScene = new QMenu(menuBar);
        menuScene->setObjectName(QString::fromUtf8("menuScene"));
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
        menuBar->addAction(menuScene->menuAction());
        menuBar->addAction(menuSettings->menuAction());
        menuBar->addAction(menuSketchpad->menuAction());
        menuBar->addAction(menu_Help->menuAction());
        menu_File->addAction(action_New_Storyboard);
        menu_File->addAction(action_Open_Storyboard);
        menu_File->addAction(action_Save_Storyboard);
        menu_File->addSeparator();
        menu_File->addAction(actionPreferences);
        menu_File->addSeparator();
        menu_File->addAction(actionE_xit);
        menuSettings->addAction(actionSet_Pen_Color);
        menuSettings->addAction(menuLoad_Pen->menuAction());
        menuSettings->addAction(actionErase_Sketch_Pen);
        menuLoad_Pen->addAction(actionLoad_Pen_1);
        menuLoad_Pen->addAction(actionLoad_Pen_2);
        menuLoad_Pen->addAction(actionLoad_Pen_3);
        menuLoad_Pen->addAction(actionLoad_Pen_4);
        menuSketchpad->addAction(actionAppend_Sketchpad);
        menuSketchpad->addAction(actionInsert_Sketchpad);
        menuSketchpad->addAction(actionCenter_Storyboard);
        menuSketchpad->addAction(actionErase_All);
        menuSketchpad->addAction(actionDelete_drawing);
        menuSketchpad->addSeparator();
        menuSketchpad->addAction(actionMovePadLeft);
        menuSketchpad->addAction(actionMovePadRight);
        menu_Help->addAction(action_About);
        menuScene->addAction(action_New_Scene);
        menuScene->addSeparator();
        menuScene->addAction(actionRun_Scene);

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
        actionSet_Pen_Color->setText(QApplication::translate("MainWindow", "Set Pen Color and Width", 0, QApplication::UnicodeUTF8));
        actionSet_Pen_Color->setShortcut(QApplication::translate("MainWindow", "F4", 0, QApplication::UnicodeUTF8));
        actionSave_Settings->setText(QApplication::translate("MainWindow", "Save Settings", 0, QApplication::UnicodeUTF8));
        actionSave_Settings->setShortcut(QApplication::translate("MainWindow", "Alt+S", 0, QApplication::UnicodeUTF8));
        actionAppend_Sketchpad->setText(QApplication::translate("MainWindow", "Append Sketchpad", 0, QApplication::UnicodeUTF8));
        actionAppend_Sketchpad->setShortcut(QApplication::translate("MainWindow", "+", 0, QApplication::UnicodeUTF8));
        actionInsert_Sketchpad->setText(QApplication::translate("MainWindow", "Insert Sketchpad", 0, QApplication::UnicodeUTF8));
        actionInsert_Sketchpad->setShortcut(QApplication::translate("MainWindow", "Ins", 0, QApplication::UnicodeUTF8));
        action_Open_Storyboard->setText(QApplication::translate("MainWindow", "&Open Storyboard", 0, QApplication::UnicodeUTF8));
        action_Open_Storyboard->setShortcut(QApplication::translate("MainWindow", "Ctrl+O", 0, QApplication::UnicodeUTF8));
        action_About->setText(QApplication::translate("MainWindow", "&About", 0, QApplication::UnicodeUTF8));
        actionErase_All->setText(QApplication::translate("MainWindow", "Erase drawing", 0, QApplication::UnicodeUTF8));
        actionErase_All->setShortcut(QApplication::translate("MainWindow", "F9", 0, QApplication::UnicodeUTF8));
        actionErase_Sketch_Pen->setText(QApplication::translate("MainWindow", "Erase Sketch Pen", 0, QApplication::UnicodeUTF8));
        actionErase_Sketch_Pen->setShortcut(QApplication::translate("MainWindow", "Shift+F5", 0, QApplication::UnicodeUTF8));
        actionPreferences->setText(QApplication::translate("MainWindow", "Preferences", 0, QApplication::UnicodeUTF8));
        actionPreferences->setShortcut(QApplication::translate("MainWindow", "F12", 0, QApplication::UnicodeUTF8));
        actionCenter_Storyboard->setText(QApplication::translate("MainWindow", "Center Storyboard", 0, QApplication::UnicodeUTF8));
        actionCenter_Storyboard->setShortcut(QApplication::translate("MainWindow", "Alt+C", 0, QApplication::UnicodeUTF8));
        action_New_Scene->setText(QApplication::translate("MainWindow", "&New Scene", 0, QApplication::UnicodeUTF8));
        action_New_Scene->setShortcut(QApplication::translate("MainWindow", "Alt+N", 0, QApplication::UnicodeUTF8));
        action_Open_Scene->setText(QApplication::translate("MainWindow", "&Open Scene", 0, QApplication::UnicodeUTF8));
        action_Open_Scene->setShortcut(QApplication::translate("MainWindow", "Alt+O", 0, QApplication::UnicodeUTF8));
        actionDelete_drawing->setText(QApplication::translate("MainWindow", "Delete drawing", 0, QApplication::UnicodeUTF8));
        actionDelete_drawing->setShortcut(QApplication::translate("MainWindow", "Del", 0, QApplication::UnicodeUTF8));
        actionMovePadLeft->setText(QApplication::translate("MainWindow", "Move pad to the left", 0, QApplication::UnicodeUTF8));
        actionMovePadLeft->setShortcut(QApplication::translate("MainWindow", "Shift+Left", 0, QApplication::UnicodeUTF8));
        actionMovePadRight->setText(QApplication::translate("MainWindow", "Move pad to the right", 0, QApplication::UnicodeUTF8));
        actionMovePadRight->setShortcut(QApplication::translate("MainWindow", "Shift+Right", 0, QApplication::UnicodeUTF8));
        actionRun_Scene->setText(QApplication::translate("MainWindow", "Run Scene", 0, QApplication::UnicodeUTF8));
        actionRun_Scene->setShortcut(QApplication::translate("MainWindow", "F2", 0, QApplication::UnicodeUTF8));
        labComments->setText(QApplication::translate("MainWindow", "Comments:  (max 100 chars.)", 0, QApplication::UnicodeUTF8));
        labScene->setText(QApplication::translate("MainWindow", "Scene", 0, QApplication::UnicodeUTF8));
        labSceneInfo->setText(QString());
        labShot->setText(QApplication::translate("MainWindow", "Shot", 0, QApplication::UnicodeUTF8));
        labFrames->setText(QApplication::translate("MainWindow", "Frames:", 0, QApplication::UnicodeUTF8));
        labScenes->setText(QApplication::translate("MainWindow", "Scenes:", 0, QApplication::UnicodeUTF8));
        labPens->setText(QApplication::translate("MainWindow", "Pens:", 0, QApplication::UnicodeUTF8));
        btnStandardPen->setText(QApplication::translate("MainWindow", "Pen", 0, QApplication::UnicodeUTF8));
        btnF5->setText(QApplication::translate("MainWindow", "F5 @", 0, QApplication::UnicodeUTF8));
        btnF6->setText(QApplication::translate("MainWindow", "F6", 0, QApplication::UnicodeUTF8));
        btnF7->setText(QApplication::translate("MainWindow", "F7", 0, QApplication::UnicodeUTF8));
        btnF8->setText(QApplication::translate("MainWindow", "F8", 0, QApplication::UnicodeUTF8));
        labFrameCount->setText(QApplication::translate("MainWindow", "Frames total:", 0, QApplication::UnicodeUTF8));
        labActivePadInfo->setText(QString());
        labTimeValue->setText(QString());
        labTime->setText(QApplication::translate("MainWindow", "Time:", 0, QApplication::UnicodeUTF8));
        labActivePad->setText(QApplication::translate("MainWindow", "Active pad:", 0, QApplication::UnicodeUTF8));
        labFramesCountValue->setText(QString());
        menu_File->setTitle(QApplication::translate("MainWindow", "&File/Storyboard", 0, QApplication::UnicodeUTF8));
        menuSettings->setTitle(QApplication::translate("MainWindow", "Pen", 0, QApplication::UnicodeUTF8));
        menuLoad_Pen->setTitle(QApplication::translate("MainWindow", "Load Pen", 0, QApplication::UnicodeUTF8));
        menuSketchpad->setTitle(QApplication::translate("MainWindow", "Sketchpad", 0, QApplication::UnicodeUTF8));
        menu_Help->setTitle(QApplication::translate("MainWindow", "&Help", 0, QApplication::UnicodeUTF8));
        menuScene->setTitle(QApplication::translate("MainWindow", "Scene", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H

/********************************************************************************
** Form generated from reading UI file 'VIE_MainWin.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_VIE_MAINWIN_H
#define UI_VIE_MAINWIN_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QGraphicsView>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QMainWindow>
#include <QtGui/QMenu>
#include <QtGui/QMenuBar>
#include <QtGui/QProgressBar>
#include <QtGui/QStatusBar>
#include <QtGui/QToolBar>
#include <QtGui/QVBoxLayout>
#include <QtGui/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QAction *action_Add;
    QAction *actionSettings;
    QAction *actionStop;
    QAction *actionStart;
    QAction *actionOpen;
    QAction *actionSave;
    QAction *actionSJT_6;
    QAction *actionSJT_3;
    QAction *actionStrategy;
    QAction *actionBarrett;
    QAction *actionHumanHand;
    QAction *actionSample1;
    QAction *actionSample2;
    QAction *actionAddObjects;
    QAction *actionReset;
    QAction *actionAddCustomHand;
    QAction *actionTraining;
    QAction *actionTesting;
    QWidget *centralwidget;
    QVBoxLayout *verticalLayout;
    QGraphicsView *graphicsView;
    QHBoxLayout *horizontalLayout;
    QLineEdit *LECountdown;
    QProgressBar *progressBar;
    QMenuBar *menubar;
    QMenu *menu_F;
    QMenu *menu_S;
    QMenu *menu;
    QMenu *menu_2;
    QStatusBar *statusbar;
    QToolBar *viewToolBar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName(QString::fromUtf8("MainWindow"));
        MainWindow->resize(765, 527);
        QSizePolicy sizePolicy(QSizePolicy::Preferred, QSizePolicy::Preferred);
        sizePolicy.setHorizontalStretch(0);
        sizePolicy.setVerticalStretch(0);
        sizePolicy.setHeightForWidth(MainWindow->sizePolicy().hasHeightForWidth());
        MainWindow->setSizePolicy(sizePolicy);
        action_Add = new QAction(MainWindow);
        action_Add->setObjectName(QString::fromUtf8("action_Add"));
        actionSettings = new QAction(MainWindow);
        actionSettings->setObjectName(QString::fromUtf8("actionSettings"));
        actionStop = new QAction(MainWindow);
        actionStop->setObjectName(QString::fromUtf8("actionStop"));
        actionStart = new QAction(MainWindow);
        actionStart->setObjectName(QString::fromUtf8("actionStart"));
        actionOpen = new QAction(MainWindow);
        actionOpen->setObjectName(QString::fromUtf8("actionOpen"));
        actionSave = new QAction(MainWindow);
        actionSave->setObjectName(QString::fromUtf8("actionSave"));
        actionSJT_6 = new QAction(MainWindow);
        actionSJT_6->setObjectName(QString::fromUtf8("actionSJT_6"));
        actionSJT_3 = new QAction(MainWindow);
        actionSJT_3->setObjectName(QString::fromUtf8("actionSJT_3"));
        actionStrategy = new QAction(MainWindow);
        actionStrategy->setObjectName(QString::fromUtf8("actionStrategy"));
        actionBarrett = new QAction(MainWindow);
        actionBarrett->setObjectName(QString::fromUtf8("actionBarrett"));
        actionHumanHand = new QAction(MainWindow);
        actionHumanHand->setObjectName(QString::fromUtf8("actionHumanHand"));
        actionSample1 = new QAction(MainWindow);
        actionSample1->setObjectName(QString::fromUtf8("actionSample1"));
        actionSample2 = new QAction(MainWindow);
        actionSample2->setObjectName(QString::fromUtf8("actionSample2"));
        actionAddObjects = new QAction(MainWindow);
        actionAddObjects->setObjectName(QString::fromUtf8("actionAddObjects"));
        actionReset = new QAction(MainWindow);
        actionReset->setObjectName(QString::fromUtf8("actionReset"));
        actionAddCustomHand = new QAction(MainWindow);
        actionAddCustomHand->setObjectName(QString::fromUtf8("actionAddCustomHand"));
        actionTraining = new QAction(MainWindow);
        actionTraining->setObjectName(QString::fromUtf8("actionTraining"));
        actionTesting = new QAction(MainWindow);
        actionTesting->setObjectName(QString::fromUtf8("actionTesting"));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName(QString::fromUtf8("centralwidget"));
        verticalLayout = new QVBoxLayout(centralwidget);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        graphicsView = new QGraphicsView(centralwidget);
        graphicsView->setObjectName(QString::fromUtf8("graphicsView"));
        graphicsView->setLineWidth(1);

        verticalLayout->addWidget(graphicsView);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        LECountdown = new QLineEdit(centralwidget);
        LECountdown->setObjectName(QString::fromUtf8("LECountdown"));
        LECountdown->setReadOnly(true);

        horizontalLayout->addWidget(LECountdown);

        progressBar = new QProgressBar(centralwidget);
        progressBar->setObjectName(QString::fromUtf8("progressBar"));
        progressBar->setValue(0);
        progressBar->setTextVisible(false);

        horizontalLayout->addWidget(progressBar);

        horizontalLayout->setStretch(0, 1);
        horizontalLayout->setStretch(1, 8);

        verticalLayout->addLayout(horizontalLayout);

        MainWindow->setCentralWidget(centralwidget);
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName(QString::fromUtf8("menubar"));
        menubar->setGeometry(QRect(0, 0, 765, 23));
        menu_F = new QMenu(menubar);
        menu_F->setObjectName(QString::fromUtf8("menu_F"));
        menu_S = new QMenu(menubar);
        menu_S->setObjectName(QString::fromUtf8("menu_S"));
        menu = new QMenu(menubar);
        menu->setObjectName(QString::fromUtf8("menu"));
        menu_2 = new QMenu(menubar);
        menu_2->setObjectName(QString::fromUtf8("menu_2"));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName(QString::fromUtf8("statusbar"));
        MainWindow->setStatusBar(statusbar);
        viewToolBar = new QToolBar(MainWindow);
        viewToolBar->setObjectName(QString::fromUtf8("viewToolBar"));
        MainWindow->addToolBar(Qt::TopToolBarArea, viewToolBar);

        menubar->addAction(menu_F->menuAction());
        menubar->addAction(menu_S->menuAction());
        menubar->addAction(menu->menuAction());
        menubar->addAction(menu_2->menuAction());
        menu_F->addAction(action_Add);
        menu_F->addSeparator();
        menu_F->addAction(actionOpen);
        menu_F->addAction(actionSave);
        menu_F->addSeparator();
        menu_F->addAction(actionReset);
        menu_S->addAction(actionStart);
        menu_S->addAction(actionStop);
        menu_S->addSeparator();
        menu_S->addAction(actionSettings);
        menu->addAction(actionSJT_3);
        menu->addAction(actionSJT_6);
        menu->addAction(actionBarrett);
        menu->addAction(actionHumanHand);
        menu->addAction(actionAddCustomHand);
        menu->addSeparator();
        menu->addAction(actionAddObjects);
        menu_2->addAction(actionTraining);
        menu_2->addAction(actionTesting);

        retranslateUi(MainWindow);

        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QApplication::translate("MainWindow", "\347\224\237\346\234\272\347\224\265\350\231\232\346\213\237\347\216\257\345\242\203\346\265\213\350\257\225\345\271\263\345\217\260", 0, QApplication::UnicodeUTF8));
        action_Add->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240...(&A)", 0, QApplication::UnicodeUTF8));
        actionSettings->setText(QApplication::translate("MainWindow", "\350\256\276\347\275\256...", 0, QApplication::UnicodeUTF8));
        actionStop->setText(QApplication::translate("MainWindow", "\345\201\234\346\255\242", 0, QApplication::UnicodeUTF8));
        actionStart->setText(QApplication::translate("MainWindow", "\345\220\257\345\212\250", 0, QApplication::UnicodeUTF8));
        actionOpen->setText(QApplication::translate("MainWindow", "\346\211\223\345\274\200\346\226\207\344\273\266...(&O)", 0, QApplication::UnicodeUTF8));
        actionSave->setText(QApplication::translate("MainWindow", "\344\277\235\345\255\230\345\234\272\346\231\257...(&S)", 0, QApplication::UnicodeUTF8));
        actionSJT_6->setText(QApplication::translate("MainWindow", "SJT_6", 0, QApplication::UnicodeUTF8));
        actionSJT_3->setText(QApplication::translate("MainWindow", "SJT_3", 0, QApplication::UnicodeUTF8));
        actionStrategy->setText(QApplication::translate("MainWindow", "\347\255\226\347\225\245\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        actionBarrett->setText(QApplication::translate("MainWindow", "Barrett", 0, QApplication::UnicodeUTF8));
        actionHumanHand->setText(QApplication::translate("MainWindow", "HumanHand", 0, QApplication::UnicodeUTF8));
        actionSample1->setText(QApplication::translate("MainWindow", "Sample1", 0, QApplication::UnicodeUTF8));
        actionSample2->setText(QApplication::translate("MainWindow", "Sample2", 0, QApplication::UnicodeUTF8));
        actionAddObjects->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\346\212\223\345\217\226\347\211\251\344\275\223...", 0, QApplication::UnicodeUTF8));
        actionReset->setText(QApplication::translate("MainWindow", "\351\207\215\347\275\256\347\216\257\345\242\203", 0, QApplication::UnicodeUTF8));
        actionAddCustomHand->setText(QApplication::translate("MainWindow", "\346\267\273\345\212\240\350\207\252\345\256\232\344\271\211\346\211\213...", 0, QApplication::UnicodeUTF8));
        actionTraining->setText(QApplication::translate("MainWindow", "Training", 0, QApplication::UnicodeUTF8));
        actionTesting->setText(QApplication::translate("MainWindow", "Testing", 0, QApplication::UnicodeUTF8));
        menu_F->setTitle(QApplication::translate("MainWindow", "\346\226\207\344\273\266(&F)", 0, QApplication::UnicodeUTF8));
        menu_S->setTitle(QApplication::translate("MainWindow", "\344\273\277\347\234\237(&S)", 0, QApplication::UnicodeUTF8));
        menu->setTitle(QApplication::translate("MainWindow", "\347\233\264\346\216\245\345\212\240\350\275\275", 0, QApplication::UnicodeUTF8));
        menu_2->setTitle(QApplication::translate("MainWindow", "\346\250\241\345\274\217\350\257\206\345\210\253", 0, QApplication::UnicodeUTF8));
        viewToolBar->setWindowTitle(QApplication::translate("MainWindow", "toolBar", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_VIE_MAINWIN_H

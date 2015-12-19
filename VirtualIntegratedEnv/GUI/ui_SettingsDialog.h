/********************************************************************************
** Form generated from reading UI file 'SettingsDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_SETTINGSDIALOG_H
#define UI_SETTINGSDIALOG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QComboBox>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QTextBrowser>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_SettingsDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *groupBox_1;
    QVBoxLayout *verticalLayout;
    QTextBrowser *textBrowser;
    QHBoxLayout *horizontalLayout_5;
    QLabel *label;
    QComboBox *StrategyBox;
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_2;
    QTextBrowser *textBrowser_2;
    QHBoxLayout *horizontalLayout_2;
    QLabel *label1;
    QComboBox *InputBox;
    QHBoxLayout *horizontalLayout_3;
    QLabel *label2;
    QComboBox *OutputBox;
    QHBoxLayout *horizontalLayout;
    QSpacerItem *horizontalSpacer;
    QPushButton *pushButtonDone;
    QPushButton *pushButtonCancel;

    void setupUi(QDialog *SettingsDialog)
    {
        if (SettingsDialog->objectName().isEmpty())
            SettingsDialog->setObjectName(QString::fromUtf8("SettingsDialog"));
        SettingsDialog->resize(360, 450);
        SettingsDialog->setMinimumSize(QSize(360, 450));
        SettingsDialog->setMaximumSize(QSize(360, 450));
        verticalLayout_3 = new QVBoxLayout(SettingsDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        groupBox_1 = new QGroupBox(SettingsDialog);
        groupBox_1->setObjectName(QString::fromUtf8("groupBox_1"));
        verticalLayout = new QVBoxLayout(groupBox_1);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        textBrowser = new QTextBrowser(groupBox_1);
        textBrowser->setObjectName(QString::fromUtf8("textBrowser"));

        verticalLayout->addWidget(textBrowser);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        label = new QLabel(groupBox_1);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout_5->addWidget(label);

        StrategyBox = new QComboBox(groupBox_1);
        StrategyBox->setObjectName(QString::fromUtf8("StrategyBox"));

        horizontalLayout_5->addWidget(StrategyBox);


        verticalLayout->addLayout(horizontalLayout_5);


        verticalLayout_3->addWidget(groupBox_1);

        groupBox = new QGroupBox(SettingsDialog);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_2 = new QVBoxLayout(groupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        textBrowser_2 = new QTextBrowser(groupBox);
        textBrowser_2->setObjectName(QString::fromUtf8("textBrowser_2"));

        verticalLayout_2->addWidget(textBrowser_2);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        label1 = new QLabel(groupBox);
        label1->setObjectName(QString::fromUtf8("label1"));

        horizontalLayout_2->addWidget(label1);

        InputBox = new QComboBox(groupBox);
        InputBox->setObjectName(QString::fromUtf8("InputBox"));

        horizontalLayout_2->addWidget(InputBox);


        verticalLayout_2->addLayout(horizontalLayout_2);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        label2 = new QLabel(groupBox);
        label2->setObjectName(QString::fromUtf8("label2"));

        horizontalLayout_3->addWidget(label2);

        OutputBox = new QComboBox(groupBox);
        OutputBox->setObjectName(QString::fromUtf8("OutputBox"));

        horizontalLayout_3->addWidget(OutputBox);


        verticalLayout_2->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(groupBox);

        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout->addItem(horizontalSpacer);

        pushButtonDone = new QPushButton(SettingsDialog);
        pushButtonDone->setObjectName(QString::fromUtf8("pushButtonDone"));

        horizontalLayout->addWidget(pushButtonDone);

        pushButtonCancel = new QPushButton(SettingsDialog);
        pushButtonCancel->setObjectName(QString::fromUtf8("pushButtonCancel"));

        horizontalLayout->addWidget(pushButtonCancel);


        verticalLayout_3->addLayout(horizontalLayout);


        retranslateUi(SettingsDialog);

        QMetaObject::connectSlotsByName(SettingsDialog);
    } // setupUi

    void retranslateUi(QDialog *SettingsDialog)
    {
        SettingsDialog->setWindowTitle(QApplication::translate("SettingsDialog", "\350\256\276\347\275\256", 0, QApplication::UnicodeUTF8));
        groupBox_1->setTitle(QApplication::translate("SettingsDialog", "\346\216\247\345\210\266\347\255\226\347\225\245\351\200\211\346\213\251", 0, QApplication::UnicodeUTF8));
        textBrowser->setHtml(QApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\264\346\230\216\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\246\202\346\236\234\350\231\232\346\213\237\347\216\257\345\242\203\344\270\255\346\234\252\345\212\240\350\275\275\350\231\232\346\213\237\346\211\213\357\274\214\345\210\231\344\270\215\344\274\232\347\224\237\346\210\220\344\273\273\344\275\225\346\216\247\345\210\266\347\255\226\347\225\245\343\200\202\350\257\267\347\241\256\344\277\235\345\234\250\347\224\237\346\210\220\346\216\247\345\210\266"
                        "\347\255\226\347\225\245\344\271\213\345\211\215\357\274\214\345\267\262\347\273\217\345\212\240\350\275\275\344\272\206\344\273\273\344\275\225\344\270\200\347\247\215\350\231\232\346\213\237\346\211\213\343\200\202</p></body></html>", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("SettingsDialog", "\347\224\237\346\210\220\346\216\247\345\210\266\347\255\226\347\225\245\357\274\232 ", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("SettingsDialog", "\350\256\276\347\275\256\344\270\262\345\217\243\345\217\267", 0, QApplication::UnicodeUTF8));
        textBrowser_2->setHtml(QApplication::translate("SettingsDialog", "<!DOCTYPE HTML PUBLIC \"-//W3C//DTD HTML 4.0//EN\" \"http://www.w3.org/TR/REC-html40/strict.dtd\">\n"
"<html><head><meta name=\"qrichtext\" content=\"1\" /><style type=\"text/css\">\n"
"p, li { white-space: pre-wrap; }\n"
"</style></head><body style=\" font-family:'SimSun'; font-size:9pt; font-weight:400; font-style:normal;\">\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\257\264\346\230\216\357\274\232</p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\345\271\266\344\270\215\346\230\257\346\257\217\344\270\200\347\247\215\346\216\247\345\210\266\347\255\226\347\225\245\351\203\275\351\234\200\350\246\201\347\224\250\345\210\260\344\270\262\345\217\243\343\200\202\345\275\223\344\270\215\351\234\200\350\246\201\344\275\277\347\224\250\344\270\262\345\217\243\346\227\266\357\274\214\345\215\263\344\276\277\344\277\256\346\224\271\344\272\206\344\270\262"
                        "\345\217\243\345\217\267\357\274\214\347\250\213\345\272\217\344\271\237\344\270\215\344\274\232\345\257\271\350\277\231\346\240\267\347\232\204\344\277\256\346\224\271\344\275\234\345\207\272\345\223\215\345\272\224\357\274\233\345\275\223\351\234\200\350\246\201\344\275\277\347\224\250\344\270\262\345\217\243\346\227\266\357\274\214\350\257\267\347\241\256\344\277\235\351\200\211\346\213\251\344\272\206\346\255\243\347\241\256\347\232\204\344\270\262\345\217\243\343\200\202</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\346\216\245\346\224\266\345\221\275\344\273\244\344\270\262\345\217\243\357\274\232\345\244\226\351\203\250\346\216\247\345\210\266\346\272\220\345\220\221\347\250\213\345\272\217\345\217\221\351\200\201\346\216\247\345\210\266\345\255\227\347\254\246\357"
                        "\274\214\344\273\245\346\216\247\345\210\266\350\231\232\346\213\237\346\211\213\345\212\250\344\275\234\357\274\233</p>\n"
"<p style=\"-qt-paragraph-type:empty; margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\"><br /></p>\n"
"<p style=\" margin-top:0px; margin-bottom:0px; margin-left:0px; margin-right:0px; -qt-block-indent:0; text-indent:0px;\">\350\276\223\345\207\272\345\221\275\344\273\244\344\270\262\345\217\243\357\274\232\347\250\213\345\272\217\345\220\221\345\244\226\351\203\250\350\242\253\346\216\247\345\257\271\350\261\241\345\217\221\351\200\201\346\216\247\345\210\266\345\255\227\347\254\246\343\200\202</p></body></html>", 0, QApplication::UnicodeUTF8));
        label1->setText(QApplication::translate("SettingsDialog", "\346\216\245\346\224\266\345\221\275\344\273\244\344\270\262\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
        InputBox->clear();
        InputBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "COM0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM15", 0, QApplication::UnicodeUTF8)
        );
        label2->setText(QApplication::translate("SettingsDialog", "\350\276\223\345\207\272\345\221\275\344\273\244\344\270\262\345\217\243\357\274\232", 0, QApplication::UnicodeUTF8));
        OutputBox->clear();
        OutputBox->insertItems(0, QStringList()
         << QApplication::translate("SettingsDialog", "COM0", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM1", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM2", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM3", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM4", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM5", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM6", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM7", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM8", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM9", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM10", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM11", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM12", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM13", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM14", 0, QApplication::UnicodeUTF8)
         << QApplication::translate("SettingsDialog", "COM15", 0, QApplication::UnicodeUTF8)
        );
        pushButtonDone->setText(QApplication::translate("SettingsDialog", "\347\241\256\345\256\232", 0, QApplication::UnicodeUTF8));
        pushButtonCancel->setText(QApplication::translate("SettingsDialog", "\345\217\226\346\266\210", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class SettingsDialog: public Ui_SettingsDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_SETTINGSDIALOG_H

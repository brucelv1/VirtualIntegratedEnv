/********************************************************************************
** Form generated from reading UI file 'addingDialog.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDINGDIALOG_H
#define UI_ADDINGDIALOG_H

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
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddDialog
{
public:
    QVBoxLayout *verticalLayout_3;
    QGroupBox *partInfoGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *partList;
    QComboBox *partListCombo;
    QLabel *partName;
    QLineEdit *partNameLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fileName;
    QLineEdit *fileNameLineEdit;
    QPushButton *browseBtn;
    QGroupBox *PAgroupBox;
    QVBoxLayout *verticalLayout_2;
    QHBoxLayout *horizontalLayout_4;
    QLabel *XLabel;
    QLineEdit *XLineEdit;
    QLabel *YLabel;
    QLineEdit *YLineEdit;
    QLabel *ZLabel;
    QLineEdit *ZLineEdit;
    QHBoxLayout *horizontalLayout_6;
    QLabel *Heading;
    QLineEdit *HLineEdit;
    QLabel *Pitch;
    QLineEdit *PLineEdit;
    QLabel *Roll;
    QLineEdit *RLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *ApplyBtn;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;

    void setupUi(QDialog *AddDialog)
    {
        if (AddDialog->objectName().isEmpty())
            AddDialog->setObjectName(QString::fromUtf8("AddDialog"));
        AddDialog->resize(352, 473);
        verticalLayout_3 = new QVBoxLayout(AddDialog);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        partInfoGroupBox = new QGroupBox(AddDialog);
        partInfoGroupBox->setObjectName(QString::fromUtf8("partInfoGroupBox"));
        verticalLayout = new QVBoxLayout(partInfoGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        partList = new QLabel(partInfoGroupBox);
        partList->setObjectName(QString::fromUtf8("partList"));

        horizontalLayout->addWidget(partList);

        partListCombo = new QComboBox(partInfoGroupBox);
        partListCombo->setObjectName(QString::fromUtf8("partListCombo"));

        horizontalLayout->addWidget(partListCombo);

        partName = new QLabel(partInfoGroupBox);
        partName->setObjectName(QString::fromUtf8("partName"));

        horizontalLayout->addWidget(partName);

        partNameLineEdit = new QLineEdit(partInfoGroupBox);
        partNameLineEdit->setObjectName(QString::fromUtf8("partNameLineEdit"));

        horizontalLayout->addWidget(partNameLineEdit);


        verticalLayout->addLayout(horizontalLayout);

        horizontalLayout_3 = new QHBoxLayout();
        horizontalLayout_3->setObjectName(QString::fromUtf8("horizontalLayout_3"));
        fileName = new QLabel(partInfoGroupBox);
        fileName->setObjectName(QString::fromUtf8("fileName"));

        horizontalLayout_3->addWidget(fileName);

        fileNameLineEdit = new QLineEdit(partInfoGroupBox);
        fileNameLineEdit->setObjectName(QString::fromUtf8("fileNameLineEdit"));

        horizontalLayout_3->addWidget(fileNameLineEdit);

        browseBtn = new QPushButton(partInfoGroupBox);
        browseBtn->setObjectName(QString::fromUtf8("browseBtn"));

        horizontalLayout_3->addWidget(browseBtn);


        verticalLayout->addLayout(horizontalLayout_3);


        verticalLayout_3->addWidget(partInfoGroupBox);

        PAgroupBox = new QGroupBox(AddDialog);
        PAgroupBox->setObjectName(QString::fromUtf8("PAgroupBox"));
        verticalLayout_2 = new QVBoxLayout(PAgroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        horizontalLayout_4 = new QHBoxLayout();
        horizontalLayout_4->setObjectName(QString::fromUtf8("horizontalLayout_4"));
        XLabel = new QLabel(PAgroupBox);
        XLabel->setObjectName(QString::fromUtf8("XLabel"));

        horizontalLayout_4->addWidget(XLabel);

        XLineEdit = new QLineEdit(PAgroupBox);
        XLineEdit->setObjectName(QString::fromUtf8("XLineEdit"));

        horizontalLayout_4->addWidget(XLineEdit);

        YLabel = new QLabel(PAgroupBox);
        YLabel->setObjectName(QString::fromUtf8("YLabel"));

        horizontalLayout_4->addWidget(YLabel);

        YLineEdit = new QLineEdit(PAgroupBox);
        YLineEdit->setObjectName(QString::fromUtf8("YLineEdit"));

        horizontalLayout_4->addWidget(YLineEdit);

        ZLabel = new QLabel(PAgroupBox);
        ZLabel->setObjectName(QString::fromUtf8("ZLabel"));

        horizontalLayout_4->addWidget(ZLabel);

        ZLineEdit = new QLineEdit(PAgroupBox);
        ZLineEdit->setObjectName(QString::fromUtf8("ZLineEdit"));

        horizontalLayout_4->addWidget(ZLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_4);

        horizontalLayout_6 = new QHBoxLayout();
        horizontalLayout_6->setObjectName(QString::fromUtf8("horizontalLayout_6"));
        Heading = new QLabel(PAgroupBox);
        Heading->setObjectName(QString::fromUtf8("Heading"));

        horizontalLayout_6->addWidget(Heading);

        HLineEdit = new QLineEdit(PAgroupBox);
        HLineEdit->setObjectName(QString::fromUtf8("HLineEdit"));

        horizontalLayout_6->addWidget(HLineEdit);

        Pitch = new QLabel(PAgroupBox);
        Pitch->setObjectName(QString::fromUtf8("Pitch"));

        horizontalLayout_6->addWidget(Pitch);

        PLineEdit = new QLineEdit(PAgroupBox);
        PLineEdit->setObjectName(QString::fromUtf8("PLineEdit"));

        horizontalLayout_6->addWidget(PLineEdit);

        Roll = new QLabel(PAgroupBox);
        Roll->setObjectName(QString::fromUtf8("Roll"));

        horizontalLayout_6->addWidget(Roll);

        RLineEdit = new QLineEdit(PAgroupBox);
        RLineEdit->setObjectName(QString::fromUtf8("RLineEdit"));

        horizontalLayout_6->addWidget(RLineEdit);


        verticalLayout_2->addLayout(horizontalLayout_6);


        verticalLayout_3->addWidget(PAgroupBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        ApplyBtn = new QPushButton(AddDialog);
        ApplyBtn->setObjectName(QString::fromUtf8("ApplyBtn"));

        horizontalLayout_5->addWidget(ApplyBtn);

        OkBtn = new QPushButton(AddDialog);
        OkBtn->setObjectName(QString::fromUtf8("OkBtn"));

        horizontalLayout_5->addWidget(OkBtn);

        CancelBtn = new QPushButton(AddDialog);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

        horizontalLayout_5->addWidget(CancelBtn);


        verticalLayout_3->addLayout(horizontalLayout_5);


        retranslateUi(AddDialog);

        QMetaObject::connectSlotsByName(AddDialog);
    } // setupUi

    void retranslateUi(QDialog *AddDialog)
    {
        AddDialog->setWindowTitle(QApplication::translate("AddDialog", "Add", 0, QApplication::UnicodeUTF8));
        partInfoGroupBox->setTitle(QApplication::translate("AddDialog", "Part Information", 0, QApplication::UnicodeUTF8));
        partList->setText(QApplication::translate("AddDialog", "Part List ", 0, QApplication::UnicodeUTF8));
        partName->setText(QApplication::translate("AddDialog", "Part Name", 0, QApplication::UnicodeUTF8));
        fileName->setText(QApplication::translate("AddDialog", "File Name", 0, QApplication::UnicodeUTF8));
        browseBtn->setText(QApplication::translate("AddDialog", "Browse...", 0, QApplication::UnicodeUTF8));
        PAgroupBox->setTitle(QApplication::translate("AddDialog", "Position and Attitude", 0, QApplication::UnicodeUTF8));
        XLabel->setText(QApplication::translate("AddDialog", "X", 0, QApplication::UnicodeUTF8));
        YLabel->setText(QApplication::translate("AddDialog", "Y", 0, QApplication::UnicodeUTF8));
        ZLabel->setText(QApplication::translate("AddDialog", "Z", 0, QApplication::UnicodeUTF8));
        Heading->setText(QApplication::translate("AddDialog", "Heading", 0, QApplication::UnicodeUTF8));
        Pitch->setText(QApplication::translate("AddDialog", "Pitch", 0, QApplication::UnicodeUTF8));
        Roll->setText(QApplication::translate("AddDialog", "Roll", 0, QApplication::UnicodeUTF8));
        ApplyBtn->setText(QApplication::translate("AddDialog", "Apply", 0, QApplication::UnicodeUTF8));
        OkBtn->setText(QApplication::translate("AddDialog", "Ok", 0, QApplication::UnicodeUTF8));
        CancelBtn->setText(QApplication::translate("AddDialog", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddDialog: public Ui_AddDialog {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDINGDIALOG_H

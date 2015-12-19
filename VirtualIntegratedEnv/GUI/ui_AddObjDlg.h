/********************************************************************************
** Form generated from reading UI file 'AddObjDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_ADDOBJDLG_H
#define UI_ADDOBJDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QRadioButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_AddObjDlg
{
public:
    QVBoxLayout *verticalLayout_4;
    QGroupBox *partInfoGroupBox;
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *partName;
    QLineEdit *partNameLineEdit;
    QHBoxLayout *horizontalLayout_3;
    QLabel *fileName;
    QLineEdit *fileNameLineEdit;
    QPushButton *browseBtn;
    QGroupBox *PAgroupBox;
    QVBoxLayout *verticalLayout_2;
    QRadioButton *PosAttRBtn;
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
    QGroupBox *groupBox;
    QVBoxLayout *verticalLayout_3;
    QRadioButton *MatRBtn;
    QLabel *label;
    QLabel *label_2;
    QLineEdit *MatrixLineEdit;
    QHBoxLayout *horizontalLayout_5;
    QSpacerItem *horizontalSpacer;
    QPushButton *ApplyBtn;
    QPushButton *OkBtn;
    QPushButton *CancelBtn;

    void setupUi(QDialog *AddObjDlg)
    {
        if (AddObjDlg->objectName().isEmpty())
            AddObjDlg->setObjectName(QString::fromUtf8("AddObjDlg"));
        AddObjDlg->resize(352, 473);
        verticalLayout_4 = new QVBoxLayout(AddObjDlg);
        verticalLayout_4->setObjectName(QString::fromUtf8("verticalLayout_4"));
        partInfoGroupBox = new QGroupBox(AddObjDlg);
        partInfoGroupBox->setObjectName(QString::fromUtf8("partInfoGroupBox"));
        verticalLayout = new QVBoxLayout(partInfoGroupBox);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
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


        verticalLayout_4->addWidget(partInfoGroupBox);

        PAgroupBox = new QGroupBox(AddObjDlg);
        PAgroupBox->setObjectName(QString::fromUtf8("PAgroupBox"));
        verticalLayout_2 = new QVBoxLayout(PAgroupBox);
        verticalLayout_2->setObjectName(QString::fromUtf8("verticalLayout_2"));
        PosAttRBtn = new QRadioButton(PAgroupBox);
        PosAttRBtn->setObjectName(QString::fromUtf8("PosAttRBtn"));
        PosAttRBtn->setChecked(true);

        verticalLayout_2->addWidget(PosAttRBtn);

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


        verticalLayout_4->addWidget(PAgroupBox);

        groupBox = new QGroupBox(AddObjDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        verticalLayout_3 = new QVBoxLayout(groupBox);
        verticalLayout_3->setObjectName(QString::fromUtf8("verticalLayout_3"));
        MatRBtn = new QRadioButton(groupBox);
        MatRBtn->setObjectName(QString::fromUtf8("MatRBtn"));

        verticalLayout_3->addWidget(MatRBtn);

        label = new QLabel(groupBox);
        label->setObjectName(QString::fromUtf8("label"));

        verticalLayout_3->addWidget(label);

        label_2 = new QLabel(groupBox);
        label_2->setObjectName(QString::fromUtf8("label_2"));

        verticalLayout_3->addWidget(label_2);

        MatrixLineEdit = new QLineEdit(groupBox);
        MatrixLineEdit->setObjectName(QString::fromUtf8("MatrixLineEdit"));

        verticalLayout_3->addWidget(MatrixLineEdit);


        verticalLayout_4->addWidget(groupBox);

        horizontalLayout_5 = new QHBoxLayout();
        horizontalLayout_5->setObjectName(QString::fromUtf8("horizontalLayout_5"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_5->addItem(horizontalSpacer);

        ApplyBtn = new QPushButton(AddObjDlg);
        ApplyBtn->setObjectName(QString::fromUtf8("ApplyBtn"));

        horizontalLayout_5->addWidget(ApplyBtn);

        OkBtn = new QPushButton(AddObjDlg);
        OkBtn->setObjectName(QString::fromUtf8("OkBtn"));

        horizontalLayout_5->addWidget(OkBtn);

        CancelBtn = new QPushButton(AddObjDlg);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

        horizontalLayout_5->addWidget(CancelBtn);


        verticalLayout_4->addLayout(horizontalLayout_5);


        retranslateUi(AddObjDlg);

        QMetaObject::connectSlotsByName(AddObjDlg);
    } // setupUi

    void retranslateUi(QDialog *AddObjDlg)
    {
        AddObjDlg->setWindowTitle(QApplication::translate("AddObjDlg", "Add Grasping Object", 0, QApplication::UnicodeUTF8));
        partInfoGroupBox->setTitle(QApplication::translate("AddObjDlg", "Part Information", 0, QApplication::UnicodeUTF8));
        partName->setText(QApplication::translate("AddObjDlg", "Part Name", 0, QApplication::UnicodeUTF8));
        fileName->setText(QApplication::translate("AddObjDlg", "File Name", 0, QApplication::UnicodeUTF8));
        fileNameLineEdit->setText(QApplication::translate("AddObjDlg", "C:\\", 0, QApplication::UnicodeUTF8));
        browseBtn->setText(QApplication::translate("AddObjDlg", "Browse...", 0, QApplication::UnicodeUTF8));
        PAgroupBox->setTitle(QApplication::translate("AddObjDlg", "Position and Attitude", 0, QApplication::UnicodeUTF8));
        PosAttRBtn->setText(QApplication::translate("AddObjDlg", "Using Position and Attitude", 0, QApplication::UnicodeUTF8));
        XLabel->setText(QApplication::translate("AddObjDlg", "X", 0, QApplication::UnicodeUTF8));
        XLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        YLabel->setText(QApplication::translate("AddObjDlg", "Y", 0, QApplication::UnicodeUTF8));
        YLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        ZLabel->setText(QApplication::translate("AddObjDlg", "Z", 0, QApplication::UnicodeUTF8));
        ZLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        Heading->setText(QApplication::translate("AddObjDlg", "Heading", 0, QApplication::UnicodeUTF8));
        HLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        Pitch->setText(QApplication::translate("AddObjDlg", "Pitch", 0, QApplication::UnicodeUTF8));
        PLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        Roll->setText(QApplication::translate("AddObjDlg", "Roll", 0, QApplication::UnicodeUTF8));
        RLineEdit->setText(QApplication::translate("AddObjDlg", "0.0", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("AddObjDlg", "Matrix", 0, QApplication::UnicodeUTF8));
        MatRBtn->setText(QApplication::translate("AddObjDlg", "Using Matrix", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("AddObjDlg", "Input 4x4 elements divided by comma: ", 0, QApplication::UnicodeUTF8));
        label_2->setText(QApplication::translate("AddObjDlg", "a01,a02,a03,a04,a05,a06,a07,a08,a09,...,a16", 0, QApplication::UnicodeUTF8));
        MatrixLineEdit->setText(QApplication::translate("AddObjDlg", "0,0,0,0,0,0,0,0,0,0,0,0,0,0,0,0", 0, QApplication::UnicodeUTF8));
        ApplyBtn->setText(QApplication::translate("AddObjDlg", "Apply", 0, QApplication::UnicodeUTF8));
        OkBtn->setText(QApplication::translate("AddObjDlg", "Ok", 0, QApplication::UnicodeUTF8));
        CancelBtn->setText(QApplication::translate("AddObjDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class AddObjDlg: public Ui_AddObjDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_ADDOBJDLG_H

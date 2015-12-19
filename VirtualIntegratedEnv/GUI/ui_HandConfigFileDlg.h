/********************************************************************************
** Form generated from reading UI file 'HandConfigFileDlg.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_HANDCONFIGFILEDLG_H
#define UI_HANDCONFIGFILEDLG_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QGroupBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLineEdit>
#include <QtGui/QPushButton>
#include <QtGui/QSpacerItem>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_HandConfigFileDlg
{
public:
    QVBoxLayout *verticalLayout;
    QGroupBox *groupBox;
    QHBoxLayout *horizontalLayout;
    QLineEdit *PathLine;
    QPushButton *BrowseBtn;
    QHBoxLayout *horizontalLayout_2;
    QSpacerItem *horizontalSpacer;
    QPushButton *OKBtn;
    QPushButton *CancelBtn;

    void setupUi(QDialog *HandConfigFileDlg)
    {
        if (HandConfigFileDlg->objectName().isEmpty())
            HandConfigFileDlg->setObjectName(QString::fromUtf8("HandConfigFileDlg"));
        HandConfigFileDlg->resize(382, 102);
        verticalLayout = new QVBoxLayout(HandConfigFileDlg);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        groupBox = new QGroupBox(HandConfigFileDlg);
        groupBox->setObjectName(QString::fromUtf8("groupBox"));
        horizontalLayout = new QHBoxLayout(groupBox);
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        PathLine = new QLineEdit(groupBox);
        PathLine->setObjectName(QString::fromUtf8("PathLine"));

        horizontalLayout->addWidget(PathLine);

        BrowseBtn = new QPushButton(groupBox);
        BrowseBtn->setObjectName(QString::fromUtf8("BrowseBtn"));

        horizontalLayout->addWidget(BrowseBtn);


        verticalLayout->addWidget(groupBox);

        horizontalLayout_2 = new QHBoxLayout();
        horizontalLayout_2->setObjectName(QString::fromUtf8("horizontalLayout_2"));
        horizontalSpacer = new QSpacerItem(40, 20, QSizePolicy::Expanding, QSizePolicy::Minimum);

        horizontalLayout_2->addItem(horizontalSpacer);

        OKBtn = new QPushButton(HandConfigFileDlg);
        OKBtn->setObjectName(QString::fromUtf8("OKBtn"));

        horizontalLayout_2->addWidget(OKBtn);

        CancelBtn = new QPushButton(HandConfigFileDlg);
        CancelBtn->setObjectName(QString::fromUtf8("CancelBtn"));

        horizontalLayout_2->addWidget(CancelBtn);


        verticalLayout->addLayout(horizontalLayout_2);


        retranslateUi(HandConfigFileDlg);

        QMetaObject::connectSlotsByName(HandConfigFileDlg);
    } // setupUi

    void retranslateUi(QDialog *HandConfigFileDlg)
    {
        HandConfigFileDlg->setWindowTitle(QApplication::translate("HandConfigFileDlg", "HandConfigFile", 0, QApplication::UnicodeUTF8));
        groupBox->setTitle(QApplication::translate("HandConfigFileDlg", "\351\205\215\347\275\256\346\226\207\344\273\266\350\267\257\345\276\204", 0, QApplication::UnicodeUTF8));
        BrowseBtn->setText(QApplication::translate("HandConfigFileDlg", "Browse...", 0, QApplication::UnicodeUTF8));
        OKBtn->setText(QApplication::translate("HandConfigFileDlg", "OK", 0, QApplication::UnicodeUTF8));
        CancelBtn->setText(QApplication::translate("HandConfigFileDlg", "Cancel", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class HandConfigFileDlg: public Ui_HandConfigFileDlg {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_HANDCONFIGFILEDLG_H

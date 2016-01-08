/********************************************************************************
** Form generated from reading UI file 'Parameter.ui'
**
** Created by: Qt User Interface Compiler version 4.8.6
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PARAMETER_H
#define UI_PARAMETER_H

#include <QtCore/QVariant>
#include <QtGui/QAction>
#include <QtGui/QApplication>
#include <QtGui/QButtonGroup>
#include <QtGui/QDialog>
#include <QtGui/QDialogButtonBox>
#include <QtGui/QHBoxLayout>
#include <QtGui/QHeaderView>
#include <QtGui/QLabel>
#include <QtGui/QLineEdit>
#include <QtGui/QVBoxLayout>

QT_BEGIN_NAMESPACE

class Ui_Parameter
{
public:
    QVBoxLayout *verticalLayout;
    QHBoxLayout *horizontalLayout;
    QLabel *label;
    QLineEdit *NameLEdit;
    QDialogButtonBox *buttonBox;

    void setupUi(QDialog *Parameter)
    {
        if (Parameter->objectName().isEmpty())
            Parameter->setObjectName(QString::fromUtf8("Parameter"));
        Parameter->resize(400, 300);
        verticalLayout = new QVBoxLayout(Parameter);
        verticalLayout->setObjectName(QString::fromUtf8("verticalLayout"));
        horizontalLayout = new QHBoxLayout();
        horizontalLayout->setObjectName(QString::fromUtf8("horizontalLayout"));
        label = new QLabel(Parameter);
        label->setObjectName(QString::fromUtf8("label"));

        horizontalLayout->addWidget(label);

        NameLEdit = new QLineEdit(Parameter);
        NameLEdit->setObjectName(QString::fromUtf8("NameLEdit"));

        horizontalLayout->addWidget(NameLEdit);


        verticalLayout->addLayout(horizontalLayout);

        buttonBox = new QDialogButtonBox(Parameter);
        buttonBox->setObjectName(QString::fromUtf8("buttonBox"));
        buttonBox->setOrientation(Qt::Horizontal);
        buttonBox->setStandardButtons(QDialogButtonBox::Cancel|QDialogButtonBox::Ok);

        verticalLayout->addWidget(buttonBox);


        retranslateUi(Parameter);
        QObject::connect(buttonBox, SIGNAL(accepted()), Parameter, SLOT(accept()));
        QObject::connect(buttonBox, SIGNAL(rejected()), Parameter, SLOT(reject()));

        QMetaObject::connectSlotsByName(Parameter);
    } // setupUi

    void retranslateUi(QDialog *Parameter)
    {
        Parameter->setWindowTitle(QApplication::translate("Parameter", "\345\217\202\346\225\260", 0, QApplication::UnicodeUTF8));
        label->setText(QApplication::translate("Parameter", "Hand Name", 0, QApplication::UnicodeUTF8));
    } // retranslateUi

};

namespace Ui {
    class Parameter: public Ui_Parameter {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PARAMETER_H

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    AddDialog.cpp 
/// @brief   ��������ֲ����Ի���Դ�ļ�  
///  
/// ���ļ������ӶԻ������ʵ��  
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
////////////////////////////////////////////////////////////////////////// 
#include "AddDialog.h" 
#include <iostream>
#include <QtCore/QString>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QRegExp>


AddDialog::AddDialog(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);

	initPartListCombo();
	initPositionAttitude();
	partNameLineEdit->setEnabled(false);
	//partNameLineEdit->setReadOnly(true);

	connect(ApplyBtn, SIGNAL(clicked()),this,SLOT(on_ApplyBtn_clicked()));
	connect(OkBtn, SIGNAL(clicked()),this,SLOT(accept()));
	connect(CancelBtn, SIGNAL(clicked()),this,SLOT(reject()));
	//connect(partListCombo,SIGNAL(currentIndexChanged(const QString&)),this,SLOT(on_Changed(const QString&)));

}

AddDialog::~AddDialog(void)
{
}

bool AddDialog::initPartListCombo()
{
	char* item[24] = {"mArm","mPostWrist","mWrist","mPalm",
					 "mThumb0","mThumb1","mThumb2","mThumb3",
					 "mIndex0","mIndex1","mIndex2","mIndex3",
					 "mMiddle0","mMiddle1","mMiddle2","mMiddle3",
					 "mRing0","mRing1","mRing2","mRing3",
					 "mLittle0","mLittle1","mLittle2","mLittle3"};
	for(int i=0;i<24;i++)
	{
		partListCombo->addItem(item[i]);
	}
	return true;
}


bool AddDialog::initPositionAttitude()
{
	QRegExp regExp("^(-?[0]|-?[1-9][0-9]{0,9})(?:\\.\\d{1,8})?$|(^\\t?$)");  //������ʽ�������븡����
	QRegExpValidator *pRevalidotor = new QRegExpValidator(regExp, this);

	XLineEdit->setValidator(pRevalidotor);
	XLineEdit->setText("0");

	YLineEdit->setValidator(pRevalidotor);
	YLineEdit->setText("0");

	ZLineEdit->setValidator(pRevalidotor);
	ZLineEdit->setText("0");

	HLineEdit->setValidator(pRevalidotor);
	HLineEdit->setText("0");

	PLineEdit->setValidator(pRevalidotor);
	PLineEdit->setText("0");

	RLineEdit->setValidator(pRevalidotor);
	RLineEdit->setText("0");
	return true;
}

void AddDialog::on_ApplyBtn_clicked()
{
	accept();
}

void AddDialog::on_partListCombo_currentIndexChanged(const QString& text)  //�Զ�������
{
	QString t = text;  
	t.remove(0,1);  //���ַ���t�ӵ�0��λ�ÿ�ʼ���Ƴ�1���ַ�����ȥ����ͷ��m
	partNameLineEdit->setText(t);
}

void AddDialog::on_browseBtn_clicked()
{
	//�򿪱�׼�Ի���ѡȡҪ�򿪵��ļ�

	//QString fileContext = "D:/Delta3D/REL-2.5.0/examples/data";
	QString fileContext = QDir::currentPath();  //����Ӧ�ó�������Ŀ¼��Ϊ������
	QString path = QFileDialog::getOpenFileName(this, tr("Select File"), fileContext, tr("OSG Files(*.osg)"));
	
	if(path.isEmpty() == true) //�����ȡ����path�ǿյ�
	{ 
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any file.")); 
	}
	else
	{ 
		//QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path); 
		fileNameLineEdit->setText(path);
	} 
}

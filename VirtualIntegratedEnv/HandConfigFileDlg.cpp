////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    HandConfigFileDlg.cpp
/// @brief   ���ڼ��������������ļ����Դ�ļ�    
/// 
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "HandConfigFileDlg.h" 
#include <iostream>
#include <QtCore/QString>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QRegExp>


HandConfigFileDlg::HandConfigFileDlg(QWidget* parent)
	:QDialog(parent)
{
	setupUi(this);

	connect(OKBtn, SIGNAL(clicked()),this,SLOT(accept()));
	connect(CancelBtn, SIGNAL(clicked()),this,SLOT(reject()));
}

HandConfigFileDlg::~HandConfigFileDlg(void)
{
}

void HandConfigFileDlg::on_BrowseBtn_clicked()
{
	//�򿪱�׼�Ի���ѡȡҪ�򿪵��ļ�

	//QString fileContext = "D:/Delta3D/REL-2.5.0/examples/data";
	QString fileContext = QDir::currentPath();  //����Ӧ�ó�������Ŀ¼��Ϊ������
	QString path = QFileDialog::getOpenFileName(this, tr("Select File"), fileContext/*, tr("OSG Files(*.osg)")*/);

	if(path.isEmpty() == true) //�����ȡ����path�ǿյ�
	{ 
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any file.")); 
	}
	else
	{ 
		//QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path); 
		PathLine->setText(path);
	} 
}

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    AddObjDlg.cpp
/// @brief   添加虚拟手抓取对象对话框类的源文件  
///  
/// 本文件完成添加物体对话框类的实现  
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "AddObjDlg.h" 
#include <iostream>
#include <QtCore/QString>
#include <QtGui/QFileDialog>
#include <QtGui/QMessageBox>
#include <QtCore/QRegExp>


AddObjDlg::AddObjDlg(QWidget* parent)
:QDialog(parent)
{
	setupUi(this);

	initPositionAttitude();

	connect(ApplyBtn, SIGNAL(clicked()),this,SLOT(on_ApplyBtn_clicked()));
	connect(OkBtn, SIGNAL(clicked()),this,SLOT(accept()));
	connect(CancelBtn, SIGNAL(clicked()),this,SLOT(reject()));
}

AddObjDlg::~AddObjDlg(void)
{
}

bool AddObjDlg::initPositionAttitude()
{
	QRegExp regExp("^(-?[0]|-?[1-9][0-9]{0,9})(?:\\.\\d{1,8})?$|(^\\t?$)");  //正则表达式限制输入浮点数
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

void AddObjDlg::on_ApplyBtn_clicked()
{
	accept();
}

void AddObjDlg::on_browseBtn_clicked()
{
	//打开标准对话框，选取要打开的文件

	//QString fileContext = "D:/Delta3D/REL-2.5.0/examples/data";
	QString fileContext = QDir::currentPath();  //返回应用程序所在目录作为上下文
	QString path = QFileDialog::getOpenFileName(this, tr("Select File"), fileContext/*, tr("OSG Files(*.osg)")*/);
	
	if(path.isEmpty() == true) //点击了取消，path是空的
	{ 
		QMessageBox::information(NULL, tr("Path"), tr("You didn't select any file.")); 
	}
	else
	{ 
		//QMessageBox::information(NULL, tr("Path"), tr("You selected ") + path); 
		fileNameLineEdit->setText(path);
	} 
}

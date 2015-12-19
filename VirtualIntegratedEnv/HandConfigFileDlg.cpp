////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    HandConfigFileDlg.cpp
/// @brief   用于加载虚拟手配置文件类的源文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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
		PathLine->setText(path);
	} 
}

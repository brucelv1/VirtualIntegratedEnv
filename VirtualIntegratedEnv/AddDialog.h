////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    AddDialog.h 
/// @brief   添加虚拟手部件对话框头文件  
///  
/// 本文件完成添加对话框类的声明  
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////  

#ifndef _Delta_AddingDialog_H_
#define _Delta_AddingDialog_H_

#include <QtGui/QDialog>
#include "GUI/ui_addingDialog.h"

/// @brief
class AddDialog :
	public QDialog, public Ui_AddDialog
{
	Q_OBJECT
public:
	AddDialog(QWidget* parent = NULL);
	~AddDialog(void);
	//初始化填写combo的内容
	bool initPartListCombo();

	bool initPositionAttitude();

public slots:
	void on_ApplyBtn_clicked();
	void on_partListCombo_currentIndexChanged(const QString& text);
	void on_browseBtn_clicked();
};
#endif //_Delta_AddingDialog_H_

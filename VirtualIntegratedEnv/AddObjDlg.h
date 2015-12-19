////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    AddObjDlg.h
/// @brief   添加虚拟手抓取对象对话框类的头文件  
///  
/// 本文件完成添加物体对话框类的声明  
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////  

#ifndef _Delta_AddObjDlg_H_
#define _Delta_AddObjDlg_H_

#include <QtGui/QDialog>
#include "GUI/ui_AddObjDlg.h"


class AddObjDlg :
	public QDialog, public Ui_AddObjDlg
{
	Q_OBJECT
public:
	AddObjDlg(QWidget* parent = NULL);
	~AddObjDlg(void);

	bool initPositionAttitude();

public slots:
	void on_ApplyBtn_clicked();
	void on_browseBtn_clicked();
};
#endif //_Delta_AddObjDlg_H_

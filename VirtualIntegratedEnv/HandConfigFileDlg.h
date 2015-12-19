////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    HandConfigFileDlg.h
/// @brief   用于加载虚拟手配置文件类的头文件    
/// 
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _Delta_HandConfigFileDlg_H_
#define _Delta_HandConfigFileDlg_H_

#include <QtGui/QDialog>
#include "GUI/ui_HandConfigFileDlg.h"


class HandConfigFileDlg :
	public QDialog, public Ui_HandConfigFileDlg
{
	Q_OBJECT
public:
	HandConfigFileDlg(QWidget* parent = NULL);
	~HandConfigFileDlg(void);

	public slots:
		void on_BrowseBtn_clicked();
};
#endif //_Delta_HandConfigFileDlg_H_

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    SettingsDlg.h
/// @brief   设置对话框类的头文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
////////////////////////////////////////////////////////////////////////// 

#ifndef _Delta_SettingsDlg_H_
#define _Delta_SettingsDlg_H_

#include <QtGui/QDialog>
#include "GUI/ui_SettingsDialog.h"
#include <vector>

class SettingsDlg :
	public QDialog , public Ui_SettingsDialog
{
	Q_OBJECT
public:
	SettingsDlg(std::vector<std::string> vstr, QWidget* parent = NULL);
	~SettingsDlg(void);

	void initStrategyListCombo(std::vector<std::string> vstr);
};
#endif //_Delta_SettingsDlg_H_
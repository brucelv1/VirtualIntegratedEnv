////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    SettingsDlg.h
/// @brief   ���öԻ������ͷ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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
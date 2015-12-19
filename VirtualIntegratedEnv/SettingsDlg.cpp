////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    SettingsDlg.cpp
/// @brief   ���öԻ������Դ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
////////////////////////////////////////////////////////////////////////// 

#include "SettingsDlg.h"

SettingsDlg::SettingsDlg(std::vector<std::string> vstr, QWidget* parent)
: QDialog(parent)
{
	setupUi(this);
	initStrategyListCombo(vstr);

	connect(pushButtonDone,SIGNAL(clicked()),this,SLOT(accept()));
	connect(pushButtonCancel,SIGNAL(clicked()),this,SLOT(reject()));
}

SettingsDlg::~SettingsDlg(void)
{
}

void SettingsDlg::initStrategyListCombo( std::vector<std::string> vstr )
{
	this->StrategyBox->addItem(QString("<Strategies>"));

	for (unsigned int i=0; i<vstr.size(); i++)
	{
		QString qstr = QString(vstr[i].c_str());
		this->StrategyBox->addItem(qstr);
	}
}

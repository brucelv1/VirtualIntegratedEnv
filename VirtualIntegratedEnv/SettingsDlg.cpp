////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    SettingsDlg.cpp
/// @brief   设置对话框类的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    HandConfigFileDlg.h
/// @brief   ���ڼ��������������ļ����ͷ�ļ�    
/// 
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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

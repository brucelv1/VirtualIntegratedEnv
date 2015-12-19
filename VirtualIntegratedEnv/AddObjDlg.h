////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    AddObjDlg.h
/// @brief   ���������ץȡ����Ի������ͷ�ļ�  
///  
/// ���ļ�����������Ի����������  
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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

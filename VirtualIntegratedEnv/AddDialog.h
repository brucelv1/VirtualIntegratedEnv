////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    AddDialog.h 
/// @brief   ��������ֲ����Ի���ͷ�ļ�  
///  
/// ���ļ������ӶԻ����������  
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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
	//��ʼ����дcombo������
	bool initPartListCombo();

	bool initPositionAttitude();

public slots:
	void on_ApplyBtn_clicked();
	void on_partListCombo_currentIndexChanged(const QString& text);
	void on_browseBtn_clicked();
};
#endif //_Delta_AddingDialog_H_

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    MyQtWindow.h
/// @brief   程序主窗口的头文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _Delta_MyMainWindow_H_
#define _Delta_MyMainWindow_H_

////ode要求指定dSINGLE或dDOUBLE
//#ifndef dSINGLE
//#define dSINGLE
//#endif

#include <QtGui/QMainWindow>
#include "GUI/ui_VIE_MainWin.h"
#include "userAddInfoStruct.h"
#include "VIECoreApp.h"
#include <dtCore/base.h> //使用其消息机制
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>
#include <QtCore/QTimer>

class MyQtWindow :
	public QMainWindow , public Ui_MainWindow, public dtCore::Base //采用了多继承，注意二义性！
{
	Q_OBJECT
public:
	MyQtWindow(VIECoreApp* _vcApp, QMainWindow* parent = NULL);
	virtual ~MyQtWindow(void);
	
	//把osg视图窗口从delta3d中提取出来，嵌入到Qt窗口的graphicsView部件中
	bool addOsgViewerToQtGraphicsView();

	virtual void OnMessage(MessageData* data);

public slots:
	void on_action_Add_triggered();
	void on_actionStart_triggered();
	void on_actionStop_triggered();
	void on_actionSettings_triggered();
	void on_actionOpen_triggered();
	void on_actionSave_triggered();
	void on_actionSJT_6_triggered();
	void on_actionSJT_3_triggered();
	void on_actionBarrett_triggered();
	void on_actionHumanHand_triggered();
	void on_actionAddObjects_triggered();
	void on_actionReset_triggered();
	void on_actionAddCustomHand_triggered();
	void on_actionTraining_triggered();
	void on_actionTesting_triggered();
	void on_actionExercising_triggered();

private slots:
	void _qTimer_timeout();

signals:
	void userAddData(userAddInfo* uAI);
	void StartTriggered();
	void StopTriggered();
	void SettingsInfo(bool isUsingKeyboard,
					  bool isUsingDataGlove,
					  bool isUsingPlatform,
					  bool isUsingCollision,
					  int platformSerialNum,
					  int hardwareSerialNum);
	void fileSave(std::string path);
	void fileOpen(std::string path);

private:
	VIECoreApp* mVIECoreApp;
	// shared memory
	boost::interprocess::windows_shared_memory _winshm;
	boost::interprocess::mapped_region _region;
	unsigned char* _ucpSharedMem;
	size_t         _stLenSharedMem;

	// 创建训练测试子进程
	void createTrainTestProcess(std::string& module_path, const std::string& NameSharedMem);

	// Timer, for processing bar
	QTimer* qTimer;
	int processingBarVal;
};
#endif //_Delta_MyMainWindow_H_
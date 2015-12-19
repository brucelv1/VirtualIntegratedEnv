////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    main.cpp
/// @brief   ��������ڵ�Դ�ļ�    
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_MAIN

#include "VIECoreApp.h"
/************delta3d app ��Qt app ͬ���������ͷ�ļ�*******************/
#include <dtQt/qtguiwindowsystemwrapper.h>
#include <dtQt/deltastepper.h>
#include <QtGui/QApplication>
#include <dtCore/system.h>
/************************    end      ***********************************/
#include "MyQtWindow.h"

int main(int argc, char** argv)
{
	QApplication qapp(argc, argv);
	qapp.addLibraryPath("./");
	dtQt::QtGuiWindowSystemWrapper::EnableQtGUIWrapper();

	//Instantiate the application and look for the config file
	dtCore::RefPtr<VIECoreApp> app = new VIECoreApp("config.xml");
	app->Config(); //configuring the application
	dtCore::System::GetInstance().Start(); //�����൱��app->Run()������ֱ��qapp.exec();��䣬��ͼ�Żᱻ��ȫ����

	MyQtWindow* myWin = new MyQtWindow(app);
	myWin->show();
	dtQt::DeltaStepper stepper;
	stepper.Start();

	qapp.exec();

	stepper.Stop();
	dtCore::System::GetInstance().Stop();

	return 0;
}

#endif

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    main.cpp
/// @brief   程序主入口的源文件    
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DEBUG_MAIN

#include "VIECoreApp.h"
/************delta3d app 和Qt app 同步启动相关头文件*******************/
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
	dtCore::System::GetInstance().Start(); //这行相当于app->Run()，不过直到qapp.exec();语句，视图才会被完全画出

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

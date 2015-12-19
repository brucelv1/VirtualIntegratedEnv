////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    VIECoreApp.h
/// @brief   虚拟环境测试平台的核心应用程序类的头文件
/// 
/// 本文件所定义的核心应用程序类包含了软件了主要业务逻辑
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DELTA_VIECOREAPP_H_
#define DELTA_VIECOREAPP_H_

//ode要求指定dSINGLE或dDOUBLE
#ifndef dSINGLE
#define dSINGLE
#endif

#include <dtABC/application.h>
#include <dtCore/object.h>
#include <dtCore/odebodywrap.h>
#include <dtCore/odecontroller.h>
#include <dtCore/orbitmotionmodel.h>
#include <dtCore/scene.h>
#include <dtCore/camera.h>
#include <dtCore/system.h>
#include <dtCore/transform.h>
#include <dtCore/compass.h>      //左下角小坐标系
#include <dtUtil/mathdefines.h>
#include <queue>
#include <iostream>
#include <dtCore/infinitelight.h> //用于跟随camera的光照
#include "InfoVisitor.h"
#include "IControlCharStrategy.h"
#include "IExternDataStrategy.h"
#include <bitset>
#include "IHand.h"
#include "InfoStruct.h"
#include <vector>

using namespace dtCore;
using namespace dtABC;
using namespace dtUtil;

class VIECoreApp : public Application
{
public:
	VIECoreApp(const std::string& configFile = "config.xml");

	void On_StartTriggered();
	void On_StopTriggered();
	bool On_SettingsInfo(SettingsInfoStruct& sis);
	void On_AddObjectsDlg(const std::string& _name, const std::string& _filepath, 
		double* data, const std::string& type);
	void On_ResetVIE();

	void LoadHand(const std::string& _name, const std::string& _filePath="");

	std::vector<std::string> strategyList;

protected:
	virtual ~VIECoreApp();

	virtual void PreFrame(const double deltaFrameTime);

	virtual bool KeyPressed(const dtCore::Keyboard* keyboard, int key);


	// If a physical object is picked, apply a little spinning force to it
	virtual bool MouseButtonPressed(const dtCore::Mouse* mouse, dtCore::Mouse::MouseButton button);


	///Use the mouse pick point to calculate the starting location
	Transform GetStartTransform();

private:
	const unsigned int mLimit;
	std::queue< RefPtr<Object> > mToAdd;
	std::queue< RefPtr<Object> > mToRemove;
	std::deque< RefPtr<Object> > mObjects;


	RefPtr<OrbitMotionModel> omm;
	RefPtr<Object> mGround;
	RefPtr<dtCore::Map> mMap;
	bool mRenderCollisionGeometry;
	bool m_UsingSceneLight;
	RefPtr<dtCore::Compass> mCompass;

	//控制每帧更新的开启和关闭
	bool b_mDoPreFrame;

	//仿真控制的设置
	bool CreateStrategy(SettingsInfoStruct& sis);
	IControlCharStrategy* mCtrlStr;
	IExternDataStrategy* mExDataStr;

	IHand* mHand;
	Part* mGraspingObj;
};

#endif //DELTA_VIECOREAPP_H_
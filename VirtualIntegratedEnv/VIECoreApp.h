////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    VIECoreApp.h
/// @brief   ���⻷������ƽ̨�ĺ���Ӧ�ó������ͷ�ļ�
/// 
/// ���ļ�������ĺ���Ӧ�ó�����������������Ҫҵ���߼�
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef DELTA_VIECOREAPP_H_
#define DELTA_VIECOREAPP_H_

//odeҪ��ָ��dSINGLE��dDOUBLE
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
#include <dtCore/compass.h>      //���½�С����ϵ
#include <dtUtil/mathdefines.h>
#include <queue>
#include <iostream>
#include <dtCore/infinitelight.h> //���ڸ���camera�Ĺ���
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

	//����ÿ֡���µĿ����͹ر�
	bool b_mDoPreFrame;

	//������Ƶ�����
	bool CreateStrategy(SettingsInfoStruct& sis);
	IControlCharStrategy* mCtrlStr;
	IExternDataStrategy* mExDataStr;

	IHand* mHand;
	Part* mGraspingObj;
};

#endif //DELTA_VIECOREAPP_H_
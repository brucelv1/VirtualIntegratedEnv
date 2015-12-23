////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    VIECoreApp.cpp
/// @brief   虚拟环境测试平台的核心应用程序类的源文件
/// 
/// 本文件所实现的核心应用程序类包含了软件了主要业务逻辑
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "VIECoreApp.h"
//用于串口
#include "SerialPort.h"
//用于寻找节点树中的某个节点
#include "findNodeVisitor.h" 
//用于加载天空盒
#include <dtCore/map.h>
#include <dtCore/project.h>
#include "CCS_Keyboard.h"
#include "HandFactory.h"
#include "StrategyPrototype.h"

//全局的尺寸放缩量，调整这一个值就可以使手部件、物体、装配参数同比例放缩
#define globalScale float(0.1)  

using namespace dtCore;
using namespace dtABC;
using namespace dtUtil;



VIECoreApp::VIECoreApp(const std::string& configFile)
	: Application(configFile)
	, mLimit(5)
	, mGround(NULL)
	, mMap(NULL)
	, mRenderCollisionGeometry(false)
	, b_mDoPreFrame(false) //初始不进行每帧更新
	, m_UsingSceneLight(false)
	, mCtrlStr(NULL)
	, mExDataStr(NULL)
	, mHand(NULL)
	, mGraspingObj(NULL)
{
	StrategyPrototype::RegisterStrategy();

	for (unsigned int i=0; i<IControlCharStrategy::CCSNameList.size(); i++)
	{
		strategyList.push_back(IControlCharStrategy::CCSNameList[i]);
	}

	for(unsigned int i=0; i<IExternDataStrategy::EDSNameList.size(); i++)
	{
		strategyList.push_back(IExternDataStrategy::EDSNameList[i]);
	}

	// setup some default physics values
	GetScene()->SetGravity(0.0f, 0.0f, -15.0f);
	GetScene()->GetPhysicsController()->GetWorldWrapper()->SetDamping(0.1f, 0.1f);

	// position the camera
	dtCore::Transform CamPosition;
	CamPosition.Set( 400.0f, 400.0f, 400.0f,  //Position
		0.0f  ,   0.0f , 0.0f  ,  //LookAt Point
		0.0f  ,   0.0f , 1.0f  ); //Up Vector
	// scaling
	CamPosition.SetTranslation(CamPosition.GetTranslation()*globalScale);
	// setting
	GetCamera()->SetTransform(CamPosition);

	// Add the compass (3d basis axes) to the bottom left of the screen
	mCompass = new dtCore::Compass(GetCamera());
	GetScene()->GetSceneNode()->addChild(mCompass->GetOSGNode());

	// load ground
	{
		mGround = new Object("Ground");
		mGround->LoadFile("./models/woodfloor.osg");

		// position the ground
		dtCore::Transform posGround;
		posGround.Set(0,0,-300,0,0,0);
		// scaling
		posGround.SetTranslation(posGround.GetTranslation()*globalScale);
		mGround->SetTransform(posGround);

		// create collision mesh
		mGround->SetCollisionMesh();

		// Add the object to the Scene to be rendered
		GetScene()->AddChild(mGround.get());

		// render collision geometry (for debugging)
		mGround->RenderCollisionGeometry(mRenderCollisionGeometry);
	}

	omm = new OrbitMotionModel(GetKeyboard(), GetMouse());
	omm->SetTarget(GetCamera());

	// calculate and set focal distance for orbit motion model (origin -> camera)
	{
		Transform trans;
		GetCamera()->GetTransform(trans);

		osg::Vec3 camLoc;
		trans.GetTranslation(camLoc);

		osg::Vec3 origin(0.0f, 0.0f, 0.0f);
		omm->SetDistance((camLoc - origin).length());
	}
}

VIECoreApp::~VIECoreApp()
{
}

void VIECoreApp::On_ResetVIE()
{
	// 1.clear mObjects and mGraspingObj
	while (!mObjects.empty())
	{
		GetScene()->RemoveChild(mObjects.front().get());
		mObjects.pop_front();
	}
	if (mGraspingObj != NULL)
	{
		GetScene()->RemoveChild(mGraspingObj->getCoordinatePtr());
		delete mGraspingObj;
		mGraspingObj = NULL;
	}

	// 2.stop simulation before clearing the hand and the strategy,
	// in case of unexpected error
	b_mDoPreFrame = false;

	// 3.clear the operating strategy
	if(mCtrlStr != NULL)
	{
		mCtrlStr->Destroy();
		mCtrlStr = NULL;
	}
	if(mExDataStr != NULL)
	{
		mExDataStr->Destroy();
		mExDataStr = NULL;
	}
	// 4.clear the hand
	GetScene()->RemoveChild(mHand->getHandRoot()->getCoordinatePtr());
	delete mHand;
	mHand = NULL;
}

void VIECoreApp::PreFrame(const double deltaFrameTime)
{
	/*
	* 让场景默认光源（Name:SkyLight）跟随camera一起运动，
	* 这样就可以照亮虚拟手朝下的部分，从而能够让观察者
	* 看清虚拟手的细节
	*/
	Transform camTrans;
	GetCamera()->GetTransform(camTrans);
	GetScene()->GetLight("SkyLight")->SetTransform(camTrans);
	GetScene()->GetLight("SkyLight")->SetDiffuse(1.0,1.0,1.0,1.0);

	while (!mToAdd.empty())
	{
		GetScene()->AddChild(mToAdd.front().get());
		mObjects.push_back(mToAdd.front());
		mToAdd.pop();
	}

	while (!mToRemove.empty())
	{
		GetScene()->RemoveChild(mToRemove.front().get());
		mObjects.pop_front();
		mToRemove.pop();
	}

	//如果b_mDoPreFrame为真，则进行仿真
	if(b_mDoPreFrame == true)
	{
		//如果使用外部数据策略，进入这里
		if(mExDataStr != NULL)
		{
			mExDataStr->UpdateHand();
		}
		
		//如果使用控制字符策略，进入这里
		if(mCtrlStr != NULL)  
		{			  
			mCtrlStr->doGesture();
			mCtrlStr->doWristAction();
		}
	}
}

bool VIECoreApp::KeyPressed(const dtCore::Keyboard* keyboard, int key)
{
	// SetCollision____ must be called before setTransform so
	// that a dGeomID will exist before a prePhysicsUpdate, otherwise
	// the scale will never be applied to the physics geometry
	bool verdict(false);

	switch (key)
	{
	case 'p':
		System::GetInstance().SetPause(!System::GetInstance().GetPause());
		verdict = true;
		break;

	//case osgGA::GUIEventAdapter::KEY_Escape:
	//	while (!mToAdd.empty())
	//	{
	//		mToAdd.pop();
	//	}

	//	while (!mToRemove.empty())
	//	{
	//		mToRemove.pop();
	//	}

	//	while (!mObjects.empty())
	//	{
	//		mObjects.pop_front();
	//	}

	//	Quit();
	//	verdict = true;
	//	break;

	case 'b':
		if (mObjects.size() < mLimit)
		{
			RefPtr<Object> box = new Object("box");
			box->LoadFile("./models/physics_crate.ive");

			float scaleVal = 30.0 * globalScale;
			box->SetScale(osg::Vec3(scaleVal, scaleVal, scaleVal));

			box->SetCollisionBox();
			box->SetTransform(GetStartTransform());
			box->RenderCollisionGeometry(mRenderCollisionGeometry);

			double lx = 1.0;
			double ly = 1.0;
			double lz = 1.0;

			dMass mass;
			dMassSetBox(&mass, 1.0, lx, ly, lz);
			box->SetMass(&mass);

			box->EnableDynamics();

			mToAdd.push(box);
		}
		else
		{
			mToRemove.push(mObjects.front());
		}
		verdict = true;
		break;

	case 's':
		if (mObjects.size() < mLimit)
		{
			RefPtr<Object> sphere = new Object("sphere");
			sphere->LoadFile("./models/physics_happy_sphere.ive");

			float randomScale = RandFloat(40.0f, 50.0f) * globalScale;
			sphere->SetScale(osg::Vec3(randomScale, randomScale, randomScale));

			sphere->SetCollisionSphere();
			sphere->SetTransform(GetStartTransform());
			sphere->RenderCollisionGeometry(mRenderCollisionGeometry);

			double radius = 0.5;

			dMass mass;
			dMassSetSphere(&mass, 1.0, radius);
			sphere->SetMass(&mass);
			sphere->EnableDynamics();

			mToAdd.push(sphere);
		}
		else
		{
			mToRemove.push(mObjects.front());
		}
		verdict = true;
		break;

	case 'c':
		if (mObjects.size() < mLimit)
		{
			RefPtr<Object> cyl = new Object("cylinder");
			cyl->LoadFile("./models/physics_barrel.ive");

			float randomScale = RandFloat(59.0f, 60.0f) * globalScale;
			cyl->SetScale(osg::Vec3(randomScale, randomScale, randomScale));

			cyl->SetCollisionCappedCylinder();
			cyl->SetTransform(GetStartTransform());
			cyl->RenderCollisionGeometry(mRenderCollisionGeometry);

			double radius = 0.321;
			double length = 1.0;

			dMass mass;
			dMassSetCappedCylinder(&mass, 1.0, 2, radius, length);
			cyl->SetMass(&mass);

			cyl->EnableDynamics();

			mToAdd.push(cyl);
		}
		else
		{
			mToRemove.push(mObjects.front());
		}
		verdict = true;
		break;

	case '0':
		GetScene()->RemoveChild(mObjects.front().get());
		mObjects.pop_front();
		verdict = true;
		break;

	case 'd':
		// toggle drawing of all collision geometry
		mRenderCollisionGeometry = !mRenderCollisionGeometry;
		mGround->RenderCollisionGeometry(mRenderCollisionGeometry);
		for (size_t i = 0; i < mObjects.size(); ++i)
		{
			mObjects[i]->RenderCollisionGeometry(mRenderCollisionGeometry);
		}
		break;

	case 'l':
		m_UsingSceneLight = !m_UsingSceneLight;
		GetScene()->UseSceneLight(m_UsingSceneLight);
		break;

	default:
		break;
	}

	//在使用键盘控制模式时，当点击“启动”之后（b_mDoPreFrame变为true）才进行按键监听
	if(b_mDoPreFrame == true && mCtrlStr != NULL && mCtrlStr->getStrategyName() == "CCS_Keyboard")
	{
		dynamic_cast<CCS_Keyboard*>(mCtrlStr)->updateCommand(key);
	}

	return verdict;
}

// If a physical object is picked, apply a little spinning force to it
bool VIECoreApp::MouseButtonPressed(const dtCore::Mouse* mouse, dtCore::Mouse::MouseButton button)
{
	//if (button != 0) { return false; }

	//dtCore::DeltaDrawable* drawable = GetView()->GetMousePickedObject();
	//if (drawable == NULL) { return false; } // nothing picked

	//dtCore::Physical* phys = dynamic_cast<dtCore::Physical*>(drawable);
	//if (phys == NULL) { return false; } // didn't pick a Physical

	//if (phys->DynamicsEnabled() == false) { return false; } // not enabled

	//phys->GetBodyWrapper()->ApplyForce(osg::Vec3(0.f, 0.f, 120.f));
	//phys->GetBodyWrapper()->ApplyTorque(osg::Vec3(0.f, 0.f, 60.f));
	return true;
}

///Use the mouse pick point to calculate the starting location
Transform VIECoreApp::GetStartTransform()
{
	osg::Vec3 xyz;
	if (GetView()->GetMousePickPosition(xyz))
	{
		Transform xform;
		xyz[2] += 120.f * globalScale; // bump up the z so objects aren't buried underground
		xform.SetTranslation(xyz);
		xform.SetRotation(RandFloat(0.0f, 180.0f),
			RandFloat(0.0f,  90.0f),
			RandFloat(0.0f,  90.0f));

		return xform;
	}

	return Transform();
}

void VIECoreApp::On_StartTriggered()
{
	b_mDoPreFrame = true;
	System::GetInstance().SetPause(false);
}

void VIECoreApp::On_StopTriggered()
{
	b_mDoPreFrame = false;
}

bool VIECoreApp::On_SettingsInfo(SettingsInfoStruct& sis)
{	
	return CreateStrategy(sis);
}

void VIECoreApp::LoadHand(const std::string& _name, const std::string& _filePath)
{
	//如果在运行时进行虚拟手的切换，需要做以下工作保证程序正常运行
	if (mHand != NULL)
	{
		//关闭仿真
		b_mDoPreFrame = false;
		//删除正在使用的策略
		if(mCtrlStr != NULL)
		{
			mCtrlStr->Destroy();
			mCtrlStr = NULL;
		}
		if(mExDataStr != NULL)
		{
			mExDataStr->Destroy();
			mExDataStr = NULL;
		}
		//删除正在使用的虚拟手
		GetScene()->RemoveChild(mHand->getHandRoot()->getCoordinatePtr());
		delete mHand;
		mHand = NULL;
	}

	mHand = HandFactory::createHand(_name, globalScale, _filePath);
	if(mHand != NULL)
		GetScene()->AddChild(mHand->getHandRoot()->getCoordinatePtr());
}

bool VIECoreApp::CreateStrategy(SettingsInfoStruct& sis)
{
	//如果尚未加载虚拟手，则不创建任何策略，直接返回
	if(mHand == NULL)
		return false;

	//在创建策略前，先删除已有策略，保证运行过程中始终只有一个策略
	if(mCtrlStr != NULL)
	{
		mCtrlStr->Destroy();
		mCtrlStr = NULL;
	}
	if(mExDataStr != NULL)
	{
		mExDataStr->Destroy();
		mExDataStr = NULL;
	}

	//根据策略名创建相应的控制策略
	if (sis.strategy.substr(0,4) == "CCS_")
	{
		mCtrlStr = IControlCharStrategy::makeCCSProduct(sis.strategy);
		mCtrlStr->initStrategyConfig(sis,mHand,GetScene());
		return true;
	}

	if (sis.strategy.substr(0,4) == "EDS_")
	{
		mExDataStr = IExternDataStrategy::makeEDSProduct(sis.strategy);

		// 初始化，同时执行检查，若失败，则恢复原状
		if(false == mExDataStr->initStrategyConfig(sis,mHand,GetScene()))
		{
			mExDataStr->Destroy();
			mExDataStr = NULL;
			return false;
		}
		return true;
	}

	return false;
}

void VIECoreApp::On_AddObjectsDlg(const std::string& _name, const std::string& _filepath, 
	double* data, const std::string& type)
{
	if(mHand == NULL)
		return;

	if (mGraspingObj != NULL)
	{
		GetScene()->RemoveChild(mGraspingObj->getCoordinatePtr());
		delete mGraspingObj;
		mGraspingObj = NULL;
	}
	mGraspingObj = new Part();
	mGraspingObj->setName(_name);
	mGraspingObj->loadFile(_filepath);
	float _scale = mHand->getHandScale();
	mGraspingObj->getModelPtr()->SetScale(osg::Vec3(_scale,_scale,_scale));

	if (type == "HPR")
	{
		mGraspingObj->setOriginPosition(osg::Vec3(data[0],data[1],data[2]));
		mGraspingObj->setOriginAttitude(osg::Vec3(data[3],data[4],data[5]));
		mGraspingObj->makeAssembly();
	}
	if (type == "MATRIX")
	{
		osg::Matrix tmp;
		tmp.set(data);
		mGraspingObj->setOriginPosition(tmp.getTrans());
		mGraspingObj->setOriginAttitude(tmp.getRotate().asVec3());
		mGraspingObj->makeAssembly();
	}
	mGraspingObj->getModelPtr()->SetCollisionMesh();
	GetScene()->AddChild(mGraspingObj->getCoordinatePtr());
}
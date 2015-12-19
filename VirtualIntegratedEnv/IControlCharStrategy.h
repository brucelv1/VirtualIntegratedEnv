////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IControlCharStrategy.h
/// @brief   控制字符策略抽象基类的头文件    
/// 
/// 本文件声明了控制字符抽象类，包括其对外接口和用于子类继承的接口
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _CONTROLSTRATEGY_H_
#define _CONTROLSTRATEGY_H_

//ode要求指定dSINGLE或dDOUBLE
#ifndef dSINGLE
#define dSINGLE
#endif

#include <dtCore/base.h>
#include <dtCore/scene.h>
#include <osg/Vec3>
#include <bitset>
#include "IHand.h"
#include "Finger.h"

#define MAKE_CCS_PROTOTYPE(NAME) \
	IControlCharStrategy* NAME ## _MyCCS = \
		IControlCharStrategy::addCCSPrototype(#NAME, new NAME());

#define IMPLEMENT_CCS_CLONE(NAME) \
	IControlCharStrategy* clone() const { return new NAME(*this); }

class IControlCharStrategy : public dtCore::Base
{
public:
	/// for prototype purpose
	IControlCharStrategy();
	IControlCharStrategy(const IControlCharStrategy& ICCS);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	std::string getStrategyName();
	void setStrategyName(const std::string& _name) {mName=_name;}

	void setHandPtr(IHand* _hand) {mHand=_hand;}

	void setDeltaScene(dtCore::Scene* _scene)
	{
		mScene=_scene;
		this->AddSender(mScene);
	}
	
	void Destroy()
	{
		delete this;
	}

	//设置动作指令，提供最多五根手指的指令，由低位到高位（0~4）分别是拇指到小指
	virtual void setCommandBits(std::bitset<5> bits)
	{
		mCommandBits = bits;
	}
	//手腕指令，共七种：0回位1外旋2内旋3内翻4外翻5下切6上切
	virtual void setWristActionType(int _type)
	{
		mWristActionType = _type;
	}

	//手指动作
	virtual void doGesture()=0;
	//手腕动作
	virtual void doWristAction(){};

	// for prototype purpose
	static std::vector<std::string> CCSNameList;
	static std::vector<IControlCharStrategy*> CCSObjectList;
	static IControlCharStrategy* addCCSPrototype(std::string _name, IControlCharStrategy* icc);
	virtual IControlCharStrategy* clone() const = 0;
	static IControlCharStrategy* makeCCSProduct(std::string _name);

protected:
	virtual ~IControlCharStrategy();
	//传入手指根部指节,extend返回bool型，用于检测手指是否回到初始装配位置
	virtual void flexFinger(Finger* _finger);
	virtual bool extendFinger(Finger* _finger);

	//指节版本，只检查一个指节，可用于整根手指同步动作情形
	bool checkKnuckleRecovered(Part* knuckle, const osg::Vec3& deltaAttitudePerFrame);
	//手指版本，用于需要检查整个手指每个指节的情形
	bool checkFingerRecovered(Finger* _finger);

	std::string mName;
	dtCore::Scene* mScene;
	IHand* mHand;
	std::bitset<5> mCommandBits;
	int mWristActionType;
};

#endif // _CONTROLSTRATEGY_H_
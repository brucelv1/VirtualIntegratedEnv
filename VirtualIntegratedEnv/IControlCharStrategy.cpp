////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IControlCharStrategy.cpp
/// @brief   控制字符策略抽象基类的源文件    
/// 
/// 本文件实现了控制字符抽象类中的公共方法
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#include "IControlCharStrategy.h"

std::vector<std::string> IControlCharStrategy::CCSNameList;
std::vector<IControlCharStrategy*> IControlCharStrategy::CCSObjectList;

IControlCharStrategy::IControlCharStrategy()
: mName("DefaultName")
, mHand(NULL)
, mScene(NULL)
, mWristActionType(0)
{
}

IControlCharStrategy::IControlCharStrategy(const IControlCharStrategy& ICCS)
: mName(ICCS.mName)
, mHand(ICCS.mHand)
, mScene(ICCS.mScene)
, mWristActionType(ICCS.mWristActionType)
{
}

IControlCharStrategy::~IControlCharStrategy()
{
	this->RemoveSender(mScene);
}

std::string IControlCharStrategy::getStrategyName()
{
	return mName;
}

void IControlCharStrategy::flexFinger(Finger* _finger)
{
	if(_finger == NULL)
		return;
	//被观察的其他手指没有停下来，就不进行运动
	if(!_finger->readyToMove())
		return;

	for (unsigned int i=0; i<_finger->numOfKnuckles(); i++)
	{
		Part* knuckle = _finger->getKnuckleAt(i);
		knuckle->setAttitude(knuckle->getAttitude() + knuckle->getDeltaAttitudePerFrame());
		knuckle->makeTransform();
	}
}

bool IControlCharStrategy::extendFinger(Finger* _finger)
{
	if(_finger == NULL)
		return true;
	if(true == checkFingerRecovered(_finger))
		return true;

	for (unsigned int i=0; i<_finger->numOfKnuckles(); i++)
	{
		Part* knuckle = _finger->getKnuckleAt(i);
		if(false == checkKnuckleRecovered(knuckle,knuckle->getDeltaAttitudePerFrame()))
		{
			knuckle->setAttitude(knuckle->getAttitude() - knuckle->getDeltaAttitudePerFrame());
			knuckle->makeTransform();
		}
	}
	return false;
}

bool IControlCharStrategy::checkKnuckleRecovered(Part* knuckle, const osg::Vec3& deltaAttitudePerFrame)
{
	//该函数要检测手指根部指节是否回到初始姿态，显然，如果对象为空或没有加载手指部件，当然可以认为已经回到初始状态
	if(knuckle == NULL || !knuckle->isLoaded())
		return true;

	if(deltaAttitudePerFrame == osg::Vec3(0,0,0))
		return true;

	//由于deltaAttitudePerFrame的三个元素可正可负可为零，因此在比较大小时，必须要考虑这三个元素的正负性
	float deltaX = deltaAttitudePerFrame.x();
	float deltaY = deltaAttitudePerFrame.y();
	float deltaZ = deltaAttitudePerFrame.z();

	osg::Vec3 att = knuckle->getAttitude();
	//osg::Vec3 oriAtt = knuckle->getOriginAttitude();
	osg::Vec3 oriAtt = osg::Vec3(0,0,0);

	//通过不等号左右两边同时乘以delta*，可以将正、负、零三种情况都用<=表达清楚
	bool xb = (att.x()*deltaX) <= (oriAtt.x()*deltaX);
	bool yb = (att.y()*deltaY) <= (oriAtt.y()*deltaY);
	bool zb = (att.z()*deltaZ) <= (oriAtt.z()*deltaZ);

	return xb && yb && zb;
}

bool IControlCharStrategy::checkFingerRecovered(Finger* _finger)
{
	//没有手指，默认为回位状态
	if(_finger == NULL)
		return true;

	std::vector<bool> bRecover;

	for (unsigned int i=0; i<_finger->numOfKnuckles(); i++)
	{
		Part* knuckle = _finger->getKnuckleAt(i);
		bRecover.push_back(checkKnuckleRecovered(knuckle, knuckle->getDeltaAttitudePerFrame()));
	}

	for (unsigned int j=0; j<bRecover.size(); j++)
	{
		//只要有一个false，就返回false
		if(bRecover[j] == false)
			return false;
	}

	return true;
}

void IControlCharStrategy::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	this->setStrategyName(si.strategy);
	this->setHandPtr(_hand);
	this->setDeltaScene(_scene);
}

IControlCharStrategy* IControlCharStrategy::addCCSPrototype( std::string _name, IControlCharStrategy* icc )
{
	std::cout << "adding CCS prototype for " << _name << std::endl;
	CCSNameList.push_back(_name);
	CCSObjectList.push_back(icc);
	std::cout << "done\n";
	return icc;
}

IControlCharStrategy* IControlCharStrategy::makeCCSProduct( std::string _name )
{
	IControlCharStrategy* icc;
	unsigned int CCS_id=0;
	for (CCS_id; CCS_id<CCSNameList.size(); CCS_id++)
	{
		if (CCSNameList[CCS_id] == _name)
		{
			icc = CCSObjectList[CCS_id];
			return icc->clone();
		}
	}

	// if not found
	std::cout << "Cannot find the CCS prototype: " << _name.c_str() << std::endl;
	return NULL;
}

////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    IControlCharStrategy.cpp
/// @brief   �����ַ����Գ�������Դ�ļ�    
/// 
/// ���ļ�ʵ���˿����ַ��������еĹ�������
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
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
	//���۲��������ָû��ͣ�������Ͳ������˶�
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
	//�ú���Ҫ�����ָ����ָ���Ƿ�ص���ʼ��̬����Ȼ���������Ϊ�ջ�û�м�����ָ��������Ȼ������Ϊ�Ѿ��ص���ʼ״̬
	if(knuckle == NULL || !knuckle->isLoaded())
		return true;

	if(deltaAttitudePerFrame == osg::Vec3(0,0,0))
		return true;

	//����deltaAttitudePerFrame������Ԫ�ؿ����ɸ���Ϊ�㣬����ڱȽϴ�Сʱ������Ҫ����������Ԫ�ص�������
	float deltaX = deltaAttitudePerFrame.x();
	float deltaY = deltaAttitudePerFrame.y();
	float deltaZ = deltaAttitudePerFrame.z();

	osg::Vec3 att = knuckle->getAttitude();
	//osg::Vec3 oriAtt = knuckle->getOriginAttitude();
	osg::Vec3 oriAtt = osg::Vec3(0,0,0);

	//ͨ�����Ⱥ���������ͬʱ����delta*�����Խ����������������������<=������
	bool xb = (att.x()*deltaX) <= (oriAtt.x()*deltaX);
	bool yb = (att.y()*deltaY) <= (oriAtt.y()*deltaY);
	bool zb = (att.z()*deltaZ) <= (oriAtt.z()*deltaZ);

	return xb && yb && zb;
}

bool IControlCharStrategy::checkFingerRecovered(Finger* _finger)
{
	//û����ָ��Ĭ��Ϊ��λ״̬
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
		//ֻҪ��һ��false���ͷ���false
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

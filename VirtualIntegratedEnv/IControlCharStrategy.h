////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    IControlCharStrategy.h
/// @brief   �����ַ����Գ�������ͷ�ļ�    
/// 
/// ���ļ������˿����ַ������࣬���������ӿں���������̳еĽӿ�
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _CONTROLSTRATEGY_H_
#define _CONTROLSTRATEGY_H_

//odeҪ��ָ��dSINGLE��dDOUBLE
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

	//���ö���ָ��ṩ��������ָ��ָ��ɵ�λ����λ��0~4���ֱ���Ĵָ��Сָ
	virtual void setCommandBits(std::bitset<5> bits)
	{
		mCommandBits = bits;
	}
	//����ָ������֣�0��λ1����2����3�ڷ�4�ⷭ5����6����
	virtual void setWristActionType(int _type)
	{
		mWristActionType = _type;
	}

	//��ָ����
	virtual void doGesture()=0;
	//������
	virtual void doWristAction(){};

	// for prototype purpose
	static std::vector<std::string> CCSNameList;
	static std::vector<IControlCharStrategy*> CCSObjectList;
	static IControlCharStrategy* addCCSPrototype(std::string _name, IControlCharStrategy* icc);
	virtual IControlCharStrategy* clone() const = 0;
	static IControlCharStrategy* makeCCSProduct(std::string _name);

protected:
	virtual ~IControlCharStrategy();
	//������ָ����ָ��,extend����bool�ͣ����ڼ����ָ�Ƿ�ص���ʼװ��λ��
	virtual void flexFinger(Finger* _finger);
	virtual bool extendFinger(Finger* _finger);

	//ָ�ڰ汾��ֻ���һ��ָ�ڣ�������������ָͬ����������
	bool checkKnuckleRecovered(Part* knuckle, const osg::Vec3& deltaAttitudePerFrame);
	//��ָ�汾��������Ҫ���������ָÿ��ָ�ڵ�����
	bool checkFingerRecovered(Finger* _finger);

	std::string mName;
	dtCore::Scene* mScene;
	IHand* mHand;
	std::bitset<5> mCommandBits;
	int mWristActionType;
};

#endif // _CONTROLSTRATEGY_H_
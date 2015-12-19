////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    IExternDataStrategy.h
/// @brief   �ⲿ���ݲ��Գ�������ͷ�ļ�    
/// 
/// ���ļ��������ⲿ���ݳ����࣬���������ӿں���������̳еĽӿ�
///
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef IEXTERNDATASTRTEGY_H_
#define IEXTERNDATASTRTEGY_H_

#include <dtCore/base.h>
#include "IHand.h"
#include <dtCore/scene.h>

#define MAKE_EDS_PROTOTYPE(NAME) \
	IExternDataStrategy* NAME ## _MyEDS = \
		IExternDataStrategy::addEDSPrototype(#NAME, new NAME());

#define IMPLEMENT_EDS_CLONE(NAME) \
	IExternDataStrategy* clone() const { return new NAME(*this); }

class IExternDataStrategy : public dtCore::Base
{
public:
	/// for reflection purpose
	IExternDataStrategy() : mName("DefaultName"), mHand(NULL), mScene(NULL) {}

	/// deep copy, also for reflection purpose
	IExternDataStrategy(const IExternDataStrategy& IEDS)
		: mName(IEDS.mName)
		, mHand(IEDS.mHand)
		, mScene(IEDS.mScene)
	{}
	/// for reflection purpose
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene)
	{
		mName = si.strategy;
		mHand = _hand;
		mScene = _scene;
		this->AddSender(mScene);
	}

	void Destroy()
	{
		delete this;
	}

	std::string getStrategyName() {return mName;}

	//���ⲿ���õĽӿڣ�����������λ����̬����
	virtual void UpdateHand()=0;

	static std::vector<std::string> EDSNameList;
	static std::vector<IExternDataStrategy*> EDSObjectList;
	static IExternDataStrategy* addEDSPrototype(std::string _name, IExternDataStrategy* ied);
	virtual IExternDataStrategy* clone() const = 0;
	static IExternDataStrategy* makeEDSProduct(std::string _name);

protected:
	virtual ~IExternDataStrategy() {this->RemoveSender(mScene);}

	std::string mName;
	IHand* mHand;
	dtCore::Scene* mScene;	
};

#endif // IEXTERNDATASTRTEGY_H_
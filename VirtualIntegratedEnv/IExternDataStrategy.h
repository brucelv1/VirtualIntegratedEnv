////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    IExternDataStrategy.h
/// @brief   外部数据策略抽象基类的头文件    
/// 
/// 本文件声明了外部数据抽象类，包括其对外接口和用于子类继承的接口
///
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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

	//供外部调用的接口，更新虚拟手位置姿态数据
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
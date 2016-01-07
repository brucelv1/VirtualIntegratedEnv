////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_MatlabYangFan.h
/// @brief   外部数据策略-Barrett手的Matlab控制算法数据类的头文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _EDS_MATLABYANGFAN_H_
#define _EDS_MATLABYANGFAN_H_

#include "iexterndatastrategy.h"
#include "JAGenerater.h"
#include <fstream>

class EDS_MatlabYangFan :
	public IExternDataStrategy
{
public:
	IMPLEMENT_EDS_CLONE(EDS_MatlabYangFan)
		EDS_MatlabYangFan(void);
	EDS_MatlabYangFan(const EDS_MatlabYangFan& copy);
	virtual bool initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~EDS_MatlabYangFan(void);

	virtual void UpdateHand();

	virtual void OnMessage(MessageData* data);

protected:
	std::vector<int> mFingerCollided;

	bool b_mLibLoaded;

	mwArray* mLAngle;
	mwArray* mRAngle;
	mwArray* mMAngle;
	mwArray* mIAngle;
	mwArray* mTAngle;
	mwArray* mSteps;

	std::ofstream mOutputFile;

private:
	void _outputInfoOnce(unsigned int fingerIndex, Part* knuckle, dtCore::Scene::CollisionData* cd, double steps);
};

#endif //_EDS_MATLABYANGFAN_H_


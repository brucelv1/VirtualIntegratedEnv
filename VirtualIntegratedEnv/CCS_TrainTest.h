////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_TrainTest.h
/// @brief   控制字符策略-模式分类训练和测试的头文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2016/11 
//////////////////////////////////////////////////////////////////////////

#ifndef _CCS_TRAIN_TEST_H_
#define _CCS_TRAIN_TEST_H_

////ode要求指定dSINGLE或dDOUBLE
//#ifndef dSINGLE
//#define dSINGLE
//#endif

#include "IControlCharStrategy.h"
#include <osg/Vec3>
#include <dtCore/scene.h>
#include <boost/interprocess/windows_shared_memory.hpp>
#include <boost/interprocess/mapped_region.hpp>

class CCS_TrainTest :
	public IControlCharStrategy
{
	
public:
	/// for prototype purpose
	IMPLEMENT_CCS_CLONE(CCS_TrainTest)

	CCS_TrainTest();
	CCS_TrainTest(const CCS_TrainTest& kbs);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~CCS_TrainTest(void);

	// 创建训练进程
	void createTrainProcess();

	//手指动作函数
	virtual void doGesture();
	void extendAllFingers();

	//手腕动作函数
	virtual void doWristAction();
	void recoverWrist();

	//手肘动作函数
	virtual void doElbowAction();

	virtual void setCommandBits(std::bitset<5> bits);
	virtual void setWristActionType(int _type);

	void updateCommand(int key);

	//碰撞响应
	virtual void OnMessage(MessageData* data);
	
private:
	bool b_mAllFingersRecoverd;
	bool b_mFingerActionFinished;
	bool b_mWristRecovered;
	bool b_mWristActionFinished;
	bool b_mNeedRecoverToLastFrameToAvoidCollisionDetect[5];

	// shared memory
	boost::interprocess::windows_shared_memory _winshm;
	boost::interprocess::mapped_region _region;
	unsigned char* _ucpSharedMem;
	size_t         _stLenSharedMem;
};

#endif // _CCS_TRAIN_TEST_H_
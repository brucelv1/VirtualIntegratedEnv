////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    CCS_TrainTest.h
/// @brief   �����ַ�����-ģʽ����ѵ���Ͳ��Ե�ͷ�ļ�    
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2016/11 
//////////////////////////////////////////////////////////////////////////

#ifndef _CCS_TRAIN_TEST_H_
#define _CCS_TRAIN_TEST_H_

////odeҪ��ָ��dSINGLE��dDOUBLE
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

	// ����ѵ������
	void createTrainProcess();

	//��ָ��������
	virtual void doGesture();
	void extendAllFingers();

	//����������
	virtual void doWristAction();
	void recoverWrist();

	//���⶯������
	virtual void doElbowAction();

	virtual void setCommandBits(std::bitset<5> bits);
	virtual void setWristActionType(int _type);

	void updateCommand(int key);

	//��ײ��Ӧ
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
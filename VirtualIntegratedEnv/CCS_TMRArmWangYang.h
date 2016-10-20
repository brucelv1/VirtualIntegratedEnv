////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_TMRArmWangYang.h
/// @brief   控制字符策略-TMR Arm控制策略类的头文件
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2016/10 
////////////////////////////////////////////////////////////////////////// 

#ifndef _CCS_TMRARMWANGYANG_H_
#define _CCS_TMRARMWANGYANG_H_

#include "IControlCharStrategy.h"
#include "SerialPort.h"

class CCS_TMRArmWangYang
	: public IControlCharStrategy
{
public:
	/// for prototype purpose
	IMPLEMENT_CCS_CLONE(CCS_TMRArmWangYang)
		CCS_TMRArmWangYang();
	CCS_TMRArmWangYang(const CCS_TMRArmWangYang& copy);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~CCS_TMRArmWangYang();

	//打开串口，接收分类器发来的控制字符
	void openPortForClassifier(unsigned int nCOM);

	//打开串口，向硬件设备发送控制字符
	void openPortForHardware(unsigned int nCOM);

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

	//碰撞响应
	virtual void OnMessage(MessageData* data);

private:
	void updateCommand();
	CSerialPort* mClassifierPort;
	CSerialPort* mHardwarePort;

	bool b_mAllFingersRecoverd;
	bool b_mFingerActionFinished;
	bool b_mWristRecovered;
	bool b_mWristActionFinished;
	bool b_mNeedRecoverToLastFrameToAvoidCollisionDetect[5];

	float f_mSpeedRatio;

};

#endif
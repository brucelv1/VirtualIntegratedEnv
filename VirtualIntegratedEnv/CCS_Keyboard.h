////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_Keyboard.h
/// @brief   控制字符策略-键盘策略类的头文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
//////////////////////////////////////////////////////////////////////////

#ifndef _CCS_KEYBOARD_H_
#define _CCS_KEYBOARD_H_

////ode要求指定dSINGLE或dDOUBLE
//#ifndef dSINGLE
//#define dSINGLE
//#endif

#include "IControlCharStrategy.h"
#include <osg/Vec3>
#include <dtCore/scene.h>

class CCS_Keyboard :
	public IControlCharStrategy
{
public:
	/// for prototype purpose
	IMPLEMENT_CCS_CLONE(CCS_Keyboard)
	CCS_Keyboard();
	CCS_Keyboard(const CCS_Keyboard& kbs);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~CCS_Keyboard(void);

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
};

#endif // _CCS_KEYBOARD_H_
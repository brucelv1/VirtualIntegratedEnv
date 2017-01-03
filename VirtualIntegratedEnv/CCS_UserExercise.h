////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_UserExercise.h
/// @brief   控制字符策略-用户练习的头文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2016/11 
//////////////////////////////////////////////////////////////////////////

#ifndef _CCS_USER_EXERCISE_H_
#define _CCS_USER_EXERCISE_H_

#include "IControlCharStrategy.h"
#include <osg/Vec3>
#include <dtCore/scene.h>
#include <boost/thread.hpp>

class CCS_UserExercise :
	public IControlCharStrategy
{
private:

	IHand* mHintHand;

	unsigned char num_decision;
	static const int NUM_DECISION_BYTE = 7;
	static const int DECISION_TYPE_BYTE = 8;
	static const int FINGER_RETURN_COMMAND_BYTE = 9;
	static const int HINT_HAND_MOVE_BYTE = 10;
	static const int HINT_HAND_MOVE_BYTE4 = 11;
	static const int HINT_HAND_MOVE_BYTE3 = 12;
	static const int HINT_HAND_MOVE_BYTE2 = 13;
	static const int HINT_HAND_MOVE_BYTE1 = 14;
	static const int HINT_HAND_RETURN_BYTE = 15;
	enum DECISION_TYPE { FINGER=1, WRIST };

	boost::thread hintColorThread;
public:
	/// for prototype purpose
	IMPLEMENT_CCS_CLONE(CCS_UserExercise)

	CCS_UserExercise();
	CCS_UserExercise(const CCS_UserExercise& kbs);
	virtual void initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene);

	virtual ~CCS_UserExercise(void);

	//手指动作函数
	virtual void doGesture();
	void extendAllFingers();
	void doOpenHand(char command); // called in doGesture()

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

	void moveFinger();
	
private:
	bool b_mAllFingersRecoverd;
	bool b_mFingerActionFinished;
	bool b_mWristRecovered;
	bool b_mWristActionFinished;
	bool b_mNeedRecoverToLastFrameToAvoidCollisionDetect[5];

	unsigned char* _ucpSharedMem;
	size_t         _stLenSharedMem;

	std::vector<unsigned char> cmdVec;
	std::vector<unsigned char> hintCmdVec;

private:
	void setHintHandFingers();
	void returnHintHandFingers();

	bool allowChildThread;
	enum HINT_COLOR_TYPE {UNSET=0, NORMAL, RIGHT};
	HINT_COLOR_TYPE hintHandColorType;
	static void hintColorThreadFunc(CCS_UserExercise* param);
	void setHintRightColor();
	void setHintNormalColor();
};

#endif // _CCS_USER_EXERCISE_H_
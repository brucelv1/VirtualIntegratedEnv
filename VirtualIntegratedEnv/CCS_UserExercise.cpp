////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_UserExercise.cpp
/// @brief   控制字符策略-用户练习的源文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2016/11 
//////////////////////////////////////////////////////////////////////////

#include "CCS_UserExercise.h"
#include <iostream>
#include "ColorVisitor.h"

CCS_UserExercise::CCS_UserExercise()
: IControlCharStrategy()
, b_mAllFingersRecoverd(false)
, b_mFingerActionFinished(false)
, b_mWristRecovered(false)
, b_mWristActionFinished(false)
, num_decision(0)
{
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
}

CCS_UserExercise::CCS_UserExercise(const CCS_UserExercise& kbs)
{
	// 设定动作执行的速度倍数
	IControlCharStrategy::mSpeedScale = 2.0;

	b_mAllFingersRecoverd = kbs.b_mAllFingersRecoverd;
	b_mFingerActionFinished = kbs.b_mFingerActionFinished;
	b_mWristRecovered = kbs.b_mWristRecovered;
	b_mWristActionFinished = kbs.b_mWristActionFinished;
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = \
		kbs.b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i];
}

CCS_UserExercise::~CCS_UserExercise(void)
{
}

void CCS_UserExercise::newDoGesture()
{
	// is there new decision?
	if (num_decision == _ucpSharedMem[NUM_DECISION_BYTE])
		return;

	if(_ucpSharedMem[DECISION_TYPE_BYTE] == FINGER)
		_ucpSharedMem[DECISION_TYPE_BYTE] = 0;
	else
		return;

	num_decision = _ucpSharedMem[NUM_DECISION_BYTE];

	unsigned char cmd = _ucpSharedMem[4];

	// musk default rest
	if (cmd == 0)
		return;

	// assign user-defined return-finger command
	if (cmd == _ucpSharedMem[FINGER_RETURN_COMMAND_BYTE])
	{
		cmd = 0;
		mCommandBits = std::bitset<5>(cmd);
	}
	else
	{
		cmd = 0X1F & _ucpSharedMem[4];
		mCommandBits = std::bitset<5>(cmd);
	}

	
	// move
	if (cmdVec.empty())
	{
		if(cmd!=0)
		{
			cmdVec.push_back(cmd);
			moveFinger();
		}
	}
	else
	{
		if(cmd==0 || cmd != *(cmdVec.rbegin()))
		{
			cmdVec.pop_back();
			doOpenHand(0);
			extendAllFingers();
		}
		else
		{
			cmdVec.push_back(cmd);
			moveFinger();
		}
	}
	std::cout<< cmdVec.size() << std::endl;
}

void CCS_UserExercise::moveFinger()
{
	//根据mCommandBits做动作
	for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
	{
		if(mCommandBits.at(i) == 1)
			flexFinger(mHand->getFingerFromVector(i));
	}

	//如果产生碰撞，该布尔变量在OnMessage中被赋值为真，使手指回退一帧，避免持续的碰撞检测
	for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
	{
		if (b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] == true)
		{
			extendFinger(mHand->getFingerFromVector(i));
			b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
		}
	}
}

void CCS_UserExercise::doGesture()
{
	newDoGesture();
}

void CCS_UserExercise::extendAllFingers()
{
	//根据手指数初始化一个容器，全部设置为false
	std::vector<bool> recoveredVec(mHand->FingersVector.size(), false);
	for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
	{
		recoveredVec[i] = extendFinger(mHand->getFingerFromVector(i));
	}

	//检查容器，有一个元素是false，说明还有手指没有回位，直接return
	for (unsigned int j=0; j<recoveredVec.size(); j++)
	{
		if(recoveredVec[j] == false)
			return;
	}
	//所有手指都回位，才能执行到这一步
	b_mAllFingersRecoverd = true;
}

void CCS_UserExercise::doOpenHand( char command )
{
	mHand->OpenHand(command==1);
}

void CCS_UserExercise::OnMessage(MessageData* data)
{
	if (data->message == "collision")
	{
		dtCore::Scene::CollisionData* cd = static_cast< dtCore::Scene::CollisionData* >( data->userData );
		
		bool isNotParentChild = (cd->mBodies[0]->GetParent()->GetParent() != cd->mBodies[1])
								&& (cd->mBodies[1]->GetParent()->GetParent() != cd->mBodies[0]);
		if(!isNotParentChild)
			return;
		
		for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
		{
			unsigned int tipID = mHand->getFingerFromVector(i)->numOfKnuckles()-1;
			Part* tipKnuckle = mHand->getFingerFromVector(i)->getKnuckleAt(tipID);
			if (cd->mBodies[0] == tipKnuckle->getModelPtr() || cd->mBodies[1] == tipKnuckle->getModelPtr())
			{
				b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = true;
				mCommandBits[i] = 0;
			}
		}
	}
}

void CCS_UserExercise::setCommandBits(std::bitset<5> bits)
{
	//要做新动作，所以相关标志置为false
	b_mAllFingersRecoverd = false;
	mCommandBits = bits;
}

void CCS_UserExercise::setWristActionType(int _type)
{
	mWristActionType = _type;
}

void CCS_UserExercise::doWristAction()
{
	// is there new decision?
	if (num_decision == _ucpSharedMem[NUM_DECISION_BYTE])
		return;

	if(_ucpSharedMem[DECISION_TYPE_BYTE] == WRIST)
		_ucpSharedMem[DECISION_TYPE_BYTE] = 0;
	else
		return;

	num_decision = _ucpSharedMem[NUM_DECISION_BYTE];

	// query shared memory
	// 256: shangqie, 512: xiaqie
	// 1024: neifan, 2048: waifan
	// 4096: neixuan, 8192: waixuan
	// the command should be divided by 256

	unsigned char cmd = 0XFF & _ucpSharedMem[3];
	switch (cmd)
	{
	case 0:
		setWristActionType(0);
		break;
	case 1:
		setWristActionType(6);
		break;
	case 2:
		setWristActionType(5);
		break;
	case 4:
		setWristActionType(3);
		break;
	case 8:
		setWristActionType(4);
		break;
	case 16:
		setWristActionType(2);
		break;
	case 32:
		setWristActionType(1);
		break;
	default:
		return;
	}

	//动作
	//外旋
	if(mWristActionType == 1)
	{
		Part* pt = mHand->mPostWrist;
		if(pt != NULL && pt->getAttitude().z() < 70)
		{
			pt->setAttitude(pt->getAttitude() + osg::Vec3(0,0,3.0));
			pt->makeTransform();
		}
	}
	//内旋
	if(mWristActionType == 2)
	{
		Part* pt = mHand->mPostWrist;
		if(pt != NULL && pt->getAttitude().z() > -70)
		{
			pt->setAttitude(pt->getAttitude() - osg::Vec3(0,0,3.0));
			pt->makeTransform();
		}
	}
	//内翻
	if(mWristActionType == 3)
	{
		Part* pt = mHand->mWrist;
		if(pt != NULL && pt->getAttitude().y() > -70)
		{
			pt->setAttitude(pt->getAttitude() - osg::Vec3(0,3.0,0));
			pt->makeTransform();
		}
	}
	//外翻
	if(mWristActionType == 4)
	{
		Part* pt = mHand->mWrist;
		if(pt != NULL && pt->getAttitude().y() < 70)
		{
			pt->setAttitude(pt->getAttitude() + osg::Vec3(0,3.0,0));
			pt->makeTransform();
		}
	}
	//下切
	if(mWristActionType == 5)
	{
		Part* pt = mHand->mWrist;
		if(pt != NULL && pt->getAttitude().x() > -70)
		{
			pt->setAttitude(pt->getAttitude() - osg::Vec3(3.0,0,0));
			pt->makeTransform();
		}
	}
	//上切
	if(mWristActionType == 6)
	{
		Part* pt = mHand->mWrist;
		if(pt != NULL && pt->getAttitude().x() < 70)
		{
			pt->setAttitude(pt->getAttitude() + osg::Vec3(3.0,0,0));
			pt->makeTransform();
		}
	}
}

void CCS_UserExercise::recoverWrist()
{
	bool postR = true;
	bool wP = true;
	bool wH = true;

	Part* pt1 = mHand->mPostWrist;
	Part* pt2 = mHand->mWrist;
	if(pt1 != NULL)
	{
		if (pt1->getAttitude().z() < 0)
			pt1->setAttitude(pt1->getAttitude() + osg::Vec3(0,0,3.0));
		if (pt1->getAttitude().z() > 0)
			pt1->setAttitude(pt1->getAttitude() - osg::Vec3(0,0,3.0));

		pt1->makeTransform();

		postR = (-1.5 <= pt1->getAttitude().z() && pt1->getAttitude().z() <= 1.5);
	}
	
	if(pt2 != NULL)
	{
		if (pt2->getAttitude().y() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(0,3.0,0));
		if (pt2->getAttitude().y() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(0,3.0,0));
		if (pt2->getAttitude().x() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(3.0,0,0));
		if (pt2->getAttitude().x() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(3.0,0,0));

		pt2->makeTransform();

		wP = (-1.5 <= pt2->getAttitude().y() && pt2->getAttitude().y() <= 1.5);
		wH = (-1.5 <= pt2->getAttitude().x() && pt2->getAttitude().x() <= 1.5);
	}

	if(postR && wP && wH)
		b_mWristRecovered = true;
}

void CCS_UserExercise::doElbowAction()
{
	// testing purpose
	return;


	// query shared memory
	// 16384: shenzhou, _ucpSharedMem[3]的第6位,2^6
	// 32768: quzhou, _ucpSharedMem[3]的第7位,2^7
	// the command should be divided by 256
	static unsigned char last_cmd = 0;
	unsigned char cmd = 0XFF & _ucpSharedMem[3];
	if(cmd != last_cmd)
	{
		switch (cmd)
		{
		case 0:
			setElbowActionType(0);
			break;
		case 64:
			setElbowActionType(1);
			break;
		case 128:
			setElbowActionType(0);
			break;
		default:
			return;
		}
		last_cmd = cmd;
	}

	static float Angle = 0;
	Part* ForeArm = mHand->mForeArm;
	Part* UpperArm = mHand->mArm;

	if (ForeArm == NULL || UpperArm == NULL)
	    return;

	// 屈肘，默认休息态
	if (mElbowActionType == 0 && Angle > 0)
	{
		Angle -= 2.0;
		UpperArm->setAttitude(osg::Vec3(Angle,0,0));
		ForeArm->setAttitude(osg::Vec3(-Angle,0,0));
	}

	// 伸肘
	if (mElbowActionType == 1 && Angle <= 50) // 前伸至50度位置
	{
		Angle += 2.0;
		UpperArm->setAttitude(osg::Vec3(Angle,0,0));
		ForeArm->setAttitude(osg::Vec3(-Angle,0,0));
	}

	UpperArm->makeTransform();
	ForeArm->makeTransform();
}

void CCS_UserExercise::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IControlCharStrategy::initStrategyConfig(si,_hand,_scene);
	this->_ucpSharedMem = si.nameSharedMem;
	this->_stLenSharedMem = si.lenSharedMem;

	ColorVisitor cv;
	cv.setRGBA(1,1,1,0.5);
	mHand->getHandRoot()->getModelPtr()->GetOSGNode()->accept(cv);
}

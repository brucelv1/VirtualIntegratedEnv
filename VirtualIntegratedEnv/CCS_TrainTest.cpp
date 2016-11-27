////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_TrainTest.cpp
/// @brief   控制字符策略-模式分类训练和测试的源文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2016/11 
//////////////////////////////////////////////////////////////////////////

#include "CCS_TrainTest.h"
#include <iostream>

/// for prototype purpose
//MAKE_CCS_PROTOTYPE(CCS_TrainTest)

CCS_TrainTest::CCS_TrainTest()
: IControlCharStrategy()
, b_mAllFingersRecoverd(false)
, b_mFingerActionFinished(false)
, b_mWristRecovered(false)
, b_mWristActionFinished(false)
{
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
}

CCS_TrainTest::CCS_TrainTest(const CCS_TrainTest& kbs)
{
	b_mAllFingersRecoverd = kbs.b_mAllFingersRecoverd;
	b_mFingerActionFinished = kbs.b_mFingerActionFinished;
	b_mWristRecovered = kbs.b_mWristRecovered;
	b_mWristActionFinished = kbs.b_mWristActionFinished;
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = \
		kbs.b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i];
}

CCS_TrainTest::~CCS_TrainTest(void)
{
}

void CCS_TrainTest::createTrainProcess()
{
	using namespace boost::interprocess;

	std::string NameSharedMem = "SharedMemoryTrainTest";

	// Create a native windows shared memory object.
	// 5 bytes to contain: 0: reference count, 1-4: command int, left->right == high->low
	_winshm = windows_shared_memory(create_only, NameSharedMem.c_str(), read_write, 5);

	// Map the whole shared memory in this process
	_region = mapped_region(_winshm, read_write);

	// Write all the memory to 0
	std::memset(_region.get_address(), 0, _region.get_size());

	// Bind to member variables
	_ucpSharedMem = static_cast<unsigned char*>(_region.get_address());
	_stLenSharedMem = _region.get_size();

	// add up reference count
	_ucpSharedMem[0]+=1;

	// Launch child process
	// "start" -- async
	std::string TrainProcess = "start E:\\My_Cpp_Code\\GitHubVersion\\TrainAndTestModule\\Debug\\TrainModule.exe";
	std::string cmd = TrainProcess+ " " + NameSharedMem;
	system(cmd.c_str());

	// windows_shared_memory is destroyed when the last attached process dies...
	// so there is no need to destroy the shared memory manually
}

void CCS_TrainTest::doGesture()
{
	// query shared memory
	static unsigned char last_cmd = 0;
	unsigned char cmd = 0X1F & _ucpSharedMem[4];
	if(cmd != last_cmd)
	{
		setCommandBits(std::bitset<5>(cmd));
		last_cmd = cmd;
	}

	if(b_mAllFingersRecoverd == false)
	{
		if(b_mFingerActionFinished == true)
			extendAllFingers();
		else
			b_mAllFingersRecoverd = true;
	}
	else
	{
		//如果mCommandBits == 00000，则说明动作结束
		if(mCommandBits == std::bitset<5>(0))
			b_mFingerActionFinished = true;

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
}

void CCS_TrainTest::extendAllFingers()
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

void CCS_TrainTest::OnMessage(MessageData* data)
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

void CCS_TrainTest::setCommandBits(std::bitset<5> bits)
{
	//要做新动作，所以相关标志置为false
	b_mAllFingersRecoverd = false;
	//IControlCharStrategy::setCommandBits(bits);
	mCommandBits = bits;
}

void CCS_TrainTest::setWristActionType(int _type)
{
	//要做新动作，所以相关标志置为false
	b_mWristRecovered = false;
	//IControlCharStrategy::setWristActionType(_type);
	mWristActionType = _type;
}

void CCS_TrainTest::doWristAction()
{
	// query shared memory
	// 256: shangqie, 512: xiaqie
	// 1024: neifan, 2048: waifan
	// 4096: neixuan, 8192: waixuan
	// the command should be divided by 256
	static unsigned char last_cmd = 0;
	unsigned char cmd = 0XFF & _ucpSharedMem[3];
	if(cmd != last_cmd)
	{
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
		last_cmd = cmd;
	}

	if(b_mWristRecovered == false)
	{
		if(b_mWristActionFinished == true)
			recoverWrist();
		else
			b_mWristRecovered = true;
	}
	else
	{
		//用于恢复手腕位置
		if(mWristActionType == 0)
			b_mWristActionFinished = true;
		
		//动作
		//外旋
		if(mWristActionType == 1)
		{
			Part* pt = mHand->mPostWrist;
			if(pt != NULL && pt->getAttitude().z() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(0,0,1.5));
				pt->makeTransform();
			}
		}
		//内旋
		if(mWristActionType == 2)
		{
			Part* pt = mHand->mPostWrist;
			if(pt != NULL && pt->getAttitude().z() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(0,0,1.5));
				pt->makeTransform();
			}
		}
		//内翻
		if(mWristActionType == 3)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(0,1.5,0));
				pt->makeTransform();
			}
		}
		//外翻
		if(mWristActionType == 4)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(0,1.5,0));
				pt->makeTransform();
			}
		}
		//下切
		if(mWristActionType == 5)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().x() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(1.5,0,0));
				pt->makeTransform();
			}
		}
		//上切
		if(mWristActionType == 6)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().x() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(1.5,0,0));
				pt->makeTransform();
			}
		}
	}
}

void CCS_TrainTest::recoverWrist()
{
	bool postR = true;
	bool wP = true;
	bool wH = true;

	Part* pt1 = mHand->mPostWrist;
	Part* pt2 = mHand->mWrist;
	if(pt1 != NULL)
	{
		if (pt1->getAttitude().z() < 0)
			pt1->setAttitude(pt1->getAttitude() + osg::Vec3(0,0,1.5));
		if (pt1->getAttitude().z() > 0)
			pt1->setAttitude(pt1->getAttitude() - osg::Vec3(0,0,1.5));

		pt1->makeTransform();

		postR = (-0.75 <= pt1->getAttitude().z() && pt1->getAttitude().z() <= 0.75);
	}
	
	if(pt2 != NULL)
	{
		if (pt2->getAttitude().y() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(0,1.5,0));
		if (pt2->getAttitude().y() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(0,1.5,0));
		if (pt2->getAttitude().x() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(1.5,0,0));
		if (pt2->getAttitude().x() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(1.5,0,0));

		pt2->makeTransform();

		wP = (-0.75 <= pt2->getAttitude().y() && pt2->getAttitude().y() <= 0.75);
		wH = (-0.75 <= pt2->getAttitude().x() && pt2->getAttitude().x() <= 0.75);
	}

	if(postR && wP && wH)
		b_mWristRecovered = true;
}

void CCS_TrainTest::doElbowAction()
{
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

//void CCS_TrainTest::updateCommand(int key)
//{
//	switch(key)
//	{
//	case '1':
//		setWristActionType(1);
//		break;
//	case '2':
//		setWristActionType(2);
//		break;
//	case '3':
//		setWristActionType(3);
//		break;
//	case '4':
//		setWristActionType(4);
//		break;
//	case '5':
//		setWristActionType(5);
//		break;
//	case '6':
//		setWristActionType(6);
//		break;
//	case '7':
//		setElbowActionType(1);
//		break;
//	case 'f':
//		setCommandBits(std::bitset<5>(0X1F));
//		break;
//
//	case 'g':
//		setCommandBits(std::bitset<5>(0X19));
//		break;
//
//	case 't':
//		setCommandBits(std::bitset<5>(0X03));
//		break;
//
//	case 'x':
//		setCommandBits(std::bitset<5>(0X0E));
//		break;
//
//	case 'u':
//		setCommandBits(std::bitset<5>(0X07));
//		break;
//
//	case 'i':
//		setCommandBits(std::bitset<5>(0X1D));
//		break;
//
//	case 'n':
//		setCommandBits(std::bitset<5>(0X1C));
//		break;
//
//	case 'r':
//		setCommandBits(std::bitset<5>(0X00));
//		setWristActionType(0);
//		setElbowActionType(0);
//		break;
//
//	default:
//		break;
//	}
//}

void CCS_TrainTest::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IControlCharStrategy::initStrategyConfig(si,_hand,_scene);
	createTrainProcess();
}

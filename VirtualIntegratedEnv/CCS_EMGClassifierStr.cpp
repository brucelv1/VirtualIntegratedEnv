////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    CCS_EMGClassifierStr.cpp
/// @brief   控制字符策略-肌电信号分类器策略类的源文件    
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
/// @date    2015/7 
////////////////////////////////////////////////////////////////////////// 

#include "CCS_EMGClassifierStr.h"

/// for prototype purpose
//MAKE_CCS_PROTOTYPE(CCS_EMGClassifierStr)

/* 全局变量：分类平台传来的命令
*  涉及的cpp：CCS_EMGClassifierStr.cpp
*            SerialPort.cpp
*/
extern unsigned char global_PatternCommand;

CCS_EMGClassifierStr::CCS_EMGClassifierStr()
: IControlCharStrategy()
, b_mAllFingersRecoverd(false)
, b_mFingerActionFinished(false)
, b_mWristRecovered(false)
, b_mWristActionFinished(false)
, mClassifierPort(NULL)
, mHardwarePort(NULL)
{
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
}

CCS_EMGClassifierStr::CCS_EMGClassifierStr(const CCS_EMGClassifierStr& copy)
{
	b_mAllFingersRecoverd = copy.b_mAllFingersRecoverd;
	b_mFingerActionFinished = copy.b_mFingerActionFinished;
	b_mWristRecovered = copy.b_mWristRecovered;
	b_mWristActionFinished = copy.b_mWristActionFinished;
	mClassifierPort = copy.mClassifierPort; //must be NULL
	mHardwarePort = copy.mHardwarePort; //must be NULL
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = \
		copy.b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i];
}

void CCS_EMGClassifierStr::initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene)
{
	IControlCharStrategy::initStrategyConfig(si,_hand,_scene);
	if (si.inputCOM != 0)
	{
		mClassifierPort = new CSerialPort();
		openPortForClassifier(si.inputCOM);
	}
	
	if (si.outputCOM != 0)
	{
		mHardwarePort = new CSerialPort();
		openPortForHardware(si.outputCOM);
	}	
}


CCS_EMGClassifierStr::~CCS_EMGClassifierStr()
{
	if (mClassifierPort != NULL)
	{
		delete mClassifierPort;
		mClassifierPort = NULL;
	}

	if (mHardwarePort != NULL)
	{
		delete mHardwarePort;
		mHardwarePort = NULL;
	}
}

void CCS_EMGClassifierStr::openPortForClassifier(unsigned int nCOM)
{
	if(mClassifierPort == NULL || nCOM == 0)
		return;

	if(mClassifierPort->InitPort(nCOM))
	{
		printf("Classifier: COM%d initialization successful !\n",nCOM);

		if(mClassifierPort->OpenListenThread())
			printf("Classifier: Open ListenThread successful !\n");
		else
			printf("Classifier: Open ListenThread failed !\n");
	}
	else
		printf("Classifier: COM%d initialization failed !\n",nCOM);
}

void CCS_EMGClassifierStr::openPortForHardware(unsigned int nCOM)
{
	if(mHardwarePort == NULL || nCOM == 0)
		return;

	if(mHardwarePort->InitPort(nCOM))
	{
		printf("Hardware: COM%d initialization successful !\n",nCOM);

		if(mHardwarePort->OpenListenThread())
			printf("Hardware: Open ListenThread successful !\n");
		else
			printf("Hardware: Open ListenThread failed !\n");
	}
	else
		printf("Hardware: COM%d initialization failed !\n",nCOM);
}


void CCS_EMGClassifierStr::doGesture()
{
	updateCommand();

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

void CCS_EMGClassifierStr::extendAllFingers()
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



void CCS_EMGClassifierStr::OnMessage(MessageData* data)
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

void CCS_EMGClassifierStr::setCommandBits(std::bitset<5> bits)
{
	//要做新动作，所以相关标志置为false
	b_mAllFingersRecoverd = false;
	//IControlCharStrategy::setCommandBits(bits);
	mCommandBits = bits;
}

void CCS_EMGClassifierStr::setWristActionType(int _type)
{
	//要做新动作，所以相关标志置为false
	b_mWristRecovered = false;
	//IControlCharStrategy::setWristActionType(_type);
	mWristActionType = _type;
}

void CCS_EMGClassifierStr::doWristAction()
{
	updateCommand();

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
		//下切
		if(mWristActionType == 3)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(0,1.5,0));
				pt->makeTransform();
			}
		}
		//上切
		if(mWristActionType == 4)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(0,1.5,0));
				pt->makeTransform();
			}
		}
		//外翻
		if(mWristActionType == 5)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().x() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(1.5,0,0));
				pt->makeTransform();
			}
		}
		//内翻
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

void CCS_EMGClassifierStr::recoverWrist()
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

void CCS_EMGClassifierStr::updateCommand()
{
	switch(global_PatternCommand)
	{
	case ' ':
		break;

	case 'P':
		setCommandBits(std::bitset<5>(0X1F)); // 握拳
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'Q':
		setCommandBits(std::bitset<5>(0X19)); // 胜利
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'R':
		setCommandBits(std::bitset<5>(0X03)); // OK
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'S':
		setCommandBits(std::bitset<5>(0X0E)); // 手势“六”
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'u':
		setCommandBits(std::bitset<5>(0X1C)); //枪姿
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'i':
		setCommandBits(std::bitset<5>(0X1D)); //食指向前
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'n':
		setCommandBits(std::bitset<5>(0X07)); //三指捏
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'r':
		setCommandBits(std::bitset<5>(0X00));
		setWristActionType(0);
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '5':
		setWristActionType(1); //外旋
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '1':
		setWristActionType(2); //内旋
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '3':
		setWristActionType(3); //内翻
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '4':
		setWristActionType(4); //外翻
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '2':
		setWristActionType(5); //下切
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '6':
		setWristActionType(6); //上切
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	default:
		break;
	}
}
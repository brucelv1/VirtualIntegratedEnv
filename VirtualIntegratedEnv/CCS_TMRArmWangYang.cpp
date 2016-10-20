////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    CCS_TMRArmWangYang.cpp
/// @brief   �����ַ�����-TMR Arm���Ʋ������Դ�ļ�
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2016/10 
////////////////////////////////////////////////////////////////////////// 

#include "CCS_TMRArmWangYang.h"

/* ȫ�ֱ���������ƽ̨����������
*  �漰��cpp��CCS_EMGClassifierStr.cpp
*            SerialPort.cpp
*/
extern unsigned char global_PatternCommand;

CCS_TMRArmWangYang::CCS_TMRArmWangYang()
	: IControlCharStrategy()
	, b_mAllFingersRecoverd(false)
	, b_mFingerActionFinished(false)
	, b_mWristRecovered(false)
	, b_mWristActionFinished(false)
	, mClassifierPort(NULL)
	, mHardwarePort(NULL)
	, f_mSpeedRatio(1.0)
{
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
}

CCS_TMRArmWangYang::CCS_TMRArmWangYang(const CCS_TMRArmWangYang& copy)
{
	b_mAllFingersRecoverd = copy.b_mAllFingersRecoverd;
	b_mFingerActionFinished = copy.b_mFingerActionFinished;
	b_mWristRecovered = copy.b_mWristRecovered;
	b_mWristActionFinished = copy.b_mWristActionFinished;
	mClassifierPort = copy.mClassifierPort; //must be NULL
	mHardwarePort = copy.mHardwarePort; //must be NULL
	f_mSpeedRatio = copy.f_mSpeedRatio;
	for (int i=0; i<5; i++)
		b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = \
		copy.b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i];
}

void CCS_TMRArmWangYang::initStrategyConfig(SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene)
{
	// ���ݽ���ѡ���ʼ�����봮��
	IControlCharStrategy::initStrategyConfig(si,_hand,_scene);
	if (si.inputCOM != 0)
	{
		mClassifierPort = new CSerialPort();
		openPortForClassifier(si.inputCOM);
	}

	// ���ݽ���ѡ���ʼ���������
	if (si.outputCOM != 0)
	{
		mHardwarePort = new CSerialPort();
		openPortForHardware(si.outputCOM);
	}	
}

CCS_TMRArmWangYang::~CCS_TMRArmWangYang()
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

void CCS_TMRArmWangYang::openPortForClassifier(unsigned int nCOM)
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

void CCS_TMRArmWangYang::openPortForHardware(unsigned int nCOM)
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

void CCS_TMRArmWangYang::doGesture()
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
		//���mCommandBits == 00000����˵����������
		if(mCommandBits == std::bitset<5>(0))
			b_mFingerActionFinished = true;

		//����mCommandBits������
		for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
		{
			if(mCommandBits.at(i) == 1)
				flexFinger(mHand->getFingerFromVector(i), f_mSpeedRatio);
		}

		//���������ײ���ò���������OnMessage�б���ֵΪ�棬ʹ��ָ����һ֡�������������ײ���
		for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
		{
			if (b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] == true)
			{
				extendFinger(mHand->getFingerFromVector(i), f_mSpeedRatio);
				b_mNeedRecoverToLastFrameToAvoidCollisionDetect[i] = false;
			}
		}
	}
}

void CCS_TMRArmWangYang::extendAllFingers()
{
	//������ָ����ʼ��һ��������ȫ������Ϊfalse
	std::vector<bool> recoveredVec(mHand->FingersVector.size(), false);
	for (unsigned int i=0; i<mHand->FingersVector.size(); i++)
	{
		recoveredVec[i] = extendFinger(mHand->getFingerFromVector(i), f_mSpeedRatio);
	}

	//�����������һ��Ԫ����false��˵��������ָû�л�λ��ֱ��return
	for (unsigned int j=0; j<recoveredVec.size(); j++)
	{
		if(recoveredVec[j] == false)
			return;
	}
	//������ָ����λ������ִ�е���һ��
	b_mAllFingersRecoverd = true;
}

void CCS_TMRArmWangYang::OnMessage(MessageData* data)
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

void CCS_TMRArmWangYang::setCommandBits(std::bitset<5> bits)
{
	//Ҫ���¶�����������ر�־��Ϊfalse
	b_mAllFingersRecoverd = false;
	//IControlCharStrategy::setCommandBits(bits);
	mCommandBits = bits;
}

void CCS_TMRArmWangYang::setWristActionType(int _type)
{
	//Ҫ���¶�����������ر�־��Ϊfalse
	b_mWristRecovered = false;
	//IControlCharStrategy::setWristActionType(_type);
	mWristActionType = _type;
}

void CCS_TMRArmWangYang::doWristAction()
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
		//���ڻָ�����λ��
		if(mWristActionType == 0)
			b_mWristActionFinished = true;

		//����
		//����
		if(mWristActionType == 1)
		{
			Part* pt = mHand->mPostWrist;
			if(pt != NULL && pt->getAttitude().z() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(0,0,1.5)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
		//����
		if(mWristActionType == 2)
		{
			Part* pt = mHand->mPostWrist;
			if(pt != NULL && pt->getAttitude().z() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(0,0,1.5)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
		//����
		if(mWristActionType == 3)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(0,1.5,0)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
		//����
		if(mWristActionType == 4)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().y() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(0,1.5,0)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
		//�ⷭ
		if(mWristActionType == 5)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().x() > -30)
			{
				pt->setAttitude(pt->getAttitude() - osg::Vec3(1.5,0,0)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
		//�ڷ�
		if(mWristActionType == 6)
		{
			Part* pt = mHand->mWrist;
			if(pt != NULL && pt->getAttitude().x() < 30)
			{
				pt->setAttitude(pt->getAttitude() + osg::Vec3(1.5,0,0)*f_mSpeedRatio);
				pt->makeTransform();
			}
		}
	}
}

void CCS_TMRArmWangYang::recoverWrist()
{
	bool postR = true;
	bool wP = true;
	bool wH = true;

	Part* pt1 = mHand->mPostWrist;
	Part* pt2 = mHand->mWrist;
	if(pt1 != NULL)
	{
		if (pt1->getAttitude().z() < 0)
			pt1->setAttitude(pt1->getAttitude() + osg::Vec3(0,0,1.5)*f_mSpeedRatio);
		if (pt1->getAttitude().z() > 0)
			pt1->setAttitude(pt1->getAttitude() - osg::Vec3(0,0,1.5)*f_mSpeedRatio);

		pt1->makeTransform();

		postR = (-0.75 <= pt1->getAttitude().z() && pt1->getAttitude().z() <= 0.75);
	}

	if(pt2 != NULL)
	{
		if (pt2->getAttitude().y() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(0,1.5,0)*f_mSpeedRatio);
		if (pt2->getAttitude().y() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(0,1.5,0)*f_mSpeedRatio);
		if (pt2->getAttitude().x() < 0)
			pt2->setAttitude(pt2->getAttitude() + osg::Vec3(1.5,0,0)*f_mSpeedRatio);
		if (pt2->getAttitude().x() > 0)
			pt2->setAttitude(pt2->getAttitude() - osg::Vec3(1.5,0,0)*f_mSpeedRatio);


		pt2->makeTransform();


		wP = (-0.75 <= pt2->getAttitude().y() && pt2->getAttitude().y() <= 0.75);
		wH = (-0.75 <= pt2->getAttitude().x() && pt2->getAttitude().x() <= 0.75);
	}

	if(postR && wP && wH)
		b_mWristRecovered = true;
}

void CCS_TMRArmWangYang::doElbowAction()
{
	static float Angle = 0;
	Part* ForeArm = mHand->mForeArm;
	Part* UpperArm = mHand->mArm;

	if (ForeArm == NULL || UpperArm == NULL)
		return;

	if (mElbowActionType == 0 && Angle > 0)
	{
		Angle -= 2.0*f_mSpeedRatio;
		UpperArm->setAttitude(osg::Vec3(Angle,0,0));
		ForeArm->setAttitude(osg::Vec3(-Angle,0,0));
	}

	if (mElbowActionType == 1 && Angle <= 50) // ǰ����50��λ��
	{
		Angle += 2.0*f_mSpeedRatio;
		UpperArm->setAttitude(osg::Vec3(Angle,0,0));
		ForeArm->setAttitude(osg::Vec3(-Angle,0,0));
	}

	UpperArm->makeTransform();
	ForeArm->makeTransform();
}

void CCS_TMRArmWangYang::updateCommand()
{
	/*
	* ������Ҫ����f_mSpeedRatio��global_PatternCommand��һ��char����Ҫ�޸�����Ľ�����ʽ
	*/
	switch(global_PatternCommand)
	{
	case ' ':
		break;

	case 'P':
		setCommandBits(std::bitset<5>(0X1F)); // ��ȭ
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'Q':
		setCommandBits(std::bitset<5>(0X19)); // ʤ��
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
		setCommandBits(std::bitset<5>(0X0E)); // ���ơ�����
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'u':
		setCommandBits(std::bitset<5>(0X1C)); //ǹ��
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'i':
		setCommandBits(std::bitset<5>(0X1D)); //ʳָ��ǰ
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case 'n':
		setCommandBits(std::bitset<5>(0X07)); //��ָ��
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
		setWristActionType(1); //����
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '1':
		setWristActionType(2); //����
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '3':
		setWristActionType(3); //�ڷ�
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '4':
		setWristActionType(4); //�ⷭ
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '2':
		setWristActionType(5); //����
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	case '6':
		setWristActionType(6); //����
		if(mHardwarePort != NULL)
			mHardwarePort->WriteData(&global_PatternCommand, 1);
		global_PatternCommand = ' ';
		break;
	default:
		break;
	}
}
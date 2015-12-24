////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_2x3PlaneFingers.h
/// @brief   �ⲿ���ݲ���-2��ָ��3ָ���ֵĿ����㷨�������Դ�ļ�   
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/12
//////////////////////////////////////////////////////////////////////////

#include "EDS_2x3PlaneFingers.h"
#include <QtGUI/QMessageBox>
#include <Windows.h>

EDS_2x3PlaneFingers::EDS_2x3PlaneFingers()
: IExternDataStrategy()
, mGraspingObj(NULL)
{
	
}

EDS_2x3PlaneFingers::EDS_2x3PlaneFingers( const EDS_2x3PlaneFingers& copy )
{
	mGraspingObj = copy.mGraspingObj;
}

EDS_2x3PlaneFingers::~EDS_2x3PlaneFingers()
{
	if(mOutPutFile.is_open())
		mOutPutFile.close();
}

bool EDS_2x3PlaneFingers::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IExternDataStrategy::initStrategyConfig(si,_hand,_scene);

	// �Ϸ��Լ��
	std::vector<int> FingerConfiguration;
	_hand->getFingerConfigInfo(FingerConfiguration);
	if(2 != FingerConfiguration.size())
	{
		QMessageBox::warning(NULL,"Warning","This is not a 2-finger hand!");
		return false;
	}
	if(3 != FingerConfiguration[0] || 3 != FingerConfiguration[1])
	{
		QMessageBox::warning(NULL,"Warning","Each finger has to be 3-knuckled!");
		return false;
	}

	mGraspingObj = _hand->getPartFromVector("GraspObj");
	if (mGraspingObj == NULL)
	{
		QMessageBox::warning(NULL,"Warning","No part named 'GraspObj' has been found!");
		return false;
	}
	mGraspingObj->addToScene(_scene);
	mObjPosX = -40;
	mObjPosY = 48;

	_makeDataZero();

	mOutPutFile.open("./Data/TwoFingers.txt",std::ios::out);

	return true;
}

void EDS_2x3PlaneFingers::UpdateHand()
{
	_updateData();

	for (unsigned int i=0; i<2; i++)
	{
		for (unsigned int j=0; j<3; j++)
		{
			mHand->getFingerFromVector(i)->getKnuckleAt(j)->setAttitude(osg::Vec3(mTheta[i][j],0,0));
			mHand->getFingerFromVector(i)->getKnuckleAt(j)->makeTransform();
		}
	}

	//�ȸ�����ָ �ٸ������� �����ڸ��¹����г�������
	/*mGraspingObj->setPosition(osg::Vec3(mObjPosX, mObjPosY, -10) * mHand->getHandScale());
	mGraspingObj->makeTransform();*/
}

void EDS_2x3PlaneFingers::OnMessage( MessageData* data )
{
	if (data->message == "collision")
	{
		dtCore::Scene::CollisionData* cd = static_cast< dtCore::Scene::CollisionData* >( data->userData );

		for(unsigned int i=0; i<2; i++)
		{
			for(unsigned int j=0; j<3; j++)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				if(pt == NULL)
					break;

				if(cd->mBodies[0] == pt->getModelPtr() || cd->mBodies[1] == pt->getModelPtr())
				{
					// ����kָ�ڷ�����ײ����k, k-1, ..., 0ָ�ھ���Ϊ������ײ
					int index = j;
					for(; index>-1; index--)
						mCollided[i][index] = 1;

					mContactPos[i][j] = cd->mLocation;
					mContactNormal[i][j] = cd->mNormal;
				}
			}
		}
	}
}

void EDS_2x3PlaneFingers::_updateData()
{
	if (_isStopped() == true)
	{
		Sleep(50);

		// writeData
		if(mOutPutFile.is_open())
		{
			char temp[200];
			sprintf_s(temp,"%f, %f\n",mObjPosX,mObjPosY);
			mOutPutFile << temp;
		}

		// re-position the object
		if (mObjPosX < 40 && mObjPosY < 88)
		{
			mObjPosX += 7;
			if (mObjPosX > 40)
			{
				mObjPosX = -40;
				mObjPosY += 7;
			}
			mGraspingObj->setPosition(osg::Vec3(mObjPosX, mObjPosY, -10) * mHand->getHandScale());
			mGraspingObj->makeTransform();
		}

		_makeDataZero();
		return;
	}

	// �ֽ��������ǵ�һ���������ʱ�����������ݵ��������
	//////////////////////////////////////////////////////////////////////////
	// �ֽ���������������й����У����������ݵ�һ����²���

	for (int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (mCollided[i][j]==0 && mReachLimit[i][j]==0)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				double CurrentPos = pt->getAttitude().x();

				// ��ǰ��λ�ô���90�㣬����Ϊ���Ｋ��λ��
				if(fabs(CurrentPos) >= 90)
					mReachLimit[i][j] = 1;
				// ���򣬸��½�λ��
				else
					mTheta[i][j] += pt->getDeltaAttitudePerFrame().x();	

				break; // ���ڿ���ָ���˶����Ⱥ����ڵ�����£�ǰһ��ָ��ֹͣ�˶��󣬺�һ���ŻῪʼ�˶�
			}
		}
	}
}

void EDS_2x3PlaneFingers::_makeDataZero()
{
	for(int i=0; i<2; i++)
	{
		for(int j=0; j<3; j++)
		{
			mTheta[i][j] = 0;
			mCollided[i][j] = 0;
			mReachLimit[i][j] = 0;
			mContactPos[i][j] = osg::Vec3(0,0,0);
			mContactNormal[i][j] = osg::Vec3(0,0,0);
		}
	}
}

bool EDS_2x3PlaneFingers::_isStopped()
{
	// �üӷ����桰�򡱲���
	for(int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (mCollided[i][j] + mReachLimit[i][j] == 0)
				return false;
		}
	}
	return true;
}

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
#include <dtCore/odebodywrap.h>

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
	if(mOutputFile.is_open())
		mOutputFile.close();
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
	//mObjPosX = -40;
	//mObjPosY = 48;
	mObjPosX = mGraspingObj->getPosition().x();
	mObjPosY = mGraspingObj->getPosition().y();
	//mGraspingObj->getModelPtr()->EnableDynamics();

	_makeDataZero();

	mOutputFile.open("./Data/TwoFingers.txt",std::ios::out);

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
					// ��֤���з�����Ҫô����ָ���������ģ�Ҫô���Ǳ�����������
					if(cd->mBodies[0] == pt->getModelPtr())
					    mContactNormal[i][j] = cd->mNormal * (-1.0);
					else
						mContactNormal[i][j] = cd->mNormal * 1.0;
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
		if(mOutputFile.is_open())
		{
			double abs_ObjPosX = mObjPosX+mGraspingObj->getOriginPosition().x();
			double abs_ObjPosY = mObjPosY+mGraspingObj->getOriginPosition().y();
            mOutputFile << abs_ObjPosX << ", " << abs_ObjPosY << ", ";
            int i,j;
            for(i=0; i<2; i++)
                for(j=0; j<3; j++)
                    mOutputFile << mTheta[i][j] << ", ";
                    
            for(i=0; i<2; i++)
                for(j=0; j<3; j++) 
                {
                    mOutputFile << mContactPos[i][j].x() << ", ";
                    mOutputFile << mContactPos[i][j].y() << ", ";
					mOutputFile << mContactPos[i][j].z() << ", ";
                }
            
            for(i=0; i<2; i++)
                for(j=0; j<3; j++) 
                {
                    mOutputFile << mContactNormal[i][j].x() << ", ";
                    mOutputFile << mContactNormal[i][j].y() << ", ";
					mOutputFile << mContactNormal[i][j].z() << ", ";
                }
            
            // use '0' as tail of this record
            mOutputFile << 0 << '\n';
		}

		// re-position the object
		if (mObjPosX <= 80 && mObjPosY <= 40)
		{
			mObjPosX += 20;
			if (mObjPosX > 80)
			{
				mObjPosX = 0;
				mObjPosY += 20;
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

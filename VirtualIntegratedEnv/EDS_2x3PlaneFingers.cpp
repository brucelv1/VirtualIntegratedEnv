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

EDS_2x3PlaneFingers::EDS_2x3PlaneFingers()
: IExternDataStrategy()
{
	
}

EDS_2x3PlaneFingers::EDS_2x3PlaneFingers( const EDS_2x3PlaneFingers& copy )
{

}

EDS_2x3PlaneFingers::~EDS_2x3PlaneFingers()
{

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

	_makeDataZero();
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
					// ����kָ�ڷ�����ײ����k-1, k-2, ..., 0ָ�ھ���Ϊ������ײ
					int index = j;
					for(; index>-1; index--)
						mCollided[i][index] = 1;
				}
			}
		}
	}
}

void EDS_2x3PlaneFingers::_updateData()
{
	for (int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (mCollided[i][j]==0 && mReachLimit[i][j]==0)
			{
				mTheta[i][j] += 0.2;
				if(mTheta[i][j] >= 60)
					mReachLimit[i][j] = 1;
				break; // ���ڿ���ָ���˶����Ⱥ����ڵ�����£�ǰһ��ָ��ֹͣ�˶��󣬺�һ���ŻῪʼ�˶�
			}
		}
	}
}

void EDS_2x3PlaneFingers::_makeDataZero()
{
	for(int i=0; i<2; i++)
		for(int j=0; j<3; j++)
			mTheta[i][j] = 0;

	for(int i=0; i<2; i++)
		for(int j=0; j<3; j++)
			mCollided[i][j] = 0;

	for(int i=0; i<2; i++)
		for(int j=0; j<3; j++)
			mReachLimit[i][j] = 0;
}

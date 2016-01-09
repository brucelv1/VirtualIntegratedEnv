////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, �Ϻ���ͨ��ѧ-������ʵ����. All rights reserved.  
///   
/// @file    EDS_GraspRegionAnalysis.h
/// @brief   �ⲿ���ݲ���-2��ָ��3ָ���ֵĿ����㷨�������Դ�ļ�   
///  
/// @version 1.0     
/// @author  ����   
/// @E-mail��lvwei.sjtu@foxmail.com  
/// @date    2015/12
//////////////////////////////////////////////////////////////////////////

#include "EDS_GraspRegionAnalysis.h"
#include <QtGUI/QMessageBox>
#include <Windows.h>
#include <dtCore/odebodywrap.h>
#include "Dlg2x3Parameter.h"

EDS_GraspRegionAnalysis::EDS_GraspRegionAnalysis()
: IExternDataStrategy()
, mGraspingObj(NULL)
{
	
}

EDS_GraspRegionAnalysis::EDS_GraspRegionAnalysis( const EDS_GraspRegionAnalysis& copy )
{
	mGraspingObj = copy.mGraspingObj;
}

EDS_GraspRegionAnalysis::~EDS_GraspRegionAnalysis()
{
	if(mOutputFile.is_open())
		mOutputFile.close();
}

bool EDS_GraspRegionAnalysis::initStrategyConfig( SettingsInfoStruct& si, IHand* _hand, dtCore::Scene* _scene )
{
	IExternDataStrategy::initStrategyConfig(si,_hand,_scene);

	// �Ϸ��Լ��
	_hand->getFingerConfigInfo(mFingerConfigInfo);

	//if(2 != mFingerConfigInfo.size())
	//{
	//	QMessageBox::warning(NULL,"Warning","This is not a 2-finger hand!");
	//	return false;
	//}
	//if(3 != mFingerConfigInfo[0] || 3 != mFingerConfigInfo[1])
	//{
	//	QMessageBox::warning(NULL,"Warning","Each finger has to be 3-knuckled!");
	//	return false;
	//}

	mGraspingObj = _hand->getPartFromVector("GraspObj");
	if (mGraspingObj == NULL)
	{
		QMessageBox::warning(NULL,"Warning","No part named 'GraspObj' has been found!");
		return false;
	}
	//mGraspingObj->addToScene(_scene);
	_hand->getHandRoot()->addChild(mGraspingObj);
	mObjPos = mGraspingObj->getPosition();

	//mGraspingObj->getModelPtr()->EnableDynamics();

	int nFinger = mFingerConfigInfo.size();
	mDataTable.resize(nFinger);
	mStateTable.resize(nFinger);

	for (int i=0; i<nFinger; i++)
	{
		for (unsigned int j=0; j<mFingerConfigInfo[i]; j++)
		{
			DataCollector* dc = new DataCollector();
			dc->Reset();
			mDataTable[i].push_back(dc);

			StateCollector* sc = new StateCollector();
			sc->Reset();
			mStateTable[i].push_back(sc);
		}
	}

	// �����Ե�λ��
	_fillTestPointList(80,40,40,40,0,0);

	mOutputFile.open("./Data/TwoFingers.txt",std::ios::out);

	return true;
}

void EDS_GraspRegionAnalysis::UpdateHand()
{
	_updateData();

	for (unsigned int i=0; i<mFingerConfigInfo.size(); i++)
	{
		for (unsigned int j=0; j<mFingerConfigInfo[i]; j++)
		{
			mHand->getFingerFromVector(i)->getKnuckleAt(j)->setAttitude(mDataTable[i][j]->Angle);
			mHand->getFingerFromVector(i)->getKnuckleAt(j)->makeTransform();
		}
	}
}

void EDS_GraspRegionAnalysis::OnMessage( MessageData* data )
{
	if (data->message == "collision")
	{
		dtCore::Scene::CollisionData* cd = static_cast< dtCore::Scene::CollisionData* >( data->userData );

		for(unsigned int i=0; i<mFingerConfigInfo.size(); i++)
		{
			for(unsigned int j=0; j<mFingerConfigInfo[i]; j++)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				if(pt == NULL)
					break;

				if(cd->mBodies[0] == pt->getModelPtr() || cd->mBodies[1] == pt->getModelPtr())
				{
					// ����kָ�ڷ�����ײ����k, k-1, ..., 0ָ�ھ���Ϊ������ײ
					int index = j;
					for(; index>-1; index--)
						mStateTable[i][index]->IsCollided = true;

					mDataTable[i][j]->ContactPos = cd->mLocation;

					// ��֤���з�����Ҫô����ָ���������ģ�Ҫô���Ǳ�����������
					if(cd->mBodies[0] == pt->getModelPtr())
					    mDataTable[i][j]->ContactNorm = cd->mNormal * (-1.0);
					else
						mDataTable[i][j]->ContactNorm = cd->mNormal * 1.0;
				}
			}
		}
	}
}

void EDS_GraspRegionAnalysis::_updateData()
{
	if (_isStopped() == true)
	{
		Sleep(50);

		// writeData
		if(mOutputFile.is_open())
		{
			osg::Vec3 absObjPos = mObjPos + mGraspingObj->getOriginPosition();
            mOutputFile << absObjPos.x() << ", " << absObjPos.y() << ", " << absObjPos.z() << ", ";
            
			unsigned int i,j;
            for(i=0; i<mDataTable.size(); i++)
                for(j=0; j<mDataTable[i].size(); j++)
				{
                    mOutputFile << mDataTable[i][j]->Angle.x() << ", ";
					mOutputFile << mDataTable[i][j]->Angle.y() << ", ";
					mOutputFile << mDataTable[i][j]->Angle.z() << ", ";
				}
                    
			for(i=0; i<mDataTable.size(); i++)
				for(j=0; j<mDataTable[i].size(); j++)
                {
					mOutputFile << mDataTable[i][j]->ContactPos.x() << ", ";
					mOutputFile << mDataTable[i][j]->ContactPos.y() << ", ";
					mOutputFile << mDataTable[i][j]->ContactPos.z() << ", ";
                }
            
            for(i=0; i<mDataTable.size(); i++)
                for(j=0; j<mDataTable[i].size(); j++)
                {
					mOutputFile << mDataTable[i][j]->ContactNorm.x() << ", ";
					mOutputFile << mDataTable[i][j]->ContactNorm.y() << ", ";
					mOutputFile << mDataTable[i][j]->ContactNorm.z() << ", ";
                }
            
            // use '0' as tail of this record
            mOutputFile << 0 << '\n';
		}

		// re-position the object
		if(mTestPointList.empty() == false)
		{
			mObjPos = mTestPointList.front();
			mTestPointList.pop();
			mGraspingObj->setPosition(mObjPos * mHand->getHandScale());
			mGraspingObj->makeTransform();
		}

		_makeDataZero();

		return;
	}

	// �ֽ��������ǵ�һ���������ʱ�����������ݵ��������
	//////////////////////////////////////////////////////////////////////////
	// �ֽ���������������й����У����������ݵ�һ����²���

	for (unsigned int i=0; i<mFingerConfigInfo.size(); i++)
	{
		for (unsigned int j=0; j<mFingerConfigInfo[i]; j++)
		{
			if (mStateTable[i][j]->IsCollided==false && mStateTable[i][j]->IsLimited==false)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				// ���ڲ��˶��Ĺ̶�ָ�ڣ�����⵽��һ��ʵʱ������Ϊ���Ѿ����Ｋ��λ��
				if (pt->getDeltaAttitudePerFrame().length() == 0)
					mStateTable[i][j]->IsLimited = true;

				// ��Ϊ�ؽ�ֻ�漰һ�����ɶȵ�ת������˿����ó���������ǰת���ĽǶ�
				double CurrentPos = pt->getAttitude().length();

				// ��ǰ��λ�ô���90�㣬����Ϊ���Ｋ��λ��
				if(CurrentPos >= 90)
					mStateTable[i][j]->IsLimited = true;
				// ���򣬸��½�λ��
				else
					mDataTable[i][j]->Angle += pt->getDeltaAttitudePerFrame();

				break; // ���ڿ���ָ���˶����Ⱥ����ڵ�����£�ǰһ��ָ��ֹͣ�˶��󣬺�һ���ŻῪʼ�˶�
			}
		}
	}
}

void EDS_GraspRegionAnalysis::_makeDataZero()
{
	for (unsigned int i=0; i<mFingerConfigInfo.size(); i++)
	{
		for (unsigned int j=0; j<mFingerConfigInfo[i]; j++)
		{
			mDataTable[i][j]->Reset();
			mStateTable[i][j]->Reset();
		}
	}
}

bool EDS_GraspRegionAnalysis::_isStopped()
{
	for(unsigned int i=0; i<mStateTable.size(); i++)
	{
		for(unsigned int j=0; j<mStateTable[i].size(); j++)
		{
			// ֻҪ��һ��ָ���ڶ����ͷ���false
			bool thisKnuckleStopped = mStateTable[i][j]->IsCollided || mStateTable[i][j]->IsLimited;
			if( ! thisKnuckleStopped)
				return false;
		}
	}
	return true;
}

void EDS_GraspRegionAnalysis::_fillTestPointList( double xDomain, double xInc, double yDomain, double yInc, double zDomain, double zInc )
{
	unsigned int x_size, y_size, z_size;
	if(xInc == 0)
		x_size = 1;
	else
		x_size = (unsigned int)(xDomain / xInc) + 1;

	if(yInc == 0)
		y_size = 1;
	else
		y_size = (unsigned int)(yDomain / yInc) + 1;

	if(zInc == 0)
		z_size = 1;
	else
		z_size = (unsigned int)(zDomain / zInc) + 1;

	for(unsigned int i=0; i<z_size; i++)
		for(unsigned int j=0; j<y_size; j++)
			for(unsigned int k=0; k<x_size; k++)
			{
				osg::Vec3 p;
				p.set(k*xInc, j*yInc, i*zInc);
				mTestPointList.push(p);
			}
}

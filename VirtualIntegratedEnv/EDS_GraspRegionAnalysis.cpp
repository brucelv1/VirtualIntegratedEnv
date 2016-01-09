////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_GraspRegionAnalysis.h
/// @brief   外部数据策略-2手指、3指节手的控制算法数据类的源文件   
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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

	// 合法性检查
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

	// 填充测试点位置
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
					// 若第k指节发生碰撞，则k, k-1, ..., 0指节均视为发生碰撞
					int index = j;
					for(; index>-1; index--)
						mStateTable[i][index]->IsCollided = true;

					mDataTable[i][j]->ContactPos = cd->mLocation;

					// 保证所有法向量要么都是指向物体中心，要么都是背离物体中心
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

	// 分界线以上是当一次试验完成时，对所有数据的清零操作
	//////////////////////////////////////////////////////////////////////////
	// 分界线以下是试验进行过程中，对所有数据的一般更新操作

	for (unsigned int i=0; i<mFingerConfigInfo.size(); i++)
	{
		for (unsigned int j=0; j<mFingerConfigInfo[i]; j++)
		{
			if (mStateTable[i][j]->IsCollided==false && mStateTable[i][j]->IsLimited==false)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				// 对于不运动的固定指节，当检测到这一事实时，就认为其已经到达极限位置
				if (pt->getDeltaAttitudePerFrame().length() == 0)
					mStateTable[i][j]->IsLimited = true;

				// 因为关节只涉及一个自由度的转动，因此可以用长度来代表当前转过的角度
				double CurrentPos = pt->getAttitude().length();

				// 当前角位置大于90°，则认为到达极限位置
				if(CurrentPos >= 90)
					mStateTable[i][j]->IsLimited = true;
				// 否则，更新角位置
				else
					mDataTable[i][j]->Angle += pt->getDeltaAttitudePerFrame();

				break; // 用于控制指节运动的先后，现在的情况下，前一个指节停止运动后，后一个才会开始运动
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
			// 只要有一个指节在动，就返回false
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

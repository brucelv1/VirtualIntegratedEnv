////////////////////////////////////////////////////////////////////////// 
/// Copyright (c) 2015, 上海交通大学-生机电实验室. All rights reserved.  
///   
/// @file    EDS_2x3PlaneFingers.h
/// @brief   外部数据策略-2手指、3指节手的控制算法数据类的源文件   
///  
/// @version 1.0     
/// @author  吕威   
/// @E-mail：lvwei.sjtu@foxmail.com  
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

	// 合法性检查
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

	//先更新手指 再更新物体 避免在更新过程中出现问题
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
					// 若第k指节发生碰撞，则k, k-1, ..., 0指节均视为发生碰撞
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

	// 分界线以上是当一次试验完成时，对所有数据的清零操作
	//////////////////////////////////////////////////////////////////////////
	// 分界线以下是试验进行过程中，对所有数据的一般更新操作

	for (int i=0; i<2; i++)
	{
		for (int j=0; j<3; j++)
		{
			if (mCollided[i][j]==0 && mReachLimit[i][j]==0)
			{
				Part* pt = mHand->getFingerFromVector(i)->getKnuckleAt(j);
				double CurrentPos = pt->getAttitude().x();

				// 当前角位置大于90°，则认为到达极限位置
				if(fabs(CurrentPos) >= 90)
					mReachLimit[i][j] = 1;
				// 否则，更新角位置
				else
					mTheta[i][j] += pt->getDeltaAttitudePerFrame().x();	

				break; // 用于控制指节运动的先后，现在的情况下，前一个指节停止运动后，后一个才会开始运动
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
	// 用加法代替“或”操作
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
